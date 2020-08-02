#include "r_rastr_ast_group_expression_r_node.h"
#include "GroupExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::GroupExpressionRNode;
using rastr::ast::GroupExpressionRNodeSPtr;

SEXP r_rastr_ast_group_expression_r_node_create(SEXP r_opening_delimiter,
                                                SEXP r_body,
                                                SEXP r_closing_delimiter) {
    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    GroupExpressionRNodeSPtr node = std::make_shared<GroupExpressionRNode>(
        opening_delimiter, body, closing_delimiter);

    return to_sexp<GroupExpressionRNode>(node);
}

