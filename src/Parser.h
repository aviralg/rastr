#ifndef RASTR_PARSER_H
#define RASTR_PARSER_H

#include <rastr/api.h>
#include "Lexer.h"
#include "Input.h"
#include "utilities.h"
#include "interop.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "internal_api.h"

const int LOWEST_PRECEDENCE = 0;
const int INVALID_PRECEDENCE = -1;

/* TODO: remove this. */
void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root);

#define PROPAGATE_ERROR(node)            \
    if (node_type_(node) == RASTR_ERR) { \
        res = node;                      \
        goto end;                        \
    }

#define PROPAGATE_ERROR_IF_NOT(node, type, msg) \
    if (node_type_(node) != type) {             \
        res = pcont_error(msg);                 \
        goto end;                               \
    }

#define PROPAGATE_ERROR_IF(node, type, msg) \
    if (node_type_(node) == type) {         \
        res = pcont_error(msg);             \
        goto end;                           \
    }

#define RETURN_IF_UNDEFINED(node)        \
    if (rastr_node_is_undefined(node)) { \
        return node;                     \
    }

class Parser {
  public:
    Parser(Input& input, rastr_ast_t& ast)
        : ast_(ast), lexer_(input, ast_), saved_tok_(), pcont_() {
    }

    int node_type_(rastr_node_t node) {
        return rastr_node_is_newline(node) ? RASTR_NL
                                           : rastr_node_type(ast_, node);
    }

    rastr_node_t parse_prog() {
        rastr_node_t res;
        rastr_node_t end;
        rastr_node_t exprs;

        pcont_push("<pgm> ▸ <stmt>* <expr>? <eof>");

        std::vector<rastr_node_t> stmts;

        rastr_node_t beg = next_token_();
        PROPAGATE_ERROR_IF_NOT(beg, RASTR_BEG, "expected '<beg>'")

        while (true) {
            rastr_node_t node = peek_token_();

            /* if <eof> is encountered, program has been parsed */
            if (node_type_(node) == RASTR_END) {
                consume_();
                end = node;
                break;
            }

            /* this case happens if there are comments or spaces at the
               beginning of the file. since we have not yet read a stmt (which
               would have eaten up subsequent newlines), we have to eat and
               destroy this newlines until we encounter a non-newline token */
            else if (node_type_(node) == RASTR_NL) {
                consume_();
                continue;
            }

            else {
                rastr_node_t stmt = parse_stmt(RASTR_END);
                PROPAGATE_ERROR(stmt);

                stmts.push_back(stmt);
            }
        }

        exprs = rastr_exprs_new(ast_, stmts.size(), stmts.data());
        res = rastr_pgm_new(ast_, beg, exprs, end);

    end:
        pcont_pop();
        return res;
    }

