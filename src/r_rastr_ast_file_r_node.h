#include "RIncludes.hpp"

extern "C" {
SEXP r_rastr_ast_file_r_node_create(SEXP r_filepath, SEXP r_program);
SEXP r_rastr_ast_file_r_node_get_filepath(SEXP r_node);
SEXP r_rastr_ast_file_r_node_set_filepath(SEXP r_node, SEXP r_filepath);
SEXP r_rastr_ast_file_r_node_get_program(SEXP r_node);
SEXP r_rastr_ast_file_r_node_set_program(SEXP r_node, SEXP r_program);
}
