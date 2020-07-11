#ifndef RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IntegerLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit IntegerLiteralExpressionRNode(int representation = 0)
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::IntegerLiteralExpressionRNode);
    }

    int get_representation() const {
        return representation_;
    }

    void set_representation(int representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<IntegerLiteralExpressionRNode>
    from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<IntegerLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    int representation_;

    static SEXP class_;
};

using IntegerLiteralExpressionRNodeSPtr =
    std::shared_ptr<IntegerLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP */
