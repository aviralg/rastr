#ifndef RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP
#define RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP

#include "LiteralExpressionRNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class ComplexLiteralExpressionRNode
    : public LiteralExpressionRNode
    , public IRepresentation {
  public:
    explicit ComplexLiteralExpressionRNode(const Rcomplex& value,
                                           const std::string& representation)
        : LiteralExpressionRNode(Type::ComplexLiteralExpressionRNode)
        , IRepresentation(representation)
        , value_(value) {
    }

    const Rcomplex& get_value() const {
        return value_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    Rcomplex value_;

    static SEXP class_;
};

using ComplexLiteralExpressionRNodeSPtr =
    std::shared_ptr<ComplexLiteralExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_COMPLEX_LITERAL_EXPRESSION_RNODE_HPP */
