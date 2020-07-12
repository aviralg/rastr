#ifndef RASTR_RASTR_HPP
#define RASTR_RASTR_HPP

#include <Rinternals.h>
#include <memory>
#include <vector>
#include <string>

namespace rastr {

SEXP get_undefined_object();

bool is_undefined_object(SEXP object);

bool is_defined_object(SEXP object);

SEXP create_class(const std::vector<std::string>& class_names);

template <typename T>
void destroy_sexp(SEXP r_node) {
    delete static_cast<std::shared_ptr<T>*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

template <typename T>
std::shared_ptr<T> from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("from_sexp: object is null");
    } else {
        return *static_cast<std::shared_ptr<T>*>(node);
    }
}

template <typename T>
SEXP to_sexp(std::shared_ptr<T> node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new std::shared_ptr<T>(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, destroy_sexp<T>, TRUE);

    setAttrib(r_node, R_ClassSymbol, T::get_class());

    UNPROTECT(1);

    return r_node;
}

void initialize();

} // namespace rastr

#endif /* RASTR_RASTR_HPP */
