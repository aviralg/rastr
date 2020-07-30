#ifndef RASTR_R_PARSER_SYNTAX_ERROR_HPP
#define RASTR_R_PARSER_SYNTAX_ERROR_HPP

#include <string>
#include "Location.hpp"

namespace rastr {
namespace r {
namespace parser {

class SyntaxError {
  public:
    SyntaxError(): valid_(false) {
    }

    SyntaxError(rastr::r::parser::Location& location, std::string& description)
        : valid_(true), location_(location), description_(description) {
    }

    bool is_valid() const {
        return valid_;
    }

    const rastr::r::parser::Location& get_location() const {
        return location_;
    }

    const std::string& get_description() const {
        return description_;
    }

  private:
    bool valid_;
    rastr::r::parser::Location location_;
    std::string description_;
};

} // namespace parser
} // namespace r
} // namespace rastr

#endif /* RASTR_R_PARSER_SYNTAX_ERROR_HPP */
