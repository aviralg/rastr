#include "WhileLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP WhileLoopExpressionRNode::class_ = NULL;

void WhileLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_loop_while",
                                  "rastr_node_r_expression_loop",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void WhileLoopExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP WhileLoopExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
