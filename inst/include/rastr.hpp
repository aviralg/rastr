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

void initialize();

} // namespace rastr

#endif /* RASTR_RASTR_HPP */
