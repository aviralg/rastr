#include "ForLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ForLoopExpressionRNode::class_ = NULL;

void ForLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_for",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ForLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ForLoopExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
