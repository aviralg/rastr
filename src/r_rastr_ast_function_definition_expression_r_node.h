#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_function_definition_expression_r_node_create(
    SEXP r_keyword,
    SEXP r_opening_delimiter,
    SEXP r_parameters,
    SEXP r_closing_delimiter,
    SEXP r_body);
SEXP r_rastr_ast_function_definition_expression_r_node_get_parameters(
    SEXP r_node);
SEXP r_rastr_ast_function_definition_expression_r_node_set_parameters(
    SEXP r_node,
    SEXP r_parameters);
}
