#include "NonDefaultValueParameterRNode.hpp"

namespace rastr {
namespace ast {

SEXP NonDefaultValueParameterRNode::class_ = NULL;

void NonDefaultValueParameterRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_parameter_value_default_non",
                                  "rastr_node_r_parameter",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void NonDefaultValueParameterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP NonDefaultValueParameterRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
