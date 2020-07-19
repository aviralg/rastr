#ifndef RASTR_AST_UNARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_UNARY_EXPRESSION_RNODE_HPP

#include "OperatorRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class UnaryExpressionRNode: public ExpressionRNode {
  public:
    UnaryExpressionRNode(OperatorRNodeSPtr op, ExpressionRNodeSPtr expression)
        : ExpressionRNode(), op_(op), expression_(expression) {
    }

    OperatorRNodeSPtr get_operator() const {
        return op_;
    }

    ExpressionRNodeSPtr get_expression() const {
        return expression_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    OperatorRNodeSPtr op_;
    ExpressionRNodeSPtr expression_;

    static SEXP class_;
};

using UnaryExpressionRNodeSPtr = std::shared_ptr<UnaryExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_UNARY_EXPRESSION_RNODE_HPP */
