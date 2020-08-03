#include "IfElseConditionalExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IfElseConditionalExpressionRNode::class_ = NULL;

void IfElseConditionalExpressionRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_ast_node_r_expression_conditional_else_if",
                             "rastr_ast_node_r_expression_conditional",
                             "rastr_ast_node_r_expression",
                             "rastr_ast_node_r",
                             "rastr_ast_node",
                             "rastr_ast_condition_i"});
    R_PreserveObject(class_);
}

void IfElseConditionalExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IfElseConditionalExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
