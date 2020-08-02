#include "r_rastr_ast_for_loop_expression_r_node.h"
#include "ForLoopExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ConditionRNode;
using rastr::ast::ConditionRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ForLoopExpressionRNode;
using rastr::ast::ForLoopExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_for_loop_expression_r_node_create(SEXP r_keyword,
                                                   SEXP r_condition,
                                                   SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    ConditionRNodeSPtr condition = from_sexp<ConditionRNode>(r_condition);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    ForLoopExpressionRNodeSPtr node =
        std::make_shared<ForLoopExpressionRNode>(keyword, condition, body);

    return to_sexp<ForLoopExpressionRNode>(node);
}
