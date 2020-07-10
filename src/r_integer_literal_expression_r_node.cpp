#include "r_integer_literal_expression_r_node.h"
#include "IntegerLiteralExpressionRNode.hpp"

using rastr::ast::IntegerLiteralExpressionRNode;
using rastr::ast::IntegerLiteralExpressionRNodeSPtr;

SEXP r_integer_literal_expression_r_node_create(SEXP r_value) {
    int value = asInteger(r_value);

    IntegerLiteralExpressionRNodeSPtr node =
        std::make_shared<IntegerLiteralExpressionRNode>(value);

    return IntegerLiteralExpressionRNode::to_sexp(node);
}

SEXP r_integer_literal_expression_r_node_get_value(SEXP r_node) {
    IntegerLiteralExpressionRNodeSPtr node =
        IntegerLiteralExpressionRNode::from_sexp(r_node);

    int value = node->get_value();

    return ScalarInteger(value);
}

SEXP r_integer_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value) {
    IntegerLiteralExpressionRNodeSPtr node =
        IntegerLiteralExpressionRNode::from_sexp(r_node);

    int value = asInteger(r_value);

    node->set_value(value);

    return r_node;
}
