#include "rastr.hpp"

namespace rastr {
namespace ast {

SEXP UndefinedObject = NULL;

SEXP get_undefined_object() {
    return UndefinedObject;
}

bool is_undefined_object(SEXP object) {
    return object == UndefinedObject;
}

bool is_defined_object(SEXP object) {
    return !(is_undefined_object(object));
}

} // namespace ast
} // namespace rastr
