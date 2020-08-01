#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_function_call_expression_r_node_create(
    SEXP r_function,
    SEXP r_opening_delimiter,
    SEXP r_arguments,
    SEXP r_closing_delimiter);
SEXP r_rastr_ast_function_call_expression_r_node_get_function(SEXP r_node);
SEXP r_rastr_ast_function_call_expression_r_node_set_function(SEXP r_node,
                                                              SEXP r_function);
SEXP r_rastr_ast_function_call_expression_r_node_get_arguments(SEXP r_node);
SEXP r_rastr_ast_function_call_expression_r_node_set_arguments(
    SEXP r_node,
    SEXP r_arguments);
}
