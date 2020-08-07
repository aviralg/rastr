#include "r_rastr_ast_non_default_value_parameter_r_node.h"
#include "NonDefaultValueParameterRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::NonDefaultValueParameterRNode;
using rastr::ast::NonDefaultValueParameterRNodeSPtr;
using rastr::ast::SymbolRNode;
using rastr::ast::SymbolRNodeSPtr;

SEXP r_rastr_ast_non_default_value_parameter_r_node_create(SEXP r_name) {
    SymbolRNodeSPtr name = from_sexp<SymbolRNode>(r_name);

    NonDefaultValueParameterRNodeSPtr node =
        std::make_shared<NonDefaultValueParameterRNode>(name);
    return to_sexp<NonDefaultValueParameterRNode>(node);
}
