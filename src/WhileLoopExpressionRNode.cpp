#include "WhileLoopExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP WhileLoopExpressionRNode::class_ = NULL;

void WhileLoopExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_loop_while",
                                  "rastr_ast_node_r_expression_loop",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_keyword_i",
                                  "rastr_ast_body_i",
                                  "rastr_ast_condition_i"});
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
