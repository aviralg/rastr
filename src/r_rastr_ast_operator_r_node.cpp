#include "r_rastr_ast_operator_r_node.h"
#include "OperatorRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;

SEXP r_rastr_ast_operator_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    OperatorRNodeSPtr node = std::make_shared<OperatorRNode>(representation);

    return to_sexp<OperatorRNode>(node);
}
