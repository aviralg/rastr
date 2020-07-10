#include "r_double_literal_expression_r_node.h"
#include "DoubleLiteralExpressionRNode.hpp"

using rastr::ast::DoubleLiteralExpressionRNode;
using rastr::ast::DoubleLiteralExpressionRNodeSPtr;

SEXP r_double_literal_expression_r_node_create(SEXP r_value) {
    double value = asReal(r_value);

    DoubleLiteralExpressionRNodeSPtr node =
        std::make_shared<DoubleLiteralExpressionRNode>(value);

    return DoubleLiteralExpressionRNode::to_sexp(node);
}

SEXP r_double_literal_expression_r_node_get_value(SEXP r_node) {
    DoubleLiteralExpressionRNodeSPtr node =
        DoubleLiteralExpressionRNode::from_sexp(r_node);

    double value = node->get_value();

    return ScalarReal(value);
}

SEXP r_double_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value) {
    DoubleLiteralExpressionRNodeSPtr node =
        DoubleLiteralExpressionRNode::from_sexp(r_node);

    double value = asReal(r_value);

    node->set_value(value);

    return r_node;
}
