#include "r_rastr_ast_expression_condition_r_node.h"
#include "ExpressionConditionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionConditionRNode;
using rastr::ast::ExpressionConditionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;

SEXP r_rastr_ast_expression_condition_r_node_create(SEXP r_opening_delimiter,
                                                    SEXP r_expression,
                                                    SEXP r_closing_delimiter) {
    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionRNodeSPtr expression = from_sexp<ExpressionRNode>(r_expression);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    ExpressionConditionRNodeSPtr node =
        std::make_shared<ExpressionConditionRNode>(
            opening_delimiter, expression, closing_delimiter);

    return to_sexp<ExpressionConditionRNode>(node);
}
