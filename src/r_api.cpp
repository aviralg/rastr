#include <rastr/api.h>
#include "utilities.h"
#include "interop.h"

SEXP R_RASTR_AST_CLASS = R_NilValue;
SEXP R_RASTR_NODE_CLASS = R_NilValue;

void r_rastr_ast_destroy(SEXP r_ast) {
    rastr_ast_t ast = (rastr_ast_t) rastr_r_externalptr_to_c_pointer(r_ast);
    if (ast == NULL) {
        rastr_log_error("encountered NULL ast reference");
    }
    R_ClearExternalPtr(r_ast);
    rastr_ast_destroy(ast);
}

SEXP r_rastr_ast_to_sexp(rastr_ast_t ast) {
    SEXP r_ast = rastr_c_pointer_to_r_externalptr(
        ast, R_NilValue, R_NilValue, r_rastr_ast_destroy);
    PROTECT(r_ast);
    rastr_sexp_set_class(r_ast, R_RASTR_AST_CLASS);
    UNPROTECT(1);
    return r_ast;
}

rastr_ast_t r_rastr_ast_from_sexp(SEXP r_ast) {
    rastr_ast_t ast = (rastr_ast_t) rastr_r_externalptr_to_c_pointer(r_ast);
    return ast;
}

SEXP r_rastr_initialize(SEXP r_pack_env) {
    R_RASTR_AST_CLASS = rastr_c_string_to_r_character("rastr_ast");
    rastr_sexp_acquire(R_RASTR_AST_CLASS);
    R_RASTR_NODE_CLASS = rastr_c_string_to_r_character("rastr_node");
    rastr_sexp_acquire(R_RASTR_NODE_CLASS);
    return R_NilValue;
}

SEXP r_rastr_finalize(SEXP r_pack_env) {
    rastr_sexp_release(R_RASTR_AST_CLASS);
    rastr_sexp_release(R_RASTR_NODE_CLASS);
    return R_NilValue;
}

SEXP r_rastr_parse_file(SEXP r_filepath) {
    SEXPTYPE type = TYPEOF(r_filepath);

    if (type != STRSXP) {
        Rf_error("expected a filepath of type string, received a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_filepath);

    if (length != 1) {
        Rf_error("expected a filepath string of size 1, received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_filepath, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ instead");
        return R_NilValue;
    }

    const char* filepath = CHAR(str_elt);

    if (!file_exists(filepath)) {
        Rf_error("failed to open file '%s'", filepath);
        return R_NilValue;
    }

    rastr_ast_t ast = rastr_parse_file(CHAR(str_elt));

    return r_rastr_ast_to_sexp(ast);
}

SEXP r_rastr_parse_str(SEXP r_string) {
    SEXPTYPE type = TYPEOF(r_string);

    if (type != STRSXP) {
        Rf_error("expected a value of type string, received a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_string);

    if (length != 1) {
        Rf_error("expected a string vector of size 1, received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_string, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ instead");
        return R_NilValue;
    }

    rastr_ast_t ast = rastr_parse_str(CHAR(str_elt));

    return r_rastr_ast_to_sexp(ast);
}

SEXP r_rastr_ast_print(SEXP r_ast) {
    return R_NilValue;
}
