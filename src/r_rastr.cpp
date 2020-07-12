#include "r_rastr.h"
#include "rastr.hpp"

SEXP r_rastr_initialize() {
    rastr::initialize();
    return R_NilValue;
}
