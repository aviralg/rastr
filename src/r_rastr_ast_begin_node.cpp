#include "r_rastr_ast_begin_node.h"
#include "BeginNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BeginNode;
using rastr::ast::BeginNodeSPtr;

SEXP r_rastr_ast_begin_node_create() {
    BeginNodeSPtr node = std::make_shared<BeginNode>();

    return to_sexp<BeginNode>(node);
}
