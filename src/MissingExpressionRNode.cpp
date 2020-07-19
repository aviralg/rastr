#include "MissingExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP MissingExpressionRNode::class_ = NULL;

void MissingExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_missing",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void MissingExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP MissingExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
