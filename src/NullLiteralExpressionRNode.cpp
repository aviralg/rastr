#include "NullLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP NullLiteralExpressionRNode::class_ = NULL;

void NullLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_literal_null",
                                  "rastr_ast_node_r_expression_literal",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_representation_i"});
    R_PreserveObject(class_);
}

void NullLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP NullLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
