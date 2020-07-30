#ifndef RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "ICondition.hpp"

namespace rastr {
namespace ast {

class ForLoopExpressionRNode
    : public LoopExpressionRNode
    , public ICondition {
  public:
    explicit ForLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                    ConditionRNodeSPtr condition,
                                    ExpressionRNodeSPtr body)
        : LoopExpressionRNode(keyword, body), ICondition(condition) {
        set_type(Type::ForLoopExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using ForLoopExpressionRNodeSPtr = std::shared_ptr<ForLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP */
