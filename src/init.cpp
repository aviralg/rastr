#include "CharacterLiteralExpressionRNode.hpp"
#include "ComplexLiteralExpressionRNode.hpp"
#include "DoubleLiteralExpressionRNode.hpp"
#include "IntegerLiteralExpressionRNode.hpp"
#include "LogicalLiteralExpressionRNode.hpp"
#include "RawLiteralExpressionRNode.hpp"

#include <R_ext/Rdynload.h>
#include <stdio.h>

extern "C" {

static const R_CallMethodDef CallEntries[] = {{NULL, NULL, 0}};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
}
