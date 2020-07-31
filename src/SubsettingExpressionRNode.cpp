#include "SubsettingExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP SubsettingExpressionRNode::class_ = NULL;

void SubsettingExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_subsetting",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void SubsettingExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SubsettingExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
