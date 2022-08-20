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
        r_row_ = PROTECT(int_vec(size, NA_INTEGER));
        r_col_ = PROTECT(int_vec(size, NA_INTEGER));
        r_chr_ = PROTECT(int_vec(size, NA_INTEGER));
        r_byte_ = PROTECT(int_vec(size, NA_INTEGER));
    }

    ~AstDf() {
        UNPROTECT(14);
    }

    SEXP materialize() {
        return rastr_create_data_frame(14,
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
                                       r_val_cplx_,
                                       "row",
                                       r_row_,
                                       "col",
                                       r_col_,
                                       "chr",
                                       r_chr_,
                                       "byte",
                                       r_byte_);
    }

    void inc_index() {
        ++index_;
    }

    void set_pos(int row, int col, int chr, int byte) {
        int_set(r_row_, index_, row);
        int_set(r_col_, index_, col);
        int_set(r_chr_, index_, chr);
        int_set(r_byte_, index_, byte);
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
    SEXP r_row_;
    SEXP r_col_;
    SEXP r_chr_;
    SEXP r_byte_;
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

    void walk(rastr_ast_t ast, rastr_node_t node) override {
        df_->inc_index();
        AstWalker::walk(ast, node);
    }

    bool pre_op(rastr_ast_t ast, rastr_node_t node) override {
        PRE(op)

        df_->set_syn(rastr_op_syn(ast, node));
        df_->set_str(rastr_op_val(ast, node));

        return true;
    }

    void post_op(rastr_ast_t ast, rastr_node_t node) override {
        POST(op)
    }

    bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dlmtr)

        df_->set_syn(rastr_node_delimiter_syntax(ast, node));
        df_->set_str(rastr_node_delimiter_value(ast, node));

        return true;
    }

    void post_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        POST(dlmtr)
    }

    bool pre_term(rastr_ast_t ast, rastr_node_t node) override {
        PRE(term)

        df_->set_syn(rastr_node_terminator_syntax(ast, node));
        df_->set_str(rastr_node_terminator_value(ast, node));

        return true;
    }

    void post_term(rastr_ast_t ast, rastr_node_t node) override {
        POST(term)
    }

    bool pre_null(rastr_ast_t ast, rastr_node_t node) override {
        PRE(null)

        df_->set_syn(rastr_node_null_syntax(ast, node));

        return true;
    }

    void post_null(rastr_ast_t ast, rastr_node_t node) override {
        POST(null)
    }

    bool pre_logical(rastr_ast_t ast, rastr_node_t node) override {
        PRE(logical)

        df_->set_syn(rastr_node_logical_syntax(ast, node));
        df_->set_lgl(rastr_node_logical_value(ast, node));

        return true;
    }

    void post_logical(rastr_ast_t ast, rastr_node_t node) override {
        POST(logical)
    }

    bool pre_integer(rastr_ast_t ast, rastr_node_t node) override {
        PRE(integer)

        df_->set_syn(rastr_node_integer_syntax(ast, node));
        df_->set_int(rastr_node_integer_value(ast, node));

        return true;
    }

    void post_integer(rastr_ast_t ast, rastr_node_t node) override {
        POST(integer)
    }

    bool pre_real(rastr_ast_t ast, rastr_node_t node) override {
        PRE(real)

        df_->set_syn(rastr_node_real_syntax(ast, node));
        df_->set_dbl(rastr_node_real_value(ast, node));

        return true;
    }

    void post_real(rastr_ast_t ast, rastr_node_t node) override {
        POST(real)
    }

    bool pre_complex(rastr_ast_t ast, rastr_node_t node) override {
        PRE(complex)

        df_->set_syn(rastr_node_complex_syntax(ast, node));
        df_->set_cplx(rastr_node_complex_value(ast, node));

        return true;
    }

    void post_complex(rastr_ast_t ast, rastr_node_t node) override {
        POST(complex)
    }

    bool pre_string(rastr_ast_t ast, rastr_node_t node) override {
        PRE(string)

        df_->set_syn(rastr_node_string_syntax(ast, node));
        df_->set_str(rastr_node_string_value(ast, node));

        return true;
    }

    void post_string(rastr_ast_t ast, rastr_node_t node) override {
        POST(string)
    }

    bool pre_symbol(rastr_ast_t ast, rastr_node_t node) override {
        PRE(symbol)

        df_->set_syn(rastr_node_symbol_syntax(ast, node));
        df_->set_str(rastr_node_symbol_value(ast, node));

        return true;
    }

    void post_symbol(rastr_ast_t ast, rastr_node_t node) override {
        POST(symbol)
    }

    bool pre_blk(rastr_ast_t ast, rastr_node_t node) override {
        PRE(blk)
        return true;
    }

    void post_blk(rastr_ast_t ast, rastr_node_t node) override {
        POST(blk)
    }

    bool pre_grp(rastr_ast_t ast, rastr_node_t node) override {
        PRE(grp)
        return true;
    }

    void post_grp(rastr_ast_t ast, rastr_node_t node) override {
        POST(grp)
    }

    bool pre_nuop(rastr_ast_t ast, rastr_node_t node) override {
        PRE(nuop)
        return true;
    }

    void post_nuop(rastr_ast_t ast, rastr_node_t node) override {
        POST(nuop)
    }

    bool pre_unop(rastr_ast_t ast, rastr_node_t node) override {
        PRE(unop)
        return true;
    }

    void post_unop(rastr_ast_t ast, rastr_node_t node) override {
        POST(unop)
    }

    bool pre_binop(rastr_ast_t ast, rastr_node_t node) override {
        PRE(binop)
        return true;
    }

    void post_binop(rastr_ast_t ast, rastr_node_t node) override {
        POST(binop)
    }

    bool pre_rlp(rastr_ast_t ast, rastr_node_t node) override {
        PRE(rlp)
        return true;
    }

    void post_rlp(rastr_ast_t ast, rastr_node_t node) override {
        POST(rlp)
    }

    bool pre_wlp(rastr_ast_t ast, rastr_node_t node) override {
        PRE(wlp)
        return true;
    }

    void post_wlp(rastr_ast_t ast, rastr_node_t node) override {
        POST(wlp)
    }

    bool pre_flp(rastr_ast_t ast, rastr_node_t node) override {
        PRE(flp)
        return true;
    }

    void post_flp(rastr_ast_t ast, rastr_node_t node) override {
        POST(flp)
    }

    bool pre_icnd(rastr_ast_t ast, rastr_node_t node) override {
        PRE(icnd)
        return true;
    }

    void post_icnd(rastr_ast_t ast, rastr_node_t node) override {
        POST(icnd)
    }

    bool pre_iecnd(rastr_ast_t ast, rastr_node_t node) override {
        PRE(iecnd)
        return true;
    }

    void post_iecnd(rastr_ast_t ast, rastr_node_t node) override {
        POST(iecnd)
    }

    bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        ;
        PRE(fndefn)
        return true;
    }

    void post_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        POST(fndefn)
    }

    bool pre_fncall(rastr_ast_t ast, rastr_node_t node) override {
        PRE(fncall)
        return true;
    }

    void post_fncall(rastr_ast_t ast, rastr_node_t node) override {
        POST(fncall)
    }

    bool pre_sub(rastr_ast_t ast, rastr_node_t node) override {
        PRE(sub)
        return true;
    }

    void post_sub(rastr_ast_t ast, rastr_node_t node) override {
        POST(sub)
    }

    bool pre_idx(rastr_ast_t ast, rastr_node_t node) override {
        PRE(idx)
        return true;
    }

    void post_idx(rastr_ast_t ast, rastr_node_t node) override {
        POST(idx)
    }

    bool pre_params(rastr_ast_t ast, rastr_node_t node) override {
        PRE(params)
        return true;
    }

    void post_params(rastr_ast_t ast, rastr_node_t node) override {
        POST(params)
    }

    bool pre_dparam(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dparam)
        return true;
    }

    void post_dparam(rastr_ast_t ast, rastr_node_t node) override {
        POST(dparam)
    }

    bool pre_ndparam(rastr_ast_t ast, rastr_node_t node) override {
        PRE(ndparam)
        return true;
    }

    void post_ndparam(rastr_ast_t ast, rastr_node_t node) override {
        POST(ndparam)
    }

    bool pre_args(rastr_ast_t ast, rastr_node_t node) override {
        PRE(args)
        return true;
    }

    void post_args(rastr_ast_t ast, rastr_node_t node) override {
        POST(args)
    }

    bool pre_narg(rastr_ast_t ast, rastr_node_t node) override {
        PRE(narg)
        return true;
    }

    void post_narg(rastr_ast_t ast, rastr_node_t node) override {
        POST(narg)
    }

    bool pre_parg(rastr_ast_t ast, rastr_node_t node) override {
        PRE(parg)
        return true;
    }

    void post_parg(rastr_ast_t ast, rastr_node_t node) override {
        POST(parg)
    }

    bool pre_cnd(rastr_ast_t ast, rastr_node_t node) override {
        PRE(cnd)
        return true;
    }

    void post_cnd(rastr_ast_t ast, rastr_node_t node) override {
        POST(cnd)
    }

    bool pre_iter(rastr_ast_t ast, rastr_node_t node) override {
        PRE(iter)
        return true;
    }

    void post_iter(rastr_ast_t ast, rastr_node_t node) override {
        POST(iter)
    }

    bool pre_pgm(rastr_ast_t ast, rastr_node_t node) override {
        PRE(pgm)
        return true;
    }

    void post_pgm(rastr_ast_t ast, rastr_node_t node) override {
        POST(pgm)
    }

    bool pre_dlmtd(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dlmtd)
        return true;
    }

    void post_dlmtd(rastr_ast_t ast, rastr_node_t node) override {
        POST(dlmtd)
    }

    bool pre_msng(rastr_ast_t ast, rastr_node_t node) override {
        PRE(msng)
        return true;
    }

    void post_msng(rastr_ast_t ast, rastr_node_t node) override {
        POST(msng)
    }

    bool pre_beg(rastr_ast_t ast, rastr_node_t node) override {
        PRE(beg)
        return true;
    }

    void post_beg(rastr_ast_t ast, rastr_node_t node) override {
        POST(beg)
    }

    bool pre_end(rastr_ast_t ast, rastr_node_t node) override {
        PRE(end)
        return true;
    }

    void post_end(rastr_ast_t ast, rastr_node_t node) override {
        POST(end)
    }

    bool pre_ws(rastr_ast_t ast, rastr_node_t node) override {
        PRE(ws)

        int count = rastr_ws_count(ast, node);
        char chr = rastr_ws_chr(ast, node);
        std::string syntax(count, chr);

        df_->set_syn(syntax.c_str());
        df_->set_str(syntax.c_str());

        return true;
    }

    void post_ws(rastr_ast_t ast, rastr_node_t node) override {
        POST(ws)
    }

    bool pre_cmnt(rastr_ast_t ast, rastr_node_t node) override {
        PRE(cmnt)

        const char* value = rastr_cmnt_value(ast, node);

        df_->set_syn(value);
        df_->set_str(value);

        return true;
    }

    void post_cmnt(rastr_ast_t ast, rastr_node_t node) override {
        POST(cmnt)
    }

    bool pre_gap(rastr_ast_t ast, rastr_node_t node) override {
        PRE(gap)
        return true;
    }

    void post_gap(rastr_ast_t ast, rastr_node_t node) override {
        POST(gap)
    }

    bool pre_loc(rastr_ast_t ast, rastr_node_t node) override {
        PRE(loc)
        return true;
    }

    void post_loc(rastr_ast_t ast, rastr_node_t node) override {
        POST(loc)
    }

    bool pre_pos(rastr_ast_t ast, rastr_node_t node) override {
        PRE(pos)

        int row = rastr_pos_row(ast, node);
        int col = rastr_pos_col(ast, node);
        int chr = rastr_pos_chr(ast, node);
        int byte = rastr_pos_byte(ast, node);

        df_->set_pos(row, col, chr, byte);

        return true;
    }

    void post_pos(rastr_ast_t ast, rastr_node_t node) override {
        POST(pos)
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
