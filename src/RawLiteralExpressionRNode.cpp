#include "RawLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP RawLiteralExpressionRNode::class_ = NULL;

void RawLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_r_node_expression_literal_raw",
                                  "rastr_r_node_expression_literal",
                                  "rastr_r_node_expression",
                                  "rastr_r_node",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void RawLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RawLiteralExpressionRNode::get_class() {
    return class_;
}

RawLiteralExpressionRNodeSPtr
RawLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("RawLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<RawLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP RawLiteralExpressionRNode::to_sexp(RawLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new RawLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, RawLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, RawLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void RawLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<RawLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
