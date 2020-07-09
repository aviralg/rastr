#ifndef RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ComplexLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit ComplexLiteralExpressionRNode(const Rcomplex& value)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::ComplexLiteralExpressionRNode);
    }

    const Rcomplex& get_value() const {
        return value_;
    }

    void set_value(const Rcomplex& value) {
        value_ = value;
    }

  private:
    Rcomplex value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP */
