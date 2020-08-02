#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_i_expression_get_expression(SEXP r_i_expression);
SEXP r_rastr_ast_i_expression_set_expression(SEXP r_i_expression,
                                             SEXP r_expression);
}
