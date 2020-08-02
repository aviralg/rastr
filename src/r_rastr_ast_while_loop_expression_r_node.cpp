#include "r_rastr_ast_while_loop_expression_r_node.h"
#include "WhileLoopExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ConditionRNode;
using rastr::ast::ConditionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;
using rastr::ast::WhileLoopExpressionRNode;
using rastr::ast::WhileLoopExpressionRNodeSPtr;

SEXP r_rastr_ast_while_loop_expression_r_node_create(SEXP r_keyword,
                                                     SEXP r_condition,
                                                     SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    ConditionRNodeSPtr condition = from_sexp<ConditionRNode>(r_condition);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    WhileLoopExpressionRNodeSPtr node =
        std::make_shared<WhileLoopExpressionRNode>(keyword, condition, body);

    return to_sexp<WhileLoopExpressionRNode>(node);
}
