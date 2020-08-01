#include "FunctionCallExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP FunctionCallExpressionRNode::class_ = NULL;

void FunctionCallExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_call_function",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_bounded_i"});
    R_PreserveObject(class_);
}

void FunctionCallExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP FunctionCallExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
