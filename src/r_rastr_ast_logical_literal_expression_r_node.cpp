#include "r_rastr_ast_logical_literal_expression_r_node.h"
#include "LogicalLiteralExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::LogicalLiteralExpressionRNode;
using rastr::ast::LogicalLiteralExpressionRNodeSPtr;

SEXP r_rastr_ast_logical_literal_expression_r_node_create(
    SEXP r_value,
    SEXP r_representation) {
    int value = asLogical(r_value);

    const char* representation = CHAR(asChar(r_representation));

    LogicalLiteralExpressionRNodeSPtr node =
        std::make_shared<LogicalLiteralExpressionRNode>(value, representation);

    return to_sexp<LogicalLiteralExpressionRNode>(node);
}

SEXP r_rastr_ast_logical_literal_expression_r_node_get_value(SEXP r_node) {
    LogicalLiteralExpressionRNodeSPtr node =
        from_sexp<LogicalLiteralExpressionRNode>(r_node);

    int value = node->get_value();

    return ScalarLogical(value);
}
