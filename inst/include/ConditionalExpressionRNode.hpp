#ifndef RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP

#include "ConditionRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ConditionalExpressionRNode: public ExpressionRNode {
  public:
    explicit ConditionalExpressionRNode(ConditionRNodeSPtr condition)
        : ExpressionRNode(), condition_(condition) {
    }

    ConditionRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(ConditionRNodeSPtr condition) {
        condition_ = condition;
    }

  private:
    ConditionRNodeSPtr condition_;

    static SEXP class_;
}; // namespace ast

using ConditionalExpressionRNodeSPtr =
    std::shared_ptr<ConditionalExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONDITIONAL_EXPRESSION_RNODE_HPP */
