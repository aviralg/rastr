#include "RIncludes.hpp"

extern "C" {
SEXP r_function_definition_expression_r_node_create(SEXP r_keyword,
                                                    SEXP r_parameters,
                                                    SEXP r_body);
SEXP r_function_definition_expression_r_node_get_keyword(SEXP r_node);
SEXP r_function_definition_expression_r_node_set_keyword(SEXP r_node,
                                                         SEXP r_keyword);
SEXP r_function_definition_expression_r_node_get_body(SEXP r_node);
SEXP r_function_definition_expression_r_node_set_body(SEXP r_node, SEXP r_body);
SEXP r_function_definition_expression_r_node_get_parameters(SEXP r_node);
SEXP r_function_definition_expression_r_node_set_parameters(SEXP r_node,
                                                            SEXP r_parameters);
}
