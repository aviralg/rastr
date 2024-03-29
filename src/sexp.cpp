#include <rastr/api.h>
#include <vector>
#include "interop.h"
#include "r_api.h"
// Copied from src/main/gram.y

/* Stretchy List Structures : Lists are created and grown using a special */
/* dotted pair.  The CAR of the list points to the last cons-cell in the */
/* list and the CDR points to the first.  The list can be extracted from */
/* the pair by taking its CDR, while the CAR gives fast access to the end */
/* of the list. */

/* These functions must be called with arguments protected */

/* Create a stretchy-list dotted pair */
static SEXP NewList(void) {
    SEXP s = CONS(R_NilValue, R_NilValue);
    SETCAR(s, s);
    return s;
}

/* Add a new element at the end of a stretchy list */
static void GrowList(SEXP l, SEXP s) {
    SEXP tmp;
    tmp = CONS(s, R_NilValue);
    SETCDR(CAR(l), tmp);
    SETCAR(l, tmp);
}

/* Create a stretchy list with a single named element */
static SEXP FirstArg(SEXP s, SEXP tag) {
    SEXP tmp;
    PROTECT(tmp = NewList());
    GrowList(tmp, s);
    SET_TAG(CAR(tmp), tag);
    UNPROTECT(1); /* tmp */
    return tmp;
}

/* Add named element to the end of a stretchy list */
static void NextArg(SEXP l, SEXP s, SEXP tag) {
    GrowList(l, s);
    SET_TAG(CAR(l), tag);
}

int is_placeholder(SEXP sym) {
    return TYPEOF(sym) == SYMSXP ? !strcmp("_", CHAR(PRINTNAME(sym))) : 0;
}

int is_pipebind(SEXP sym) {
    return TYPEOF(sym) == SYMSXP ? !strcmp("=>", CHAR(PRINTNAME(sym))) : 0;
}

static int checkForPlaceholder(SEXP arg) {
    // if (!HavePlaceholder)
    //     return FALSE;
    if (is_placeholder(arg))
        return TRUE;
    else if (TYPEOF(arg) == LANGSXP)
        for (SEXP cur = arg; cur != R_NilValue; cur = CDR(cur))
            if (checkForPlaceholder(CAR(cur)))
                return TRUE;
    return FALSE;
}

/* this table is copied from src/names.c */
const char* Spec_name[] = {
    "if",  "while", "repeat", "for", "break", "next", "return", "function",
    "(",   "{",     "+",      "-",   "*",     "/",    "^",      "%%",
    "%/%", "%*%",   ":",      "::",  ":::",   "?",    "|>",     "~",
    "@",   "=>",    "==",     "!=",  "<",     ">",    "<=",     ">=",
    "&",   "|",     "&&",     "||",  "!",     "<-",   "<<-",    "=",
    "$",   "[",     "[[",     "$<-", "[<-",   "[[<-", 0};

/* this is an inefficient implementation. the original implementation in
 * src/Defh.h relies on checking SEXP flags which are inaccessible to
 * packages.*/
int IS_SPECIAL_SYMBOL(SEXP sym) {
    const char* val = CHAR(PRINTNAME(sym));

    for (int i = 0; Spec_name[i] != nullptr; ++i) {
        if (!strcmp(Spec_name[i], val)) {
            return 1;
        }
    }

    return 0;
}

static void check_rhs(SEXP rhs) {
    /* rule out syntactically special functions */
    /* the IS_SPECIAL_SYMBOL bit is set in names.c */
    SEXP fun = CAR(rhs);
    if (TYPEOF(fun) == SYMSXP && IS_SPECIAL_SYMBOL(fun))
        error("function '%s' not supported in RHS call of a pipe",
              CHAR(PRINTNAME(fun)));
}

static void checkTooManyPlaceholders(SEXP rhs, SEXP args) {
    for (SEXP rest = args; rest != R_NilValue; rest = CDR(rest))
        if (is_placeholder(CAR(rest)))
            rastr_log_errorcall(rhs, "pipe placeholder may only appear once");
}

