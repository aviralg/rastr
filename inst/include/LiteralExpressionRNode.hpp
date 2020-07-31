#ifndef RASTR_AST_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_LITERAL_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class LiteralExpressionRNode: public ExpressionRNode {
  public:
    LiteralExpressionRNode(Type type): ExpressionRNode(type) {
    }

    virtual ~LiteralExpressionRNode() {
    }

    bool is_literal_expression_node() const override {
        return true;
    }
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LITERAL_EXPRESSION_RNODE_HPP */
