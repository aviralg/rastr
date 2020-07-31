#include "BinaryOperationExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP BinaryOperationExpressionRNode::class_ = NULL;

void BinaryOperationExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_binary",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void BinaryOperationExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BinaryOperationExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
