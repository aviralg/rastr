#include "r_loop_expression_r_node.h"
#include "LoopExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;
using rastr::ast::LoopExpressionRNode;
using rastr::ast::LoopExpressionRNodeSPtr;

SEXP r_loop_expression_r_node_get_keyword(SEXP r_node) {
    LoopExpressionRNodeSPtr node = from_sexp<LoopExpressionRNode>(r_node);

    KeywordRNodeSPtr keyword = node->get_keyword();

    return to_sexp<KeywordRNode>(keyword);
}

SEXP r_loop_expression_r_node_set_keyword(SEXP r_node, SEXP r_keyword) {
    LoopExpressionRNodeSPtr node = from_sexp<LoopExpressionRNode>(r_node);

    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    node->set_keyword(keyword);

    return r_node;
}

SEXP r_loop_expression_r_node_get_body(SEXP r_node) {
    LoopExpressionRNodeSPtr node = from_sexp<LoopExpressionRNode>(r_node);

    ExpressionRNodeSPtr body = node->get_body();

    return to_sexp(body);
}

SEXP r_loop_expression_r_node_set_body(SEXP r_node, SEXP r_body) {
    LoopExpressionRNodeSPtr node = from_sexp<LoopExpressionRNode>(r_node);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    node->set_body(body);

    return r_node;
}
