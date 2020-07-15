#include "BinaryExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP BinaryExpressionRNode::class_ = NULL;

void BinaryExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_binary",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void BinaryExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BinaryExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
