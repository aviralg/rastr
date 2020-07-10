#include "r_raw_literal_expression_r_node.h"
#include "RawLiteralExpressionRNode.hpp"

using rastr::ast::RawLiteralExpressionRNode;
using rastr::ast::RawLiteralExpressionRNodeSPtr;

SEXP r_raw_literal_expression_r_node_create(SEXP r_value) {
    Rbyte value = RAW(r_value)[0];

    RawLiteralExpressionRNodeSPtr node =
        std::make_shared<RawLiteralExpressionRNode>(value);

    return RawLiteralExpressionRNode::to_sexp(node);
}

SEXP r_raw_literal_expression_r_node_get_value(SEXP r_node) {
    RawLiteralExpressionRNodeSPtr node =
        RawLiteralExpressionRNode::from_sexp(r_node);

    Rbyte value = node->get_value();

    SEXP r_value = PROTECT(allocVector(RAWSXP, 1));

    RAW(r_value)[0] = value;

    UNPROTECT(1);

    return r_value;
}

SEXP r_raw_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value) {
    RawLiteralExpressionRNodeSPtr node =
        RawLiteralExpressionRNode::from_sexp(r_node);

    Rbyte value = RAW(r_value)[0];

    node->set_value(value);

    return r_node;
}
