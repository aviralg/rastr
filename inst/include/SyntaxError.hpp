#ifndef RASTR_R_PARSER_SYNTAX_ERROR_HPP
#define RASTR_R_PARSER_SYNTAX_ERROR_HPP

#include <string>
#include "Location.hpp"
#include "rastr.hpp"

namespace rastr {
namespace parser {

class SyntaxError {
  public:
    SyntaxError(): valid_(false) {
    }

    SyntaxError(Location& location, std::string& description)
        : valid_(true), location_(location), description_(description) {
    }

    bool is_valid() const {
        return valid_;
    }

    const Location& get_location() const {
        return location_;
    }

    const std::string& get_description() const {
        return description_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    bool valid_;
    Location location_;
    std::string description_;

    static SEXP class_;
};

using SyntaxErrorSPtr = std::shared_ptr<SyntaxError>;

} // namespace parser
} // namespace rastr

#endif /* RASTR_R_PARSER_SYNTAX_ERROR_HPP */
