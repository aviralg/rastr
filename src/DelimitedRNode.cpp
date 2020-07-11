#include "DelimitedRNode.hpp"

namespace rastr {
namespace ast {

SEXP DelimitedRNode::class_ = NULL;

void DelimitedRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_delimited", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void DelimitedRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DelimitedRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
