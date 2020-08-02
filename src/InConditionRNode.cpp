#include "InConditionRNode.hpp"

namespace rastr {
namespace ast {

SEXP InConditionRNode::class_ = NULL;

void InConditionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_condition_in",
                                  "rastr_ast_node_r_condition",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_bounded_i",
                                  "rastr_ast_symbol_i",
                                  "rastr_ast_keyword_i",
                                  "rastr_ast_expression_i"});
    R_PreserveObject(class_);
}

void InConditionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP InConditionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
