#ifndef RASTR_AST_OPERATION_EXPRESSION_RNODE_HPP
#define RASTR_AST_OPERATION_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IOperator.hpp"

namespace rastr {
namespace ast {

class OperationExpressionRNode
    : public ExpressionRNode
    , public IOperator {
  public:
    OperationExpressionRNode(OperatorRNodeSPtr op)
        : ExpressionRNode(), IOperator(op) {
    }

    virtual ~OperationExpressionRNode() = default;
};

using ExpressionRNodeSPtr = std::shared_ptr<ExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_OPERATION_EXPRESSION_RNODE_HPP */
