#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_unary_operation_expression_r_node_create(SEXP r_op,
                                                          SEXP r_operand);
SEXP r_rastr_ast_unary_operation_expression_r_node_get_operand(SEXP r_node);
SEXP r_rastr_ast_unary_operation_expression_r_node_set_operand(SEXP r_node,
                                                               SEXP r_operand);
}
