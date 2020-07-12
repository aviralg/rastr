#ifndef RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP

#include "ConditionalExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "ConditionRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IfConditionalExpressionRNode: public ConditionalExpressionRNode {
  public:
    explicit IfConditionalExpressionRNode(
        KeywordRNodeSPtr if_keyword,
        ConditionRNodeSPtr condition,
        ExpressionRNodeSPtr consequent_expression)
        : ConditionalExpressionRNode(condition)
        , if_keyword_(if_keyword)
        , consequent_expression_(consequent_expression) {
        set_type(Type::IfConditionalExpressionRNode);
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

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    KeywordRNodeSPtr if_keyword_;
    ExpressionRNodeSPtr consequent_expression_;

    static SEXP class_;
}; // namespace ast

using IfConditionalExpressionRNodeSPtr =
    std::shared_ptr<IfConditionalExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP */
