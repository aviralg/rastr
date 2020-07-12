#include "FunctionDefinitionExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP FunctionDefinitionExpressionRNode::class_ = NULL;

void FunctionDefinitionExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_definition_function",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
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
