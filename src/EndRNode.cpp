#include "EndRNode.hpp"

namespace rastr {
namespace ast {

SEXP EndRNode::class_ = NULL;

void EndRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_node_r_end", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void EndRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP EndRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
