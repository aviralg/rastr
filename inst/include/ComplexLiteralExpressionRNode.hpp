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

    static std::shared_ptr<ComplexLiteralExpressionRNode>
    from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<ComplexLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    Rcomplex representation_;

    static SEXP class_;
};

using ComplexLiteralExpressionRNodeSPtr =
    std::shared_ptr<ComplexLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP */
