#include "r_rastr_ast_repeat_loop_expression_r_node.h"
#include "RepeatLoopExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;
using rastr::ast::RepeatLoopExpressionRNode;
using rastr::ast::RepeatLoopExpressionRNodeSPtr;

SEXP r_rastr_ast_repeat_loop_expression_r_node_create(SEXP r_keyword,
                                                      SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    RepeatLoopExpressionRNodeSPtr node =
        std::make_shared<RepeatLoopExpressionRNode>(keyword, body);

    return to_sexp<RepeatLoopExpressionRNode>(node);
}
