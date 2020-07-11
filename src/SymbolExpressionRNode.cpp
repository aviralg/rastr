#include "SymbolExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP SymbolExpressionRNode::class_ = NULL;

void SymbolExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_symbol",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void SymbolExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SymbolExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
