#include "BreakExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP BreakExpressionRNode::class_ = NULL;

void BreakExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_break",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void BreakExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BreakExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
