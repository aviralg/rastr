#include "RawStringLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP RawStringLiteralExpressionRNode::class_ = NULL;

void RawStringLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_string_raw",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void RawStringLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RawStringLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
