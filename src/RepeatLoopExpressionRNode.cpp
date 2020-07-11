#include "RepeatLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP RepeatLoopExpressionRNode::class_ = NULL;

void RepeatLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_repeat",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void RepeatLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RepeatLoopExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
