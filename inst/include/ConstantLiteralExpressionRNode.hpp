#ifndef RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ConstantLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit ConstantLiteralExpressionRNode(
        const std::string& representation = "")
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::ConstantLiteralExpressionRNode);
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

using ConstantLiteralExpressionRNodeSPtr =
    std::shared_ptr<ConstantLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP */
