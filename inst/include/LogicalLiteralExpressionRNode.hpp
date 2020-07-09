#ifndef RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class LogicalLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit LogicalLiteralExpressionRNode(bool value = true)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::LogicalLiteralExpressionRNode);
    }

    bool get_value() const {
        return value_;
    }

    void set_value(bool value) {
        value_ = value;
    }

  private:
    bool value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP */
