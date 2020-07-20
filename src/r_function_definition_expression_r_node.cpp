#include "r_function_definition_expression_r_node.h"
#include "FunctionDefinitionExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::FunctionDefinitionExpressionRNode;
using rastr::ast::FunctionDefinitionExpressionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_function_definition_expression_r_node_create(SEXP r_keyword,
                                                    SEXP r_parameters,
                                                    SEXP r_body) {
    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    ExpressionSequenceRNodeSPtr parameters =
        from_sexp<ExpressionSequenceRNode>(r_parameters);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    FunctionDefinitionExpressionRNodeSPtr node =
        std::make_shared<FunctionDefinitionExpressionRNode>(
            keyword, parameters, body);

    return to_sexp<FunctionDefinitionExpressionRNode>(node);
}

SEXP r_function_definition_expression_r_node_get_keyword(SEXP r_node) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    KeywordRNodeSPtr keyword = node->get_keyword();

    return to_sexp<KeywordRNode>(keyword);
}

SEXP r_function_definition_expression_r_node_set_keyword(SEXP r_node,
                                                         SEXP r_keyword) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    node->set_keyword(keyword);

    return r_node;
}

SEXP r_function_definition_expression_r_node_get_body(SEXP r_node) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionRNodeSPtr body = node->get_body();

    return to_sexp(body);
}

SEXP r_function_definition_expression_r_node_set_body(SEXP r_node,
                                                      SEXP r_body) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    node->set_body(body);

    return r_node;
}

SEXP r_function_definition_expression_r_node_get_parameters(SEXP r_node) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr parameters = node->get_parameters();

    return to_sexp<ExpressionSequenceRNode>(parameters);
}

SEXP r_function_definition_expression_r_node_set_parameters(SEXP r_node,
                                                            SEXP r_parameters) {
    FunctionDefinitionExpressionRNodeSPtr node =
        from_sexp<FunctionDefinitionExpressionRNode>(r_node);

    ExpressionSequenceRNodeSPtr parameters =
        from_sexp<ExpressionSequenceRNode>(r_parameters);

    node->set_parameters(parameters);

    return r_node;
}
