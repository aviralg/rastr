#ifndef RASTR_AST_IF_ELSE_CONDITIONAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_IF_ELSE_CONDITIONAL_EXPRESSION_RNODE_HPP

#include "ConditionalExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "ConditionRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IfElseConditionalExpressionRNode
    : public virtual ConditionalExpressionRNode {
  public:
    explicit IfElseConditionalExpressionRNode(
        KeywordRNodeSPtr if_keyword,
        ConditionRNodeSPtr condition,
        ExpressionRNodeSPtr consequent_expression,
        KeywordRNodeSPtr else_keyword,
        ExpressionRNodeSPtr alternative_expression)
        : ConditionalExpressionRNode(condition)
        , if_keyword_(if_keyword)
        , consequent_expression_(consequent_expression)
        , else_keyword_(else_keyword)
        , alternative_expression_(alternative_expression) {
        set_type(Type::IfElseConditionalExpressionRNode);
    }

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

    KeywordRNodeSPtr get_else_keyword() const {
        return else_keyword_;
    }

    void set_else_keyword(KeywordRNodeSPtr else_keyword) {
        else_keyword_ = else_keyword;
    }

    ExpressionRNodeSPtr get_alternative_expression() const {
        return alternative_expression_;
    }

    void
    set_alternative_expression(ExpressionRNodeSPtr alternative_expression) {
        alternative_expression_ = alternative_expression;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    KeywordRNodeSPtr if_keyword_;
    ExpressionRNodeSPtr consequent_expression_;
    KeywordRNodeSPtr else_keyword_;
    ExpressionRNodeSPtr alternative_expression_;

    static SEXP class_;
}; // namespace ast

using IfElseConditionalExpressionRNodeSPtr =
    std::shared_ptr<IfElseConditionalExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_IF_ELSE_CONDITIONAL_EXPRESSION_RNODE_HPP */
