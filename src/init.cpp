#include "CharacterLiteralRNode.hpp"
#include "ComplexLiteralRNode.hpp"
#include "DoubleLiteralRNode.hpp"
#include "IntegerLiteralRNode.hpp"
#include "LogicalLiteralRNode.hpp"
#include "DoubleLiteralRNode.hpp"

#include <R_ext/Rdynload.h>
#include <stdio.h>

extern "C" {

static const R_CallMethodDef CallEntries[] = {{NULL, NULL, 0}};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
}
