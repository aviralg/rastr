#ifndef RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class RawLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit RawLiteralExpressionRNode(const Rbyte representation = 0)
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::RawLiteralExpressionRNode);
    }

    const Rbyte get_representation() const {
        return representation_;
    }

    void set_representation(const Rbyte representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<RawLiteralExpressionRNode> from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<RawLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    Rbyte representation_;

    static SEXP class_;
};

using RawLiteralExpressionRNodeSPtr =
    std::shared_ptr<RawLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP */
