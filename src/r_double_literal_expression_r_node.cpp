#include "r_double_literal_expression_r_node.h"
#include "DoubleLiteralExpressionRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::DoubleLiteralExpressionRNode;
using rastr::ast::DoubleLiteralExpressionRNodeSPtr;

SEXP r_double_literal_expression_r_node_create(SEXP r_representation) {
    double representation = asReal(r_representation);

    DoubleLiteralExpressionRNodeSPtr node =
        std::make_shared<DoubleLiteralExpressionRNode>(representation);

    return to_sexp<DoubleLiteralExpressionRNode>(node);
}

SEXP r_double_literal_expression_r_node_get_representation(SEXP r_node) {
    DoubleLiteralExpressionRNodeSPtr node =
        from_sexp<DoubleLiteralExpressionRNode>(r_node);

    double representation = node->get_representation();

    return ScalarReal(representation);
}

SEXP r_double_literal_expression_r_node_set_representation(
    SEXP r_node,
    SEXP r_representation) {
    DoubleLiteralExpressionRNodeSPtr node =
        from_sexp<DoubleLiteralExpressionRNode>(r_node);

    double representation = asReal(r_representation);

    node->set_representation(representation);

    return r_node;
}
