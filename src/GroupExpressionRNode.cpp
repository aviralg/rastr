#include "GroupExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP GroupExpressionRNode::class_ = NULL;

void GroupExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_group",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_bounded_i",
                                  "rastr_ast_body_i"});
    R_PreserveObject(class_);
}

void GroupExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP GroupExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
