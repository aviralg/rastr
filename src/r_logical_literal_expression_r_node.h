#include <R.h>
#include <R_ext/Error.h>
#include <Rdefines.h>

extern "C" {
SEXP r_logical_literal_expression_r_node_create(SEXP r_value);
SEXP r_logical_literal_expression_r_node_get_value(SEXP r_node);
SEXP r_logical_literal_expression_r_node_set_value(SEXP r_node, SEXP r_value);
}
