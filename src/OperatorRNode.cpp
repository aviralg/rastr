#include "OperatorRNode.hpp"

namespace rastr {
namespace ast {

SEXP OperatorRNode::class_ = NULL;

void OperatorRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_operator", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void OperatorRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP OperatorRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
