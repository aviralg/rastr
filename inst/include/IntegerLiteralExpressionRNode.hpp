#ifndef RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IntegerLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit IntegerLiteralExpressionRNode(int value = 0): LiteralExpressionRNode(), value_(value) {
        set_type(Type::IntegerLiteralExpressionRNode);
    }

    int get_value() const {
        return value_;
    }

    void set_value(int value) {
        value_ = value;
    }

  private:
    int value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP */
