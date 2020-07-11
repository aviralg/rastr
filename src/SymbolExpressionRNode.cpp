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

SymbolExpressionRNodeSPtr SymbolExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("SymbolExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<SymbolExpressionRNodeSPtr*>(node);
    }
}

SEXP SymbolExpressionRNode::to_sexp(SymbolExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new SymbolExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, SymbolExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, SymbolExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void SymbolExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<SymbolExpressionRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
