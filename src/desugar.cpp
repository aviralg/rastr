#include <rastr/api.h>
#include "r_api.h"
#include "interop.h"
#include "internal_api.h"
#include <stack>
#include <vector>
#include <string>
#include "utilities.h"
#include "logger.h"

class StrictnessDesugarer: public AstWalker {
  private:
    typedef std::vector<rastr_node_t> force_seq_t;

  public:
    StrictnessDesugarer(): AstWalker() {
    }

    bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        force_calls_.push({});
        return true;
    }

    void post_fndefn(rastr_ast_t ast, rastr_node_t fndefn) override {
        force_seq_t& force_calls = force_calls_.top();

        if (force_calls.size() != 0) {
            insert_force_calls_(ast, fndefn, force_calls);
        }

        force_calls_.pop();
    }

    void post_pars(rastr_ast_t ast, rastr_node_t pars) override {
        int len = rastr_pars_len_get(ast, pars);

        for (int i = 0; i < len; ++i) {
            rastr_node_t dlmtd = rastr_pars_get(ast, pars, i);

            bool is_dlmtd = rastr_node_type(ast, dlmtd) == RASTR_DLMTD;

            rastr_node_t aexpr =
                is_dlmtd ? rastr_dlmtd_expr_get(ast, dlmtd) : dlmtd;

            if (rastr_node_type(ast, aexpr) != RASTR_AEXPR)
                continue;

            rastr_node_t ann = rastr_aexpr_ann_get(ast, aexpr);

            if (!is_strict_annotation_(ast, ann)) {
                continue;
            }

            rastr_node_t par = rastr_aexpr_expr_get(ast, aexpr);

            push_force_call_(ast, par, rastr_sym_gap_get(ast, ann));

            /* remove 'strict' annotation from the parameter list */
            if (is_dlmtd) {
                rastr_dlmtd_expr_set(ast, dlmtd, par);
            }
            /* functions with a single parameter are not delimited */
            else {
                rastr_pars_set(ast, pars, i, par);
            }
        }
    }

    // void post_aexpr(rastr_ast_t ast, rastr_node_t node) {
    //     rastr_node_t expr = rastr_aexpr_expr_get(ast, node);
    //     rastr_node_type_t type = rastr_node_type(ast, expr);
    //     rastr_node_t par_name;
    //
    //     switch (type) {
    //     case RASTR_NDPAR:
    //         par_name = rastr_ndpar_name_get(ast, expr);
    //         break;
    //
    //     case RASTR_DPAR:
    //         par_name = rastr_dpar_name_get(ast, expr);
    //         break;
    //
    //     default:
    //         return;
    //     }
    //     std::cout << "par_name" << par_name.index << "\n";
    //
    //     rastr_node_t ann = rastr_aexpr_ann_get(ast, node);
    //
    //     if (!is_strict_annotation_(ast, ann)) {
    //         return;
    //     }
    //
    //     strict_pars_.top().push_back(
    //         par_name); //#rastr_node_clone(ast, par_name));
    // }

  private:
    std::stack<force_seq_t> force_calls_;

    const char* get_sym_name_(rastr_ast_t ast, rastr_node_t node) {
        return (rastr_node_type(ast, node) == RASTR_SYM)
                   ? rastr_sym_syn_get(ast, node)
                   : nullptr;
    }

    bool is_strict_annotation_(rastr_ast_t ast, rastr_node_t ann) {
        return (rastr_node_type(ast, ann) == RASTR_SYM) &&
               !strcmp(rastr_sym_val_get(ast, ann), "strict");
    }

    void push_force_call_(rastr_ast_t ast, rastr_node_t par, rastr_node_t gap) {
        rastr_node_t par_name;
        rastr_node_type_t type = rastr_node_type(ast, par);

        switch (type) {
        case RASTR_NDPAR:
            par_name = rastr_ndpar_name_get(ast, par);
            break;

        case RASTR_DPAR:
            par_name = rastr_dpar_name_get(ast, par);
            break;

        default:
            fail_with("incorrect node type; expected a dpar or ndpar, got %s",
                      rastr_node_type_to_string(type));
            return;
        }

        rastr_sym_gap_set(ast, par_name, gap);

        rastr_node_t force_call =
            make_force_call_(ast, rastr_node_clone(ast, par_name));

        force_calls_.top().push_back(force_call);
    }

    void insert_force_calls_(rastr_ast_t ast,
                             rastr_node_t fndefn,
                             force_seq_t& force_calls) {
        rastr_node_t body = rastr_fndefn_body_get(ast, fndefn);

        if (rastr_node_type(ast, body) == RASTR_BLK) {
            rastr_node_t exprs = rastr_blk_exprs_get(ast, body);

            if (rastr_exprs_len_get(ast, exprs) > 0) {
                rastr_node_t expr = rastr_exprs_get(ast, exprs, 0);

                update_gap_(ast, rastr_node_leftmost(ast, expr));
            }

            rastr_exprs_ins(
                ast, exprs, 0, force_calls.size(), force_calls.data());
        }
        // if body is an expression, put it in a block;
        else {
            update_gap_(ast, rastr_node_leftmost(ast, body));

            force_calls.push_back(body);

            rastr_node_t exprs =
                rastr_exprs_new(ast, force_calls.size(), force_calls.data());

            rastr_node_t lbkt = rastr_bkt_new_unsafe(
                ast,
                RASTR_BKT_LT_CURL,
                rastr_gap_new(ast, " ", make_empty_loc_(ast)),
                make_empty_loc_(ast));

            rastr_node_t rbkt = rastr_bkt_new_unsafe(
                ast,
                RASTR_BKT_RT_CURL,
                rastr_gap_new(ast, "\n", make_empty_loc_(ast)),
                make_empty_loc_(ast));

            rastr_node_t new_body = rastr_blk_new(ast, lbkt, exprs, rbkt);

            rastr_fndefn_body_rep(ast, fndefn, new_body);
        }
    }

    rastr_node_t make_force_call_(rastr_ast_t ast, rastr_node_t par_name) {
        rastr_node_t fn =
            rastr_sym_new(ast,
                          "force",
                          0,
                          rastr_gap_new(ast, "\n    ", make_empty_loc_(ast)),
                          make_empty_loc_(ast));

        rastr_node_t lbkt = make_empty_bkt_(ast, RASTR_BKT_LT_RND);

        rastr_node_t rbkt = make_empty_bkt_(ast, RASTR_BKT_RT_RND);

        rastr_sym_gap_set(ast, par_name, make_empty_gap_(ast));

        rastr_node_t args = rastr_args_new(ast, 1, &par_name);

        rastr_node_t call = rastr_fncall_new(ast, fn, lbkt, args, rbkt);

        return call;
    }

    void update_gap_(rastr_ast_t ast, rastr_node_t node) {
        rastr_node_t gap = rastr_node_gap_get(ast, node);

        std::string str(rastr_gap_val_get(ast, gap));
        bool has_nl = (str.size() > 0) && (str[0] == '\n');

        if (has_nl) {
            return;
        }

        str.insert(0, 1, '\n');

        rastr_node_t new_gap =
            rastr_gap_new(ast, str.c_str(), make_empty_gap_(ast));

        rastr_node_gap_set(ast, node, new_gap);
    }

    rastr_node_t make_empty_bkt_(rastr_ast_t ast, rastr_node_type_t type) {
        return rastr_bkt_new_unsafe(
            ast, type, make_empty_gap_(ast), make_empty_loc_(ast));
    }

    rastr_node_t make_empty_gap_(rastr_ast_t ast) {
        return rastr_gap_new(ast, "", make_empty_loc_(ast));
    }

    rastr_node_t make_empty_loc_(rastr_ast_t ast) {
        return rastr_loc_new(ast, 0, 0, 0, 0, 0, 0, 0, 0);
    }
};


void rastr_desugar(rastr_ast_t ast, rastr_node_t node, int strictness) {
    if (strictness) {
        StrictnessDesugarer* desugarer = new StrictnessDesugarer();
        desugarer->walk(ast, node);
        delete desugarer;
    }
}

SEXP r_rastr_desugar(SEXP r_ast, SEXP r_node, SEXP r_strictness) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int strictness = (int) num_get(r_strictness, 0);
    rastr_desugar(ast, node, strictness);
    return R_NilValue;
}
