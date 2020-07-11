#ifndef RASTR_AST_IN_RNODE_HPP
#define RASTR_AST_IN_RNODE_HPP

#include "RNode.hpp"
#include "SymbolExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class InRNode: public RNode {
  public:
    explicit InRNode(SymbolExpressionRNodeSPtr symbol,
                     KeywordRNodeSPtr keyword,
                     ExpressionRNodeSPtr expression)
        : RNode(), symbol_(symbol), keyword_(keyword), expression_(expression) {
    }

    SymbolExpressionRNodeSPtr get_symbol() const {
        return symbol_;
    }

    void set_symbol(SymbolExpressionRNodeSPtr symbol) {
        symbol_ = symbol;
    }

    KeywordRNodeSPtr get_keyword() const {
        return keyword_;
    }

    void set_keyword(KeywordRNodeSPtr keyword) {
        keyword_ = keyword;
    }

    ExpressionRNodeSPtr get_expression() const {
        return expression_;
    }

    void set_expression(ExpressionRNodeSPtr expression) {
        expression_ = expression;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    SymbolExpressionRNodeSPtr symbol_;
    KeywordRNodeSPtr keyword_;
    ExpressionRNodeSPtr expression_;

    static SEXP class_;
};

using InRNodeSPtr = std::shared_ptr<InRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_IN_RNODE_HPP */
