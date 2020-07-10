#ifndef RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IntegerLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit IntegerLiteralExpressionRNode(int value = 0)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::IntegerLiteralExpressionRNode);
    }

    int get_value() const {
        return value_;
    }

    void set_value(int value) {
        value_ = value;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<IntegerLiteralExpressionRNode>
    from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<IntegerLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    int value_;

    static SEXP class_;
};

using IntegerLiteralExpressionRNodeSPtr =
    std::shared_ptr<IntegerLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP */
