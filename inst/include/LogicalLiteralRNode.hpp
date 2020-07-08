#ifndef RASTR_AST_LOGICAL_LITERAL_RNODE_HPP
#define RASTR_AST_LOGICAL_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class LogicalLiteralRNode: public LiteralRNode {
  public:
    explicit LogicalLiteralRNode(bool value = true)
        : LiteralRNode(), value_(value) {
    }

    bool get_value() const {
        return value_;
    }

    void set_value(bool value) {
        value_ = value;
    }

  private:
    bool value_;

    static const Type type_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOGICAL_LITERAL_RNODE_HPP */
