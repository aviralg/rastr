#include "r_operator_r_node.h"
#include "OperatorRNode.hpp"

using rastr::from_sexp;
using rastr::to_sexp;
using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;

SEXP r_operator_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    OperatorRNodeSPtr node = std::make_shared<OperatorRNode>(representation);

    return to_sexp<OperatorRNode>(node);
}

SEXP r_operator_r_node_get_representation(SEXP r_node) {
    OperatorRNodeSPtr node = from_sexp<OperatorRNode>(r_node);

    const std::string& representation = node->get_representation();

    return mkString(representation.c_str());
}
