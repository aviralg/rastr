#ifndef RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP
#define RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"
#include "IKeyword.hpp"
#include "IBody.hpp"

namespace rastr {
namespace ast {

class FunctionDefinitionExpressionRNode
    : public ExpressionRNode
    , public IKeyword
    , public IBody {
  public:
    explicit FunctionDefinitionExpressionRNode(
        KeywordRNodeSPtr keyword,
        ExpressionSequenceRNodeSPtr parameters,
        ExpressionRNodeSPtr body)
        : ExpressionRNode()
        , IKeyword(keyword)
        , IBody(body)
        , parameters_(parameters) {
        set_type(Type::FunctionDefinitionExpressionRNode);
    }

    ExpressionSequenceRNodeSPtr get_parameters() const {
        return parameters_;
    }

    void set_parameters(ExpressionSequenceRNodeSPtr parameters) {
        parameters_ = parameters;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionSequenceRNodeSPtr parameters_;

    static SEXP class_;
}; // namespace ast

using FunctionDefinitionExpressionRNodeSPtr =
    std::shared_ptr<FunctionDefinitionExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP */
