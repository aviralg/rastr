#ifndef RASTR_AST_BINARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_BINARY_EXPRESSION_RNODE_HPP

#include "IOperator.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class BinaryExpressionRNode
    : public ExpressionRNode
    , public IOperator {
  public:
    BinaryExpressionRNode(OperatorRNodeSPtr op,
                          ExpressionRNodeSPtr first_operand,
                          ExpressionRNodeSPtr second_operand)
        : ExpressionRNode()
        , IOperator(op)
        , first_operand_(first_operand)
        , second_operand_(second_operand) {
    }

    ExpressionRNodeSPtr get_first_operand() const {
        return first_operand_;
    }

    ExpressionRNodeSPtr get_second_operand() const {
        return second_operand_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr first_operand_;
    ExpressionRNodeSPtr second_operand_;

    static SEXP class_;
};

using BinaryExpressionRNodeSPtr = std::shared_ptr<BinaryExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BINARY_EXPRESSION_RNODE_HPP */
