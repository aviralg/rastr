#include <rastr/api.h>
#include <iostream>
#include "utilities.h"
#include "Parser.h"

rastr_ast_t rastr_parse_str(const char* str) {
    Input input(str, std::strlen(str));

    Parser parser(input, 16);
    rastr_ast_t ast = parser.parse_prog();
    std::cerr << "reached here!" << std::endl;
    std::cerr << rastr_ast_to_string(ast) << std::endl;
    //
    //rastr_node_t node;
    //rastr_node_type_t type;
    //
    //do {
    //    node = lexer.next_token();
    //    type = rastr_node_type(ast, node);
    //    std::cerr << rastr_node_to_string(ast, node) << std::endl;
    //} while (type != End);

    return ast;
}

SEXP r_rastr_parse_str(SEXP r_string) {
    SEXPTYPE type = TYPEOF(r_string);

    if (type != STRSXP) {
        Rf_error("expected a value of type string, received a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_string);

    if (length != 1) {
        Rf_error("expected a string vector of size 1, received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_string, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ instead");
        return R_NilValue;
    }

    rastr_ast_t ast = rastr_parse_str(CHAR(str_elt));

    return r_rastr_ast_to_sexp(ast);
}


rastr_ast_t rastr_parse_file(const char* filepath) {
    std::string content = read_file(filepath);
    return rastr_parse_str(content.c_str());
}

SEXP r_rastr_parse_file(SEXP r_filepath) {
    SEXPTYPE type = TYPEOF(r_filepath);

    if (type != STRSXP) {
        Rf_error("expected a filepath of type string, received a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_filepath);

    if (length != 1) {
        Rf_error("expected a filepath string of size 1, received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_filepath, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ instead");
        return R_NilValue;
    }

    const char* filepath = CHAR(str_elt);

    if (!file_exists(filepath)) {
        Rf_error("failed to open file '%s'", filepath);
        return R_NilValue;
    }

    rastr_ast_t ast = rastr_parse_file(CHAR(str_elt));

    return r_rastr_ast_to_sexp(ast);
}
