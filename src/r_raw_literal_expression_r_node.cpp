#include "r_raw_literal_expression_r_node.h"
#include "RawLiteralExpressionRNode.hpp"

using rastr::ast::RawLiteralExpressionRNode;
using rastr::ast::RawLiteralExpressionRNodeSPtr;

SEXP r_raw_literal_expression_r_node_create(SEXP r_representation) {
    Rbyte representation = RAW(r_representation)[0];

    RawLiteralExpressionRNodeSPtr node =
        std::make_shared<RawLiteralExpressionRNode>(representation);

    return RawLiteralExpressionRNode::to_sexp(node);
}

SEXP r_raw_literal_expression_r_node_get_representation(SEXP r_node) {
    RawLiteralExpressionRNodeSPtr node =
        RawLiteralExpressionRNode::from_sexp(r_node);

    Rbyte representation = node->get_representation();

    SEXP r_representation = PROTECT(allocVector(RAWSXP, 1));

    RAW(r_representation)[0] = representation;

    UNPROTECT(1);

    return r_representation;
}

SEXP r_raw_literal_expression_r_node_set_representation(SEXP r_node,
                                                        SEXP r_representation) {
    RawLiteralExpressionRNodeSPtr node =
        RawLiteralExpressionRNode::from_sexp(r_node);

    Rbyte representation = RAW(r_representation)[0];

    node->set_representation(representation);

    return r_node;
}
