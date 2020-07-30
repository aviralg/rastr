#ifndef RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP

#include "ICondition.hpp"
#include "ExpressionRNode.hpp"
#include "KeywordRNode.hpp"

namespace rastr {
namespace ast {

class ConditionalExpressionRNode
    : public ExpressionRNode
    , public ICondition {
  public:
    explicit ConditionalExpressionRNode(
        KeywordRNodeSPtr if_keyword,
        ConditionRNodeSPtr condition,
        ExpressionRNodeSPtr consequent_expression)
        : ExpressionRNode()
        , ICondition(condition)
        , if_keyword_(if_keyword)
        , consequent_expression_(consequent_expression) {
    }

    virtual ~ConditionalExpressionRNode() = default;

    KeywordRNodeSPtr get_if_keyword() const {
        return if_keyword_;
    }

    void set_if_keyword(KeywordRNodeSPtr if_keyword) {
        if_keyword_ = if_keyword;
    }

    ExpressionRNodeSPtr get_consequent_expression() const {
        return consequent_expression_;
    }

    void set_consequent_expression(ExpressionRNodeSPtr consequent_expression) {
        consequent_expression_ = consequent_expression;
    }

  private:
    KeywordRNodeSPtr if_keyword_;
    ExpressionRNodeSPtr consequent_expression_;
}; // namespace ast

using ConditionalExpressionRNodeSPtr =
    std::shared_ptr<ConditionalExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP */
