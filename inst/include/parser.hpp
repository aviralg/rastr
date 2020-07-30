#include "ast.hpp"
#include <string>

namespace rastr {
namespace r {
namespace parser {

using rastr::ast::ProgramRNodeSPtr;

ProgramRNodeSPtr parse_stdin(bool debug_lexer, bool debug_parser);

ProgramRNodeSPtr
parse_string(const char* string, bool debug_lexer, bool debug_parser);

ProgramRNodeSPtr
parse_file(const std::string& filepath, bool debug_lexer, bool debug_parser);

} // namespace parser
} // namespace r
} // namespace rastr
