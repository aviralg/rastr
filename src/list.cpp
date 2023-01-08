#include <rastr/api.h>
#include "interop.h"
#include <vector>
#include "r_api.h"
#include <string>
#include "internal_api.h"

SEXP rastr_to_list(rastr_ast_t ast, rastr_node_t node) {
    return R_NilValue;
}

SEXP r_rastr_to_list(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    return rastr_to_list(ast, node);
}
