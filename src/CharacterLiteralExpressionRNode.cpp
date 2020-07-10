#include "CharacterLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP CharacterLiteralExpressionRNode::class_ = NULL;

void CharacterLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_r_node_expression_literal_character",
                                  "rastr_r_node_expression_literal",
                                  "rastr_r_node_expression",
                                  "rastr_r_node",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void CharacterLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP CharacterLiteralExpressionRNode::get_class() {
    return class_;
}

CharacterLiteralExpressionRNodeSPtr
CharacterLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("CharacterLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<CharacterLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP CharacterLiteralExpressionRNode::to_sexp(
    CharacterLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new CharacterLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, CharacterLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(
        r_node, R_ClassSymbol, CharacterLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void CharacterLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<CharacterLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
