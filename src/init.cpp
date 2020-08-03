#include "r_rastr.h"
#include "r_character_literal_expression_r_node.h"
#include "r_complex_literal_expression_r_node.h"
#include "r_double_literal_expression_r_node.h"
#include "r_integer_literal_expression_r_node.h"
#include "r_logical_literal_expression_r_node.h"
#include "r_raw_literal_expression_r_node.h"

#include "r_symbol_expression_r_node.h"

#include "r_parser.h"

#include "r_rastr_ast_i_body.h"
#include "r_rastr_ast_i_bounded.h"
#include "r_rastr_ast_i_condition.h"
#include "r_rastr_ast_i_expressions.h"
#include "r_rastr_ast_i_indices.h"
#include "r_rastr_ast_i_keyword.h"
#include "r_rastr_ast_i_symbol.h"
#include "r_rastr_ast_i_expression.h"
#include "r_rastr_ast_i_object.h"
#include "r_rastr_ast_i_operator.h"
#include "r_rastr_ast_i_representation.h"

#include "r_rastr_ast_conditional_expression_r_node.h"

#include "r_rastr_ast_operator_r_node.h"
#include "r_rastr_ast_keyword_r_node.h"
#include "r_rastr_ast_delimiter_r_node.h"

#include "r_rastr_ast_begin_r_node.h"
#include "r_rastr_ast_end_r_node.h"
#include "r_rastr_ast_program_r_node.h"
#include "r_rastr_ast_file_r_node.h"
#include "r_rastr_ast_expression_sequence_r_node.h"

#include "r_rastr_ast_group_expression_r_node.h"
#include "r_rastr_ast_block_expression_r_node.h"

