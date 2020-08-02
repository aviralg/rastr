#include "r_rastr_ast_if_conditional_expression_r_node.h"
#include "IfConditionalExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionConditionRNode;
using rastr::ast::ExpressionConditionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::IfConditionalExpressionRNode;
using rastr::ast::IfConditionalExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_if_conditional_expression_r_node_create(
    SEXP r_if_keyword,
    SEXP r_condition,
    SEXP r_consequent_expression) {
    KeywordRNodeSPtr if_keyword = from_sexp<KeywordRNode>(r_if_keyword);

    ExpressionConditionRNodeSPtr condition =
        from_sexp<ExpressionConditionRNode>(r_condition);

    ExpressionRNodeSPtr consequent_expression =
        from_sexp<ExpressionRNode>(r_consequent_expression);

    IfConditionalExpressionRNodeSPtr node =
        std::make_shared<IfConditionalExpressionRNode>(
            if_keyword, condition, consequent_expression);

    return to_sexp<IfConditionalExpressionRNode>(node);
}
