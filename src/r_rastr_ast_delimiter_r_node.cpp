#include "r_rastr_ast_delimiter_r_node.h"
#include "DelimiterRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;

SEXP r_rastr_ast_delimiter_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    DelimiterRNodeSPtr node = std::make_shared<DelimiterRNode>(representation);

    return to_sexp<DelimiterRNode>(node);
}
