#include "DoubleLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP DoubleLiteralExpressionRNode::class_ = NULL;

void DoubleLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_double",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void DoubleLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DoubleLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
