#include "BlockExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP BlockExpressionRNode::class_ = NULL;

void BlockExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_block",
                                  "rastr_node_r_sequence_expression",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void BlockExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BlockExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
