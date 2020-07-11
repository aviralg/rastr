#include "InRNode.hpp"

namespace rastr {
namespace ast {

SEXP InRNode::class_ = NULL;

void InRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_node_r_in", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void InRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP InRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
