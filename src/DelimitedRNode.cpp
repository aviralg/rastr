#include "DelimitedRNode.hpp"

namespace rastr {
namespace ast {

SEXP DelimitedRNode::class_ = NULL;

void DelimitedRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_delimited", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void DelimitedRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DelimitedRNode::get_class() {
    return class_;
}

DelimitedRNodeSPtr DelimitedRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("DelimitedRNode::from_sexp: object is null");
    } else {
        return *static_cast<DelimitedRNodeSPtr*>(node);
    }
}

SEXP DelimitedRNode::to_sexp(DelimitedRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new DelimitedRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, DelimitedRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, DelimitedRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void DelimitedRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<DelimitedRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
