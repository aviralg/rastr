#ifndef RASTR_AST_NEXT_EXPRESSION_RNODE_HPP
#define RASTR_AST_NEXT_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class NextExpressionRNode
    : public ExpressionRNode
    , public IRepresentation {
  public:
    explicit NextExpressionRNode()
        : ExpressionRNode(Type::NextExpressionRNode), IRepresentation("next") {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using NextExpressionRNodeSPtr = std::shared_ptr<NextExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_NEXT_EXPRESSION_RNODE_HPP */
