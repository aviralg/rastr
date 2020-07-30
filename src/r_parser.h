#include "RIncludes.hpp"

extern "C" {
SEXP r_parser_parse_stdin();
SEXP r_parser_parse_string(SEXP r_string);
SEXP r_parser_parse_file(SEXP r_filename);
}
