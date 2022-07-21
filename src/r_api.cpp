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

rastr_ast_t rastr_ast_from_sexp(SEXP r_ast) {
    rastr_ast_t ast = (rastr_ast_t) rastr_r_externalptr_to_c_pointer(r_ast);
    return ast;
}

void r_rastr_node_destroy(SEXP r_node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) rastr_r_externalptr_to_c_pointer(r_node);
    if (node_ptr == NULL) {
        rastr_log_error("encountered NULL node reference");
    }
    R_ClearExternalPtr(r_node);
    free(node_ptr);
}

SEXP r_rastr_node_to_sexp(rastr_node_t node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t));
    node_ptr->index = node.index;

    SEXP r_node = rastr_c_pointer_to_r_externalptr(
                                                   node_ptr, R_NilValue, R_NilValue, r_rastr_node_destroy);
    PROTECT(r_node);
    rastr_sexp_set_class(r_node, R_RASTR_NODE_CLASS);
    UNPROTECT(1);
    return r_node;
}

rastr_node_t r_rastr_node_from_sexp(SEXP r_node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) rastr_r_externalptr_to_c_pointer(r_node);
    return *node_ptr;
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


SEXP r_rastr_ast_print(SEXP r_ast) {
    return R_NilValue;
}
