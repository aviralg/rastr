#include "DoubleLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP DoubleLiteralExpressionRNode::class_ = NULL;

void DoubleLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_r_node_expression_literal_double",
                                  "rastr_r_node_expression_literal",
                                  "rastr_r_node_expression",
                                  "rastr_r_node",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void DoubleLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DoubleLiteralExpressionRNode::get_class() {
    return class_;
}

DoubleLiteralExpressionRNodeSPtr
DoubleLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("DoubleLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<DoubleLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP DoubleLiteralExpressionRNode::to_sexp(
    DoubleLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new DoubleLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, DoubleLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, DoubleLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void DoubleLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<DoubleLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
