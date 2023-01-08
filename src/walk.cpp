#include <rastr/api.h>
#include "interop.h"

struct sexp_walker_t {
    SEXP r_env;
    SEXP r_state;
    SEXP r_pre_op;
    SEXP r_post_op;
    SEXP r_pre_dlmtr;
    SEXP r_post_dlmtr;
    SEXP r_pre_bkt;
    SEXP r_post_bkt;
    SEXP r_pre_null;
    SEXP r_post_null;
    SEXP r_pre_lgl;
    SEXP r_post_lgl;
    SEXP r_pre_int;
    SEXP r_post_int;
    SEXP r_pre_dbl;
    SEXP r_post_dbl;
    SEXP r_pre_cpx;
    SEXP r_post_cpx;
    SEXP r_pre_chr;
    SEXP r_post_chr;
    SEXP r_pre_sym;
    SEXP r_post_sym;
    SEXP r_pre_blk;
    SEXP r_post_blk;
    SEXP r_pre_grp;
    SEXP r_post_grp;
    SEXP r_pre_nuop;
    SEXP r_post_nuop;
    SEXP r_pre_unop;
    SEXP r_post_unop;
    SEXP r_pre_binop;
    SEXP r_post_binop;
    SEXP r_pre_rlp;
    SEXP r_post_rlp;
    SEXP r_pre_wlp;
    SEXP r_post_wlp;
    SEXP r_pre_flp;
    SEXP r_post_flp;
    SEXP r_pre_icond;
    SEXP r_post_icond;
    SEXP r_pre_iecond;
    SEXP r_post_iecond;
    SEXP r_pre_fndefn;
    SEXP r_post_fndefn;
    SEXP r_pre_fncall;
    SEXP r_post_fncall;
    SEXP r_pre_sub;
    SEXP r_post_sub;
    SEXP r_pre_idx;
    SEXP r_post_idx;
    SEXP r_pre_aexpr;
    SEXP r_post_aexpr;
    SEXP r_pre_exprs;
    SEXP r_post_exprs;
    SEXP r_pre_pars;
    SEXP r_post_pars;
    SEXP r_pre_dpar;
    SEXP r_post_dpar;
    SEXP r_pre_ndpar;
    SEXP r_post_ndpar;
    SEXP r_pre_args;
    SEXP r_post_args;
    SEXP r_pre_narg;
    SEXP r_post_narg;
    SEXP r_pre_parg;
    SEXP r_post_parg;
    SEXP r_pre_cond;
    SEXP r_post_cond;
    SEXP r_pre_iter;
    SEXP r_post_iter;
    SEXP r_pre_pgm;
    SEXP r_post_pgm;
    SEXP r_pre_dlmtd;
    SEXP r_post_dlmtd;
    SEXP r_pre_msng;
    SEXP r_post_msng;
    SEXP r_pre_beg;
    SEXP r_post_beg;
    SEXP r_pre_end;
    SEXP r_post_end;
    SEXP r_pre_gap;
    SEXP r_post_gap;
    SEXP r_pre_loc;
    SEXP r_post_loc;
};

#define CALL_PRE(NODE)                                                       \
    if (sexp_walker->r_pre_##NODE) {                                         \
        r_node = rastr_node_wrap(node);                                      \
        SEXP r_call = Rf_lang4(                                              \
            sexp_walker->r_pre_##NODE, r_ast, r_node, sexp_walker->r_state); \
        SEXP r_result = PROTECT(Rf_eval(r_call, sexp_walker->r_env));        \
        result = TYPEOF(r_result) == LGLSXP && lgl_get(r_result, 0) == 1;    \
        UNPROTECT(1);                                                        \
    }

#define CALL_POST(NODE)                                                       \
    if (sexp_walker->r_post_##NODE) {                                         \
        SEXP r_call = Rf_lang4(                                               \
            sexp_walker->r_post_##NODE, r_ast, r_node, sexp_walker->r_state); \
        Rf_eval(r_call, sexp_walker->r_env);                                  \
    }

#define SEXP_WALK(NODE, CHILD) \
    sexp_walk(ast, rastr_##NODE##_##CHILD##_get(ast, node), r_ast, sexp_walker);

#define CALL_WALKER_0(NODE) \
    CALL_PRE(NODE)          \
    if (result) {           \
        CALL_POST(NODE)     \
    }

#define CALL_WALKER_1(NODE, CHILD1) \
    CALL_PRE(NODE)                  \
    if (result) {                   \
        SEXP_WALK(NODE, CHILD1)     \
        CALL_POST(NODE)             \
    }

#define CALL_WALKER_2(NODE, CHILD1, CHILD2) \
    CALL_PRE(NODE)                          \
    if (result) {                           \
        SEXP_WALK(NODE, CHILD1)             \
        SEXP_WALK(NODE, CHILD2)             \
        CALL_POST(NODE)                     \
    }

#define CALL_WALKER_3(NODE, CHILD1, CHILD2, CHILD3) \
    CALL_PRE(NODE)                                  \
    if (result) {                                   \
        SEXP_WALK(NODE, CHILD1)                     \
        SEXP_WALK(NODE, CHILD2)                     \
        SEXP_WALK(NODE, CHILD3)                     \
        CALL_POST(NODE)                             \
    }

#define CALL_WALKER_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4) \
    CALL_PRE(NODE)                                          \
    if (result) {                                           \
        SEXP_WALK(NODE, CHILD1)                             \
        SEXP_WALK(NODE, CHILD2)                             \
        SEXP_WALK(NODE, CHILD3)                             \
        SEXP_WALK(NODE, CHILD4)                             \
        CALL_POST(NODE)                                     \
    }

#define CALL_WALKER_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
    CALL_PRE(NODE)                                                  \
    if (result) {                                                   \
        SEXP_WALK(NODE, CHILD1)                                     \
        SEXP_WALK(NODE, CHILD2)                                     \
        SEXP_WALK(NODE, CHILD3)                                     \
        SEXP_WALK(NODE, CHILD4)                                     \
        SEXP_WALK(NODE, CHILD5)                                     \
        CALL_POST(NODE)                                             \
    }

#define CALL_WALKER_SEQ(NODE, LEN, SEQ)                            \
    CALL_PRE(NODE)                                                 \
    if (result) {                                                  \
        int len = rastr_##NODE##_##LEN##_get(ast, node);           \
        for (int i = 0; i < len; ++i) {                            \
            rastr_node_t child = rastr_##NODE##_get(ast, node, i); \
            sexp_walk(ast, child, r_ast, sexp_walker);             \
        }                                                          \
        CALL_POST(NODE)                                            \
    }

void sexp_walk(rastr_ast_t ast,
               rastr_node_t node,
               SEXP r_ast,
               sexp_walker_t* sexp_walker) {
    int result = 0;
    SEXP r_node;

    rastr_node_type_t type = rastr_node_type(ast, node);
    switch (type) {
        /********************************************************************************
         Operators
        ********************************************************************************/
    case RASTR_OP_SP:
    case RASTR_OP_PLUS:
    case RASTR_OP_MINUS:
    case RASTR_OP_MUL:
    case RASTR_OP_DIV:
    case RASTR_OP_POW:
    case RASTR_OP_POW2:
    case RASTR_OP_LESS:
    case RASTR_OP_LESS_EQ:
    case RASTR_OP_GREAT:
    case RASTR_OP_GREAT_EQ:
    case RASTR_OP_EQ:
    case RASTR_OP_NOT_EQ:
    case RASTR_OP_NOT:
    case RASTR_OP_AND:
    case RASTR_OP_VEC_AND:
    case RASTR_OP_OR:
    case RASTR_OP_VEC_OR:
    case RASTR_OP_EQ_ASGN:
    case RASTR_OP_LT_ASGN:
    case RASTR_OP_RT_ASGN:
    case RASTR_OP_LT_SUP_ASGN:
    case RASTR_OP_RT_SUP_ASGN:
    case RASTR_OP_COLON_ASGN:
    case RASTR_OP_PIPE_FWD:
    case RASTR_OP_PIPE_BIND:
    case RASTR_OP_PUB_NS:
    case RASTR_OP_PVT_NS:
    case RASTR_OP_RANGE:
    case RASTR_OP_HELP:
    case RASTR_OP_SLOT:
    case RASTR_OP_FORMULA:
    case RASTR_OP_PART:
    case RASTR_OP_FN:
    case RASTR_OP_FN2:
    case RASTR_OP_WHILE:
    case RASTR_OP_REPEAT:
    case RASTR_OP_FOR:
    case RASTR_OP_IN:
    case RASTR_OP_IF:
    case RASTR_OP_ELSE:
    case RASTR_OP_NEXT:
    case RASTR_OP_BREAK:
        CALL_WALKER_2(op, gap, loc);
        break;

        /********************************************************************************
         Brackets
        ********************************************************************************/
    case RASTR_BKT_LT_RND:
    case RASTR_BKT_RT_RND:
    case RASTR_BKT_LT_CURL:
    case RASTR_BKT_RT_CURL:
    case RASTR_BKT_LT_SQR:
    case RASTR_BKT_RT_SQR:
    case RASTR_BKT_LT_DBL_SQR:
        CALL_WALKER_2(bkt, gap, loc);
        break;

        /********************************************************************************
         Delimiters
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        CALL_WALKER_2(dlmtr, gap, loc);
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        CALL_WALKER_2(null, gap, loc);
        break;

    case RASTR_LGL:
        CALL_WALKER_2(lgl, gap, loc);
        break;

    case RASTR_INT:
        CALL_WALKER_2(int, gap, loc);
        break;

    case RASTR_DBL:
        CALL_WALKER_2(dbl, gap, loc);
        break;

    case RASTR_CPX:
        CALL_WALKER_2(cpx, gap, loc);
        break;

    case RASTR_CHR:
        CALL_WALKER_2(chr, gap, loc);
        break;

    case RASTR_SYM:
        CALL_WALKER_2(sym, gap, loc);
        break;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
        CALL_WALKER_3(blk, lbkt, exprs, rbkt)
        break;

    case RASTR_GRP:
        CALL_WALKER_3(grp, lbkt, expr, rbkt);
        break;

    case RASTR_NUOP:
        CALL_WALKER_1(nuop, op);
        break;

    case RASTR_UNOP:
        CALL_WALKER_2(unop, op, expr);
        break;

    case RASTR_BINOP:
        CALL_WALKER_3(binop, lexpr, op, rexpr);
        break;

    case RASTR_RLP:
        CALL_WALKER_2(rlp, op, body);
        break;

    case RASTR_WLP:
        CALL_WALKER_3(wlp, op, cond, body);
        break;

    case RASTR_FLP:
        CALL_WALKER_3(flp, op, iter, body);
        break;

    case RASTR_ICOND:
        CALL_WALKER_3(icond, iop, cond, ibody);
        break;

    case RASTR_IECOND:
        CALL_WALKER_5(iecond, iop, cond, ibody, eop, ebody);
        break;

    case RASTR_FNDEFN:
        CALL_WALKER_5(fndefn, op, lbkt, pars, rbkt, body);
        break;

    case RASTR_FNCALL:
        CALL_WALKER_4(fncall, fn, lbkt, args, rbkt);
        break;

    case RASTR_SUB:
        CALL_WALKER_4(sub, obj, lbkt, args, rbkt);
        break;

    case RASTR_IDX:
        CALL_WALKER_5(idx, obj, lbkt, args, rbkt1, rbkt2);
        break;

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    case RASTR_AEXPR:
        CALL_WALKER_2(aexpr, ann, expr)
        break;

    case RASTR_EXPRS:
        CALL_WALKER_SEQ(exprs, len, seq)
        break;

    case RASTR_PARS:
        CALL_WALKER_SEQ(pars, len, seq)
        break;

    case RASTR_DPAR:
        CALL_WALKER_3(dpar, name, op, expr)
        break;

    case RASTR_NDPAR:
        CALL_WALKER_1(ndpar, name)
        break;

    case RASTR_ARGS:
        CALL_WALKER_SEQ(args, len, seq)
        break;

    case RASTR_NARG:
        CALL_WALKER_3(narg, name, op, expr)
        break;

    case RASTR_PARG:
        CALL_WALKER_1(parg, expr)
        break;

    case RASTR_COND:
        CALL_WALKER_3(cond, lbkt, expr, rbkt)
        break;

    case RASTR_ITER:
        CALL_WALKER_5(iter, lbkt, var, op, expr, rbkt)
        break;

    case RASTR_PGM:
        CALL_WALKER_3(pgm, beg, exprs, end)
        break;

    case RASTR_DLMTD:
        CALL_WALKER_2(dlmtd, expr, dlmtr)
        break;

    case RASTR_MSNG:
        CALL_WALKER_2(msng, gap, loc)
        break;

    case RASTR_BEG:
        CALL_WALKER_1(beg, loc)
        break;

    case RASTR_END:
        CALL_WALKER_2(end, gap, loc)
        break;

    case RASTR_GAP:
        CALL_WALKER_1(gap, loc)
        break;

    case RASTR_LOC:
        CALL_WALKER_0(loc)
        break;

    case RASTR_ERR:
        Rf_error("unexpected rastr node of type 'Error'");
        break;
    }
}

#define CHECK_WALK_FN_TYPE(WALKER)                                      \
    if (TYPEOF(WALKER) == NILSXP) {                                     \
        sexp_walker.WALKER = nullptr;                                   \
    } else if (TYPEOF(WALKER) == CLOSXP) {                              \
        sexp_walker.WALKER = WALKER;                                    \
    } else {                                                            \
        Rf_error("expected " #WALKER " to be either NULL or function"); \
    }

SEXP r_rastr_walk(SEXP r_ast,
                  SEXP r_node,
                  SEXP r_env,
                  SEXP r_state,
                  SEXP r_pre_op,
                  SEXP r_post_op,
                  SEXP r_pre_dlmtr,
                  SEXP r_post_dlmtr,
                  SEXP r_pre_bkt,
                  SEXP r_post_bkt,
                  SEXP r_pre_null,
                  SEXP r_post_null,
                  SEXP r_pre_lgl,
                  SEXP r_post_lgl,
                  SEXP r_pre_int,
                  SEXP r_post_int,
                  SEXP r_pre_dbl,
                  SEXP r_post_dbl,
                  SEXP r_pre_cpx,
                  SEXP r_post_cpx,
                  SEXP r_pre_chr,
                  SEXP r_post_chr,
                  SEXP r_pre_sym,
                  SEXP r_post_sym,
                  SEXP r_pre_blk,
                  SEXP r_post_blk,
                  SEXP r_pre_grp,
                  SEXP r_post_grp,
                  SEXP r_pre_nuop,
                  SEXP r_post_nuop,
                  SEXP r_pre_unop,
                  SEXP r_post_unop,
                  SEXP r_pre_binop,
                  SEXP r_post_binop,
                  SEXP r_pre_rlp,
                  SEXP r_post_rlp,
                  SEXP r_pre_wlp,
                  SEXP r_post_wlp,
                  SEXP r_pre_flp,
                  SEXP r_post_flp,
                  SEXP r_pre_icond,
                  SEXP r_post_icond,
                  SEXP r_pre_iecond,
                  SEXP r_post_iecond,
                  SEXP r_pre_fndefn,
                  SEXP r_post_fndefn,
                  SEXP r_pre_fncall,
                  SEXP r_post_fncall,
                  SEXP r_pre_sub,
                  SEXP r_post_sub,
                  SEXP r_pre_idx,
                  SEXP r_post_idx,
                  SEXP r_pre_aexpr,
                  SEXP r_post_aexpr,
                  SEXP r_pre_exprs,
                  SEXP r_post_exprs,
                  SEXP r_pre_pars,
                  SEXP r_post_pars,
                  SEXP r_pre_dpar,
                  SEXP r_post_dpar,
                  SEXP r_pre_ndpar,
                  SEXP r_post_ndpar,
                  SEXP r_pre_args,
                  SEXP r_post_args,
                  SEXP r_pre_narg,
                  SEXP r_post_narg,
                  SEXP r_pre_parg,
                  SEXP r_post_parg,
                  SEXP r_pre_cond,
                  SEXP r_post_cond,
                  SEXP r_pre_iter,
                  SEXP r_post_iter,
                  SEXP r_pre_pgm,
                  SEXP r_post_pgm,
                  SEXP r_pre_dlmtd,
                  SEXP r_post_dlmtd,
                  SEXP r_pre_msng,
                  SEXP r_post_msng,
                  SEXP r_pre_beg,
                  SEXP r_post_beg,
                  SEXP r_pre_end,
                  SEXP r_post_end,
                  SEXP r_pre_gap,
                  SEXP r_post_gap,
                  SEXP r_pre_loc,
                  SEXP r_post_loc) {
    sexp_walker_t sexp_walker;

    sexp_walker.r_env = r_env;
    sexp_walker.r_state = r_state;

    CHECK_WALK_FN_TYPE(r_pre_op)
    CHECK_WALK_FN_TYPE(r_post_op)
    CHECK_WALK_FN_TYPE(r_pre_dlmtr)
    CHECK_WALK_FN_TYPE(r_post_dlmtr)
    CHECK_WALK_FN_TYPE(r_pre_bkt)
    CHECK_WALK_FN_TYPE(r_post_bkt)
    CHECK_WALK_FN_TYPE(r_pre_null)
    CHECK_WALK_FN_TYPE(r_post_null)
    CHECK_WALK_FN_TYPE(r_pre_lgl)
    CHECK_WALK_FN_TYPE(r_post_lgl)
    CHECK_WALK_FN_TYPE(r_pre_int)
    CHECK_WALK_FN_TYPE(r_post_int)
    CHECK_WALK_FN_TYPE(r_pre_dbl)
    CHECK_WALK_FN_TYPE(r_post_dbl)
    CHECK_WALK_FN_TYPE(r_pre_cpx)
    CHECK_WALK_FN_TYPE(r_post_cpx)
    CHECK_WALK_FN_TYPE(r_pre_chr)
    CHECK_WALK_FN_TYPE(r_post_chr)
    CHECK_WALK_FN_TYPE(r_pre_sym)
    CHECK_WALK_FN_TYPE(r_post_sym)
    CHECK_WALK_FN_TYPE(r_pre_blk)
    CHECK_WALK_FN_TYPE(r_post_blk)
    CHECK_WALK_FN_TYPE(r_pre_grp)
    CHECK_WALK_FN_TYPE(r_post_grp)
    CHECK_WALK_FN_TYPE(r_pre_nuop)
    CHECK_WALK_FN_TYPE(r_post_nuop)
    CHECK_WALK_FN_TYPE(r_pre_unop)
    CHECK_WALK_FN_TYPE(r_post_unop)
    CHECK_WALK_FN_TYPE(r_pre_binop)
    CHECK_WALK_FN_TYPE(r_post_binop)
    CHECK_WALK_FN_TYPE(r_pre_rlp)
    CHECK_WALK_FN_TYPE(r_post_rlp)
    CHECK_WALK_FN_TYPE(r_pre_wlp)
    CHECK_WALK_FN_TYPE(r_post_wlp)
    CHECK_WALK_FN_TYPE(r_pre_flp)
    CHECK_WALK_FN_TYPE(r_post_flp)
    CHECK_WALK_FN_TYPE(r_pre_icond)
    CHECK_WALK_FN_TYPE(r_post_icond)
    CHECK_WALK_FN_TYPE(r_pre_iecond)
    CHECK_WALK_FN_TYPE(r_post_iecond)
    CHECK_WALK_FN_TYPE(r_pre_fndefn)
    CHECK_WALK_FN_TYPE(r_post_fndefn)
    CHECK_WALK_FN_TYPE(r_pre_fncall)
    CHECK_WALK_FN_TYPE(r_post_fncall)
    CHECK_WALK_FN_TYPE(r_pre_sub)
    CHECK_WALK_FN_TYPE(r_post_sub)
    CHECK_WALK_FN_TYPE(r_pre_idx)
    CHECK_WALK_FN_TYPE(r_post_idx)
    CHECK_WALK_FN_TYPE(r_pre_aexpr)
    CHECK_WALK_FN_TYPE(r_post_aexpr)
    CHECK_WALK_FN_TYPE(r_pre_exprs)
    CHECK_WALK_FN_TYPE(r_post_exprs)
    CHECK_WALK_FN_TYPE(r_pre_pars)
    CHECK_WALK_FN_TYPE(r_post_pars)
    CHECK_WALK_FN_TYPE(r_pre_dpar)
    CHECK_WALK_FN_TYPE(r_post_dpar)
    CHECK_WALK_FN_TYPE(r_pre_ndpar)
    CHECK_WALK_FN_TYPE(r_post_ndpar)
    CHECK_WALK_FN_TYPE(r_pre_args)
    CHECK_WALK_FN_TYPE(r_post_args)
    CHECK_WALK_FN_TYPE(r_pre_narg)
    CHECK_WALK_FN_TYPE(r_post_narg)
    CHECK_WALK_FN_TYPE(r_pre_parg)
    CHECK_WALK_FN_TYPE(r_post_parg)
    CHECK_WALK_FN_TYPE(r_pre_cond)
    CHECK_WALK_FN_TYPE(r_post_cond)
    CHECK_WALK_FN_TYPE(r_pre_iter)
    CHECK_WALK_FN_TYPE(r_post_iter)
    CHECK_WALK_FN_TYPE(r_pre_pgm)
    CHECK_WALK_FN_TYPE(r_post_pgm)
    CHECK_WALK_FN_TYPE(r_pre_dlmtd)
    CHECK_WALK_FN_TYPE(r_post_dlmtd)
    CHECK_WALK_FN_TYPE(r_pre_msng)
    CHECK_WALK_FN_TYPE(r_post_msng)
    CHECK_WALK_FN_TYPE(r_pre_beg)
    CHECK_WALK_FN_TYPE(r_post_beg)
    CHECK_WALK_FN_TYPE(r_pre_end)
    CHECK_WALK_FN_TYPE(r_post_end)
    CHECK_WALK_FN_TYPE(r_pre_gap)
    CHECK_WALK_FN_TYPE(r_post_gap)
    CHECK_WALK_FN_TYPE(r_pre_loc)
    CHECK_WALK_FN_TYPE(r_post_loc)

    sexp_walk(rastr_ast_unwrap(r_ast),
              rastr_node_unwrap(r_node),
              r_ast,
              &sexp_walker);

    return R_NilValue;
}

#undef SEXP_WALK
#undef CALL_WALKER_0
#undef CALL_WALKER_1
#undef CALL_WALKER_2
#undef CALL_WALKER_3
#undef CALL_WALKER_4
#undef CALL_WALKER_5
#undef HANDLE_SEQ
#undef CALL_WALKER_SEQ
#undef CHECK_WALK_FN_TYPE
