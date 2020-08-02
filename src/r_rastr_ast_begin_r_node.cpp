#include "r_rastr_ast_begin_r_node.h"
#include "BeginRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BeginRNode;
using rastr::ast::BeginRNodeSPtr;

SEXP r_rastr_ast_begin_r_node_create() {
    BeginRNodeSPtr node = std::make_shared<BeginRNode>();

    return to_sexp<BeginRNode>(node);
}
