#ifndef RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class LogicalLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit LogicalLiteralExpressionRNode(int value,
                                           const std::string& representation)
        : LiteralExpressionRNode(Type::LogicalLiteralExpressionRNode)
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

using LogicalLiteralExpressionRNodeSPtr =
    std::shared_ptr<LogicalLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOGICAL_LITERAL_EXPRESSION_RNODE_HPP */
