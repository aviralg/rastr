#include "RepeatLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP RepeatLoopExpressionRNode::class_ = NULL;

void RepeatLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_repeat",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void RepeatLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RepeatLoopExpressionRNode::get_class() {
    return class_;
}

RepeatLoopExpressionRNodeSPtr
RepeatLoopExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("RepeatLoopExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<RepeatLoopExpressionRNodeSPtr*>(node);
    }
}

SEXP RepeatLoopExpressionRNode::to_sexp(RepeatLoopExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new RepeatLoopExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, RepeatLoopExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, RepeatLoopExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void RepeatLoopExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<RepeatLoopExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
