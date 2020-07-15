#include "r_keyword_r_node.h"
#include "KeywordRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_keyword_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    KeywordRNodeSPtr node = std::make_shared<KeywordRNode>(representation);

    return to_sexp<KeywordRNode>(node);
}

SEXP r_keyword_r_node_get_representation(SEXP r_node) {
    KeywordRNodeSPtr node = from_sexp<KeywordRNode>(r_node);

    const std::string& representation = node->get_representation();

    return mkString(representation.c_str());
}
