#ifndef RASTR_AST_RAW_LITERAL_RNODE_HPP
#define RASTR_AST_RAW_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class RawLiteralRNode: public LiteralRNode {
  public:
    explicit RawLiteralRNode(const Rbyte value = 0)
        : LiteralRNode(), value_(value) {
    }

    const Rbyte get_value() const {
        return value_;
    }

    void set_value(const Rbyte value) {
        value_ = value;
    }

  private:
    Rbyte value_;

    static const Type type_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RAW_LITERAL_RNODE_HPP */
