#include "r_rastr_ast_function_definition_expression_r_node.h"
#include "FunctionDefinitionExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::FunctionDefinitionExpressionRNode;
using rastr::ast::FunctionDefinitionExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_function_definition_expression_r_node_create(
    SEXP r_keyword,
    SEXP r_opening_delimiter,
    SEXP r_parameters,
    SEXP r_closing_delimiter,
    SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionSequenceRNodeSPtr parameters =
        from_sexp<ExpressionSequenceRNode>(r_parameters);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    FunctionDefinitionExpressionRNodeSPtr node =
        std::make_shared<FunctionDefinitionExpressionRNode>(
            keyword, opening_delimiter, parameters, closing_delimiter, body);

    return to_sexp<FunctionDefinitionExpressionRNode>(node);
}

SEXP r_rastr_ast_function_definition_expression_r_node_get_parameters(
    SEXP r_node) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr parameters = node->get_parameters();

    return to_sexp<ExpressionSequenceRNode>(parameters);
}

SEXP r_rastr_ast_function_definition_expression_r_node_set_parameters(
    SEXP r_node,
    SEXP r_parameters) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr parameters =
        from_sexp<ExpressionSequenceRNode>(r_parameters);

    node->set_parameters(parameters);

    return r_node;
}
