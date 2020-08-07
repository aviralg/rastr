#include "r_rastr_ast_terminated_parameter_r_node.h"
#include "TerminatedParameterRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ParameterRNode;
using rastr::ast::ParameterRNodeSPtr;
using rastr::ast::TerminatedParameterRNode;
using rastr::ast::TerminatedParameterRNodeSPtr;

SEXP r_rastr_ast_terminated_parameter_r_node_create(SEXP r_parameter,
                                                    SEXP r_delimiter) {
    ParameterRNodeSPtr parameter = from_sexp<ParameterRNode>(r_parameter);
    DelimiterRNodeSPtr delimiter = from_sexp<DelimiterRNode>(r_delimiter);

    TerminatedParameterRNodeSPtr node =
        std::make_shared<TerminatedParameterRNode>(parameter, delimiter);
    return to_sexp<TerminatedParameterRNode>(node);
}
