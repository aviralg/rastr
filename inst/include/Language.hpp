#ifndef RASTR_AST_LANGUAGE_HPP
#define RASTR_AST_LANGUAGE_HPP

#include <string>

namespace rastr {
namespace ast {

enum class Language { R, C, CPP, Undefined };

const std::string language_to_string(const Language language);

Language string_to_language(const std::string& language);

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LANGUAGE_HPP */
