#ifndef RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class DoubleLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit DoubleLiteralExpressionRNode(double representation = 0.0)
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::DoubleLiteralExpressionRNode);
    }

    double get_representation() const {
        return representation_;
    }

    void set_representation(double representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    double representation_;

    static SEXP class_;
};

using DoubleLiteralExpressionRNodeSPtr =
    std::shared_ptr<DoubleLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP */
