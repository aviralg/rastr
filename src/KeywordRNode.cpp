#include "KeywordRNode.hpp"

namespace rastr {
namespace ast {

SEXP KeywordRNode::class_ = NULL;

void KeywordRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_r_node_keyword", "rastr_r_node", "rastr_node"});
    R_PreserveObject(class_);
}

void KeywordRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP KeywordRNode::get_class() {
    return class_;
}

KeywordRNodeSPtr KeywordRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("KeywordRNode::from_sexp: object is null");
    } else {
        return *static_cast<KeywordRNodeSPtr*>(node);
    }
}

SEXP KeywordRNode::to_sexp(KeywordRNodeSPtr node) {
    SEXP r_node = PROTECT(
        R_MakeExternalPtr(new KeywordRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, KeywordRNode::destroy_sexp, TRUE);

    setAttrib(r_node, R_ClassSymbol, KeywordRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void KeywordRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<KeywordRNodeSPtr*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
