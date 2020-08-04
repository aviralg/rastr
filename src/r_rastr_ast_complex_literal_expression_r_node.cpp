#include "r_rastr_ast_complex_literal_expression_r_node.h"
#include "ComplexLiteralExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ComplexLiteralExpressionRNode;
using rastr::ast::ComplexLiteralExpressionRNodeSPtr;

SEXP r_rastr_ast_complex_literal_expression_r_node_create(
    SEXP r_value,
    SEXP r_representation) {
    Rcomplex value = COMPLEX(r_value)[0];

    const char* representation = CHAR(asChar(r_representation));

    ComplexLiteralExpressionRNodeSPtr node =
        std::make_shared<ComplexLiteralExpressionRNode>(value, representation);

    return to_sexp<ComplexLiteralExpressionRNode>(node);
}

SEXP r_rastr_ast_complex_literal_expression_r_node_get_value(SEXP r_node) {
    ComplexLiteralExpressionRNodeSPtr node =
        from_sexp<ComplexLiteralExpressionRNode>(r_node);

    const Rcomplex& value = node->get_value();

    SEXP r_value = PROTECT(allocVector(CPLXSXP, 1));

    COMPLEX(r_value)[0].r = value.r;
    COMPLEX(r_value)[0].i = value.i;

    UNPROTECT(1);

    return r_value;
}
