#ifndef RASTR_I_SYMBOL_RNODE_HPP
#define RASTR_I_SYMBOL_RNODE_HPP

#include "SymbolExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ISymbol {
  public:
    explicit ISymbol(SymbolExpressionRNodeSPtr symbol): symbol_(symbol) {
    }

    virtual ~ISymbol() = default;

    SymbolExpressionRNodeSPtr get_symbol() const {
        return symbol_;
    }

    void set_symbol(SymbolExpressionRNodeSPtr symbol) {
        symbol_ = symbol;
    }

  private:
    SymbolExpressionRNodeSPtr symbol_;
};

using ISymbolSPtr = std::shared_ptr<ISymbol>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_SYMBOL_RNODE_HPP */
