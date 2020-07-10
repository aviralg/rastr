#ifndef RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class LogicalLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit LogicalLiteralExpressionRNode(bool value = true)
        : LiteralExpressionRNode(), value_(value) {
        set_type(Type::LogicalLiteralExpressionRNode);
    }

    bool get_value() const {
        return value_;
    }

    void set_value(bool value) {
        value_ = value;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<LogicalLiteralExpressionRNode>
    from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<LogicalLiteralExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    bool value_;

    static SEXP class_;
};

using LogicalLiteralExpressionRNodeSPtr =
    std::shared_ptr<LogicalLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP */
