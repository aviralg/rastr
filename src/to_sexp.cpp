#include <rastr/api.h>
#include "r_api.h"
#include "interop.h"

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

SEXP lang1_to_sexp(rastr_ast_t ast, rastr_node_t expr1) {
    SEXP r_expr1 = PROTECT(rastr_node_to_sexp(ast, expr1));

    SEXP r_result = Rf_lang1(r_expr1);

    UNPROTECT(1);

    return r_result;
}

SEXP lang2_to_sexp(rastr_ast_t ast, rastr_node_t expr1, rastr_node_t expr2) {
    SEXP r_expr1 = PROTECT(rastr_node_to_sexp(ast, expr1));
    SEXP r_expr2 = PROTECT(rastr_node_to_sexp(ast, expr2));

    SEXP r_result = Rf_lang2(r_expr1, r_expr2);

    UNPROTECT(2);

    return r_result;
}

SEXP lang3_to_sexp(rastr_ast_t ast,
                   rastr_node_t expr1,
                   rastr_node_t expr2,
                   rastr_node_t expr3) {
    SEXP r_expr1 = PROTECT(rastr_node_to_sexp(ast, expr1));
    SEXP r_expr2 = PROTECT(rastr_node_to_sexp(ast, expr2));
    SEXP r_expr3 = PROTECT(rastr_node_to_sexp(ast, expr3));

    SEXP r_result = Rf_lang3(r_expr1, r_expr2, r_expr3);

    UNPROTECT(3);

    return r_result;
}

SEXP lang4_to_sexp(rastr_ast_t ast,
                   rastr_node_t expr1,
                   rastr_node_t expr2,
                   rastr_node_t expr3,
                   rastr_node_t expr4) {
    SEXP r_expr1 = PROTECT(rastr_node_to_sexp(ast, expr1));
    SEXP r_expr2 = PROTECT(rastr_node_to_sexp(ast, expr2));
    SEXP r_expr3 = PROTECT(rastr_node_to_sexp(ast, expr3));
    SEXP r_expr4 = PROTECT(rastr_node_to_sexp(ast, expr4));

    SEXP r_result = Rf_lang4(r_expr1, r_expr2, r_expr3, r_expr4);

    UNPROTECT(4);

    return r_result;
}

SEXP pgm_to_sexp(rastr_ast_t ast, rastr_node_t pgm) {
    int len = rastr_pgm_len(ast, pgm);
    const rastr_node_t* seq = rastr_pgm_seq(ast, pgm);

    SEXP r_pgm = PROTECT(allocVector(EXPRSXP, len));

    for (int i = 0; i < len; ++i) {
        rastr_node_t expr = seq[i];
        SEXP r_expr = PROTECT(rastr_node_to_sexp(ast, expr));

        SET_VECTOR_ELT(r_pgm, i, r_expr);

        UNPROTECT(1);
    }

    UNPROTECT(1);
    return r_pgm;
}

SEXP blk_to_sexp(rastr_ast_t ast, rastr_node_t blk) {
    int len = rastr_blk_len(ast, blk);
    const rastr_node_t* seq = rastr_blk_seq(ast, blk);

    rastr_node_t lbrack = rastr_blk_lbrack(ast, blk);
    SEXP r_lbrack = PROTECT(rastr_node_to_sexp(ast, lbrack));

    SEXP r_exprs = NewList();

    for (int i = 0; i < len; ++i) {
        PROTECT(r_exprs);
        SEXP r_expr = PROTECT(rastr_node_to_sexp(ast, seq[i]));
        GrowList(r_exprs, r_expr);
        UNPROTECT(2);
    }

    PROTECT(r_exprs);

    SET_TYPEOF(r_exprs, LANGSXP);
    SETCAR(r_exprs, r_lbrack);

    UNPROTECT(2);

    return r_exprs;
}

SEXP param_to_sexp(rastr_ast_t ast, rastr_node_t param, SEXP r_params) {
    rastr_node_type_t type = rastr_node_type(ast, param);

    rastr_node_t name;
    SEXP r_name = R_NilValue;

    rastr_node_t expr;
    SEXP r_expr = R_NilValue;

    switch (type) {
    case Delimited:
        return param_to_sexp(ast, rastr_dlmtd_expr(ast, param), r_params);

    case NonDefaultParameter:
        name = rastr_ndparam_name(ast, param);
        r_name = PROTECT(rastr_node_to_sexp(ast, name));
        r_expr = PROTECT(R_MissingArg);
        break;

    case DefaultParameter:
        name = rastr_dparam_name(ast, param);
        r_name = PROTECT(rastr_node_to_sexp(ast, name));

        expr = rastr_dparam_expr(ast, param);
        r_expr = PROTECT(rastr_node_to_sexp(ast, expr));

        break;

    default:
        rastr_log_error("unexpected parameter type %s",
                        rastr_node_type_to_string(type));
    }

    if (r_params == R_NilValue) {
        r_params = FirstArg(r_expr, r_name);
    }

    else {
        NextArg(r_params, r_expr, r_name);
    }

    UNPROTECT(2);

    return r_params;
}

SEXP params_to_sexp(rastr_ast_t ast, rastr_node_t params) {
    int len = rastr_params_len(ast, params);
    const rastr_node_t* seq = rastr_params_seq(ast, params);

    SEXP r_params = R_NilValue;

    for (int i = 0; i < len; ++i) {
        PROTECT(r_params);

        rastr_node_t param = seq[i];

        r_params = param_to_sexp(ast, param, r_params);

        UNPROTECT(1);
    }

    return r_params;
}

#define EXPORT_CHILD(NOD, KIND, CHILD)                      \
    rastr_node_t CHILD = rastr_##KIND##_##CHILD(ast, NODE); \
    SEXP r_##CHILD = PROTECT(rastr_node_to_sexp(ast_, CHILD));

SEXP fndefn_to_sexp(rastr_ast_t ast, rastr_node_t fndefn) {
    rastr_node_t body = rastr_fndefn_body(ast, fndefn);
    SEXP r_body = PROTECT(rastr_node_to_sexp(ast, body));

    rastr_node_t params = rastr_fndefn_params(ast, fndefn);
    SEXP r_params = PROTECT(params_to_sexp(ast, params));

    SEXP r_result =
        Rf_lang4(R_FunctionSymbol, CDR(r_params), r_body, R_NilValue);

    UNPROTECT(2);

    return r_result;
}

SEXP arg_to_sexp(rastr_ast_t ast, rastr_node_t arg, SEXP r_args) {
    rastr_node_type_t type = rastr_node_type(ast, arg);
    SEXP r_name = R_NilValue;
    SEXP r_expr = R_NilValue;

    if (type == Delimited) {
        return arg_to_sexp(ast, rastr_dlmtd_expr(ast, arg), r_args);
    }

    else if (type == PositionalArgument) {
        r_name = PROTECT(R_NilValue);

        rastr_node_t expr = rastr_parg_expr(ast, arg);
        r_expr = PROTECT(rastr_node_to_sexp(ast, expr));
    }

    else if (type == NamedArgument) {
        rastr_node_t name = rastr_narg_name(ast, arg);
        r_name = PROTECT(rastr_node_to_sexp(ast, name));

        rastr_node_t expr = rastr_narg_expr(ast, arg);
        r_expr = PROTECT(rastr_node_to_sexp(ast, expr));
    }

    else {
        rastr_log_error("unexpected argument type %s",
                        rastr_node_type_to_string(type));
    }

    if (r_args == R_NilValue) {
        r_args = FirstArg(r_expr, r_name);
    }

    else {
        NextArg(r_args, r_expr, r_name);
    }

    UNPROTECT(2);

    return r_args;
}

SEXP args_to_sexp(rastr_ast_t ast, rastr_node_t args) {
    int len = rastr_args_len(ast, args);
    const rastr_node_t* seq = rastr_args_seq(ast, args);

    SEXP r_args = R_NilValue;

    for (int i = 0; i < len; ++i) {
        rastr_node_t arg = seq[i];

        PROTECT(r_args);

        r_args = arg_to_sexp(ast, arg, r_args);

        UNPROTECT(1);
    }

    return r_args;
}

SEXP subset_to_sexp(rastr_ast_t ast, rastr_node_t obj, rastr_node_t inds) {
    SEXP r_obj = PROTECT(rastr_node_to_sexp(ast, obj));
    SEXP r_inds = PROTECT(args_to_sexp(ast, inds));
    SEXP r_brack =
        PROTECT(rastr_node_to_sexp(ast, rastr_args_lbrack(ast, inds)));

    SEXP r_result = LCONS(r_brack, CONS(r_obj, CDR(r_inds)));

    UNPROTECT(3);

    return r_result;
}

SEXP fncall_to_sexp(rastr_ast_t ast, rastr_node_t fncall) {
    SEXP r_fncall = R_NilValue;
    SEXP r_fun = R_NilValue;

    rastr_node_t fun = rastr_fncall_fun(ast, fncall);

    if (rastr_node_type(ast, fun) == String) {
        r_fun = rastr_sym_wrap(rastr_node_string_value(ast, fun));
    } else {
        r_fun = rastr_node_to_sexp(ast, fun);
    }

    PROTECT(r_fun);

    rastr_node_t args = rastr_fncall_args(ast, fncall);
    SEXP r_args = PROTECT(args_to_sexp(ast, args));

    if (Rf_length(CDR(r_args)) == 1 && CADR(r_args) == R_MissingArg &&
        TAG(CDR(r_args)) == R_NilValue) {
        r_fncall = lang1(r_fun);
    }

    else {
        r_fncall = LCONS(r_fun, CDR(r_args));
    }

    UNPROTECT(2);

    return r_fncall;
}

SEXP r_rastr_to_sexp(SEXP r_ast) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    return rastr_to_sexp(ast);
}

SEXP r_rastr_node_to_sexp(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return rastr_node_to_sexp(ast, node);
}

SEXP rastr_to_sexp(rastr_ast_t ast) {
    if (rastr_is_empty(ast)) {
        rastr_log_error("cannot convert empty ast to SEXP");
        return R_NilValue;
    }

    /* TODO: check well formedness */
    rastr_node_t root = rastr_ast_root(ast);
    return rastr_node_to_sexp(ast, root);
}

