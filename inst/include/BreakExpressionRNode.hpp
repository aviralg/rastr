#ifndef RASTR_AST_BREAK_EXPRESSION_RNODE_HPP
#define RASTR_AST_BREAK_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class BreakExpressionRNode
    : public ExpressionRNode
    , public IRepresentation {
  public:
    explicit BreakExpressionRNode()
        : ExpressionRNode(), IRepresentation("break") {
        set_type(Type::BreakExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using BreakExpressionRNodeSPtr = std::shared_ptr<BreakExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BREAK_EXPRESSION_RNODE_HPP */
