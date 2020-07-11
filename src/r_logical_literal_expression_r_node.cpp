#include "r_logical_literal_expression_r_node.h"
#include "LogicalLiteralExpressionRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::LogicalLiteralExpressionRNode;
using rastr::ast::LogicalLiteralExpressionRNodeSPtr;

SEXP r_logical_literal_expression_r_node_create(SEXP r_representation) {
    bool representation = asLogical(r_representation);

    LogicalLiteralExpressionRNodeSPtr node =
        std::make_shared<LogicalLiteralExpressionRNode>(representation);

    return to_sexp<LogicalLiteralExpressionRNode>(node);
}

SEXP r_logical_literal_expression_r_node_get_representation(SEXP r_node) {
    LogicalLiteralExpressionRNodeSPtr node =
        from_sexp<LogicalLiteralExpressionRNode>(r_node);

    bool representation = node->get_representation();

    return ScalarLogical(representation);
}

SEXP r_logical_literal_expression_r_node_set_representation(
    SEXP r_node,
    SEXP r_representation) {
    LogicalLiteralExpressionRNodeSPtr node =
        from_sexp<LogicalLiteralExpressionRNode>(r_node);

    bool representation = asLogical(r_representation);

    node->set_representation(representation);

    return r_node;
}
