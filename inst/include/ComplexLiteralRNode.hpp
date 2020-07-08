#ifndef RASTR_AST_COMPLEX_LITERAL_RNODE_HPP
#define RASTR_AST_COMPLEX_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class ComplexLiteralRNode: public LiteralRNode {
  public:
    explicit ComplexLiteralRNode(const Rcomplex& value)
        : LiteralRNode(), value_(value) {
    }

    const Rcomplex& get_value() const {
        return value_;
    }

    void set_value(const Rcomplex& value) {
        value_ = value;
    }

  private:
    Rcomplex value_;

    static const Type type_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_COMPLEX_LITERAL_RNODE_HPP */
