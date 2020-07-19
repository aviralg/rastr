#include "IndexSequenceRNode.hpp"

namespace rastr {
namespace ast {

SEXP IndexSequenceRNode::class_ = NULL;

void IndexSequenceRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_sequence_index",
                                  "rastr_node_r_sequence_expression",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void IndexSequenceRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IndexSequenceRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
