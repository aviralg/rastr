#ifndef RASTR_AST_NULL_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_NULL_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class NullLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit NullLiteralExpressionRNode(const std::string& representation)
        : LiteralExpressionRNode(Type::NullLiteralExpressionRNode)
        , IRepresentation(representation) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using NullLiteralExpressionRNodeSPtr =
    std::shared_ptr<NullLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_NULL_LITERAL_EXPRESSION_RNODE_HPP */
