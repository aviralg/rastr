#include "r_rastr_ast_if_else_conditional_expression_r_node.h"
#include "IfElseConditionalExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionConditionRNode;
using rastr::ast::ExpressionConditionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::IfElseConditionalExpressionRNode;
using rastr::ast::IfElseConditionalExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_if_else_conditional_expression_r_node_create(
    SEXP r_if_keyword,
    SEXP r_condition,
    SEXP r_consequent_expression,
    SEXP r_else_keyword,
    SEXP r_alternative_expression) {
    KeywordRNodeSPtr if_keyword = from_sexp<KeywordRNode>(r_if_keyword);

    ExpressionConditionRNodeSPtr condition =
        from_sexp<ExpressionConditionRNode>(r_condition);

    ExpressionRNodeSPtr consequent_expression =
        from_sexp<ExpressionRNode>(r_consequent_expression);

    KeywordRNodeSPtr else_keyword = from_sexp<KeywordRNode>(r_else_keyword);

    ExpressionRNodeSPtr alternative_expression =
        from_sexp<ExpressionRNode>(r_alternative_expression);

    IfElseConditionalExpressionRNodeSPtr node =
        std::make_shared<IfElseConditionalExpressionRNode>(
            if_keyword,
            condition,
            consequent_expression,
            else_keyword,
            alternative_expression);

    return to_sexp<IfElseConditionalExpressionRNode>(node);
}

SEXP r_rastr_ast_conditional_expression_r_node_get_else_keyword(SEXP r_node) {
    IfElseConditionalExpressionRNodeSPtr node =
        from_sexp<IfElseConditionalExpressionRNode>(r_node);

    KeywordRNodeSPtr else_keyword = node->get_else_keyword();

    return to_sexp<KeywordRNode>(else_keyword);
}

SEXP r_rastr_ast_conditional_expression_r_node_set_else_keyword(
    SEXP r_node,
    SEXP r_else_keyword) {
    IfElseConditionalExpressionRNodeSPtr node =
        from_sexp<IfElseConditionalExpressionRNode>(r_node);

    KeywordRNodeSPtr else_keyword = from_sexp<KeywordRNode>(r_else_keyword);

    node->set_else_keyword(else_keyword);

    return r_node;
}

SEXP r_rastr_ast_conditional_expression_r_node_get_alternative_expression(
    SEXP r_node) {
    IfElseConditionalExpressionRNodeSPtr node =
        from_sexp<IfElseConditionalExpressionRNode>(r_node);

    ExpressionRNodeSPtr alternative_expression =
        node->get_alternative_expression();

    return to_sexp(alternative_expression);
}

SEXP r_rastr_ast_conditional_expression_r_node_set_alternative_expression(
    SEXP r_node,
    SEXP r_alternative_expression) {
    IfElseConditionalExpressionRNodeSPtr node =
        from_sexp<IfElseConditionalExpressionRNode>(r_node);

    ExpressionRNodeSPtr alternative_expression =
        from_sexp<ExpressionRNode>(r_alternative_expression);

    node->set_alternative_expression(alternative_expression);

    return r_node;
}
