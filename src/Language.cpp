#include "Language.hpp"

namespace rastr {
namespace ast {

const std::string language_to_string(const Language language) {
    switch (language) {
    case Language::R:
        return "R";
    case Language::C:
        return "C";
    case Language::CPP:
        return "C++";
    case Language::Undefined:
        return "Undefined";
    }
    return "Undefined";
}

Language string_to_language(const std::string& language) {
    if (language == "R") {
        return Language::R;
    } else if (language == "C") {
        return Language::C;
    } else if (language == "C++") {
        return Language::CPP;
    } else {
        return Language::Undefined;
    }
}

} // namespace ast
} // namespace rastr
