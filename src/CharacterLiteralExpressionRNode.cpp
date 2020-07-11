#include "CharacterLiteralExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP CharacterLiteralExpressionRNode::class_ = NULL;

void CharacterLiteralExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_literal_character",
                                  "rastr_node_r_expression_literal",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
    R_PreserveObject(class_);
}

void CharacterLiteralExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP CharacterLiteralExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
