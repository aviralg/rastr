#include "r_logical_literal_expression_r_node.h"
#include "LogicalLiteralExpressionRNode.hpp"

using rastr::ast::LogicalLiteralExpressionRNode;
using rastr::ast::LogicalLiteralExpressionRNodeSPtr;

SEXP r_logical_literal_expression_r_node_create(SEXP r_value) {
    bool value = asLogical(r_value);

    LogicalLiteralExpressionRNodeSPtr node =
        std::make_shared<LogicalLiteralExpressionRNode>(value);

    return LogicalLiteralExpressionRNode::to_sexp(node);
}

SEXP r_logical_literal_expression_r_node_get_value(SEXP r_node) {
    LogicalLiteralExpressionRNodeSPtr node =
        LogicalLiteralExpressionRNode::from_sexp(r_node);

    bool value = node->get_value();

    return ScalarLogical(value);
}

SEXP r_logical_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value) {
    LogicalLiteralExpressionRNodeSPtr node =
        LogicalLiteralExpressionRNode::from_sexp(r_node);

    bool value = asLogical(r_value);

    node->set_value(value);

    return r_node;
}
