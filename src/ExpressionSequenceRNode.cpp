#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

SEXP ExpressionSequenceRNode::class_ = NULL;

void ExpressionSequenceRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_sequence_expression",
                                  "rastr_node_r_sequence",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void ExpressionSequenceRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ExpressionSequenceRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
