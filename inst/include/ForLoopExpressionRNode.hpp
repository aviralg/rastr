#ifndef RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "ConditionRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ForLoopExpressionRNode: public LoopExpressionRNode {
  public:
    explicit ForLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                    ConditionRNodeSPtr condition,
                                    ExpressionRNodeSPtr body)
        : LoopExpressionRNode(keyword, body) {
        set_type(Type::ForLoopExpressionRNode);
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
}; // namespace ast

using ForLoopExpressionRNodeSPtr = std::shared_ptr<ForLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP */
