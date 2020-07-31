#include "ast.hpp"
#include "parser.hpp"
#include "Lexer.hpp"
#include "Parser.hxx"

#include <fstream>
#include <sstream>

namespace rastr {
namespace r {
namespace parser {

using rastr::ast::ProgramRNode;
using rastr::ast::ProgramRNodeSPtr;

void check_filepath(const std::string& filepath) {
    std::ifstream fin(filepath);
    if (!fin.good()) {
        std::cerr << "Error: path '" << filepath << "' does not exist!";
        exit(1);
    }
}

ProgramRNodeSPtr parse_(std::istream& input_stream,
                        const std::string& input_stream_name,
                        bool debug_lexer,
                        bool debug_parser) {
    ProgramRNodeSPtr program;
    Lexer lexer(input_stream);
    Parser parser(lexer, program);
    parser.parse();
    std::cout << "Size is " << program->get_expressions()->get_size()
              << std::endl;
    return program;
}

ProgramRNodeSPtr parse_stdin(bool debug_lexer, bool debug_parser) {
    std::string input_stream_name("<stdin>");
    return parse_(std::cin, input_stream_name, debug_lexer, debug_parser);
}

ProgramRNodeSPtr
parse_string(const char* string, bool debug_lexer, bool debug_parser) {
    std::istringstream input_stream(string);
    std::string input_stream_name("<string>");
    return parse_(input_stream, input_stream_name, debug_lexer, debug_parser);
}

ProgramRNodeSPtr
parse_file(const std::string& filepath, bool debug_lexer, bool debug_parser) {
    /*  TODO: remove this check */
    check_filepath(filepath);
    std::ifstream input_stream(filepath);
    std::string input_stream_name(filepath);
    return parse_(input_stream, input_stream_name, debug_lexer, debug_parser);
}

} // namespace parser
} // namespace r
} // namespace rastr
