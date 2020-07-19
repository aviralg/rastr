#include "UnaryExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP UnaryExpressionRNode::class_ = NULL;

void UnaryExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_unary",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void UnaryExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP UnaryExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
