#include "r_rastr.h"
#include "r_character_literal_expression_r_node.h"
#include "r_complex_literal_expression_r_node.h"
#include "r_double_literal_expression_r_node.h"
#include "r_integer_literal_expression_r_node.h"
#include "r_logical_literal_expression_r_node.h"
#include "r_raw_literal_expression_r_node.h"
#include "r_operator_r_node.h"
#include "r_keyword_r_node.h"
#include "r_symbol_expression_r_node.h"
#include "r_function_definition_expression_r_node.h"
#include "r_loop_expression_r_node.h"
#include "r_for_loop_expression_r_node.h"
#include "r_while_loop_expression_r_node.h"
#include "r_repeat_loop_expression_r_node.h"

#include <R_ext/Rdynload.h>
#include <stdio.h>

extern "C" {

static const R_CallMethodDef CallEntries[] = {
    /* CharacterLiteralExpressionRNode */
    {"character_literal_expression_r_node_create", (DL_FUNC) &r_character_literal_expression_r_node_create, 1},
    {"character_literal_expression_r_node_get_representation", (DL_FUNC) &r_character_literal_expression_r_node_get_representation, 1},
    {"character_literal_expression_r_node_set_representation", (DL_FUNC) &r_character_literal_expression_r_node_set_representation, 2},

    /* ComplexLiteralExpressionRNode */
    {"complex_literal_expression_r_node_create", (DL_FUNC) &r_complex_literal_expression_r_node_create, 1},
    {"complex_literal_expression_r_node_get_representation", (DL_FUNC) &r_complex_literal_expression_r_node_get_representation, 1},
    {"complex_literal_expression_r_node_set_representation", (DL_FUNC) &r_complex_literal_expression_r_node_set_representation, 2},

    /* DoubleLiteralExpressionRNode */
    {"double_literal_expression_r_node_create", (DL_FUNC) &r_double_literal_expression_r_node_create, 1},
    {"double_literal_expression_r_node_get_representation", (DL_FUNC) &r_double_literal_expression_r_node_get_representation, 1},
    {"double_literal_expression_r_node_set_representation", (DL_FUNC) &r_double_literal_expression_r_node_set_representation, 2},

    /* IntegerLiteralExpressionRNode */
    {"integer_literal_expression_r_node_create", (DL_FUNC) &r_integer_literal_expression_r_node_create, 1},
    {"integer_literal_expression_r_node_get_representation", (DL_FUNC) &r_integer_literal_expression_r_node_get_representation, 1},
    {"integer_literal_expression_r_node_set_representation", (DL_FUNC) &r_integer_literal_expression_r_node_set_representation, 2},

    /* LogicalLiteralExpressionRNode */
    {"logical_literal_expression_r_node_create", (DL_FUNC) &r_logical_literal_expression_r_node_create, 1},
    {"logical_literal_expression_r_node_get_representation", (DL_FUNC) &r_logical_literal_expression_r_node_get_representation, 1},
    {"logical_literal_expression_r_node_set_representation", (DL_FUNC) &r_logical_literal_expression_r_node_set_representation, 2},

    /* RawLiteralExpressionRNode */
    {"raw_literal_expression_r_node_create", (DL_FUNC) &r_raw_literal_expression_r_node_create, 1},
    {"raw_literal_expression_r_node_get_representation", (DL_FUNC) &r_raw_literal_expression_r_node_get_representation, 1},
    {"raw_literal_expression_r_node_set_representation", (DL_FUNC) &r_raw_literal_expression_r_node_set_representation, 2},

    /* OperatorRNode */
    {"operator_r_node_create", (DL_FUNC) &r_operator_r_node_create, 1},
    {"operator_r_node_get_representation", (DL_FUNC) &r_operator_r_node_get_representation, 1},

    /* KeywordRNode */
    {"keyword_r_node_create", (DL_FUNC) &r_keyword_r_node_create, 1},
    {"keyword_r_node_get_representation", (DL_FUNC) &r_keyword_r_node_get_representation, 1},

    /* SymbolExpressionRNode */
    {"symbol_expression_r_node_create", (DL_FUNC) &r_symbol_expression_r_node_create, 1},
    {"symbol_expression_r_node_get_representation", (DL_FUNC) &r_symbol_expression_r_node_get_representation, 1},

    /* FunctionDefinitionExpressionRNode */
    {"function_definition_expression_r_node_create", (DL_FUNC) &r_function_definition_expression_r_node_create, 3},
    {"function_definition_expression_r_node_get_keyword", (DL_FUNC) &r_function_definition_expression_r_node_get_keyword, 1},
    {"function_definition_expression_r_node_set_keyword", (DL_FUNC) &r_function_definition_expression_r_node_set_keyword, 2},
    {"function_definition_expression_r_node_get_body", (DL_FUNC) &r_function_definition_expression_r_node_get_body, 1},
    {"function_definition_expression_r_node_set_body", (DL_FUNC) &r_function_definition_expression_r_node_set_body, 2},
    {"function_definition_expression_r_node_get_parameters", (DL_FUNC) &r_function_definition_expression_r_node_get_parameters, 1},
    {"function_definition_expression_r_node_set_parameters", (DL_FUNC) &r_function_definition_expression_r_node_set_parameters, 2},

    /* LoopExpressionRNode */
    {"loop_expression_r_node_get_keyword", (DL_FUNC) &r_loop_expression_r_node_get_keyword, 1},
    {"loop_expression_r_node_set_keyword", (DL_FUNC) &r_loop_expression_r_node_set_keyword, 2},
    {"loop_expression_r_node_get_body", (DL_FUNC) &r_loop_expression_r_node_get_body, 1},
    {"loop_expression_r_node_set_body", (DL_FUNC) &r_loop_expression_r_node_set_body, 2},

    /* ForLoopExpressionRNode */
    {"for_loop_expression_r_node_create", (DL_FUNC) &r_for_loop_expression_r_node_create, 3},
    {"for_loop_expression_r_node_get_condition", (DL_FUNC) &r_for_loop_expression_r_node_get_condition, 1},
    {"for_loop_expression_r_node_set_condition", (DL_FUNC) &r_for_loop_expression_r_node_set_condition, 2},

    /* WhileLoopExpressionRNode */
    {"while_loop_expression_r_node_create", (DL_FUNC) &r_while_loop_expression_r_node_create, 3},
    {"while_loop_expression_r_node_get_condition", (DL_FUNC) &r_while_loop_expression_r_node_get_condition, 1},
    {"while_loop_expression_r_node_set_condition", (DL_FUNC) &r_while_loop_expression_r_node_set_condition, 2},

    /* RepeatLoopExpressionRNode */
    {"repeat_loop_expression_r_node_create", (DL_FUNC) &r_repeat_loop_expression_r_node_create, 3},

    {NULL, NULL, 0}
};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    r_rastr_initialize();
}
}