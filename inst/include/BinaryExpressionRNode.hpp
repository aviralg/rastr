#ifndef RASTR_AST_BINARY_EXPRESSION_RNODE_HPP
#define RASTR_AST_BINARY_EXPRESSION_RNODE_HPP

#include "OperatorRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class BinaryExpressionRNode: public ExpressionRNode {
  public:
    BinaryExpressionRNode(OperatorRNodeSPtr op,
                          ExpressionRNodeSPtr left_expression,
                          ExpressionRNodeSPtr right_expression)
        : ExpressionRNode()
        , op_(op)
        , left_expression_(left_expression)
        , right_expression_(right_expression) {
    }

    OperatorRNodeSPtr get_operator() const {
        return op_;
    }

    ExpressionRNodeSPtr get_left_expression() const {
        return left_expression_;
    }

    ExpressionRNodeSPtr get_right_expression() const {
        return right_expression_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    OperatorRNodeSPtr op_;
    ExpressionRNodeSPtr left_expression_;
    ExpressionRNodeSPtr right_expression_;

    static SEXP class_;
};

using BinaryExpressionRNodeSPtr = std::shared_ptr<BinaryExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BINARY_EXPRESSION_RNODE_HPP */
