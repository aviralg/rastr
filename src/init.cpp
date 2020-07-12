#include "r_rastr.h"
#include "r_character_literal_expression_r_node.h"
#include "r_complex_literal_expression_r_node.h"
#include "r_double_literal_expression_r_node.h"
#include "r_integer_literal_expression_r_node.h"
#include "r_logical_literal_expression_r_node.h"
#include "r_raw_literal_expression_r_node.h"

#include <R_ext/Rdynload.h>
#include <stdio.h>

extern "C" {

static const R_CallMethodDef CallEntries[] = {
    /* character_literal_expression_r_node */
    {"character_literal_expression_r_node_create", (DL_FUNC) &r_character_literal_expression_r_node_create, 1},
    {"character_literal_expression_r_node_get_representation", (DL_FUNC) &r_character_literal_expression_r_node_get_representation, 1},
    {"character_literal_expression_r_node_set_representation", (DL_FUNC) &r_character_literal_expression_r_node_set_representation, 2},

    /* complex_literal_expression_r_node */
    {"complex_literal_expression_r_node_create", (DL_FUNC) &r_complex_literal_expression_r_node_create, 1},
    {"complex_literal_expression_r_node_get_representation", (DL_FUNC) &r_complex_literal_expression_r_node_get_representation, 1},
    {"complex_literal_expression_r_node_set_representation", (DL_FUNC) &r_complex_literal_expression_r_node_set_representation, 2},

    /* double_literal_expression_r_node */
    {"double_literal_expression_r_node_create", (DL_FUNC) &r_double_literal_expression_r_node_create, 1},
    {"double_literal_expression_r_node_get_representation", (DL_FUNC) &r_double_literal_expression_r_node_get_representation, 1},
    {"double_literal_expression_r_node_set_representation", (DL_FUNC) &r_double_literal_expression_r_node_set_representation, 2},

    /* integer_literal_expression_r_node */
    {"integer_literal_expression_r_node_create", (DL_FUNC) &r_integer_literal_expression_r_node_create, 1},
    {"integer_literal_expression_r_node_get_representation", (DL_FUNC) &r_integer_literal_expression_r_node_get_representation, 1},
    {"integer_literal_expression_r_node_set_representation", (DL_FUNC) &r_integer_literal_expression_r_node_set_representation, 2},

    /* logical_literal_expression_r_node */
    {"logical_literal_expression_r_node_create", (DL_FUNC) &r_logical_literal_expression_r_node_create, 1},
    {"logical_literal_expression_r_node_get_representation", (DL_FUNC) &r_logical_literal_expression_r_node_get_representation, 1},
    {"logical_literal_expression_r_node_set_representation", (DL_FUNC) &r_logical_literal_expression_r_node_set_representation, 2},

    /* raw_literal_expression_r_node */
    {"raw_literal_expression_r_node_create", (DL_FUNC) &r_raw_literal_expression_r_node_create, 1},
    {"raw_literal_expression_r_node_get_representation", (DL_FUNC) &r_raw_literal_expression_r_node_get_representation, 1},
    {"raw_literal_expression_r_node_set_representation", (DL_FUNC) &r_raw_literal_expression_r_node_set_representation, 2},

    {NULL, NULL, 0}
};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    r_rastr_initialize();
}
}
