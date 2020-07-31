#ifndef RASTR_AST_UNARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_UNARY_EXPRESSION_RNODE_HPP

#include "OperationExpressionRNode.hpp"

namespace rastr {
namespace ast {

class UnaryOperationExpressionRNode: public OperationExpressionRNode {
  public:
    UnaryOperationExpressionRNode(OperatorRNodeSPtr op,
                                  ExpressionRNodeSPtr operand)
        : OperationExpressionRNode(Type::UnaryOperationExpressionRNode, op)
        , operand_(operand) {
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

using UnaryOperationExpressionRNodeSPtr =
    std::shared_ptr<UnaryOperationExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_UNARY_EXPRESSION_RNODE_HPP */
