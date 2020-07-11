#include "LogicalLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP LogicalLiteralExpressionRNode::class_ = NULL;

void LogicalLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_logical",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void LogicalLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP LogicalLiteralExpressionRNode::get_class() {
    return class_;
}

LogicalLiteralExpressionRNodeSPtr
LogicalLiteralExpressionRNode::from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("LogicalLiteralExpressionRNode::from_sexp: object is null");
    } else {
        return *static_cast<LogicalLiteralExpressionRNodeSPtr*>(node);
    }
}

SEXP LogicalLiteralExpressionRNode::to_sexp(
    LogicalLiteralExpressionRNodeSPtr node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new LogicalLiteralExpressionRNodeSPtr(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(
        r_node, LogicalLiteralExpressionRNode::destroy_sexp, TRUE);

    setAttrib(
        r_node, R_ClassSymbol, LogicalLiteralExpressionRNode::get_class());

    UNPROTECT(1);

    return r_node;
}

void LogicalLiteralExpressionRNode::destroy_sexp(SEXP r_node) {
    delete static_cast<LogicalLiteralExpressionRNodeSPtr*>(
        R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

} // namespace ast
} // namespace rastr
