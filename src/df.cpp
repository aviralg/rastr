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
    df_->set_pid(pids_.back());                \
    pids_.push_back(id);                       \
                                               \
    df_->set_type(rastr_node_type(ast, node)); \
                                               \
    df_->set_field(fields_.back());            \
    fields_.push_back(0);

#define POST(KIND)      \
    fields_.pop_back(); \
    ++fields_.back();   \
    pids_.pop_back();

class AstDf {
  public:
    AstDf(int size): index_(-1) {
        r_id_ = PROTECT(int_vec(size, NA_INTEGER));
        r_pid_ = PROTECT(int_vec(size, NA_INTEGER));
        r_type_ = PROTECT(chr_vec(size, nullptr));
        r_field_ = PROTECT(int_vec(size, NA_INTEGER));
        r_syn_ = PROTECT(chr_vec(size, nullptr));
        r_val_chr_ = PROTECT(chr_vec(size, nullptr));
        r_val_lgl_ = PROTECT(lgl_vec(size, NA_LOGICAL));
        r_val_int_ = PROTECT(int_vec(size, NA_INTEGER));
        r_val_dbl_ = PROTECT(dbl_vec(size, NA_REAL));
        r_val_cpx_ = PROTECT(cpx_vec(size, NA_COMPLEX));
        r_lrow_ = PROTECT(int_vec(size, NA_INTEGER));
        r_lcol_ = PROTECT(int_vec(size, NA_INTEGER));
        r_lchr_ = PROTECT(int_vec(size, NA_INTEGER));
        r_lbyte_ = PROTECT(int_vec(size, NA_INTEGER));
        r_rrow_ = PROTECT(int_vec(size, NA_INTEGER));
        r_rcol_ = PROTECT(int_vec(size, NA_INTEGER));
        r_rchr_ = PROTECT(int_vec(size, NA_INTEGER));
        r_rbyte_ = PROTECT(int_vec(size, NA_INTEGER));
    }

    ~AstDf() {
        UNPROTECT(18);
    }

    SEXP materialize() {
        return rastr_create_data_frame(18,
                                       "id",
                                       r_id_,
                                       "pid",
                                       r_pid_,
                                       "field",
                                       r_field_,
                                       "type",
                                       r_type_,
                                       "syn",
                                       r_syn_,
                                       "val_chr",
                                       r_val_chr_,
                                       "val_lgl",
                                       r_val_lgl_,
                                       "val_int",
                                       r_val_int_,
                                       "val_dbl",
                                       r_val_dbl_,
                                       "val_cpx",
                                       r_val_cpx_,
                                       "lrow",
                                       r_lrow_,
                                       "lcol",
                                       r_lcol_,
                                       "lchr",
                                       r_lchr_,
                                       "lbyte",
                                       r_lbyte_,
                                       "rrow",
                                       r_rrow_,
                                       "rcol",
                                       r_rcol_,
                                       "rchr",
                                       r_rchr_,
                                       "rbyte",
                                       r_rbyte_);
    }

    void inc_index() {
        ++index_;
    }

    void set_loc(int lrow,
                 int lcol,
                 int lchr,
                 int lbyte,
                 int rrow,
                 int rcol,
                 int rchr,
                 int rbyte) {
        int_set(r_lrow_, index_, lrow);
        int_set(r_lcol_, index_, lcol);
        int_set(r_lchr_, index_, lchr);
        int_set(r_lbyte_, index_, lbyte);
        int_set(r_rrow_, index_, rrow);
        int_set(r_rcol_, index_, rcol);
        int_set(r_rchr_, index_, rchr);
        int_set(r_rbyte_, index_, rbyte);
    }

    void set_id(int id) {
        int_set(r_id_, index_, id);
    }

    void set_pid(int pid) {
        int_set(r_pid_, index_, pid);
    }

    void set_type(rastr_node_type_t type) {
        chr_set(r_type_, index_, rastr_node_type_to_string(type));
    }

    void set_field(int field) {
        int_set(r_field_, index_, field);
    }