    /* parse complete expression followed by an actual dlmtr (\n or ;) or
     * a contextual dlmtr such as } or ) */
    rastr_node_t parse_stmt(rastr_node_type_t cont_dlmtr_type) {
        rastr_node_t res;
        rastr_node_t dlmtr;
        rastr_node_t expr;
        int dlmtr_type;

        pcont_push("<stmt> ▸ <expr> ; | <expr> \\n | <expr> <eof>");

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        dlmtr = peek_token_();
        dlmtr_type = node_type_(dlmtr);

        if (dlmtr_type == cont_dlmtr_type || dlmtr_type == RASTR_END) {
            res = expr;
        }

        else if (dlmtr_type == RASTR_DLMTR_SCOL || dlmtr_type == RASTR_NL) {
            do {
                consume_();
                /* attach delimiter if ; or , */
                if (dlmtr_type == RASTR_DLMTR_SCOL) {
                    expr = rastr_dlmtd_new(ast_, expr, dlmtr);
                }

                dlmtr = peek_token_();
                dlmtr_type = node_type_(dlmtr);

            } while (dlmtr_type == RASTR_DLMTR_SCOL || dlmtr_type == RASTR_NL);

            res = expr;
        }

        else {
            /* TODO: add token type/value */
            res = pcont_error("expected ';' or '\n'");
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_expr(int precedence) {
        pcont_push("<expr>");

        rastr_node_t res = parse_prefix_expr();
        PROPAGATE_ERROR(res);

        while (true) {
            rastr_node_t node = peek_token_();
            int cur_type = node_type_(node);

            /* terminator is encountered, return; */
            if (cur_type == RASTR_NL || cur_type == RASTR_DLMTR_COM ||
                cur_type == RASTR_DLMTR_SCOL || cur_type == RASTR_END) {
                break;
            }

            ///* if parse_expr is called from parse_block or parse_group, the
            //   expression will be delimited by right paren or right brace. */
            // else if (cur_type == RASTR_END || cur_type == RASTR_BKT_RT_RND ||
            // cur_type == RASTR_BKT_RT_CURL) {
            //    break;
            //}

            int cur_precedence = get_precedence(cur_type, false);

            if (cur_precedence <= precedence) {
                break;
            }

            res = parse_infix_expr(cur_precedence, res);
            PROPAGATE_ERROR(res);

            /* check if it is a terminator node */
            // new_left = parse_terminator_expr(left, node);
            //
            // if (new_left != UNDEFINED_NODE) {
            //     left = new_left;
            //     break;
            // }
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_prefix_expr() {
        rastr_node_t res;

        rastr_node_t op = next_token_();
        int type = node_type_(op);

        /* null, logical, real, integer, complex, string, and symbol don't need
         * extra parsing for completion*/
        if (rastr_lit_type(ast_, op)) {
            res = op;
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_BKT_LT_RND) {
            res = parse_grp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_BKT_LT_CURL) {
            res = parse_blk(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_REPEAT) {
            res = parse_rlp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_WHILE) {
            res = parse_wlp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_FOR) {
            res = parse_flp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_IF) {
            res = parse_iecnd(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_FN || type == RASTR_OP_FN2) {
            res = parse_fndefn(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_OP_NEXT || type == RASTR_OP_BREAK) {
            res = parse_nuop(op);
            PROPAGATE_ERROR(res);
        }

        else {
            int precedence = get_precedence(type, true);

            rastr_node_t expr = parse_expr(precedence);
            PROPAGATE_ERROR(expr);

            res = rastr_unop_new(ast_, op, expr);
        }

    end:
        return res;
    }

    rastr_node_t parse_infix_expr(int precedence, rastr_node_t left) {
        rastr_node_t res;

        rastr_node_t op = next_token_();
        int type = node_type_(op);

        if (type == RASTR_BKT_LT_RND) {
            res = parse_fncall(left, op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_BKT_LT_SQR) {
            res = parse_sub(left, op);
            PROPAGATE_ERROR(res);
        }

        else if (type == RASTR_BKT_LT_DBL_SQR) {
            res = parse_idx(left, op);
            PROPAGATE_ERROR(res);
        }

        else {
            /* to correctly parse right-associative operators, reduce precedence
             * by 1 */
            if (type == RASTR_OP_POW || type == RASTR_OP_POW2 ||
                type == RASTR_OP_LT_ASGN || type == RASTR_OP_LT_SUP_ASGN ||
                type == RASTR_OP_EQ_ASGN) {
                precedence = precedence - 1;
            }

            rastr_node_t right = parse_expr(precedence);
            PROPAGATE_ERROR(right);

            res = rastr_binop_new(ast_, left, op, right);
        }

    end:
        return res;
    }

    rastr_node_t parse_grp(rastr_node_t left_paren) {
        rastr_node_t res;
        rastr_node_t expr;
        rastr_node_t right_paren;

        pcont_push("<grp>  ▸ ( <expr> )");

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        right_paren = next_token_();
        PROPAGATE_ERROR_IF_NOT(right_paren, RASTR_BKT_RT_RND, "expected ')'")

        res = rastr_grp_new(ast_, left_paren, expr, right_paren);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_blk(rastr_node_t lbkt) {
        rastr_node_t res;
        rastr_node_t rbkt;
        rastr_node_t stmt;
        rastr_node_t exprs;

        pcont_push("<blk> ▸ { <stmt>* <expr>? }");

        std::vector<rastr_node_t> exprs_vec;

        while (true) {
            rastr_node_t node = peek_token_();
            int type = node_type_(node);

            if (type == RASTR_BKT_RT_CURL) {
                consume_();
                rbkt = node;
                break;
            }

            // TODO: consume_();
            PROPAGATE_ERROR_IF(node, RASTR_END, "unexpected <eof>");

            stmt = parse_stmt(RASTR_BKT_RT_CURL);
            PROPAGATE_ERROR(stmt);

            exprs_vec.push_back(stmt);
        }

        lexer_.disable_eat_lines();

        exprs = rastr_exprs_new(ast_, exprs_vec.size(), exprs_vec.data());
        res = rastr_blk_new(ast_, lbkt, exprs, rbkt);

    end:
        pcont_pop();
        return res;
    }

    /* repeat <expr> */
    rastr_node_t parse_rlp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t body;

        pcont_push("<rlp> ▸ repeat <expr>");

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_rlp_new(ast_, kw, body);

    end:
        pcont_pop();
        return res;
    }

    /* while <cond> <expr> */
    rastr_node_t parse_wlp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t cond;
        rastr_node_t body;

        pcont_push("<wlp> ▸ while <cond> <expr>");

        cond = parse_cond();
        PROPAGATE_ERROR(cond);

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_wlp_new(ast_, kw, cond, body);

    end:
        pcont_pop();
        return res;
    }

    /* for <iter> <expr> */
    rastr_node_t parse_flp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t iter;
        rastr_node_t body;

        pcont_push("<flp> ▸ for <iter> <expr>");

        iter = parse_iter();
        PROPAGATE_ERROR(iter);

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_flp_new(ast_, kw, iter, body);

    end:
        pcont_pop();
        return res;
    }

    /* <icnd> | <iecnd> : if <cond> <expr> [else <expr>] */
    rastr_node_t parse_iecnd(rastr_node_t iop) {
        rastr_node_t res;
        rastr_node_t cond;
        rastr_node_t ibody;
        rastr_node_t eop;
        rastr_node_t ebody;

        pcont_push("<icnd> | <iecnd> ▸ if <cond> <expr> [else <expr>]");

        cond = parse_cond();
        PROPAGATE_ERROR(cond);

        ibody = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(ibody);

        eop = peek_token_();

        /* there is no else following the if */
        if (node_type_(eop) != RASTR_OP_ELSE) {
            res = rastr_icond_new(ast_, iop, cond, ibody);
        }
        /* else follows if */
        else {
            consume_();

            ebody = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(ebody);

            res = rastr_iecond_new(ast_, iop, cond, ibody, eop, ebody);
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_fndefn(rastr_node_t op) {
        rastr_node_t res;
        rastr_node_t lbkt;
        rastr_node_t pars;
        rastr_node_t rbkt;
        rastr_node_t body;

        pcont_push("<fndefn> ▸ function <params> <expr>");

        lbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbkt, RASTR_BKT_LT_RND, "expected '('")

        pars = parse_pars();
        PROPAGATE_ERROR(pars);

        rbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt, RASTR_BKT_RT_RND, "expected ')'")

        lexer_.enable_eat_lines();

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_fndefn_new(ast_, op, lbkt, pars, rbkt, body);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_nuop(rastr_node_t op) {
        rastr_node_t res;

        pcont_push("<nuop> ▸ <op>");

        res = rastr_nuop_new(ast_, op);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_fncall(rastr_node_t fn, rastr_node_t lbkt) {
        rastr_node_t res;
        rastr_node_t args;
        rastr_node_t rbkt;

        pcont_push("<fncall> ▸ <fun> <args>");

        args = parse_args();
        PROPAGATE_ERROR(args);

        rbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt, RASTR_BKT_RT_RND, "expected ')'")

        res = rastr_fncall_new(ast_, fn, lbkt, args, rbkt);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_sub(rastr_node_t obj, rastr_node_t lbkt) {
        rastr_node_t res;
        rastr_node_t args;
        rastr_node_t rbkt;

        pcont_push("<sub> ▸ <obj> <inds>");

        args = parse_args();
        PROPAGATE_ERROR(args);

        rbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt, RASTR_BKT_RT_SQR, "expected ']'")

        res = rastr_sub_new(ast_, obj, lbkt, args, rbkt);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_idx(rastr_node_t obj, rastr_node_t lbkt) {
        rastr_node_t res;
        rastr_node_t args;
        rastr_node_t rbkt1;
        rastr_node_t rbkt2;

        pcont_push("<idx> ▸ <obj> <inds>");

        args = parse_args();
        PROPAGATE_ERROR(args);

        rbkt1 = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt1, RASTR_BKT_RT_SQR, "expected ']]'")

        rbkt2 = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt2, RASTR_BKT_RT_SQR, "expected ']]'")

        res = rastr_idx_new(ast_, obj, lbkt, args, rbkt1, rbkt2);

    end:
        pcont_pop();
        return res;
    }

    /* <cond>: ( <expr> ) */
    rastr_node_t parse_cond() {
        rastr_node_t res;
        rastr_node_t lbkt;
        rastr_node_t expr;
        rastr_node_t rbkt;

        pcont_push("<cond> ▸ ( <expr> )");

        lbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbkt, RASTR_BKT_LT_RND, "expected '('")

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr)

        rbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt, RASTR_BKT_RT_RND, "expected ')'")

        lexer_.enable_eat_lines();
        res = rastr_cond_new(ast_, lbkt, expr, rbkt);

    end:
        pcont_pop();
        return res;
    }

    /* <iter>: (<var> in <expr>) */
    rastr_node_t parse_iter() {
        rastr_node_t res;
        rastr_node_t lbkt;
        rastr_node_t var;
        rastr_node_t kw;
        rastr_node_t expr;
        rastr_node_t rbkt;

        pcont_push("<iter> ▸ (<var> in <expr>)");

        lbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbkt, RASTR_BKT_LT_RND, "expected '('")

        var = next_token_();
        PROPAGATE_ERROR_IF_NOT(var, RASTR_SYM, "expected symbol")

        kw = next_token_();
        PROPAGATE_ERROR_IF_NOT(kw, RASTR_OP_IN, "expected 'in'")

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        rbkt = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbkt, RASTR_BKT_RT_RND, "expected ')'")

        lexer_.enable_eat_lines();

        res = rastr_iter_new(ast_, lbkt, var, kw, expr, rbkt);

    end:
        pcont_pop();
        return res;
    }

    /* <params> : (  | (<param>,)* <param> ) */
    rastr_node_t parse_pars() {
        rastr_node_t res;
        rastr_node_t node;
        rastr_node_t par;
        std::vector<rastr_node_t> pars;

        pcont_push("<params> :  | (<param>,)* <param> ");

        while (true) {
            node = peek_token_();
            int type = node_type_(node);

            if (type == RASTR_BKT_RT_RND) {
                break;
            }

            PROPAGATE_ERROR_IF(node, RASTR_END, "unexpected <eof>")

            par = parse_par();
            PROPAGATE_ERROR(par);

            node = peek_token_();
            if (node_type_(node) == RASTR_DLMTR_COM) {
                consume_();
                par = rastr_dlmtd_new(ast_, par, node);
            }

            pars.push_back(par);
        }

        res = rastr_pars_new(ast_, pars.size(), pars.data());

    end:
        pcont_pop();
        return res;
    }

    /* <param> : <symbol> | <symbol> = <expr> */
    rastr_node_t parse_par() {
        rastr_node_t res;
        rastr_node_t name;
        rastr_node_t op;
        rastr_node_t expr;

        pcont_push("<param> : <symbol> | <symbol> = <expr>");

        name = next_token_();
        PROPAGATE_ERROR_IF_NOT(name, RASTR_SYM, "expected <symbol>")

        op = peek_token_();

        /* <param> is of the form <symbol> = <expr> */
        if (node_type_(op) == RASTR_OP_EQ_ASGN) {
            consume_();

            expr = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(expr)

            res = rastr_dpar_new(ast_, name, op, expr);
        }

        /* <param> is of the form <symbol> */
        else {
            res = rastr_ndpar_new(ast_, name);
        }

    end:
        pcont_pop();
        return res;
    }

    /* <args> : (  | (<arg>,)* <arg> ) */
    rastr_node_t parse_args() {
        rastr_node_t res;
        rastr_node_t node;
        rastr_node_t arg;
        std::vector<rastr_node_t> args;

        pcont_push("<args> : (  | (<arg>,)* <arg> )");

        while (true) {
            node = peek_token_();
            int type = node_type_(node);

            if (type == RASTR_BKT_RT_RND || type == RASTR_BKT_RT_SQR) {
                break;
            }

            PROPAGATE_ERROR_IF(node, RASTR_END, "unexpected <eof>")

            arg = parse_arg();
            PROPAGATE_ERROR(arg)

            node = peek_token_();
            if (node_type_(node) == RASTR_DLMTR_COM) {
                consume_();
                lexer_.enable_eat_lines();
                arg = rastr_dlmtd_new(ast_, arg, node);
            }

            args.push_back(arg);
        }

        res = rastr_args_new(ast_, args.size(), args.data());

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_arg() {
        rastr_node_t res;
        rastr_node_t name;
        rastr_node_t op;
        rastr_node_t mexpr;

        pcont_push("<arg> : <mexpr> | <symbol> = <mexpr> | <str> = <mexpr> | "
                   "<null> = <mexpr>");

        name = peek_token_();
        int name_type = node_type_(name);

        /* <arg> is of the form <mexpr> */
        if (name_type != RASTR_SYM && name_type != RASTR_CHR &&
            name_type != RASTR_NULL) {
            rastr_node_t mexpr = parse_mexpr();
            PROPAGATE_ERROR(mexpr)

            res = rastr_parg_new(ast_, mexpr);
        }

        /* <arg> may have any of the following forms:
           <symbol> = <mexpr>
           <str> = <mexpr>
           <null> = <mexpr> */
        else {
            consume_();
            op = peek_token_();

            /* <arg> is <mexpr> */
            if (node_type_(op) != RASTR_OP_EQ_ASGN) {
                push_token_(name);

                mexpr = parse_mexpr();
                PROPAGATE_ERROR(mexpr)

                res = rastr_parg_new(ast_, mexpr);
            }

            /* <arg> has one of the following forms:
               <symbol> = <mexpr>
               <str> = <mexpr>
               <null> = <mexpr> */
            else {
                consume_();

                mexpr = parse_mexpr();
                PROPAGATE_ERROR(mexpr)

                res = rastr_narg_new(ast_, name, op, mexpr);
            }
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_mexpr() {
        rastr_node_t res;
        rastr_node_t node;

        pcont_push("<mexpr> : <msng> | <expr>");

        node = peek_token_();
        int type = node_type_(node);

        if (type == RASTR_DLMTR_COM || type == RASTR_BKT_RT_RND ||
            type == RASTR_BKT_RT_SQR) {
            /* TODO: fix position */
            res = rastr_msng_new(
                ast_,
                rastr_gap_new_unsafe(ast_, nullptr, empty_loc_()),
                empty_loc_());
        }

        else {
            res = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(res);
        }

    end:
        pcont_pop();
        return res;
    }

    /* TODO: delete */
    rastr_node_t empty_loc_() {
        return rastr_loc_new(ast_, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    void pcont_push(const char* prod) {
        pcont_.push_back(prod);
    }

    void pcont_pop() {
        pcont_.pop_back();
    }

    rastr_node_t pcont_error(const char* msg) {
        std::ostringstream sstr;

        sstr << "\nparsing error: " << msg << std::endl;

        for (int i = pcont_.size() - 1; i >= 1; --i) {
            sstr << "               ├╴ " << pcont_[i] << std::endl;
        }

        sstr << "               └╴ " << pcont_[0];

        std::string str = sstr.str();

        return rastr_err_new(ast_, str.c_str(), empty_loc_());
    }

  private:
    rastr_ast_t ast_;
    Lexer lexer_;
    std::vector<rastr_node_t> saved_tok_;
    std::vector<const char*> pcont_;
    // %left    '?'
    // %left    LOW WHILE FOR REPEAT
    // %right   IF
    // %left    ELSE
    // %right   LEFT_ASSIGN
    // %right   EQ_ASSIGN
    // %left    RIGHT_ASSIGN
    // %left    '~' TILDE
    // %left    OR OR2
    // %left    AND AND2
    // %left    UNOT NOT
    // %nonassoc  GT GE LT LE EQ NE
    // %left		'+' '-'
    // %left    '*' '/'
    // %left    SPECIAL PIPE
    // %left    PIPEBIND
    // %left    ':'
    // %left    UMINUS UPLUS
    // %right   '^'
    // %left    '$' '@'// %left    NS_GET NS_GET_INT
    // %nonassoc '(' '[' LBB
    int get_precedence(int type, bool prefix) {
        if (prefix) {
            switch (type) {
            case RASTR_OP_HELP:
                return 1;
            case RASTR_OP_FORMULA:
                return 8;
            case RASTR_OP_NOT:
                return 11;
            case RASTR_OP_MINUS:
            case RASTR_OP_PLUS:
                return 18;
            default:
                return LOWEST_PRECEDENCE;
            }
        }

        else {
            switch (type) {
            case RASTR_OP_HELP:
                return 1;
            // case While:
            // case For:
            // case Repeat:
            //     return 2;
            // case If:
            //     return 3;
            // case Else:
            //     return 4;
            case RASTR_OP_EQ_ASGN:
                return 5;
            case RASTR_OP_LT_ASGN:
            case RASTR_OP_LT_SUP_ASGN:
            case RASTR_OP_COLON_ASGN:
                return 6;
            case RASTR_OP_RT_ASGN:
            case RASTR_OP_RT_SUP_ASGN:
                return 7;
            case RASTR_OP_FORMULA:
                return 8;
            case RASTR_OP_OR:
            case RASTR_OP_VEC_OR:
                return 9;
            case RASTR_OP_AND:
            case RASTR_OP_VEC_AND:
                return 10;
            case RASTR_OP_NOT:
                return 11;
            case RASTR_OP_LESS:
            case RASTR_OP_LESS_EQ:
            case RASTR_OP_GREAT:
            case RASTR_OP_GREAT_EQ:
            case RASTR_OP_EQ:
            case RASTR_OP_NOT_EQ:
                return 12;
            case RASTR_OP_PLUS:
            case RASTR_OP_MINUS:
                return 13;
            case RASTR_OP_MUL:
            case RASTR_OP_DIV:
                return 14;
            case RASTR_OP_SP:
            case RASTR_OP_PIPE_FWD:
                return 15;
            case RASTR_OP_PIPE_BIND:
                return 16;
            case RASTR_OP_RANGE:
                return 17;
            case RASTR_OP_POW:
            case RASTR_OP_POW2:
                return 19;
            case RASTR_OP_PART:
            case RASTR_OP_SLOT:
                return 20;
            case RASTR_OP_PUB_NS:
            case RASTR_OP_PVT_NS:
                return 21;
            case RASTR_BKT_LT_RND:
            case RASTR_BKT_LT_SQR:
            case RASTR_BKT_LT_DBL_SQR:
                return 22;
            default:
                return LOWEST_PRECEDENCE;
            }
        }
    }

    rastr_node_t peek_token_() {
        if (saved_tok_.empty()) {
            saved_tok_.push_back(lexer_.next_token());
        }
        return saved_tok_.back();
    }

    rastr_node_t next_token_() {
        if (!saved_tok_.empty()) {
            rastr_node_t tok = saved_tok_.back();
            saved_tok_.pop_back();
            return tok;
        }

        return lexer_.next_token();
    }

    void consume_() {
        saved_tok_.pop_back();
    }

    void push_token_(rastr_node_t node) {
        saved_tok_.push_back(node);
    }
};

#endif /* RASTR_PARSER_H */
