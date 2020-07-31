#include "BeginRNode.hpp"

namespace rastr {
namespace ast {

SEXP BeginRNode::class_ = NULL;

void BeginRNode::initialize() {
    class_ =
        rastr::create_class({"rastr_node_r_begin", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void BeginRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BeginRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
