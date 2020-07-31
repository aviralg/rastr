#ifndef RASTR_AST_RAW_STRING_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_RAW_STRING_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class RawStringLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit RawStringLiteralExpressionRNode(
        const std::string& opening_delimiter,
        const std::string& closing_delimiter,
        const std::string& representation = "")
        : LiteralExpressionRNode(Type::RawStringLiteralExpressionRNode)
        , representation_(representation) {
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

  private:
    std::string representation_;

    static SEXP class_;
};

using RawStringLiteralExpressionRNodeSPtr =
    std::shared_ptr<RawStringLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RAW_STRING_LITERAL_EXPRESSION_RNODE_HPP */
