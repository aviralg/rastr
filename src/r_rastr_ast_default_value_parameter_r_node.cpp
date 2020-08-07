#include "r_rastr_ast_default_value_parameter_r_node.h"
#include "DefaultValueParameterRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DefaultValueParameterRNode;
using rastr::ast::DefaultValueParameterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;
using rastr::ast::SymbolRNode;
using rastr::ast::SymbolRNodeSPtr;

SEXP r_rastr_ast_default_value_parameter_r_node_create(SEXP r_op,
                                                       SEXP r_name,
                                                       SEXP r_value) {
    OperatorRNodeSPtr op = from_sexp<OperatorRNode>(r_op);

    SymbolRNodeSPtr name = from_sexp<SymbolRNode>(r_name);

    ExpressionRNodeSPtr value = from_sexp<ExpressionRNode>(r_value);

    DefaultValueParameterRNodeSPtr node =
        std::make_shared<DefaultValueParameterRNode>(op, name, value);

    return to_sexp<DefaultValueParameterRNode>(node);
}
