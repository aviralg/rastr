#include "GroupExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP GroupExpressionRNode::class_ = NULL;

void GroupExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_group",
                                  "rastr_node_r_bounded",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
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
