#ifndef RASTR_I_EXPRESSION_RNODE_HPP
#define RASTR_I_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IExpression {
  public:
    explicit IExpression(ExpressionRNodeSPtr expression)
        : expression_(expression) {
    }

    virtual ~IExpression() = default;

    ExpressionRNodeSPtr get_expression() const {
        return expression_;
    }

    void set_expression(ExpressionRNodeSPtr expression) {
        expression_ = expression;
    }

  private:
    ExpressionRNodeSPtr expression_;
};

using IExpressionSPtr = std::shared_ptr<IExpression>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_EXPRESSION_RNODE_HPP */
