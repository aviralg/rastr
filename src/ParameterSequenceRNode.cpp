#include "ParameterSequenceRNode.hpp"

namespace rastr {
namespace ast {

SEXP ParameterSequenceRNode::class_ = NULL;

void ParameterSequenceRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_sequence_parameter",
                                  "rastr_node_r_sequence",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ParameterSequenceRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ParameterSequenceRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
