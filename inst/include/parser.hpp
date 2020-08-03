#include "ast.hpp"
#include <string>

namespace rastr {
namespace parser {

using rastr::ast::RFileNodeSPtr;
using rastr::ast::RProgramNodeSPtr;

RProgramNodeSPtr parse_stdin(bool debug_lexer, bool debug_parser);

RProgramNodeSPtr
parse_string(const char* string, bool debug_lexer, bool debug_parser);

RFileNodeSPtr
parse_file(const std::string& filepath, bool debug_lexer, bool debug_parser);

} // namespace parser
} // namespace rastr
