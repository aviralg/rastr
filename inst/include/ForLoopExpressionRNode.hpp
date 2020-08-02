#ifndef RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "InConditionRNode.hpp"

namespace rastr {
namespace ast {

class ForLoopExpressionRNode: public LoopExpressionRNode {
  public:
    explicit ForLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                    InConditionRNodeSPtr condition,
                                    ExpressionRNodeSPtr body)
        : LoopExpressionRNode(Type::ForLoopExpressionRNode, keyword, body)
        , condition_(condition) {
    }

    InConditionRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(InConditionRNodeSPtr condition) {
        condition_ = condition;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    InConditionRNodeSPtr condition_;

    static SEXP class_;
};

using ForLoopExpressionRNodeSPtr = std::shared_ptr<ForLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP */
