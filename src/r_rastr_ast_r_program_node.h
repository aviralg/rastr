#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_r_program_node_create(SEXP r_begin,
                                       SEXP r_expressions,
                                       SEXP r_end);
SEXP r_rastr_ast_r_program_node_is_well_formed(SEXP r_node);
SEXP r_rastr_ast_r_program_node_get_syntax_error(SEXP r_node);
SEXP r_rastr_ast_r_program_node_set_syntax_error(SEXP r_node,
                                                 SEXP r_syntax_error);
}
