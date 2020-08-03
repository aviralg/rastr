#include "r_rastr_ast_end_node.h"
#include "EndNode.hpp"
#include "r_cast.hpp"

using rastr::ast::EndNode;
using rastr::ast::EndNodeSPtr;

SEXP r_rastr_ast_end_node_create() {
    EndNodeSPtr node = std::make_shared<EndNode>();

    return to_sexp<EndNode>(node);
}
