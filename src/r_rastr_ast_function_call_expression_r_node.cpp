#include "r_rastr_ast_function_call_expression_r_node.h"
#include "FunctionCallExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::FunctionCallExpressionRNode;
using rastr::ast::FunctionCallExpressionRNodeSPtr;

SEXP r_rastr_ast_function_call_expression_r_node_create(
    SEXP r_function,
    SEXP r_opening_delimiter,
    SEXP r_arguments,
    SEXP r_closing_delimiter) {
    ExpressionRNodeSPtr function = from_sexp<ExpressionRNode>(r_function);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionSequenceRNodeSPtr arguments =
        from_sexp<ExpressionSequenceRNode>(r_arguments);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    FunctionCallExpressionRNodeSPtr node =
        std::make_shared<FunctionCallExpressionRNode>(
            function, opening_delimiter, arguments, closing_delimiter);

    return to_sexp<FunctionCallExpressionRNode>(node);
}

SEXP r_rastr_ast_function_call_expression_r_node_get_function(SEXP r_node) {
    FunctionCallExpressionRNodeSPtr node =
        from_sexp<FunctionCallExpressionRNode>(r_node);

    ExpressionRNodeSPtr function = node->get_function();

    return to_sexp<ExpressionRNode>(function);
}

SEXP r_rastr_ast_function_call_expression_r_node_set_function(SEXP r_node,
                                                              SEXP r_function) {
    FunctionCallExpressionRNodeSPtr node =
        from_sexp<FunctionCallExpressionRNode>(r_node);

    ExpressionRNodeSPtr function = from_sexp<ExpressionRNode>(r_function);

    node->set_function(function);

    return r_node;
}

SEXP r_rastr_ast_function_call_expression_r_node_get_arguments(SEXP r_node) {
    FunctionCallExpressionRNodeSPtr node =
        from_sexp<FunctionCallExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr arguments = node->get_arguments();

    return to_sexp<ExpressionSequenceRNode>(arguments);
}

SEXP r_rastr_ast_function_call_expression_r_node_set_arguments(
    SEXP r_node,
    SEXP r_arguments) {
    FunctionCallExpressionRNodeSPtr node =
        from_sexp<FunctionCallExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr arguments =
        from_sexp<ExpressionSequenceRNode>(r_arguments);

    node->set_arguments(arguments);

    return r_node;
}
