#include "r_rastr_ast_binary_operation_expression_r_node.h"
#include "BinaryOperationExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BinaryOperationExpressionRNode;
using rastr::ast::BinaryOperationExpressionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;

SEXP r_rastr_ast_binary_operation_expression_r_node_create(
    SEXP r_op,
    SEXP r_first_operand,
    SEXP r_second_operand) {
    OperatorRNodeSPtr op = from_sexp<OperatorRNode>(r_op);

    ExpressionRNodeSPtr first_operand =
        from_sexp<ExpressionRNode>(r_first_operand);

    ExpressionRNodeSPtr second_operand =
        from_sexp<ExpressionRNode>(r_second_operand);

    BinaryOperationExpressionRNodeSPtr node =
        std::make_shared<BinaryOperationExpressionRNode>(
            op, first_operand, second_operand);

    return to_sexp<BinaryOperationExpressionRNode>(node);
}

SEXP r_rastr_ast_binary_operation_expression_r_node_get_first_operand(
    SEXP r_node) {
    BinaryOperationExpressionRNodeSPtr node =
        from_sexp<BinaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = node->get_first_operand();

    return to_sexp<ExpressionRNode>(operand);
}

SEXP r_rastr_ast_binary_operation_expression_r_node_set_first_operand(
    SEXP r_node,
    SEXP r_operand) {
    BinaryOperationExpressionRNodeSPtr node =
        from_sexp<BinaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = from_sexp<ExpressionRNode>(r_operand);

    node->set_first_operand(operand);

    return r_node;
}

SEXP r_rastr_ast_binary_operation_expression_r_node_get_second_operand(
    SEXP r_node) {
    BinaryOperationExpressionRNodeSPtr node =
        from_sexp<BinaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = node->get_second_operand();

    return to_sexp<ExpressionRNode>(operand);
}

SEXP r_rastr_ast_binary_operation_expression_r_node_set_second_operand(
    SEXP r_node,
    SEXP r_operand) {
    BinaryOperationExpressionRNodeSPtr node =
        from_sexp<BinaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = from_sexp<ExpressionRNode>(r_operand);

    node->set_second_operand(operand);

    return r_node;
}
