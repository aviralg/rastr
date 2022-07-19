#include <rastr/api.h>
#include "Lexer.h"
#include <iostream>
#include "utilities.h"

// void parse_file(const std::string filepath) {
//     FILE* file = fopen(filepath.c_str(), "r");
//     if (file == NULL) {
//         fputs("cannot open file", stderr);
//         exit(1);
//     }
//
//     // obtain file size:
//     fseek(file, 0, SEEK_END);
//     std::size_t length = ftell(file);
//     rewind(file);
//
//     // allocate memory to contain the whole file:
//     char* buffer = (char*) malloc(sizeof(char) * length);
//     if (buffer == NULL) {
//         fputs("Memory error", stderr);
//         exit(2);
//     }
//
//     // copy the file into the buffer:
//     std::size_t bytes_read = fread(buffer, sizeof(char), length, file);
//     if (bytes_read != length) {
//         fputs("Reading error", stderr);
//         exit(3);
//     }
//
//     /* the whole file is now loaded in the memory buffer. */
//
//     // terminate
//     fclose(file);
//
//
//
// }

rastr_ast_t rastr_parse_str(const char* str) {
    Input input(str, std::strlen(str));

    rastr_ast_t ast = rastr_ast_create(16);

    Lexer lexer(input, ast);

    rastr_node_t node;
    rastr_node_type_t type;

    do {
        node = lexer.next_token();
        type = rastr_node_type(ast, node);
        std::cerr << rastr_node_to_string(ast, node) << std::endl;
    } while (type != End);

    return ast;
}

rastr_ast_t rastr_parse_file(const char* filepath) {
    std::string content = read_file(filepath);
    return rastr_parse_str(content.c_str());
}
