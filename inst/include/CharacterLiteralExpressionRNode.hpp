#ifndef RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class CharacterLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit CharacterLiteralExpressionRNode(const std::string& value = "")
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::CharacterLiteralExpressionRNode);
    }

    const std::string& get_value() const {
        return value_;
    }

    void set_value(const std::string& value) {
        value_ = value;
    }

  private:
    std::string value_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP */
