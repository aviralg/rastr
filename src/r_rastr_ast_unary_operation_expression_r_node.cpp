#include "r_rastr_ast_unary_operation_expression_r_node.h"
#include "UnaryOperationExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;
using rastr::ast::UnaryOperationExpressionRNode;
using rastr::ast::UnaryOperationExpressionRNodeSPtr;

SEXP r_rastr_ast_unary_operation_expression_r_node_create(SEXP r_op,
                                                          SEXP r_operand) {
    OperatorRNodeSPtr op = from_sexp<OperatorRNode>(r_op);

    ExpressionRNodeSPtr operand = from_sexp<ExpressionRNode>(r_operand);

    UnaryOperationExpressionRNodeSPtr node =
        std::make_shared<UnaryOperationExpressionRNode>(op, operand);

    return to_sexp<UnaryOperationExpressionRNode>(node);
}

SEXP r_rastr_ast_unary_operation_expression_r_node_get_operand(SEXP r_node) {
    UnaryOperationExpressionRNodeSPtr node =
        from_sexp<UnaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = node->get_operand();

    return to_sexp<ExpressionRNode>(operand);
}

SEXP r_rastr_ast_unary_operation_expression_r_node_set_operand(SEXP r_node,
                                                               SEXP r_operand) {
    UnaryOperationExpressionRNodeSPtr node =
        from_sexp<UnaryOperationExpressionRNode>(r_node);

    ExpressionRNodeSPtr operand = from_sexp<ExpressionRNode>(r_operand);

    node->set_operand(operand);

    return r_node;
}
