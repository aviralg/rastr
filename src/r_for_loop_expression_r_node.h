#include <R.h>
#include <R_ext/Error.h>
#include <Rdefines.h>

extern "C" {
SEXP r_for_loop_expression_r_node_create(SEXP r_keyword,
                                         SEXP r_condition,
                                         SEXP r_body);
SEXP r_for_loop_expression_r_node_get_condition(SEXP r_node);
SEXP r_for_loop_expression_r_node_set_condition(SEXP r_node, SEXP r_condition);
}
