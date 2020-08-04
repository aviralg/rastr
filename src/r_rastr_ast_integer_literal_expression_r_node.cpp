#include "r_rastr_ast_integer_literal_expression_r_node.h"
#include "IntegerLiteralExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::IntegerLiteralExpressionRNode;
using rastr::ast::IntegerLiteralExpressionRNodeSPtr;

SEXP r_rastr_ast_integer_literal_expression_r_node_create(
    SEXP r_value,
    SEXP r_representation) {
    int value = asInteger(r_value);

    const char* representation = CHAR(asChar(r_representation));

    IntegerLiteralExpressionRNodeSPtr node =
        std::make_shared<IntegerLiteralExpressionRNode>(value, representation);

    return to_sexp<IntegerLiteralExpressionRNode>(node);
}

SEXP r_rastr_ast_integer_literal_expression_r_node_get_value(SEXP r_node) {
    IntegerLiteralExpressionRNodeSPtr node =
        from_sexp<IntegerLiteralExpressionRNode>(r_node);

    int value = node->get_value();

    return ScalarInteger(value);
}
