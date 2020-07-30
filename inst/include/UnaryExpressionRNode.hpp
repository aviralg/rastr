#ifndef RASTR_AST_UNARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_UNARY_EXPRESSION_RNODE_HPP

#include "IOperator.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class UnaryExpressionRNode
    : public ExpressionRNode
    , public IOperator {
  public:
    UnaryExpressionRNode(OperatorRNodeSPtr op, ExpressionRNodeSPtr operand)
        : ExpressionRNode(), IOperator(op), operand_(operand) {
    }

    ExpressionRNodeSPtr get_operand() const {
        return operand_;
    }

    void set_operand(ExpressionRNodeSPtr operand) {
        operand_ = operand;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr operand_;

    static SEXP class_;
};

using UnaryExpressionRNodeSPtr = std::shared_ptr<UnaryExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_UNARY_EXPRESSION_RNODE_HPP */
