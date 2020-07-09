#ifndef RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class DoubleLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit DoubleLiteralExpressionRNode(double value = 0.0)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::DoubleLiteralExpressionRNode);
    }

    double get_value() const {
        return value_;
    }

    void set_value(double value) {
        value_ = value;
    }

  private:
    double value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP */
