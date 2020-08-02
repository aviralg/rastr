#include "r_rastr_ast_for_loop_expression_r_node.h"
#include "ForLoopExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ForLoopExpressionRNode;
using rastr::ast::ForLoopExpressionRNodeSPtr;
using rastr::ast::InConditionRNode;
using rastr::ast::InConditionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_for_loop_expression_r_node_create(SEXP r_keyword,
                                                   SEXP r_condition,
                                                   SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    InConditionRNodeSPtr condition = from_sexp<InConditionRNode>(r_condition);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    ForLoopExpressionRNodeSPtr node =
        std::make_shared<ForLoopExpressionRNode>(keyword, condition, body);

    return to_sexp<ForLoopExpressionRNode>(node);
}

SEXP r_rastr_ast_for_loop_expression_get_condition(SEXP r_node) {
    ForLoopExpressionRNodeSPtr node = from_sexp<ForLoopExpressionRNode>(r_node);

    InConditionRNodeSPtr condition = node->get_condition();

    return to_sexp<InConditionRNode>(condition);
}

SEXP r_rastr_ast_for_loop_expression_set_condition(SEXP r_node,
                                                   SEXP r_condition) {
    ForLoopExpressionRNodeSPtr node = from_sexp<ForLoopExpressionRNode>(r_node);

    InConditionRNodeSPtr condition = from_sexp<InConditionRNode>(r_condition);

    node->set_condition(condition);

    return r_node;
}
