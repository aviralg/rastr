#include <R.h>
#include <R_ext/Error.h>
#include <Rdefines.h>

extern "C" {
SEXP r_loop_expression_r_node_get_keyword(SEXP r_node);
SEXP r_loop_expression_r_node_set_keyword(SEXP r_node, SEXP r_keyword);
SEXP r_loop_expression_r_node_get_body(SEXP r_node);
SEXP r_loop_expression_r_node_set_body(SEXP r_node, SEXP r_body);
}
