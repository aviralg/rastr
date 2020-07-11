#include "r_integer_literal_expression_r_node.h"
#include "IntegerLiteralExpressionRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::IntegerLiteralExpressionRNode;
using rastr::ast::IntegerLiteralExpressionRNodeSPtr;

SEXP r_integer_literal_expression_r_node_create(SEXP r_representation) {
    int representation = asInteger(r_representation);

    IntegerLiteralExpressionRNodeSPtr node =
        std::make_shared<IntegerLiteralExpressionRNode>(representation);

    return to_sexp<IntegerLiteralExpressionRNode>(node);
}

SEXP r_integer_literal_expression_r_node_get_representation(SEXP r_node) {
    IntegerLiteralExpressionRNodeSPtr node =
        from_sexp<IntegerLiteralExpressionRNode>(r_node);

    int representation = node->get_representation();

    return ScalarInteger(representation);
}

SEXP r_integer_literal_expression_r_node_set_representation(
    SEXP r_node,
    SEXP r_representation) {
    IntegerLiteralExpressionRNodeSPtr node =
        from_sexp<IntegerLiteralExpressionRNode>(r_node);

    int representation = asInteger(r_representation);

    node->set_representation(representation);

    return r_node;
}
