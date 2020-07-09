#ifndef RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class RawLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit RawLiteralExpressionRNode(const Rbyte value = 0)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::RawLiteralExpressionRNode);
    }

    const Rbyte get_value() const {
        return value_;
    }

    void set_value(const Rbyte value) {
        value_ = value;
    }

  private:
    Rbyte value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP */
