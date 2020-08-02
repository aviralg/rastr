#include "r_rastr_ast_end_r_node.h"
#include "EndRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::EndRNode;
using rastr::ast::EndRNodeSPtr;

SEXP r_rastr_ast_end_r_node_create() {
    EndRNodeSPtr node = std::make_shared<EndRNode>();

    return to_sexp<EndRNode>(node);
}
