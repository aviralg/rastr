#ifndef RASTR_AST_EXPRESSION_RNODE_HPP
#define RASTR_AST_EXPRESSION_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class ExpressionRNode: public RNode {
  public:
    ExpressionRNode(Type type): RNode(type) {
    }

    virtual ~ExpressionRNode() = default;

    bool is_expression_node() const override {
        return true;
    }
};

using ExpressionRNodeSPtr = std::shared_ptr<ExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_RNODE_HPP */
