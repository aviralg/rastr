#ifndef RASTR_AST_CHARACTER_LITERAL_RNODE_HPP
#define RASTR_AST_CHARACTER_LITERAL_RNODE_HPP

#include "LiteralRNode.hpp"

namespace rastr {
namespace ast {

class CharacterLiteralRNode: public LiteralRNode {
  public:
    explicit CharacterLiteralRNode(const std::string& value = "")
        : LiteralRNode(), value_(value) {
    }

    const std::string& get_value() const {
        return value_;
    }

    void set_value(const std::string& value) {
        value_ = value;
    }

  private:
    std::string value_;

    static const Type type_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CHARACTER_LITERAL_RNODE_HPP */
