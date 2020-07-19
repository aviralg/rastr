#include "BoundedRNode.hpp"

namespace rastr {
namespace ast {

SEXP BoundedRNode::class_ = NULL;

void BoundedRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_bounded", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void BoundedRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BoundedRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
