#ifndef RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class CharacterLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit CharacterLiteralExpressionRNode(
        const std::string& representation = "")
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::CharacterLiteralExpressionRNode);
    }

    const std::string& get_representation() const {
        return representation_;
    }

    void set_representation(const std::string& representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<CharacterLiteralExpressionRNode>
    from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<CharacterLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    std::string representation_;

    static SEXP class_;
};

using CharacterLiteralExpressionRNodeSPtr =
    std::shared_ptr<CharacterLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CHARACTER_LITERAL_EXPRESSION_RNODE_HPP */
