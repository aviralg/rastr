#include "WhileLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP WhileLoopExpressionRNode::class_ = NULL;

void WhileLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_while",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void WhileLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP WhileLoopExpressionRNode::get_class() {
    return class_;
}

WhileLoopExpressionRNodeSPtr WhileLoopExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("WhileLoopExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<WhileLoopExpressionRNodeSPtr*>(node);
    }
}

SEXP WhileLoopExpressionRNode::to_sexp(WhileLoopExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new WhileLoopExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, WhileLoopExpressionRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, WhileLoopExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void WhileLoopExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<WhileLoopExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
