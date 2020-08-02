#ifndef RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "ICondition.hpp"

namespace rastr {
namespace ast {

class WhileLoopExpressionRNode
    : public LoopExpressionRNode
    , public ICondition {
  public:
    explicit WhileLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                      ExpressionConditionRNodeSPtr condition,
                                      ExpressionRNodeSPtr body)
        : LoopExpressionRNode(Type::WhileLoopExpressionRNode, keyword, body)
        , ICondition(condition) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using WhileLoopExpressionRNodeSPtr = std::shared_ptr<WhileLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_WHILE_LOOP_EXPRESSION_RNODE_HPP */
