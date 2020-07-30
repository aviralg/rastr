#include "RIncludes.hpp"

extern "C" {
SEXP r_character_literal_expression_r_node_create(SEXP r_representation);
SEXP r_character_literal_expression_r_node_get_representation(SEXP r_node);
SEXP r_character_literal_expression_r_node_set_representation(
    SEXP r_node,
    SEXP r_representation);
}
