#include "FunctionDefinitionExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP FunctionDefinitionExpressionRNode::class_ = NULL;

void FunctionDefinitionExpressionRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_ast_node_r_expression_definition_function",
                             "rastr_ast_node_r_expression",
                             "rastr_ast_node_r",
                             "rastr_ast_node",
                             "rastr_ast_keyword_i",
                             "rastr_ast_bounded_i",
                             "rastr_ast_body_i"});
    R_PreserveObject(class_);
}

void FunctionDefinitionExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP FunctionDefinitionExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
