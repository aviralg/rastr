#ifndef RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP

#include "ConditionalExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IfConditionalExpressionRNode: public ConditionalExpressionRNode {
  public:
    explicit IfConditionalExpressionRNode(
        KeywordRNodeSPtr if_keyword,
        ConditionRNodeSPtr condition,
        ExpressionRNodeSPtr consequent_expression)
        : ConditionalExpressionRNode(Type::IfConditionalExpressionRNode,
                                     if_keyword,
                                     condition,
                                     consequent_expression) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
}; // namespace ast

using IfConditionalExpressionRNodeSPtr =
    std::shared_ptr<IfConditionalExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_IF_CONDITIONAL_EXPRESSION_RNODE_HPP */
