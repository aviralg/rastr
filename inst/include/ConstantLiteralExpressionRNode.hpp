#ifndef RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class ConstantLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit ConstantLiteralExpressionRNode(const std::string& representation)
        : LiteralExpressionRNode(), IRepresentation(representation) {
        set_type(Type::ConstantLiteralExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using ConstantLiteralExpressionRNodeSPtr =
    std::shared_ptr<ConstantLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONSTANT_LITERAL_EXPRESSION_RNODE_HPP */
