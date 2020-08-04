#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_in_condition_r_node_create(SEXP r_opening_delimiter,
                                            SEXP r_symbol,
                                            SEXP r_keyword,
                                            SEXP r_expression,
                                            SEXP r_closing_delimiter);
}
