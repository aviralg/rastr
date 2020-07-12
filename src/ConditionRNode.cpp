#include "ConditionRNode.hpp"

namespace rastr {
namespace ast {

SEXP ConditionRNode::class_ = NULL;

void ConditionRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_condition", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void ConditionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ConditionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