SEXP rastr_node_to_sexp(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
        /********************************************************************************
         Operators
        ********************************************************************************/
    case Special:
    case Plus:
    case Minus:
    case Multiplication:
    case Division:
    case LessThan:
    case LessThanEqual:
    case GreaterThan:
    case GreaterThanEqual:
    case Equal:
    case NotEqual:
    case Not:
    case And:
    case VectorizedAnd:
    case Or:
    case VectorizedOr:
    case EqualAssign:
    case LeftAssign:
    case LeftSuperAssign:
    case ColonAssign:
    case PipeForward:
    case PublicNamespace:
    case PrivateNamespace:
    case Range:
    case Help:
    case SlotExtract:
    case Formula:
    case PartExtract:
    case AnonymousFunction:
        return rastr_sym_wrap(rastr_node_operator_value(ast, node));

    /* R AST always represents power as ^ even if user typed ** */
    case Power:
        return rastr_sym_wrap("^");

    case RightAssign:
    case RightSuperAssign:
    case PipeBind:
        rastr_log_error("no equivalent SEXP representation for %s",
                        rastr_node_operator_value(ast, node));
        return R_NilValue;

        /********************************************************************************
         KEYWORDS
        ********************************************************************************/
    case Function:
    case While:
    case Repeat:
    case For:
    case In:
    case If:
    case Else:
        return rastr_sym_wrap(rastr_node_keyword_value(ast, node));
    case Next:
    case Break:
        return Rf_lang1(rastr_sym_wrap(rastr_node_keyword_value(ast, node)));

        /********************************************************************************
         Delimiters
        ********************************************************************************/
    case LeftParen:
    case LeftBrace:
    case LeftBracket:
    case DoubleLeftBracket:
        return rastr_sym_wrap(rastr_node_delimiter_value(ast, node));

    case RightParen:
    case RightBrace:
    case RightBracket:
    case DoubleRightBracket:
        rastr_log_error("no equivalent SEXP representation for %s",
                        rastr_node_delimiter_value(ast, node));
        return R_NilValue;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case Semicolon:
    case Newline:
    case Comma:
        rastr_log_error("no equivalent SEXP representation for %s",
                        rastr_node_terminator_value(ast, node));
        return R_NilValue;

        /********************************************************************************
         Literals
        ********************************************************************************/
    case Null:
        return R_NilValue;

    case Logical:
        return rastr_lgl_wrap(rastr_node_logical_value(ast, node));

    case Integer:
        return rastr_int_wrap(rastr_node_integer_value(ast, node));

    case Real:
        return rastr_dbl_wrap(rastr_node_real_value(ast, node));

    case Complex:
        return rastr_cplx_wrap(rastr_node_complex_value(ast, node));

    case String:
        return rastr_str_wrap(rastr_node_string_value(ast, node));

    case Symbol:
        return rastr_sym_wrap(rastr_node_symbol_value(ast, node));

        /********************************************************************************
          Expressions
        ********************************************************************************/

    case Block:
        return blk_to_sexp(ast, node);

    case Group:
        return lang2_to_sexp(
            ast, rastr_grp_lbrack(ast, node), rastr_grp_expr(ast, node));

    case UnaryOperation:
        return lang2_to_sexp(
            ast, rastr_unop_op(ast, node), rastr_unop_expr(ast, node));

    case BinaryOperation:
        return lang3_to_sexp(ast,
                             rastr_binop_op(ast, node),
                             rastr_binop_lexpr(ast, node),
                             rastr_binop_rexpr(ast, node));

    case RepeatLoop:
        return lang2_to_sexp(
            ast, rastr_rlp_kw(ast, node), rastr_rlp_body(ast, node));

    case WhileLoop:
        return lang3_to_sexp(ast,
                             rastr_wlp_kw(ast, node),
                             rastr_cnd_expr(ast, rastr_wlp_cond(ast, node)),
                             rastr_wlp_body(ast, node));

    case ForLoop:
        return lang4_to_sexp(ast,
                             rastr_flp_kw(ast, node),
                             rastr_iter_var(ast, rastr_flp_iter(ast, node)),
                             rastr_iter_expr(ast, rastr_flp_iter(ast, node)),
                             rastr_flp_body(ast, node));

    case IfConditional:
        return lang3_to_sexp(ast,
                             rastr_icnd_ikw(ast, node),
                             rastr_cnd_expr(ast, rastr_icnd_cond(ast, node)),
                             rastr_icnd_ibody(ast, node));

    case IfElseConditional:
        return lang4_to_sexp(ast,
                             rastr_iecnd_ikw(ast, node),
                             rastr_cnd_expr(ast, rastr_iecnd_cond(ast, node)),
                             rastr_iecnd_ibody(ast, node),
                             rastr_iecnd_ebody(ast, node));

    case FunctionDefinition:
        return fndefn_to_sexp(ast, node);

    case FunctionCall:
        return fncall_to_sexp(ast, node);

    case Subset:
        return subset_to_sexp(
            ast, rastr_sub_obj(ast, node), rastr_sub_inds(ast, node));

    case Index:
        return subset_to_sexp(
            ast, rastr_idx_obj(ast, node), rastr_idx_inds(ast, node));

    case Program:
        return pgm_to_sexp(ast, node);

    case Delimited:
        return rastr_node_to_sexp(ast, rastr_dlmtd_expr(ast, node));

    case Missing:
        return R_MissingArg;

    case Condition:
    case Iteration:
    case Parameters:
    case Arguments:
    case DefaultParameter:
    case NonDefaultParameter:
    case NamedArgument:
    case PositionalArgument:
    case Error:
    case End:
        rastr_log_error(
            "no equivalent SEXP representation for rastr node of type %s",
            rastr_node_type_to_string(type));
        return R_NilValue;
    }

    rastr_log_error("unexpected node of type '%s'",
                    rastr_node_type_to_string(type));
    return R_NilValue;
}
