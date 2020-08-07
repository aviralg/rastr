#include "TerminatedParameterRNode.hpp"

namespace rastr {
namespace ast {

SEXP TerminatedParameterRNode::class_ = NULL;

void TerminatedParameterRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_parameter_terminated",
                                  "rastr_node_r_parameter",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void TerminatedParameterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP TerminatedParameterRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
