#include "ForLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ForLoopExpressionRNode::class_ = NULL;

void ForLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_for",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ForLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ForLoopExpressionRNode::get_class() {
    return class_;
}

ForLoopExpressionRNodeSPtr ForLoopExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("ForLoopExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<ForLoopExpressionRNodeSPtr*>(node);
    }
}

SEXP ForLoopExpressionRNode::to_sexp(ForLoopExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new ForLoopExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, ForLoopExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, ForLoopExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void ForLoopExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<ForLoopExpressionRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
