#ifndef RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "ConditionRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class WhileLoopExpressionRNode: public LoopExpressionRNode {
  public:
    explicit WhileLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                      ConditionRNodeSPtr condition,
                                      ExpressionRNodeSPtr body)
        : LoopExpressionRNode(keyword, body) {
        set_type(Type::WhileLoopExpressionRNode);
    }

    ConditionRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(ConditionRNodeSPtr condition) {
        condition_ = condition;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ConditionRNodeSPtr condition_;

    static SEXP class_;
};

using WhileLoopExpressionRNodeSPtr = std::shared_ptr<WhileLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP */
