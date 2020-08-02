#include "ExpressionConditionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ExpressionConditionRNode::class_ = NULL;

void ExpressionConditionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_condition_expression",
                                  "rastr_ast_node_r_condition",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_bounded_i",
                                  "rastr_ast_expression_i"});
    R_PreserveObject(class_);
}

void ExpressionConditionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ExpressionConditionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
