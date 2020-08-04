#ifndef RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class IntegerLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit IntegerLiteralExpressionRNode(int value,
                                           const std::string& representation)
        : LiteralExpressionRNode(Type::IntegerLiteralExpressionRNode)
        , IRepresentation(representation)
        , value_(value) {
    }

    int get_value() const {
        return value_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    int value_;

    static SEXP class_;
};

using IntegerLiteralExpressionRNodeSPtr =
    std::shared_ptr<IntegerLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INTEGER_LITERAL_EXPRESSION_RNODE_HPP */
