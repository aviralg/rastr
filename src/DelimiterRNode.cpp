#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

SEXP DelimiterRNode::class_ = NULL;

void DelimiterRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_delimiter", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void DelimiterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DelimiterRNode::get_class() {
    return class_;
}

DelimiterRNodeSPtr DelimiterRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("DelimiterRNode::from_sexp: object is null");
    } else {
        return *static_cast<DelimiterRNodeSPtr*>(node);
    }
}

SEXP DelimiterRNode::to_sexp(DelimiterRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new DelimiterRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, DelimiterRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, DelimiterRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void DelimiterRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<DelimiterRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
