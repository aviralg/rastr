#include "SyntaxError.hpp"

namespace rastr {
namespace parser {

SEXP SyntaxError::class_ = NULL;

void SyntaxError::initialize() {
    class_ = rastr::create_class({"rastr_parser_error_syntax"});
    R_PreserveObject(class_);
}

void SyntaxError::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SyntaxError::get_class() {
    return class_;
}

} // namespace parser
} // namespace rastr