    void set_syn(const char* value) {
        chr_set(r_syn_, index_, value);
    }

    void set_chr(const char* value) {
        chr_set(r_val_chr_, index_, value);
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

    void set_cpx(const Rcomplex& value) {
        cpx_set(r_val_cpx_, index_, value);
    }

  private:
    int index_;
    SEXP r_id_;
    SEXP r_pid_;
    SEXP r_type_;
    SEXP r_field_;
    SEXP r_syn_;
    SEXP r_val_chr_;
    SEXP r_val_lgl_;
    SEXP r_val_int_;
    SEXP r_val_dbl_;
    SEXP r_val_cpx_;
    SEXP r_lrow_;
    SEXP r_lcol_;
    SEXP r_lchr_;
    SEXP r_lbyte_;
    SEXP r_rrow_;
    SEXP r_rcol_;
    SEXP r_rchr_;
    SEXP r_rbyte_;
};

class DFTransformer: AstWalker {
  public:
    DFTransformer(): AstWalker(), df_(nullptr) {
        pids_.push_back(NA_INTEGER);
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

        df_->set_syn(rastr_op_syn_get(ast, node));

        return true;
    }

    void post_op(rastr_ast_t ast, rastr_node_t node) override {
        POST(op)
    }

    bool pre_bkt(rastr_ast_t ast, rastr_node_t node) override {
        PRE(bkt)

        df_->set_syn(rastr_bkt_syn_get(ast, node));

        return true;
    }

    void post_bkt(rastr_ast_t ast, rastr_node_t node) override {
        POST(bkt)
    }

    bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dlmtr)

        df_->set_syn(rastr_dlmtr_syn_get(ast, node));

