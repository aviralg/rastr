#ifndef RASTR_AST_BINARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_BINARY_EXPRESSION_RNODE_HPP

#include "OperationExpressionRNode.hpp"

namespace rastr {
namespace ast {

class BinaryOperationExpressionRNode: public OperationExpressionRNode {
  public:
    BinaryOperationExpressionRNode(OperatorRNodeSPtr op,
                                   ExpressionRNodeSPtr first_operand,
                                   ExpressionRNodeSPtr second_operand)
        : OperationExpressionRNode(Type::BinaryOperationExpressionRNode, op)
        , first_operand_(first_operand)
        , second_operand_(second_operand) {
    }

    ExpressionRNodeSPtr get_first_operand() const {
        return first_operand_;
    }

    void set_first_operand(ExpressionRNodeSPtr first_operand) {
        first_operand_ = first_operand;
    }

    ExpressionRNodeSPtr get_second_operand() const {
        return second_operand_;
    }

    void set_second_operand(ExpressionRNodeSPtr second_operand) {
        second_operand_ = second_operand;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr first_operand_;
    ExpressionRNodeSPtr second_operand_;

    static SEXP class_;
};

using BinaryOperationExpressionRNodeSPtr =
    std::shared_ptr<BinaryOperationExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BINARY_EXPRESSION_RNODE_HPP */
