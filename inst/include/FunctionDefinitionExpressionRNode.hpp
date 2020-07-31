#ifndef RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP
#define RASTR_AST_FUNCTION_DEFINITION_EXPRESSION_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"
#include "IKeyword.hpp"
#include "IBody.hpp"
#include "IBounded.hpp"

namespace rastr {
namespace ast {

class FunctionDefinitionExpressionRNode
    : public ExpressionRNode
    , public IKeyword
    , public IBounded
    , public IBody {
  public:
    explicit FunctionDefinitionExpressionRNode(
        KeywordRNodeSPtr keyword,
        DelimiterRNodeSPtr opening_delimiter,
        ExpressionSequenceRNodeSPtr parameters,
        DelimiterRNodeSPtr closing_delimiter,
        ExpressionRNodeSPtr body)
        : ExpressionRNode(Type::FunctionDefinitionExpressionRNode)
        , IKeyword(keyword)
        , IBounded(opening_delimiter, closing_delimiter)
        , IBody(body)
        , parameters_(parameters) {
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
