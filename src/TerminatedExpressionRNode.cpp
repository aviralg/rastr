#include "TerminatedExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP TerminatedExpressionRNode::class_ = NULL;

void TerminatedExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_terminated",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void TerminatedExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP TerminatedExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
