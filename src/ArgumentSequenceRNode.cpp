#include "ArgumentSequenceRNode.hpp"

namespace rastr {
namespace ast {

SEXP ArgumentSequenceRNode::class_ = NULL;

void ArgumentSequenceRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_sequence_argument",
                                  "rastr_node_r_sequence_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ArgumentSequenceRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ArgumentSequenceRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
