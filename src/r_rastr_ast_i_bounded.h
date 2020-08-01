#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_i_bounded_get_opening_delimiter(SEXP r_i_bounded);
SEXP r_rastr_ast_i_bounded_set_opening_delimiter(SEXP r_i_bounded,
                                                 SEXP r_opening_delimiter);
SEXP r_rastr_ast_i_bounded_get_closing_delimiter(SEXP r_i_bounded);
SEXP r_rastr_ast_i_bounded_set_closing_delimiter(SEXP r_i_bounded,
                                                 SEXP r_closing_delimiter);
}
