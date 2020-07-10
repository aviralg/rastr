#include "r_character_literal_expression_r_node.h"
#include "CharacterLiteralExpressionRNode.hpp"

using rastr::ast::CharacterLiteralExpressionRNode;
using rastr::ast::CharacterLiteralExpressionRNodeSPtr;

SEXP r_character_literal_expression_r_node_create(SEXP r_value) {
    const char* value = CHAR(asChar(r_value));

    CharacterLiteralExpressionRNodeSPtr node =
        std::make_shared<CharacterLiteralExpressionRNode>(value);

    return CharacterLiteralExpressionRNode::to_sexp(node);
}

SEXP r_character_literal_expression_r_node_get_value(SEXP r_node) {
    CharacterLiteralExpressionRNodeSPtr node =
        CharacterLiteralExpressionRNode::from_sexp(r_node);

    const std::string& value = node->get_value();

    return mkString(value.c_str());
}

SEXP r_character_literal_expression_r_node_set_value(SEXP r_node,
                                                     SEXP r_value) {
    CharacterLiteralExpressionRNodeSPtr node =
        CharacterLiteralExpressionRNode::from_sexp(r_node);

    const char* value = CHAR(asChar(r_value));

    node->set_value(value);

    return r_node;
}
