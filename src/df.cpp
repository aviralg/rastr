#include <rastr/api.h>
#include "interop.h"
#include <vector>
#include "r_api.h"
#include <string>
#include "internal_api.h"

const Rcomplex NA_COMPLEX{NA_REAL, NA_REAL};

#define PRE(KIND)                              \
    int id = rastr_node_id(ast, node);         \
    df_->set_id(id);                           \
                                               \
    df_->set_parent_id(parent_ids_.back());    \
    parent_ids_.push_back(id);                 \
                                               \
    df_->set_type(rastr_node_type(ast, node)); \
                                               \
    df_->set_field(fields_.back());            \
    fields_.push_back(0);

#define POST(KIND)      \
    fields_.pop_back(); \
    ++fields_.back();   \
    parent_ids_.pop_back();

class AstDf {
  public:
    AstDf(int size): index_(-1) {
        r_id_ = PROTECT(int_vec(size, NA_INTEGER));
        r_parent_id_ = PROTECT(int_vec(size, NA_INTEGER));
        r_type_ = PROTECT(str_vec(size, nullptr));
        r_field_ = PROTECT(int_vec(size, NA_INTEGER));
        r_syntax_ = PROTECT(str_vec(size, nullptr));
        r_val_str_ = PROTECT(str_vec(size, nullptr));
        r_val_lgl_ = PROTECT(lgl_vec(size, NA_LOGICAL));
        r_val_int_ = PROTECT(int_vec(size, NA_INTEGER));
        r_val_dbl_ = PROTECT(dbl_vec(size, NA_REAL));
        r_val_cplx_ = PROTECT(cplx_vec(size, NA_COMPLEX));
    }

    ~AstDf() {
        UNPROTECT(10);
    }

    SEXP materialize() {
        return rastr_create_data_frame(10,
                                       "id",
                                       r_id_,
                                       "parent_id",
                                       r_parent_id_,
                                       "field",
                                       r_field_,
                                       "type",
                                       r_type_,
                                       "syntax",
                                       r_syntax_,
                                       "val_str",
                                       r_val_str_,
                                       "val_lgl",
                                       r_val_lgl_,
                                       "val_int",
                                       r_val_int_,
                                       "val_dbl",
                                       r_val_dbl_,
                                       "val_cplx",
                                       r_val_cplx_);
    }

    void inc_index() {
        ++index_;
    }

    void set_id(int id) {
        int_set(r_id_, index_, id);
    }

    void set_parent_id(int parent_id) {
        int_set(r_parent_id_, index_, parent_id);
    }

    void set_type(rastr_node_type_t type) {
        str_set(r_type_, index_, rastr_node_type_to_string(type));
    }

    void set_field(int field) {
        int_set(r_field_, index_, field);
    }

    void set_syn(const char* value) {
        str_set(r_syntax_, index_, value);
    }

    void set_str(const char* value) {
        str_set(r_val_str_, index_, value);
    }

    void set_lgl(int value) {
        lgl_set(r_val_lgl_, index_, value);
    }

    void set_int(int value) {
        int_set(r_val_int_, index_, value);
    }

    void set_dbl(double value) {
        dbl_set(r_val_dbl_, index_, value);
    }

    void set_cplx(const Rcomplex& value) {
        cplx_set(r_val_cplx_, index_, value);
    }

  private:
    int index_;
    SEXP r_id_;
    SEXP r_parent_id_;
    SEXP r_type_;
    SEXP r_field_;
    SEXP r_syntax_;
    SEXP r_val_str_;
    SEXP r_val_lgl_;
    SEXP r_val_int_;
    SEXP r_val_dbl_;
    SEXP r_val_cplx_;
};

class DFTransformer: AstWalker {
  public:
    DFTransformer(): AstWalker(), df_(nullptr) {
        parent_ids_.push_back(NA_INTEGER);
        fields_.push_back(0);
    }

    SEXP transform(AstDf* df, rastr_ast_t ast, rastr_node_t node) {
        df_ = df;

        walk(ast, node);

        return df->materialize();
    }

    virtual void walk(rastr_ast_t ast, rastr_node_t node) {
        df_->inc_index();
        AstWalker::walk(ast, node);
    }

