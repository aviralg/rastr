#include "rastr.hpp"

namespace rastr {

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

SEXP create_class(const std::vector<std::string>& class_names) {
    int size = class_names.size();

    SEXP r_class_names = PROTECT(allocVector(VECSXP, size));

    for (int index = 0; index < size; ++index) {
        SET_VECTOR_ELT(
            r_class_names, index, mkString(class_names[index].c_str()));
    }

    UNPROTECT(1);

    return r_class_names;
}

} // namespace rastr
