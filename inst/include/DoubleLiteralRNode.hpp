#ifndef RASTR_AST_DOUBLE_LITERAL_RNODE_HPP
#define RASTR_AST_DOUBLE_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class DoubleLiteralRNode: public LiteralRNode {
  public:
    explicit DoubleLiteralRNode(double value = 0.0)
        : LiteralRNode(), value_(value) {
        set_type(Type::DoubleLiteralRNode);
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

#endif /* RASTR_AST_DOUBLE_LITERAL_RNODE_HPP */
