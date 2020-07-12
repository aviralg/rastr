#ifndef RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP
#define RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP

#include "ParameterSequenceRNode.hpp"
#include "KeywordRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class FunctionDefinitionExpressionRNode: public virtual ExpressionRNode {
  public:
    explicit FunctionDefinitionExpressionRNode(
        KeywordRNodeSPtr keyword,
        ParameterSequenceRNodeSPtr parameters,
        ExpressionRNodeSPtr body)
        : ExpressionRNode()
        , keyword_(keyword)
        , parameters_(parameters)
        , body_(body) {
        set_type(Type::FunctionDefinitionExpressionRNode);
    }

    KeywordRNodeSPtr get_keyword() const {
        return keyword_;
    }

    void set_keyword(KeywordRNodeSPtr keyword) {
        keyword_ = keyword;
    }

    ParameterSequenceRNodeSPtr get_parameters() const {
        return parameters_;
    }

    void set_parameters(ParameterSequenceRNodeSPtr parameters) {
        parameters_ = parameters;
    }

    ExpressionRNodeSPtr get_body() const {
        return body_;
    }

    void set_body(ExpressionRNodeSPtr body) {
        body_ = body;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    KeywordRNodeSPtr keyword_;
    ParameterSequenceRNodeSPtr parameters_;
    ExpressionRNodeSPtr body_;

    static SEXP class_;
}; // namespace ast

using FunctionDefinitionExpressionRNodeSPtr =
    std::shared_ptr<FunctionDefinitionExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP */
