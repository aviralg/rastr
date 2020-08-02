#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_conditional_expression_r_node_get_if_keyword(SEXP r_node);
SEXP r_rastr_ast_conditional_expression_r_node_set_if_keyword(
    SEXP r_node,
    SEXP r_if_keyword);
SEXP r_rastr_ast_conditional_expression_r_node_get_consequent_expression(
    SEXP r_node);
SEXP r_rastr_ast_conditional_expression_r_node_set_consequent_expression(
    SEXP r_node,
    SEXP r_consequent_expression);
}
