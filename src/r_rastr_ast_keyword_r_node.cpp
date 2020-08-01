#include "r_rastr_ast_keyword_r_node.h"
#include "KeywordRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_keyword_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    KeywordRNodeSPtr node = std::make_shared<KeywordRNode>(representation);

    return to_sexp<KeywordRNode>(node);
}
