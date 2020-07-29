#ifndef RASTR_AST_BREAK_EXPRESSION_RNODE_HPP
#define RASTR_AST_BREAK_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class BreakExpressionRNode: public ExpressionRNode {
  public:
    explicit BreakExpressionRNode(const std::string& representation = "")
        : ExpressionRNode(), representation_(representation) {
        set_type(Type::BreakExpressionRNode);
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

using BreakExpressionRNodeSPtr = std::shared_ptr<BreakExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BREAK_EXPRESSION_RNODE_HPP */
