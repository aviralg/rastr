#include "SpacingRNode.hpp"

namespace rastr {
namespace ast {

SEXP SpacingRNode::class_ = NULL;

void SpacingRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_spacing", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void SpacingRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SpacingRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
