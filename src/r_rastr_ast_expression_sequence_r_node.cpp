#include "r_rastr_ast_expression_sequence_r_node.h"
#include "ExpressionSequenceRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;

SEXP r_rastr_ast_expression_sequence_r_node_create() {
    ExpressionSequenceRNodeSPtr node =
        std::make_shared<ExpressionSequenceRNode>();

    return to_sexp<ExpressionSequenceRNode>(node);
}

SEXP r_rastr_ast_expression_sequence_r_node_get_size(SEXP r_node) {
    ExpressionSequenceRNodeSPtr node =
        from_sexp<ExpressionSequenceRNode>(r_node);

    int size = node->get_size();

    return ScalarInteger(size);
}

SEXP r_rastr_ast_expression_sequence_r_node_get_element(SEXP r_node,
                                                        SEXP r_index) {
    ExpressionSequenceRNodeSPtr node =
        from_sexp<ExpressionSequenceRNode>(r_node);

    int index = asInteger(r_index);

    ExpressionRNodeSPtr element = node->get_element(index);

    return to_sexp<ExpressionRNode>(element);
}

SEXP r_rastr_ast_expression_sequence_r_node_set_element(SEXP r_node,
                                                        SEXP r_index,
                                                        SEXP r_element) {
    ExpressionSequenceRNodeSPtr node =
        from_sexp<ExpressionSequenceRNode>(r_node);

    int index = asInteger(r_index);

    ExpressionRNodeSPtr element = from_sexp<ExpressionRNode>(r_element);

    node->set_element(index, element);

    return r_node;
}

SEXP r_rastr_ast_expression_sequence_r_node_push_back(SEXP r_node,
                                                      SEXP r_element) {
    ExpressionSequenceRNodeSPtr node =
        from_sexp<ExpressionSequenceRNode>(r_node);

    ExpressionRNodeSPtr element = from_sexp<ExpressionRNode>(r_element);

    node->push_back(element);

    return r_node;
}
