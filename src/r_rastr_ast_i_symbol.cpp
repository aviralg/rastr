#include "r_rastr_ast_i_symbol.h"
#include "ISymbol.hpp"
#include "r_cast.hpp"

using rastr::ast::ISymbol;
using rastr::ast::ISymbolSPtr;
using rastr::ast::SymbolExpressionRNode;
using rastr::ast::SymbolExpressionRNodeSPtr;

SEXP r_rastr_ast_i_symbol_get_symbol(SEXP r_i_symbol) {
    ISymbolSPtr i_symbol = from_sexp<ISymbol>(r_i_symbol);

    SymbolExpressionRNodeSPtr symbol = i_symbol->get_symbol();

    return to_sexp<SymbolExpressionRNode>(symbol);
}

SEXP r_rastr_ast_i_symbol_set_symbol(SEXP r_i_symbol, SEXP r_symbol) {
    ISymbolSPtr i_symbol = from_sexp<ISymbol>(r_i_symbol);

    SymbolExpressionRNodeSPtr symbol =
        from_sexp<SymbolExpressionRNode>(r_symbol);

    i_symbol->set_symbol(symbol);

    return r_i_symbol;
}
