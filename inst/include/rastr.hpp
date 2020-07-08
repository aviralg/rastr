#ifndef RASTR_RASTR_HPP
#define RASTR_RASTR_HPP

#include <Rinternals.h>
#include <memory>

namespace rastr {

SEXP get_undefined_object();

bool is_undefined_object(SEXP object);

bool is_defined_object(SEXP object);

} // namespace rastr

#endif /* RASTR_RASTR_HPP */
