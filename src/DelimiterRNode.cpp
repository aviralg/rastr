#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

SEXP DelimiterRNode::class_ = NULL;

void DelimiterRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_delimiter", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void DelimiterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DelimiterRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
