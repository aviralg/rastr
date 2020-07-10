#include "ComplexLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ComplexLiteralExpressionRNode::class_ = NULL;

void ComplexLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_r_node_expression_literal_complex",
                                  "rastr_r_node_expression_literal",
                                  "rastr_r_node_expression",
                                  "rastr_r_node",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ComplexLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ComplexLiteralExpressionRNode::get_class() {
    return class_;
}

ComplexLiteralExpressionRNodeSPtr
ComplexLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("ComplexLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<ComplexLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP ComplexLiteralExpressionRNode::to_sexp(
    ComplexLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new ComplexLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, ComplexLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(
        r_node, R_ClassSymbol, ComplexLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void ComplexLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<ComplexLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
