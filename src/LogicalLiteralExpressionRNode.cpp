#include "LogicalLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP LogicalLiteralExpressionRNode::class_ = NULL;

void LogicalLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_logical",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void LogicalLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP LogicalLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
