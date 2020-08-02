#include "BlockExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP BlockExpressionRNode::class_ = NULL;

void BlockExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_block",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_bounded_i",
                                  "rastr_ast_expressions_i"});
    R_PreserveObject(class_);
}

void BlockExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BlockExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
