#ifndef RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class DoubleLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit DoubleLiteralExpressionRNode(double value,
                                          const std::string& representation)
        : LiteralExpressionRNode(Type::DoubleLiteralExpressionRNode)
        , IRepresentation(representation)
        , value_(value) {
    }

    double get_value() const {
        return value_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    double value_;

    static SEXP class_;
};

using DoubleLiteralExpressionRNodeSPtr =
    std::shared_ptr<DoubleLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_DOUBLE_LITERAL_EXPRESSION_RNODE_HPP */