static SEXP xxpipe(SEXP lhs, SEXP rhs) {
    if (TYPEOF(rhs) != LANGSXP)
        rastr_log_error("The pipe operator requires a function call as RHS");

    /* allow x => log(x) on RHS */
    if (is_pipebind(CAR(rhs))) {
        SEXP var = CADR(rhs);
        SEXP expr = CADDR(rhs);
        if (TYPEOF(var) != SYMSXP)
            rastr_log_error("RHS variable must be a symbol");
        SEXP alist = list1(R_MissingArg);
        SET_TAG(alist, var);
        SEXP fun = lang4(R_FunctionSymbol, alist, expr, R_NilValue);
        return lang2(fun, lhs);
    }

    /* check for placehilder in the RHS function */
    if (checkForPlaceholder(CAR(rhs)))
        rastr_log_error("pipe placeholder cannot be used in the RHS function");

    /* allow top-level placeholder */
    for (SEXP a = CDR(rhs); a != R_NilValue; a = CDR(a))
        if (is_placeholder(CAR(a))) {
            if (TAG(a) == R_NilValue)
                rastr_log_error("pipe placeholder can only be used as a "
                                "named argument");
            checkTooManyPlaceholders(rhs, CDR(a));
            SETCAR(a, lhs);
            return rhs;
        }

    check_rhs(rhs);

    SEXP fun = CAR(rhs);
    SEXP args = CDR(rhs);

    return lcons(fun, lcons(lhs, args));
}

class SexpTransformer: public AstWalker {
  public:
    SexpTransformer(): AstWalker() {
    }

    SEXP transform(rastr_ast_t ast, rastr_node_t node) {
        this->walk(ast, node);
        UNPROTECT(1);
        return pop_();
    }

    bool pre_op(rastr_ast_t ast, rastr_node_t node) override {
        const char* val = NULL;

        switch (rastr_node_type(ast, node)) {
        case RASTR_OP_FN2:
            val = "function";
            break;

            /* binop has to reverse the order of lexpr and rexpr since R SEXP
             * does not have right assign operators */

        case RASTR_OP_RT_SUP_ASGN:
            val = "<<-";
            break;

        case RASTR_OP_RT_ASGN:
            val = "<-";
            break;

            /* TODO: handle pipe bind */
        case RASTR_OP_PIPE_BIND:
            val = "=>";
            break;

        default:
            val = rastr_op_syn_get(ast, node);
            break;
        }

        push_sym_(val);
        return false;
    }

    bool pre_bkt(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_type_t type = rastr_node_type(ast, node);

        switch (type) {
        case RASTR_BKT_LT_RND:
        case RASTR_BKT_LT_CURL:
        case RASTR_BKT_LT_SQR:
        case RASTR_BKT_LT_DBL_SQR:
            push_sym_(rastr_dlmtr_syn_get(ast, node));
            break;
        case RASTR_BKT_RT_RND:
        case RASTR_BKT_RT_CURL:
        case RASTR_BKT_RT_SQR:
            break;
        default:
            rastr_log_error("unexpected delimiter type %s",
                            rastr_node_type_to_string(type));
            break;
        }
        return false;
    }

    bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        return false;
    }

    bool pre_null(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(R_NilValue));
        return false;
    }

    bool pre_lgl(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(lgl_vec1(rastr_lgl_val_get(ast, node))));
        return false;
    }

    bool pre_int(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(int_vec1(rastr_int_val_get(ast, node))));
        return false;
    }

    bool pre_dbl(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(dbl_vec1(rastr_dbl_val_get(ast, node))));
        return false;
    }

    bool pre_cpx(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(cpx_vec1(rastr_cpx_val_get(ast, node))));
        return false;
    }

    bool pre_chr(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(chr_vec1(rastr_chr_val_get(ast, node))));
        return false;
    }

    bool pre_sym(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(Rf_install(rastr_sym_val_get(ast, node))));
        return false;
    }

    void post_blk(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_t exprs = rastr_blk_exprs_get(ast, node);
        int len = rastr_exprs_len_get(ast, exprs);

        int stack_len = stack_.size();

        SEXP r_exprs = NewList();

        for (int i = 0; i < len; ++i) {
            PROTECT(r_exprs);
            SEXP r_expr = stack_[stack_len - len + i];
            GrowList(r_exprs, r_expr);
            UNPROTECT(1);
        }

        remove_(len);
        UNPROTECT(len);

        SEXP r_lbrack = pop_();
        UNPROTECT(1);

        PROTECT(r_exprs);

        SET_TYPEOF(r_exprs, LANGSXP);
        SETCAR(r_exprs, r_lbrack);

        push_(r_exprs);
    }

    void post_grp(rastr_ast_t ast, rastr_node_t node) override {
        lang2_();
    }

    void post_nuop(rastr_ast_t ast, rastr_node_t node) override {
        lang1_();
    }

    void post_unop(rastr_ast_t ast, rastr_node_t node) override {
        lang2_();
    }

    void post_binop(rastr_ast_t ast, rastr_node_t node) override {
        SEXP rexpr = pop_();
        SEXP op = pop_();
        SEXP lexpr = pop_();
        SEXP r_ans = R_NilValue;

        rastr_node_type_t op_type =
            rastr_node_type(ast, rastr_binop_op_get(ast, node));

        switch (op_type) {
            /* R's SEXP representation converts -> to <- and reverses order of
             * expressions  */
        case RASTR_OP_RT_ASGN:
        case RASTR_OP_RT_SUP_ASGN:
            r_ans = Rf_lang3(op, rexpr, lexpr);
            break;

        case RASTR_OP_PIPE_FWD:
            r_ans = xxpipe(lexpr, rexpr);
            break;

        default:
            r_ans = Rf_lang3(op, lexpr, rexpr);
            break;
        }

        UNPROTECT(3);
        push_(PROTECT(r_ans));
    }

    void post_rlp(rastr_ast_t ast, rastr_node_t node) override {
        lang2_();
    }

    void post_wlp(rastr_ast_t ast, rastr_node_t node) override {
        lang3_();
    }

    void post_flp(rastr_ast_t ast, rastr_node_t node) override {
        lang4_();
    }

    void post_icond(rastr_ast_t ast, rastr_node_t node) override {
        lang3_();
    }

    void post_iecond(rastr_ast_t ast, rastr_node_t node) override {
        SEXP r_ebody = pop_();
        SEXP r_else = pop_();
        UNPROTECT_PTR(r_else);
        push_(r_ebody);
        lang4_();
    }

    void post_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        SEXP r_srcref = R_NilValue;
        SEXP r_body = pop_();
        SEXP r_formals = pop_();
        SEXP r_fun = pop_();
        SEXP r_res = Rf_lang4(r_fun, CDR(r_formals), r_body, r_srcref);

        UNPROTECT(3);

        push_(PROTECT(r_res));
    }

    void post_fncall(rastr_ast_t ast, rastr_node_t node) override {
        SEXP r_fncall = R_NilValue;
        SEXP r_args = pop_();
        SEXP r_fun = pop_();
        SEXP r_fun2 = r_fun;

        if (TYPEOF(r_fun) == STRSXP) {
            r_fun2 = Rf_install(CHAR(STRING_ELT(r_fun, 0)));
        }

        PROTECT(r_fun2);

        if (Rf_length(CDR(r_args)) == 1 && CADR(r_args) == R_MissingArg &&
            TAG(CDR(r_args)) == R_NilValue) {
            r_fncall = lang1(r_fun2);
        }

        else {
            r_fncall = LCONS(r_fun2, CDR(r_args));
        }

        UNPROTECT(3);
        push_(PROTECT(r_fncall));
    }

    void post_sub(rastr_ast_t ast, rastr_node_t node) override {
        SEXP r_inds = pop_();
        SEXP r_brack = PROTECT(Rf_install("[["));
        SEXP r_obj = pop_();

        SEXP r_result = LCONS(r_brack, CONS(r_obj, CDR(r_inds)));

        UNPROTECT(3);

        push_(PROTECT(r_result));
    }

    void post_idx(rastr_ast_t ast, rastr_node_t node) override {
        SEXP r_inds = pop_();
        SEXP r_brack = PROTECT(Rf_install("["));
        SEXP r_obj = pop_();

        SEXP r_result = LCONS(r_brack, CONS(r_obj, CDR(r_inds)));

        UNPROTECT(3);

        push_(PROTECT(r_result));
    }

    bool pre_aexpr(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_t expr = rastr_aexpr_expr_get(ast, node);
        walk(ast, expr);
        return false;
    }

    bool pre_pars(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(R_NilValue));
        return true;
    }

    bool pre_dpar(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_t name = rastr_dpar_name_get(ast, node);
        walk(ast, name);

        rastr_node_t expr = rastr_dpar_expr_get(ast, node);
        walk(ast, expr);

        add_arg_();

        return false;
    }

    bool pre_ndpar(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_t name = rastr_ndpar_name_get(ast, node);
        walk(ast, name);

        push_(PROTECT(R_MissingArg));

        add_arg_();

        return false;
    }

    bool pre_args(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(R_NilValue));

        return true;
    }

    bool pre_narg(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_t name = rastr_narg_name_get(ast, node);

        rastr_node_type_t name_type = rastr_node_type(ast, name);

        const char* name_str = nullptr;
        switch (name_type) {
        case RASTR_SYM:
            name_str = rastr_sym_val_get(ast, name);
            break;
        case RASTR_NULL:
            name_str = rastr_null_syn_get(ast, name);
            break;
        case RASTR_CHR:
            name_str = rastr_chr_val_get(ast, name);
            break;

        default:
            rastr_log_error("unexpected argument name type '%s'",
                            rastr_node_type_to_string(name_type));
            break;
        }

        push_sym_(name_str);

        rastr_node_t expr = rastr_narg_expr_get(ast, node);
        walk(ast, expr);

        add_arg_();

        return false;
    }

    bool pre_parg(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(R_NilValue));

        rastr_node_t expr = rastr_parg_expr_get(ast, node);
        walk(ast, expr);

        add_arg_();

        return false;
    }

    bool pre_cond(rastr_ast_t ast, rastr_node_t node) override {
        walk(ast, rastr_cond_expr_get(ast, node));
        return false;
    }

    bool pre_iter(rastr_ast_t ast, rastr_node_t node) override {
        walk(ast, rastr_iter_var_get(ast, node));
        walk(ast, rastr_iter_expr_get(ast, node));
        return false;
    }

    void post_pgm(rastr_ast_t ast, rastr_node_t node) override {
        int stack_len = stack_.size();

        rastr_node_t exprs = rastr_pgm_exprs_get(ast, node);
        int len = rastr_exprs_len_get(ast, exprs);

        SEXP r_pgm = PROTECT(allocVector(EXPRSXP, len));

        for (int i = 0; i < len; ++i) {
            SEXP r_expr = stack_[stack_len - len + i];

            SET_VECTOR_ELT(r_pgm, i, r_expr);
        }

        UNPROTECT(len + 1);

        remove_(len);

        push_(PROTECT(r_pgm));
    }

    void post_msng(rastr_ast_t ast, rastr_node_t node) override {
        push_(PROTECT(R_MissingArg));
    }

    bool pre_end(rastr_ast_t ast, rastr_node_t node) override {
        return false;
    }

    bool pre_gap(rastr_ast_t ast, rastr_node_t node) override {
        return false;
    }

    void walk(rastr_ast_t ast, rastr_node_t node) override {
        rastr_node_type_t type = rastr_node_type(ast, node);

        switch (type) {
        case RASTR_PARS:
            if (this->pre_pars(ast, node)) {
                handle_seq_(ast,
                            rastr_pars_len_get(ast, node),
                            rastr_pars_seq_get(ast, node));
                this->post_pars(ast, node);
            }

            break;

        case RASTR_ARGS:
            if (this->pre_args(ast, node)) {
                handle_seq_(ast,
                            rastr_args_len_get(ast, node),
                            rastr_args_seq_get(ast, node));
                this->post_args(ast, node);
            }

            break;

        default:
            AstWalker::walk(ast, node);
        }
    }

  private:
    std::vector<SEXP> stack_;

    void handle_seq_(rastr_ast_t ast, int len, const rastr_node_t* seq) {
        for (int i = 0; i < len; ++i) {
            this->walk(ast, seq[i]);
        }
    }

    void push_(SEXP val) {
        stack_.push_back(val);
    }

    SEXP pop_() {
        SEXP val = stack_.back();
        stack_.pop_back();
        return val;
    }

    void remove_(int len) {
        for (int i = 0; i < len; ++i) {
            pop_();
        }
    }

    void swap_() {
        SEXP a = pop_();
        SEXP b = pop_();
        push_(a);
        push_(b);
    }

    void push_sym_(const char* val) {
        push_(PROTECT(rastr_sym_wrap(val)));
    }

    void lang1_() {
        SEXP r_val1 = pop_();
        SEXP r_res = Rf_lang1(r_val1);

        UNPROTECT(1);

        push_(PROTECT(r_res));
    }

    void lang2_() {
        SEXP r_val2 = pop_();
        SEXP r_val1 = pop_();
        SEXP r_res = Rf_lang2(r_val1, r_val2);

        UNPROTECT(2);

        push_(PROTECT(r_res));
    }

    void lang3_() {
        SEXP r_val3 = pop_();
        SEXP r_val2 = pop_();
        SEXP r_val1 = pop_();
        SEXP r_res = Rf_lang3(r_val1, r_val2, r_val3);

        UNPROTECT(3);

        push_(PROTECT(r_res));
    }

    void lang4_() {
        SEXP r_val4 = pop_();
        SEXP r_val3 = pop_();
        SEXP r_val2 = pop_();
        SEXP r_val1 = pop_();
        SEXP r_res = Rf_lang4(r_val1, r_val2, r_val3, r_val4);

        UNPROTECT(4);

        push_(PROTECT(r_res));
    }

    void lang5_() {
        SEXP r_val5 = pop_();
        SEXP r_val4 = pop_();
        SEXP r_val3 = pop_();
        SEXP r_val2 = pop_();
        SEXP r_val1 = pop_();
        SEXP r_res = Rf_lang5(r_val1, r_val2, r_val3, r_val4, r_val5);

        UNPROTECT(5);

        push_(PROTECT(r_res));
    }

    void add_arg_() {
        SEXP r_expr = pop_();
        SEXP r_name = pop_();
        SEXP r_pars = pop_();

        if (r_pars == R_NilValue) {
            r_pars = FirstArg(r_expr, r_name);
        }

        else {
            NextArg(r_pars, r_expr, r_name);
        }

        UNPROTECT(3);

        push_(PROTECT(r_pars));
    }
};

struct data_t {
    SexpTransformer* transformer;
    rastr_ast_t ast;
    rastr_node_t node;
};

static SEXP transform(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    SexpTransformer* transformer = data->transformer;
    return transformer->transform(data->ast, data->node);
}

static void cleanup(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    SexpTransformer* transformer = data->transformer;
    delete transformer;
}

SEXP rastr_to_sexp(rastr_ast_t ast, rastr_node_t node) {
    SexpTransformer* transformer = new SexpTransformer();
    data_t data{transformer, ast, node};
    return R_ExecWithCleanup(transform, &data, cleanup, &data);
}

SEXP r_rastr_to_sexp(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    return rastr_to_sexp(ast, node);
}
