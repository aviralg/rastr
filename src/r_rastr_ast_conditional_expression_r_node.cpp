#include "r_rastr_ast_conditional_expression_r_node.h"
#include "ConditionalExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ConditionalExpressionRNode;
using rastr::ast::ConditionalExpressionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_conditional_expression_r_node_get_if_keyword(SEXP r_node) {
    ConditionalExpressionRNodeSPtr node =
        from_sexp<ConditionalExpressionRNode>(r_node);

    KeywordRNodeSPtr if_keyword = node->get_if_keyword();

    return to_sexp<KeywordRNode>(if_keyword);
}

SEXP r_rastr_ast_conditional_expression_r_node_set_if_keyword(
    SEXP r_node,
    SEXP r_if_keyword) {
    ConditionalExpressionRNodeSPtr node =
        from_sexp<ConditionalExpressionRNode>(r_node);

    KeywordRNodeSPtr if_keyword = from_sexp<KeywordRNode>(r_if_keyword);

    node->set_if_keyword(if_keyword);

    return r_node;
}

SEXP r_rastr_ast_conditional_expression_r_node_get_consequent_expression(
    SEXP r_node) {
    ConditionalExpressionRNodeSPtr node =
        from_sexp<ConditionalExpressionRNode>(r_node);

    ExpressionRNodeSPtr consequent_expression =
        node->get_consequent_expression();

    return to_sexp(consequent_expression);
}

SEXP r_rastr_ast_conditional_expression_r_node_set_consequent_expression(
    SEXP r_node,
    SEXP r_consequent_expression) {
    ConditionalExpressionRNodeSPtr node =
        from_sexp<ConditionalExpressionRNode>(r_node);

    ExpressionRNodeSPtr consequent_expression =
        from_sexp<ExpressionRNode>(r_consequent_expression);

    node->set_consequent_expression(consequent_expression);

    return r_node;
}
