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

  private:
    Rbyte representation_;

    static SEXP class_;
};

using RawLiteralExpressionRNodeSPtr =
    std::shared_ptr<RawLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RAW_LITERAL_EXPRESSION_RNODE_HPP */
