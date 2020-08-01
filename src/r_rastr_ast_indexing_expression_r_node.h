#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_indexing_expression_r_node_create(
    SEXP r_object,
    SEXP r_opening_delimiter,
    SEXP r_indices,
    SEXP r_first_closing_delimiter,
    SEXP r_second_closing_delimiter);
SEXP r_rastr_ast_indexing_expression_r_node_get_opening_delimiter(SEXP r_node);
SEXP r_rastr_ast_indexing_expression_r_node_set_opening_delimiter(
    SEXP r_node,
    SEXP r_opening_delimiter);
SEXP r_rastr_ast_indexing_expression_r_node_get_first_closing_delimiter(
    SEXP r_node);
SEXP r_rastr_ast_indexing_expression_r_node_set_first_closing_delimiter(
    SEXP r_node,
    SEXP r_first_closing_delimiter);

SEXP r_rastr_ast_indexing_expression_r_node_get_second_closing_delimiter(
    SEXP r_node);
SEXP r_rastr_ast_indexing_expression_r_node_set_second_closing_delimiter(
    SEXP r_node,
    SEXP r_second_closing_delimiter);

SEXP r_rastr_ast_indexing_expression_r_node_set_delimiters(
    SEXP r_node,
    SEXP r_opening_delimiter,
    SEXP r_first_closing_delimiter,
    SEXP r_second_closing_delimiter);
}
