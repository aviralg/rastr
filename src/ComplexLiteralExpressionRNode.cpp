#include "ComplexLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ComplexLiteralExpressionRNode::class_ = NULL;

void ComplexLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_complex",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ComplexLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ComplexLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
