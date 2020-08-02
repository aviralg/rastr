#ifndef RASTR_AST_EXPRESSION_CONDITION_RNODE_HPP
#define RASTR_AST_EXPRESSION_CONDITION_RNODE_HPP

#include "ConditionRNode.hpp"
#include "IExpression.hpp"

namespace rastr {
namespace ast {

class ExpressionConditionRNode
    : public ConditionRNode
    , public IExpression {
  public:
    explicit ExpressionConditionRNode(DelimiterRNodeSPtr opening_delimiter,
                                      ExpressionRNodeSPtr expression,
                                      DelimiterRNodeSPtr closing_delimiter)
        : ConditionRNode(Type::ExpressionConditionRNode,
                         opening_delimiter,
                         closing_delimiter)
        , IExpression(expression) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using ExpressionConditionRNodeSPtr = std::shared_ptr<ExpressionConditionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_CONDITION_RNODE_HPP */
