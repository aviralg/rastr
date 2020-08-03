#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_if_else_conditional_expression_r_node_create(
    SEXP r_if_keyword,
    SEXP r_condition,
    SEXP r_consequent_expression,
    SEXP r_else_keyword,
    SEXP r_alternative_expression);
SEXP r_rastr_ast_conditional_expression_r_node_get_else_keyword(SEXP r_node);
SEXP r_rastr_ast_conditional_expression_r_node_set_else_keyword(
    SEXP r_node,
    SEXP r_else_keyword);
SEXP r_rastr_ast_conditional_expression_r_node_get_alternative_expression(
    SEXP r_node);
SEXP r_rastr_ast_conditional_expression_r_node_set_alternative_expression(
    SEXP r_node,
    SEXP r_alternative_expression);
}
