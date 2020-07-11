#include "IntegerLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IntegerLiteralExpressionRNode::class_ = NULL;

void IntegerLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_integer",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void IntegerLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IntegerLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
