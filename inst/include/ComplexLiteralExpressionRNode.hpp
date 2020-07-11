#ifndef RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ComplexLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit ComplexLiteralExpressionRNode(const Rcomplex& representation)
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::ComplexLiteralExpressionRNode);
    }

    const Rcomplex& get_representation() const {
        return representation_;
    }

    void set_representation(const Rcomplex& representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    Rcomplex representation_;

    static SEXP class_;
};

using ComplexLiteralExpressionRNodeSPtr =
    std::shared_ptr<ComplexLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP */
