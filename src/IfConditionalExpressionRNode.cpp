#include "IfConditionalExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IfConditionalExpressionRNode::class_ = NULL;

void IfConditionalExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_conditional_if",
                                  "rastr_node_r_expression_conditional",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void IfConditionalExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IfConditionalExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