        return true;
    }

    void post_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        POST(dlmtr)
    }

    bool pre_null(rastr_ast_t ast, rastr_node_t node) override {
        PRE(null)

        df_->set_syn(rastr_null_syn_get(ast, node));

        return true;
    }

    void post_null(rastr_ast_t ast, rastr_node_t node) override {
        POST(null)
    }

    bool pre_lgl(rastr_ast_t ast, rastr_node_t node) override {
        PRE(lgl)

        df_->set_syn(rastr_lgl_syn_get(ast, node));
        df_->set_lgl(rastr_lgl_val_get(ast, node));

        return true;
    }

    void post_lgl(rastr_ast_t ast, rastr_node_t node) override {
        POST(lgl)
    }

    bool pre_int(rastr_ast_t ast, rastr_node_t node) override {
        PRE(int)

        df_->set_syn(rastr_int_syn_get(ast, node));
        df_->set_int(rastr_int_val_get(ast, node));

        return true;
    }

    void post_int(rastr_ast_t ast, rastr_node_t node) override {
        POST(int)
    }

    bool pre_dbl(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dbl)

        df_->set_syn(rastr_dbl_syn_get(ast, node));
        df_->set_dbl(rastr_dbl_val_get(ast, node));

        return true;
    }

    void post_dbl(rastr_ast_t ast, rastr_node_t node) override {
        POST(dbl)
    }

    bool pre_cpx(rastr_ast_t ast, rastr_node_t node) override {
        PRE(cpx)

        df_->set_syn(rastr_cpx_syn_get(ast, node));
        df_->set_cpx(rastr_cpx_val_get(ast, node));

        return true;
    }

    void post_cpx(rastr_ast_t ast, rastr_node_t node) override {
        POST(cpx)
    }

    bool pre_chr(rastr_ast_t ast, rastr_node_t node) override {
        PRE(chr)

        df_->set_syn(rastr_chr_syn_get(ast, node));
        df_->set_chr(rastr_chr_val_get(ast, node));

        return true;
    }

    void post_chr(rastr_ast_t ast, rastr_node_t node) override {
        POST(chr)
    }

    bool pre_sym(rastr_ast_t ast, rastr_node_t node) override {
        PRE(sym)

        df_->set_syn(rastr_sym_syn_get(ast, node));
        df_->set_chr(rastr_sym_val_get(ast, node));

        return true;
    }

    void post_sym(rastr_ast_t ast, rastr_node_t node) override {
        POST(sym)
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

    bool pre_icond(rastr_ast_t ast, rastr_node_t node) override {
        PRE(icond)
        return true;
    }

    void post_icond(rastr_ast_t ast, rastr_node_t node) override {
        POST(icond)
    }

    bool pre_iecond(rastr_ast_t ast, rastr_node_t node) override {
        PRE(iecond)
        return true;
    }

    void post_iecond(rastr_ast_t ast, rastr_node_t node) override {
        POST(iecond)
    }

    bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) override {
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

    bool pre_aexpr(rastr_ast_t ast, rastr_node_t node) override {
        PRE(aexpr)
        return true;
    }

    void post_aexpr(rastr_ast_t ast, rastr_node_t node) override {
        POST(aexpr)
    }

    bool pre_exprs(rastr_ast_t ast, rastr_node_t node) override {
        PRE(exprs)
        return true;
    }

    void post_exprs(rastr_ast_t ast, rastr_node_t node) override {
        POST(exprs)
    }

    bool pre_pars(rastr_ast_t ast, rastr_node_t node) override {
        PRE(pars)
        return true;
    }

    void post_pars(rastr_ast_t ast, rastr_node_t node) override {
        POST(pars)
    }

    bool pre_dpar(rastr_ast_t ast, rastr_node_t node) override {
        PRE(dpar)
        return true;
    }

    void post_dpar(rastr_ast_t ast, rastr_node_t node) override {
        POST(dpar)
    }

    bool pre_ndpar(rastr_ast_t ast, rastr_node_t node) override {
        PRE(ndpar)
        return true;
    }

    void post_ndpar(rastr_ast_t ast, rastr_node_t node) override {
        POST(ndpar)
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

    bool pre_cond(rastr_ast_t ast, rastr_node_t node) override {
        PRE(cond)
        return true;
    }

    void post_cond(rastr_ast_t ast, rastr_node_t node) override {
        POST(cond)
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

    bool pre_gap(rastr_ast_t ast, rastr_node_t node) override {
        PRE(gap)

        const char* val = rastr_gap_val_get(ast, node);

        df_->set_syn(val);
        df_->set_chr(val);

        return true;
    }

    void post_gap(rastr_ast_t ast, rastr_node_t node) override {
        POST(gap)
    }

    bool pre_loc(rastr_ast_t ast, rastr_node_t node) override {
        PRE(loc)

        int lrow = rastr_loc_lrow_get(ast, node);
        int lcol = rastr_loc_lcol_get(ast, node);
        int lchr = rastr_loc_lchr_get(ast, node);
        int lbyte = rastr_loc_lbyte_get(ast, node);
        int rrow = rastr_loc_rrow_get(ast, node);
        int rcol = rastr_loc_rcol_get(ast, node);
        int rchr = rastr_loc_rchr_get(ast, node);
        int rbyte = rastr_loc_rbyte_get(ast, node);

        df_->set_loc(lrow, lcol, lchr, lbyte, rrow, rcol, rchr, rbyte);

        return true;
    }

    void post_loc(rastr_ast_t ast, rastr_node_t node) override {
        POST(loc)
    }

  private:
    std::vector<int> pids_;
    std::vector<int> fields_;
    AstDf* df_;
};

struct data_t {
    DFTransformer* transformer;
    AstDf* df;
    rastr_ast_t ast;
    rastr_node_t node;
};

static SEXP transform(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    return data->transformer->transform(data->df, data->ast, data->node);
}

static void cleanup(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    delete data->transformer;
    delete data->df;
}

SEXP rastr_to_df(rastr_ast_t ast, rastr_node_t node) {
    DFTransformer* transformer = new DFTransformer();
    /* TODO: replace with node_size */
    int size = rastr_ast_size(ast);
    AstDf* df = new AstDf(size);
    data_t data{transformer, df, ast, node};
    return R_ExecWithCleanup(transform, &data, cleanup, &data);
}

SEXP r_rastr_to_df(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    return rastr_to_df(ast, node);
}
