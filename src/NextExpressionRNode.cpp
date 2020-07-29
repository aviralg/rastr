#include "NextExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP NextExpressionRNode::class_ = NULL;

void NextExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_next",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void NextExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP NextExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
