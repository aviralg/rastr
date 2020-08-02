#ifndef RASTR_AST_IN_CONDITION_RNODE_HPP
#define RASTR_AST_IN_CONDITION_RNODE_HPP

#include "ConditionRNode.hpp"
#include "ISymbol.hpp"
#include "IKeyword.hpp"
#include "IExpression.hpp"

namespace rastr {
namespace ast {

class InConditionRNode
    : public ConditionRNode
    , public ISymbol
    , public IKeyword
    , public IExpression {
  public:
    explicit InConditionRNode(DelimiterRNodeSPtr opening_delimiter,
                              SymbolExpressionRNodeSPtr symbol,
                              KeywordRNodeSPtr keyword,
                              ExpressionRNodeSPtr expression,
                              DelimiterRNodeSPtr closing_delimiter)
        : ConditionRNode(Type::InConditionRNode,
                         opening_delimiter,
                         closing_delimiter)
        , ISymbol(symbol)
        , IKeyword(keyword)
        , IExpression(expression) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using InConditionRNodeSPtr = std::shared_ptr<InConditionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_IN_CONDITION_RNODE_HPP */
