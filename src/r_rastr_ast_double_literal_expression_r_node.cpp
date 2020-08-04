#include "r_rastr_ast_double_literal_expression_r_node.h"
#include "DoubleLiteralExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DoubleLiteralExpressionRNode;
using rastr::ast::DoubleLiteralExpressionRNodeSPtr;

SEXP r_rastr_ast_double_literal_expression_r_node_create(
    SEXP r_value,
    SEXP r_representation) {
    double value = asReal(r_value);

    const char* representation = CHAR(asChar(r_representation));

    DoubleLiteralExpressionRNodeSPtr node =
        std::make_shared<DoubleLiteralExpressionRNode>(value, representation);

    return to_sexp<DoubleLiteralExpressionRNode>(node);
}

SEXP r_rastr_ast_double_literal_expression_r_node_get_value(SEXP r_node) {
    DoubleLiteralExpressionRNodeSPtr node =
        from_sexp<DoubleLiteralExpressionRNode>(r_node);

    double value = node->get_value();

    return ScalarReal(value);
}
