#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_parameter_sequence_r_node_create();

SEXP r_rastr_ast_parameter_sequence_r_node_get_size(SEXP r_node);

SEXP r_rastr_ast_parameter_sequence_r_node_get_element(SEXP r_node,
                                                       SEXP r_index);

SEXP r_rastr_ast_parameter_sequence_r_node_set_element(SEXP r_node,
                                                       SEXP r_index,
                                                       SEXP r_element);

SEXP r_rastr_ast_parameter_sequence_r_node_push_back(SEXP r_node,
                                                     SEXP r_element);
}
