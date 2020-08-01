#include "RIncludes.hpp"

extern "C" {

SEXP r_rastr_ast_binary_operation_expression_r_node_create(
    SEXP r_op,
    SEXP r_first_operand,
    SEXP r_second_operand);

SEXP r_rastr_ast_binary_operation_expression_r_node_get_first_operand(
    SEXP r_node);

SEXP r_rastr_ast_binary_operation_expression_r_node_set_first_operand(
    SEXP r_node,
    SEXP r_operand);

SEXP r_rastr_ast_binary_operation_expression_r_node_get_second_operand(
    SEXP r_node);

SEXP r_rastr_ast_binary_operation_expression_r_node_set_second_operand(
    SEXP r_node,
    SEXP r_operand);
}
