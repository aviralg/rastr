#ifndef RASTR_AST_INTEGER_LITERAL_RNODE_HPP
#define RASTR_AST_INTEGER_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class IntegerLiteralRNode: public LiteralRNode {
  public:
    explicit IntegerLiteralRNode(int value = 0): LiteralRNode(), value_(value) {
        set_type(Type::IntegerLiteralRNode);
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

#endif /* RASTR_AST_INTEGER_LITERAL_RNODE_HPP */
