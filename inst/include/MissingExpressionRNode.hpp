#ifndef RASTR_AST_MISSING_EXPRESSION_RNODE_HPP
#define RASTR_AST_MISSING_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class MissingExpressionRNode: public ExpressionRNode {
  public:
    MissingExpressionRNode(): ExpressionRNode() {
        set_type(Type::MissingExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using MissingExpressionRNodeSPtr = std::shared_ptr<MissingExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_MISSING_EXPRESSION_RNODE_HPP */
