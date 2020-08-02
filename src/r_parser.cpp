#include "r_parser.h"
#include "parser.hpp"
#include "r_cast.hpp"

using rastr::ast::FileRNode;
using rastr::ast::ProgramRNode;
using rastr::parser::parse_file;
using rastr::parser::parse_stdin;
using rastr::parser::parse_string;

SEXP r_parser_parse_stdin() {
    auto node = parse_stdin(false, false);

    return to_sexp<ProgramRNode>(node);
}

SEXP r_parser_parse_string(SEXP r_string) {
    auto node = parse_string(CHAR(STRING_ELT(r_string, 0)), false, false);

    return to_sexp<ProgramRNode>(node);
}

SEXP r_parser_parse_file(SEXP r_filename) {
    std::string filepath(CHAR(STRING_ELT(r_filename, 0)));

    auto node = parse_file(filepath, false, false);

    return to_sexp<FileRNode>(node);
}
