#include "r_rastr_ast_parameter_sequence_r_node.h"
#include "ParameterSequenceRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ParameterRNode;
using rastr::ast::ParameterRNodeSPtr;
using rastr::ast::ParameterSequenceRNode;
using rastr::ast::ParameterSequenceRNodeSPtr;

SEXP r_rastr_ast_parameter_sequence_r_node_create() {
    ParameterSequenceRNodeSPtr node =
        std::make_shared<ParameterSequenceRNode>();

    return to_sexp<ParameterSequenceRNode>(node);
}

SEXP r_rastr_ast_parameter_sequence_r_node_get_size(SEXP r_node) {
    ParameterSequenceRNodeSPtr node = from_sexp<ParameterSequenceRNode>(r_node);

    int size = node->get_size();

    return ScalarInteger(size);
}

SEXP r_rastr_ast_parameter_sequence_r_node_get_element(SEXP r_node,
                                                       SEXP r_index) {
    ParameterSequenceRNodeSPtr node = from_sexp<ParameterSequenceRNode>(r_node);

    int index = asInteger(r_index);

    ParameterRNodeSPtr element = node->get_element(index);

    return to_sexp<ParameterRNode>(element);
}

SEXP r_rastr_ast_parameter_sequence_r_node_set_element(SEXP r_node,
                                                       SEXP r_index,
                                                       SEXP r_element) {
    ParameterSequenceRNodeSPtr node = from_sexp<ParameterSequenceRNode>(r_node);

    int index = asInteger(r_index);

    ParameterRNodeSPtr element = from_sexp<ParameterRNode>(r_element);

    node->set_element(index, element);

    return r_node;
}

SEXP r_rastr_ast_parameter_sequence_r_node_push_back(SEXP r_node,
                                                     SEXP r_element) {
    ParameterSequenceRNodeSPtr node = from_sexp<ParameterSequenceRNode>(r_node);

    ParameterRNodeSPtr element = from_sexp<ParameterRNode>(r_element);

    node->push_back(element);

    return r_node;
}
