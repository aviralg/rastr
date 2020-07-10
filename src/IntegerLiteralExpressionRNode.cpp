#include "IntegerLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IntegerLiteralExpressionRNode::class_ = NULL;

void IntegerLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_r_node_expression_literal_integer",
                                  "rastr_r_node_expression_literal",
                                  "rastr_r_node_expression",
                                  "rastr_r_node",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void IntegerLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IntegerLiteralExpressionRNode::get_class() {
    return class_;
}

IntegerLiteralExpressionRNodeSPtr
IntegerLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("IntegerLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<IntegerLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP IntegerLiteralExpressionRNode::to_sexp(
    IntegerLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new IntegerLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, IntegerLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(
        r_node, R_ClassSymbol, IntegerLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void IntegerLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<IntegerLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