    virtual bool pre_op(rastr_ast_t ast, rastr_node_t node) {
        PRE(op)

        df_->set_syn(rastr_node_operator_syntax(ast, node));
        df_->set_str(rastr_node_operator_value(ast, node));

        return true;
    }

    virtual void post_op(rastr_ast_t ast, rastr_node_t node) {
        POST(op)
    }

    virtual bool pre_kw(rastr_ast_t ast, rastr_node_t node) {
        PRE(kw)

        df_->set_syn(rastr_node_keyword_syntax(ast, node));
        df_->set_str(rastr_node_keyword_value(ast, node));

        return true;
    }

    virtual void post_kw(rastr_ast_t ast, rastr_node_t node) {
        POST(kw)
    }

    virtual bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) {
        PRE(dlmtr)

        df_->set_syn(rastr_node_delimiter_syntax(ast, node));
        df_->set_str(rastr_node_delimiter_value(ast, node));

        return true;
    }

    virtual void post_dlmtr(rastr_ast_t ast, rastr_node_t node) {
        POST(dlmtr)
    }

    virtual bool pre_term(rastr_ast_t ast, rastr_node_t node) {
        PRE(term)

        df_->set_syn(rastr_node_terminator_syntax(ast, node));
        df_->set_str(rastr_node_terminator_value(ast, node));

        return true;
    }

    virtual void post_term(rastr_ast_t ast, rastr_node_t node) {
        POST(term)
    }

    virtual bool pre_null(rastr_ast_t ast, rastr_node_t node) {
        PRE(null)

        df_->set_syn(rastr_node_null_syntax(ast, node));

        return true;
    }

    virtual void post_null(rastr_ast_t ast, rastr_node_t node) {
        POST(null)
    }

    virtual bool pre_logical(rastr_ast_t ast, rastr_node_t node) {
        PRE(logical)

        df_->set_syn(rastr_node_logical_syntax(ast, node));
        df_->set_lgl(rastr_node_logical_value(ast, node));

        return true;
    }

    virtual void post_logical(rastr_ast_t ast, rastr_node_t node) {
        POST(logical)
    }

    virtual bool pre_integer(rastr_ast_t ast, rastr_node_t node) {
        PRE(integer)

        df_->set_syn(rastr_node_integer_syntax(ast, node));
        df_->set_int(rastr_node_integer_value(ast, node));

        return true;
    }

    virtual void post_integer(rastr_ast_t ast, rastr_node_t node) {
        POST(integer)
    }

    virtual bool pre_real(rastr_ast_t ast, rastr_node_t node) {
        PRE(real)

        df_->set_syn(rastr_node_real_syntax(ast, node));
        df_->set_dbl(rastr_node_real_value(ast, node));

        return true;
    }

    virtual void post_real(rastr_ast_t ast, rastr_node_t node) {
        POST(real)
    }

    virtual bool pre_complex(rastr_ast_t ast, rastr_node_t node) {
        PRE(complex)

        df_->set_syn(rastr_node_complex_syntax(ast, node));
        df_->set_cplx(rastr_node_complex_value(ast, node));

        return true;
    }

    virtual void post_complex(rastr_ast_t ast, rastr_node_t node) {
        POST(complex)
    }

    virtual bool pre_string(rastr_ast_t ast, rastr_node_t node) {
        PRE(string)

        df_->set_syn(rastr_node_string_syntax(ast, node));
        df_->set_str(rastr_node_string_value(ast, node));

        return true;
    }

    virtual void post_string(rastr_ast_t ast, rastr_node_t node) {
        POST(string)
    }

    virtual bool pre_symbol(rastr_ast_t ast, rastr_node_t node) {
        PRE(symbol)

        df_->set_syn(rastr_node_symbol_syntax(ast, node));
        df_->set_str(rastr_node_symbol_value(ast, node));

        return true;
    }

    virtual void post_symbol(rastr_ast_t ast, rastr_node_t node) {
        POST(symbol)
    }

    virtual bool pre_blk(rastr_ast_t ast, rastr_node_t node) {
        PRE(blk)
        return true;
    }

    virtual void post_blk(rastr_ast_t ast, rastr_node_t node) {
        POST(blk)
    }

    virtual bool pre_grp(rastr_ast_t ast, rastr_node_t node) {
        PRE(grp)
        return true;
    }

    virtual void post_grp(rastr_ast_t ast, rastr_node_t node) {
        POST(grp)
    }

    virtual bool pre_nuop(rastr_ast_t ast, rastr_node_t node) {
        PRE(nuop)
        return true;
    }

    virtual void post_nuop(rastr_ast_t ast, rastr_node_t node) {
        POST(nuop)
    }

    virtual bool pre_unop(rastr_ast_t ast, rastr_node_t node) {
        PRE(unop)
        return true;
    }

    virtual void post_unop(rastr_ast_t ast, rastr_node_t node) {
        POST(unop)
    }

    virtual bool pre_binop(rastr_ast_t ast, rastr_node_t node) {
        PRE(binop)
        return true;
    }

    virtual void post_binop(rastr_ast_t ast, rastr_node_t node) {
        POST(binop)
    }

    virtual bool pre_rlp(rastr_ast_t ast, rastr_node_t node) {
        PRE(rlp)
        return true;
    }

    virtual void post_rlp(rastr_ast_t ast, rastr_node_t node) {
        POST(rlp)
    }

    virtual bool pre_wlp(rastr_ast_t ast, rastr_node_t node) {
        PRE(wlp)
        return true;
    }

    virtual void post_wlp(rastr_ast_t ast, rastr_node_t node) {
        POST(wlp)
    }

    virtual bool pre_flp(rastr_ast_t ast, rastr_node_t node) {
        PRE(flp)
        return true;
    }

    virtual void post_flp(rastr_ast_t ast, rastr_node_t node) {
        POST(flp)
    }

    virtual bool pre_icnd(rastr_ast_t ast, rastr_node_t node) {
        PRE(icnd)
        return true;
    }

    virtual void post_icnd(rastr_ast_t ast, rastr_node_t node) {
        POST(icnd)
    }

    virtual bool pre_iecnd(rastr_ast_t ast, rastr_node_t node) {
        PRE(iecnd)
        return true;
    }

    virtual void post_iecnd(rastr_ast_t ast, rastr_node_t node) {
        POST(iecnd)
    }

    virtual bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) {
        PRE(fndefn)
        return true;
    }

    virtual void post_fndefn(rastr_ast_t ast, rastr_node_t node) {
        POST(fndefn)
    }

    virtual bool pre_fncall(rastr_ast_t ast, rastr_node_t node) {
        PRE(fncall)
        return true;
    }

    virtual void post_fncall(rastr_ast_t ast, rastr_node_t node) {
        POST(fncall)
    }

    virtual bool pre_sub(rastr_ast_t ast, rastr_node_t node) {
        PRE(sub)
        return true;
    }

    virtual void post_sub(rastr_ast_t ast, rastr_node_t node) {
        POST(sub)
    }

    virtual bool pre_idx(rastr_ast_t ast, rastr_node_t node) {
        PRE(idx)
        return true;
    }

    virtual void post_idx(rastr_ast_t ast, rastr_node_t node) {
        POST(idx)
    }

    virtual bool pre_params(rastr_ast_t ast, rastr_node_t node) {
        PRE(params)
        return true;
    }

    virtual void post_params(rastr_ast_t ast, rastr_node_t node) {
        POST(params)
    }

    virtual bool pre_dparam(rastr_ast_t ast, rastr_node_t node) {
        PRE(dparam)
        return true;
    }

    virtual void post_dparam(rastr_ast_t ast, rastr_node_t node) {
        POST(dparam)
    }

    virtual bool pre_ndparam(rastr_ast_t ast, rastr_node_t node) {
        PRE(ndparam)
        return true;
    }

    virtual void post_ndparam(rastr_ast_t ast, rastr_node_t node) {
        POST(ndparam)
    }

    virtual bool pre_args(rastr_ast_t ast, rastr_node_t node) {
        PRE(args)
        return true;
    }

    virtual void post_args(rastr_ast_t ast, rastr_node_t node) {
        POST(args)
    }

    virtual bool pre_narg(rastr_ast_t ast, rastr_node_t node) {
        PRE(narg)
        return true;
    }

    virtual void post_narg(rastr_ast_t ast, rastr_node_t node) {
        POST(narg)
    }

    virtual bool pre_parg(rastr_ast_t ast, rastr_node_t node) {
        PRE(parg)
        return true;
    }

    virtual void post_parg(rastr_ast_t ast, rastr_node_t node) {
        POST(parg)
    }

    virtual bool pre_cnd(rastr_ast_t ast, rastr_node_t node) {
        PRE(cnd)
        return true;
    }

    virtual void post_cnd(rastr_ast_t ast, rastr_node_t node) {
        POST(cnd)
    }

    virtual bool pre_iter(rastr_ast_t ast, rastr_node_t node) {
        PRE(iter)
        return true;
    }

    virtual void post_iter(rastr_ast_t ast, rastr_node_t node) {
        POST(iter)
    }

    virtual bool pre_pgm(rastr_ast_t ast, rastr_node_t node) {
        PRE(pgm)
        return true;
    }

    virtual void post_pgm(rastr_ast_t ast, rastr_node_t node) {
        POST(pgm)
    }

    virtual bool pre_dlmtd(rastr_ast_t ast, rastr_node_t node) {
        PRE(dlmtd)
        return true;
    }

    virtual void post_dlmtd(rastr_ast_t ast, rastr_node_t node) {
        POST(dlmtd)
    }

    virtual bool pre_msng(rastr_ast_t ast, rastr_node_t node) {
        PRE(msng)
        return true;
    }

    virtual void post_msng(rastr_ast_t ast, rastr_node_t node) {
        POST(msng)
    }

    virtual void beg(rastr_ast_t ast, rastr_node_t node) {
        PRE(beg)
        POST(beg)
    }

    virtual bool pre_end(rastr_ast_t ast, rastr_node_t node) {
        PRE(end)
        return true;
    }

    virtual void post_end(rastr_ast_t ast, rastr_node_t node) {
        POST(end)
    }

    virtual void ws(rastr_ast_t ast, rastr_node_t node) {
        PRE(ws)

        int count = rastr_ws_count(ast, node);
        char chr = rastr_ws_chr(ast, node);
        std::string syntax(count, chr);

        df_->set_syn(syntax.c_str());
        df_->set_str(syntax.c_str());

        POST(ws)
    }

    virtual void cmnt(rastr_ast_t ast, rastr_node_t node) {
        PRE(cmnt)

        const char* value = rastr_cmnt_value(ast, node);

        df_->set_syn(value);
        df_->set_str(value);

        POST(cmnt)
    }

    virtual bool pre_gap(rastr_ast_t ast, rastr_node_t node) {
        PRE(gap)
        return true;
    }

    virtual void post_gap(rastr_ast_t ast, rastr_node_t node) {
        POST(gap)
    }

  private:
    std::vector<int> parent_ids_;
    std::vector<int> fields_;
    AstDf* df_;
};

struct data_t {
    DFTransformer* transformer;
    AstDf* df;
    rastr_ast_t ast;
    rastr_node_t node;
};

SEXP rastr_ast_as_df(rastr_ast_t ast) {
    return rastr_node_as_df(ast, rastr_ast_root(ast));
}

SEXP r_rastr_ast_as_df(SEXP r_ast) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    return rastr_ast_as_df(ast);
}

static SEXP transform(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    return data->transformer->transform(data->df, data->ast, data->node);
}

static void cleanup(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    delete data->transformer;
    delete data->df;
}

SEXP rastr_node_as_df(rastr_ast_t ast, rastr_node_t node) {
    DFTransformer* transformer = new DFTransformer();
    /* TODO: replace with node_size */
    int size = rastr_ast_size(ast);
    AstDf* df = new AstDf(size);
    data_t data{transformer, df, ast, node};
    return R_ExecWithCleanup(transform, &data, cleanup, &data);
}

SEXP r_rastr_node_as_df(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    return rastr_node_as_df(ast, node);
}