#include "r_rastr_ast_unary_operation_expression_r_node.h"
#include "r_rastr_ast_binary_operation_expression_r_node.h"
#include "r_rastr_ast_function_definition_expression_r_node.h"
#include "r_rastr_ast_function_call_expression_r_node.h"
#include "r_rastr_ast_indexing_expression_r_node.h"
#include "r_rastr_ast_subsetting_expression_r_node.h"
#include "r_rastr_ast_for_loop_expression_r_node.h"
#include "r_rastr_ast_while_loop_expression_r_node.h"
#include "r_rastr_ast_repeat_loop_expression_r_node.h"
#include "r_rastr_ast_if_conditional_expression_r_node.h"
#include "r_rastr_ast_if_else_conditional_expression_r_node.h"

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

    /* SymbolExpressionRNode */
    {"symbol_expression_r_node_create", (DL_FUNC) &r_symbol_expression_r_node_create, 1},
    {"symbol_expression_r_node_get_representation", (DL_FUNC) &r_symbol_expression_r_node_get_representation, 1},

    /* parser */
    {"parser_parse_stdin", (DL_FUNC) &r_parser_parse_stdin, 0},
    {"parser_parse_string", (DL_FUNC) &r_parser_parse_string, 1},
    {"parser_parse_file", (DL_FUNC) &r_parser_parse_file, 1},

    /* IBody */
    {"rastr_ast_i_body_get_body", (DL_FUNC) &r_rastr_ast_i_body_get_body, 1},
    {"rastr_ast_i_body_set_body", (DL_FUNC) &r_rastr_ast_i_body_set_body, 2},

    /* IExpression */
    {"rastr_ast_i_expression_get_expression", (DL_FUNC) &r_rastr_ast_i_expression_get_expression, 1},
    {"rastr_ast_i_expression_set_expression", (DL_FUNC) &r_rastr_ast_i_expression_set_expression, 2},

    /* IObject */
    {"rastr_ast_i_object_get_object", (DL_FUNC) &r_rastr_ast_i_object_get_object, 1},
    {"rastr_ast_i_object_set_object", (DL_FUNC) &r_rastr_ast_i_object_set_object, 2},

    /* IBounded */
    {"rastr_ast_i_bounded_get_opening_delimiter", (DL_FUNC) &r_rastr_ast_i_bounded_get_opening_delimiter, 1},
    {"rastr_ast_i_bounded_set_opening_delimiter", (DL_FUNC) &r_rastr_ast_i_bounded_set_opening_delimiter, 2},
    {"rastr_ast_i_bounded_get_closing_delimiter", (DL_FUNC) &r_rastr_ast_i_bounded_get_closing_delimiter, 1},
    {"rastr_ast_i_bounded_set_closing_delimiter", (DL_FUNC) &r_rastr_ast_i_bounded_set_closing_delimiter, 2},
    {"rastr_ast_i_bounded_set_delimiters", (DL_FUNC) &r_rastr_ast_i_bounded_set_delimiters, 3},

    /* IIndices */
    {"rastr_ast_i_indices_get_indices", (DL_FUNC) &r_rastr_ast_i_indices_get_indices, 1},
    {"rastr_ast_i_indices_set_indices", (DL_FUNC) &r_rastr_ast_i_indices_set_indices, 2},

    /* IKeyword */
    {"rastr_ast_i_keyword_get_keyword", (DL_FUNC) &r_rastr_ast_i_keyword_get_keyword, 1},
    {"rastr_ast_i_keyword_set_keyword", (DL_FUNC) &r_rastr_ast_i_keyword_set_keyword, 2},

    /* ISymbol */
    {"rastr_ast_i_symbol_get_symbol", (DL_FUNC) &r_rastr_ast_i_symbol_get_symbol, 1},
    {"rastr_ast_i_symbol_set_symbol", (DL_FUNC) &r_rastr_ast_i_symbol_set_symbol, 2},

    /* IOperator */
    {"rastr_ast_i_operator_get_operator", (DL_FUNC) &r_rastr_ast_i_operator_get_operator, 1},
    {"rastr_ast_i_operator_set_operator", (DL_FUNC) &r_rastr_ast_i_operator_set_operator, 2},

    /* ICondition */
    {"rastr_ast_i_condition_get_condition", (DL_FUNC) &r_rastr_ast_i_condition_get_condition, 1},
    {"rastr_ast_i_condition_set_condition", (DL_FUNC) &r_rastr_ast_i_condition_set_condition, 2},

    /* IExpressions */
    {"rastr_ast_i_expressions_get_expressions", (DL_FUNC) &r_rastr_ast_i_expressions_get_expressions, 1},
    {"rastr_ast_i_expressions_set_expressions", (DL_FUNC) &r_rastr_ast_i_expressions_set_expressions, 2},

    /* IRepresentation */
    {"rastr_ast_i_representation_get_representation", (DL_FUNC) &r_rastr_ast_i_representation_get_representation, 1},

    /* ConditionalExpressionRNode */
    {"rastr_ast_conditional_expression_r_node_get_if_keyword", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_get_if_keyword, 1},
    {"rastr_ast_conditional_expression_r_node_set_if_keyword", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_set_if_keyword, 2},
    {"rastr_ast_conditional_expression_r_node_get_consequent_expression", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_get_consequent_expression, 1},
    {"rastr_ast_conditional_expression_r_node_set_consequent_expression", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_set_consequent_expression, 2},

    /* OperatorRNode */
    {"rastr_ast_operator_r_node_create", (DL_FUNC) &r_rastr_ast_operator_r_node_create, 1},

    /* KeywordRNode */
    {"rastr_ast_keyword_r_node_create", (DL_FUNC) &r_rastr_ast_keyword_r_node_create, 1},

    /* DelimiterRNode */
    {"rastr_ast_delimiter_r_node_create", (DL_FUNC) &r_rastr_ast_delimiter_r_node_create, 1},

    /* BeginRNode */
    {"rastr_ast_begin_r_node_create", (DL_FUNC) &r_rastr_ast_begin_r_node_create, 0},

    /* EndRNode */
    {"rastr_ast_end_r_node_create", (DL_FUNC) &r_rastr_ast_end_r_node_create, 0},

    /* ProgramRNode */
    {"rastr_ast_program_r_node_create", (DL_FUNC) &r_rastr_ast_program_r_node_create, 3},
    {"rastr_ast_program_r_node_is_well_formed", (DL_FUNC) &r_rastr_ast_program_r_node_is_well_formed, 1},
    {"rastr_ast_program_r_node_get_syntax_error", (DL_FUNC) &r_rastr_ast_program_r_node_get_syntax_error, 1},
    {"rastr_ast_program_r_node_set_syntax_error", (DL_FUNC) &r_rastr_ast_program_r_node_set_syntax_error, 2},

    /* FileRNode */
    {"rastr_ast_file_r_node_create", (DL_FUNC) &r_rastr_ast_file_r_node_create, 2},
    {"rastr_ast_file_r_node_get_filepath", (DL_FUNC) &r_rastr_ast_file_r_node_get_filepath, 1},
    {"rastr_ast_file_r_node_set_filepath", (DL_FUNC) &r_rastr_ast_file_r_node_set_filepath, 2},
    {"rastr_ast_file_r_node_get_program", (DL_FUNC) &r_rastr_ast_file_r_node_get_program, 1},
    {"rastr_ast_file_r_node_set_program", (DL_FUNC) &r_rastr_ast_file_r_node_set_program, 2},

    /* ExpressionSequenceRNode */
    {"rastr_ast_expression_sequence_r_node_create", (DL_FUNC) &r_rastr_ast_expression_sequence_r_node_create, 0},
    {"rastr_ast_expression_sequence_r_node_get_size", (DL_FUNC) &r_rastr_ast_expression_sequence_r_node_get_size, 1},
    {"rastr_ast_expression_sequence_r_node_get_element", (DL_FUNC) &r_rastr_ast_expression_sequence_r_node_get_element, 2},
    {"rastr_ast_expression_sequence_r_node_set_element", (DL_FUNC) &r_rastr_ast_expression_sequence_r_node_set_element, 3},
    {"rastr_ast_expression_sequence_r_node_push_back", (DL_FUNC) &r_rastr_ast_expression_sequence_r_node_push_back, 2},

    /* GroupExpressionRNode */
    {"rastr_ast_group_expression_r_node_create", (DL_FUNC) &r_rastr_ast_group_expression_r_node_create, 3},

    /* BlockExpressionRNode */
    {"rastr_ast_block_expression_r_node_create", (DL_FUNC) &r_rastr_ast_block_expression_r_node_create, 3},

    /* UnaryOperationExpressionRNode */
    {"rastr_ast_unary_operation_expression_r_node_create", (DL_FUNC) &r_rastr_ast_unary_operation_expression_r_node_create, 2},
    {"rastr_ast_unary_operation_expression_r_node_get_operand", (DL_FUNC) &r_rastr_ast_unary_operation_expression_r_node_get_operand, 1},
    {"rastr_ast_unary_operation_expression_r_node_set_operand", (DL_FUNC) &r_rastr_ast_unary_operation_expression_r_node_set_operand, 2},

    /* BinaryOperationExpressionRNode */
    {"rastr_ast_binary_operation_expression_r_node_create", (DL_FUNC) &r_rastr_ast_binary_operation_expression_r_node_create, 3},
    {"rastr_ast_binary_operation_expression_r_node_get_first_operand", (DL_FUNC) &r_rastr_ast_binary_operation_expression_r_node_get_first_operand, 1},
    {"rastr_ast_binary_operation_expression_r_node_set_first_operand", (DL_FUNC) &r_rastr_ast_binary_operation_expression_r_node_set_first_operand, 2},
    {"rastr_ast_binary_operation_expression_r_node_get_second_operand", (DL_FUNC) &r_rastr_ast_binary_operation_expression_r_node_get_second_operand, 1},
    {"rastr_ast_binary_operation_expression_r_node_set_second_operand", (DL_FUNC) &r_rastr_ast_binary_operation_expression_r_node_set_second_operand, 2},

    /* FunctionDefinitionExpressionRNode */
    {"rastr_ast_function_definition_expression_r_node_create", (DL_FUNC) &r_rastr_ast_function_definition_expression_r_node_create, 5},
    {"rastr_ast_function_definition_expression_r_node_get_parameters", (DL_FUNC) &r_rastr_ast_function_definition_expression_r_node_get_parameters, 1},
    {"rastr_ast_function_definition_expression_r_node_set_parameters", (DL_FUNC) &r_rastr_ast_function_definition_expression_r_node_set_parameters, 2},

    /* FunctionCallExpressionRNode */
    {"rastr_ast_function_call_expression_r_node_create", (DL_FUNC) &r_rastr_ast_function_call_expression_r_node_create, 4},
    {"rastr_ast_function_call_expression_r_node_get_function", (DL_FUNC) &r_rastr_ast_function_call_expression_r_node_get_function, 1},
    {"rastr_ast_function_call_expression_r_node_set_function", (DL_FUNC) &r_rastr_ast_function_call_expression_r_node_set_function, 2},
    {"rastr_ast_function_call_expression_r_node_get_arguments", (DL_FUNC) &r_rastr_ast_function_call_expression_r_node_get_arguments, 1},
    {"rastr_ast_function_call_expression_r_node_set_arguments", (DL_FUNC) &r_rastr_ast_function_call_expression_r_node_set_arguments, 2},

    /* IndexingExpressionRNode */
    {"rastr_ast_indexing_expression_r_node_create", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_create, 5},
    {"rastr_ast_indexing_expression_r_node_get_opening_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_get_opening_delimiter, 1},
    {"rastr_ast_indexing_expression_r_node_set_opening_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_set_opening_delimiter, 2},
    {"rastr_ast_indexing_expression_r_node_get_first_closing_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_get_first_closing_delimiter, 1},
    {"rastr_ast_indexing_expression_r_node_set_first_closing_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_set_first_closing_delimiter, 2},
    {"rastr_ast_indexing_expression_r_node_get_second_closing_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_get_second_closing_delimiter, 1},
    {"rastr_ast_indexing_expression_r_node_set_second_closing_delimiter", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_set_second_closing_delimiter, 2},
    {"rastr_ast_indexing_expression_r_node_set_delimiters", (DL_FUNC) &r_rastr_ast_indexing_expression_r_node_set_delimiters, 4},

    /* SubsettingExpressionRNode */
    {"rastr_ast_subsetting_expression_r_node_create", (DL_FUNC) &r_rastr_ast_subsetting_expression_r_node_create, 4},

    /* ForLoopExpressionRNode */
    {"rastr_ast_for_loop_expression_r_node_create", (DL_FUNC) &r_rastr_ast_for_loop_expression_r_node_create, 3},
    {"rastr_ast_for_loop_expression_get_condition", (DL_FUNC) &r_rastr_ast_for_loop_expression_get_condition, 1},
    {"rastr_ast_for_loop_expression_set_condition", (DL_FUNC) &r_rastr_ast_for_loop_expression_set_condition, 2},

    /* WhileLoopExpressionRNode */
    {"rastr_ast_while_loop_expression_r_node_create", (DL_FUNC) &r_rastr_ast_while_loop_expression_r_node_create, 3},

    /* RepeatLoopExpressionRNode */
    {"rastr_ast_repeat_loop_expression_r_node_create", (DL_FUNC) &r_rastr_ast_repeat_loop_expression_r_node_create, 2},

    /* IfConditionalExpressionRNode */
    {"r_rastr_ast_if_conditional_expression_r_node_create", (DL_FUNC) &r_rastr_ast_if_conditional_expression_r_node_create, 3},

    /* IfElseConditionalExpressionRNode */
    {"rastr_ast_if_else_conditional_expression_r_node_create", (DL_FUNC) &r_rastr_ast_if_else_conditional_expression_r_node_create, 5},
    {"rastr_ast_conditional_expression_r_node_get_else_keyword", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_get_else_keyword, 1},
    {"rastr_ast_conditional_expression_r_node_set_else_keyword", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_set_else_keyword, 2},
    {"rastr_ast_conditional_expression_r_node_get_alternative_expression", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_get_alternative_expression, 1},
    {"rastr_ast_conditional_expression_r_node_set_alternative_expression", (DL_FUNC) &r_rastr_ast_conditional_expression_r_node_set_alternative_expression, 2},

    {NULL, NULL, 0}
};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
    r_rastr_initialize();
}
}
