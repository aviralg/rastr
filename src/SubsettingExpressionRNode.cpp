#include "SubsettingExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP SubsettingExpressionRNode::class_ = NULL;

void SubsettingExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_subsetting",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_object_i",
                                  "rastr_ast_bounded_i",
                                  "rastr_ast_indices_i"});
    R_PreserveObject(class_);
}

void SubsettingExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SubsettingExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
