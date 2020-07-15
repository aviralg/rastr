#include "r_symbol_expression_r_node.h"
#include "SymbolExpressionRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::SymbolExpressionRNode;
using rastr::ast::SymbolExpressionRNodeSPtr;

SEXP r_symbol_expression_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    SymbolExpressionRNodeSPtr node =
        std::make_shared<SymbolExpressionRNode>(representation);

    return to_sexp<SymbolExpressionRNode>(node);
}

SEXP r_symbol_expression_r_node_get_representation(SEXP r_node) {
    SymbolExpressionRNodeSPtr node = from_sexp<SymbolExpressionRNode>(r_node);

    const std::string& representation = node->get_representation();

    return mkString(representation.c_str());
}
