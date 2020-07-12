#include "SeparatorRNode.hpp"

namespace rastr {
namespace ast {

SEXP SeparatorRNode::class_ = NULL;

void SeparatorRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_separator", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void SeparatorRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SeparatorRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
