#include "DefaultValueParameterRNode.hpp"

namespace rastr {
namespace ast {

SEXP DefaultValueParameterRNode::class_ = NULL;

void DefaultValueParameterRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_parameter_value_default",
                                  "rastr_node_r_parameter",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void DefaultValueParameterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DefaultValueParameterRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
