#include "InRNode.hpp"

namespace rastr {
namespace ast {

SEXP InRNode::class_ = NULL;

void InRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_node_r_in", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void InRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP InRNode::get_class() {
    return class_;
}

InRNodeSPtr InRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("InRNode::from_sexp: object is null");
    } else {
        return *static_cast<InRNodeSPtr*>(node);
    }
}

SEXP InRNode::to_sexp(InRNodeSPtr node) {
    SEXP r_node = PROTECT(
        R_MakeExternalPtr(new InRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, InRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, InRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void InRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<InRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
