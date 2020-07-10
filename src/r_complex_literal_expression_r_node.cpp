#include "r_complex_literal_expression_r_node.h"
#include "ComplexLiteralExpressionRNode.hpp"

using rastr::ast::ComplexLiteralExpressionRNode;
using rastr::ast::ComplexLiteralExpressionRNodeSPtr;

SEXP r_complex_literal_expression_r_node_create(SEXP r_value) {
    Rcomplex value = COMPLEX(r_value)[0];

    ComplexLiteralExpressionRNodeSPtr node =
        std::make_shared<ComplexLiteralExpressionRNode>(value);

    return ComplexLiteralExpressionRNode::to_sexp(node);
}

SEXP r_complex_literal_expression_r_node_get_value(SEXP r_node) {
    ComplexLiteralExpressionRNodeSPtr node =
        ComplexLiteralExpressionRNode::from_sexp(r_node);

    const Rcomplex& value = node->get_value();

    SEXP r_value = PROTECT(allocVector(CPLXSXP, 1));

    COMPLEX(r_value)[0].r = value.r;
    COMPLEX(r_value)[0].i = value.i;

    UNPROTECT(1);

    return r_value;
}

SEXP r_complex_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value) {
    ComplexLiteralExpressionRNodeSPtr node =
        ComplexLiteralExpressionRNode::from_sexp(r_node);

    Rcomplex value = COMPLEX(r_value)[0];

    node->set_value(value);

    return r_node;
}
