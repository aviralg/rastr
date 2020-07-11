#ifndef RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

class LogicalLiteralExpressionRNode: public LiteralExpressionRNode {
  public:
    explicit LogicalLiteralExpressionRNode(bool representation = true)
        : LiteralExpressionRNode(), representation_(representation) {
        set_type(Type::LogicalLiteralExpressionRNode);
    }

    bool get_representation() const {
        return representation_;
    }

    void set_representation(bool representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    bool representation_;

    static SEXP class_;
};

using LogicalLiteralExpressionRNodeSPtr =
    std::shared_ptr<LogicalLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP */
