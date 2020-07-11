#include "RawLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP RawLiteralExpressionRNode::class_ = NULL;

void RawLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_raw",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void RawLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RawLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
