#ifndef RASTR_AST_EXPRESSION_RNODE_HPP
#define RASTR_AST_EXPRESSION_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class ExpressionRNode: public virtual RNode {
  public:
    ExpressionRNode(): RNode() {
    }

    virtual ~ExpressionRNode() {
    }

    bool is_expression_node() const override {
        return true;
    }
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_RNODE_HPP */
