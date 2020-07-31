#include "UnaryOperationExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP UnaryOperationExpressionRNode::class_ = NULL;

void UnaryOperationExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_unary",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void UnaryOperationExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP UnaryOperationExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
