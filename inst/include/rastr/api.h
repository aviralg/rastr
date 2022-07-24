#ifndef RASTR_API_H
#define RASTR_API_H

#include <rastr/RIncludes.h>

/* WARN: do not change this enum, entries are order sensitive! */
enum rastr_node_type_t {
    /********************************************************************************
      Operators
    ********************************************************************************/
    Special = 0,

    /* Arithmetic:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Arithmetic.html
     */
    Plus,           // unary or binary +
    Minus,          // unary or binary -
    Multiplication, // *
    Division,       // /
    Power,          // ^ or **

    /* Comparison:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Comparison.html
     */
    LessThan,         // <
    LessThanEqual,    // <=
    GreaterThan,      // >
    GreaterThanEqual, // >=
    Equal,            // ==
    NotEqual,         // !=

    /* Logic: https://stat.ethz.ch/R-manual/R-devel/library/base/html/Logic.html
     */
    Not,           // !
    And,           // &&
    VectorizedAnd, // &
    Or,            // ||
    VectorizedOr,  // |

    /* Assignments:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/assignOps.html */
    EqualAssign,      // =
    LeftAssign,       // <-
    RightAssign,      // ->
    LeftSuperAssign,  // <<-
    RightSuperAssign, // ->>
    ColonAssign,      // :=

    /* Pipe: https://stat.ethz.ch/R-manual/R-devel/library/base/html/pipeOp.html
     */
    PipeForward, // |>
    PipeBind,    // =>

    /* Namespace:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/ns-dblcolon.html
     */
    PublicNamespace,  // ::
    PrivateNamespace, // :::

    /* Range:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Colon.html */
    Range, // :

    /* Help */
    Help, // ?

    /* Slot: https://stat.ethz.ch/R-manual/R-devel/library/base/html/slotOp.html
     */
    SlotExtract, // @

    /* Formula:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/tilde.html */
    Formula, // ~

    /* Extract:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Extract.html */
    PartExtract, // $

    /* Function */
    AnonymousFunction, /* \ */

    /********************************************************************************
      KEYWORDS
    ********************************************************************************/
    Function,
    While,
    Repeat,
    For,
    In,
    If,
    Else,
    Next,
    Break,

    /********************************************************************************
      Delimiters
    ********************************************************************************/
    LeftParen,          // (
    RightParen,         // )
    LeftBrace,          // {
    RightBrace,         // }
    LeftBracket,        // [
    RightBracket,       // ]
    DoubleLeftBracket,  // [[
    DoubleRightBracket, // ]]

    /********************************************************************************
      Terminators
    ********************************************************************************/
    Semicolon, // ;
    Newline,   // \n
    Comma,     // ,

    /********************************************************************************
      Literals
    ********************************************************************************/
    Null,
    Logical,
    Integer,
    Real,
    Complex,
    String,
    Symbol,
    Placeholder,

    /********************************************************************************
      Expressions
    ********************************************************************************/
    UnaryExpression,
    BinaryExpression,
    Block,
    Group,

    /********************************************************************************
      Statement
    ********************************************************************************/
    Statement,

    /********************************************************************************
      Program
    ********************************************************************************/
    Program,

    /********************************************************************************
      Sequence
    ********************************************************************************/
    Sequence,

    /********************************************************************************
      End
    ********************************************************************************/
    End,

    /********************************************************************************
      Error
    ********************************************************************************/
    Error,

    /********************************************************************************
      RepeatLoop
    ********************************************************************************/
    RepeatLoop,

    /********************************************************************************
      WhileLoop
    ********************************************************************************/
    WhileLoop,

    /********************************************************************************
      If
    ********************************************************************************/
    IfCond,

    /********************************************************************************
      IfElse
    ********************************************************************************/
    IfElseCond,

    /********************************************************************************
     Named
    ********************************************************************************/
    Named,

    /********************************************************************************
     Missing
    ********************************************************************************/
    Missing,

    /********************************************************************************
     Call
    ********************************************************************************/
    Call,

    /********************************************************************************
     Arguments
    ********************************************************************************/
    Arguments,

    /********************************************************************************
     Indices
    ********************************************************************************/
    Indices,

    /********************************************************************************
     Indexing
    ********************************************************************************/
    Indexing,

    Parameters,
    FunctionDefinition

    // Extract,
    // Function,
    // Default,
    // Call,
    // Missing,
    // Named,
    // Conditional,
    // Condition,
    // Loop,
    // In,
    // File,
    // Directory,
    // Package,
    // Library,
};

struct rastr_node_t {
    std::size_t index;
};

typedef struct rastr_ast_impl_t* rastr_ast_t;

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************************
 Ast
********************************************************************************/

rastr_ast_t rastr_ast_create(std::size_t capacity);
void rastr_ast_destroy(rastr_ast_t ast);
rastr_node_t rastr_ast_root(rastr_ast_t ast);
const char* rastr_ast_to_string(rastr_ast_t ast);

/********************************************************************************
 Node
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_ast_t ast, rastr_node_t node);
int rastr_node_id(rastr_ast_t ast, rastr_node_t node);
const char*
rastr_node_to_string(rastr_ast_t ast, rastr_node_t node, int spaces);

/********************************************************************************
 Node Type
********************************************************************************/
const char* rastr_node_type_to_string(rastr_node_type_t type);

/********************************************************************************
 Operators
********************************************************************************/

bool rastr_node_is_operator(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_operator(rastr_ast_t ast,
                                 const char* syntax,
                                 rastr_node_type_t type);
const char* rastr_node_operator_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_operator_syntax(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Keywords
********************************************************************************/

bool rastr_node_is_keyword(rastr_ast_t ast, rastr_node_t node);
rastr_node_t
rastr_node_keyword(rastr_ast_t ast, const char* syntax, rastr_node_type_t type);
const char* rastr_node_keyword_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_keyword_syntax(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Delimiters
********************************************************************************/

bool rastr_node_is_delimiter(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_delimiter(rastr_ast_t ast, rastr_node_type_t type);
const char* rastr_node_delimiter_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_delimiter_syntax(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Terminators
********************************************************************************/

bool rastr_node_is_terminator(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_terminator(rastr_ast_t ast, rastr_node_type_t type);
const char* rastr_node_terminator_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_terminator_syntax(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Meta
********************************************************************************/

// End
rastr_node_t rastr_node_end(rastr_ast_t ast);

// Error
rastr_node_t rastr_node_error(rastr_ast_t ast, const char* fmt, ...);
const char* rastr_node_error_message(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Literals
********************************************************************************/
bool rastr_node_is_literal(rastr_ast_t ast, rastr_node_t node);

// null
rastr_node_t rastr_node_null(rastr_ast_t ast);
const char* rastr_node_null_syntax(rastr_ast_t ast, rastr_node_t node);

// logical
rastr_node_t rastr_node_logical(rastr_ast_t ast, const char* syntax, int value);
int rastr_node_logical_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_logical_syntax(rastr_ast_t ast, rastr_node_t node);

// integer
rastr_node_t rastr_node_integer(rastr_ast_t ast, const char* syntax, int value);
int rastr_node_integer_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_integer_syntax(rastr_ast_t ast, rastr_node_t node);

// real
rastr_node_t rastr_node_real(rastr_ast_t ast, const char* syntax, double value);
double rastr_node_real_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_real_syntax(rastr_ast_t ast, rastr_node_t node);

// complex
rastr_node_t
rastr_node_complex(rastr_ast_t ast, const char* syntax, Rcomplex value);
Rcomplex rastr_node_complex_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_complex_syntax(rastr_ast_t ast, rastr_node_t node);

// string
rastr_node_t
rastr_node_string(rastr_ast_t ast, const char* syntax, const char* value);
const char* rastr_node_string_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_string_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_string_is_raw(rastr_ast_t ast, rastr_node_t node);

// symbol
rastr_node_t rastr_node_symbol(rastr_ast_t ast, const char* syntax);
const char* rastr_node_symbol_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_symbol_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_symbol_is_quoted(rastr_ast_t ast, rastr_node_t node);

// placeholder
rastr_node_t rastr_node_placeholder(rastr_ast_t ast);
const char* rastr_node_placeholder_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_placeholder_syntax(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
Unary Expression
********************************************************************************/
rastr_node_t rastr_node_unary_expression(rastr_ast_t ast,
                                         rastr_node_t op,
                                         rastr_node_t expr);
rastr_node_t rastr_node_unary_expression_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_unary_expression_expr(rastr_ast_t ast,
                                              rastr_node_t node);

/********************************************************************************
 Binary Expression
********************************************************************************/
rastr_node_t rastr_node_binary_expression(rastr_ast_t ast,
                                          rastr_node_t left_expr,
                                          rastr_node_t op,
                                          rastr_node_t right_expr);
rastr_node_t rastr_node_binary_expression_op(rastr_ast_t ast,
                                             rastr_node_t node);
rastr_node_t rastr_node_binary_expression_left_expr(rastr_ast_t ast,
                                                    rastr_node_t node);
rastr_node_t rastr_node_binary_expression_right_expr(rastr_ast_t ast,
                                                     rastr_node_t node);

/********************************************************************************
 Sequence
********************************************************************************/
rastr_node_t
rastr_node_sequence(rastr_ast_t ast, rastr_node_t* nodes, int size);
int rastr_node_sequence_size(rastr_ast_t ast, rastr_node_t node);
rastr_node_t* rastr_node_sequence_nodes(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Block
********************************************************************************/
rastr_node_t rastr_node_block(rastr_ast_t ast,
                              rastr_node_t left_brace,
                              rastr_node_t expr_seq,
                              rastr_node_t right_brace);
rastr_node_t rastr_node_block_left_brace(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_block_expressions(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_block_right_brace(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Group
********************************************************************************/
rastr_node_t rastr_node_group(rastr_ast_t ast,
                              rastr_node_t left_paren,
                              rastr_node_t expr,
                              rastr_node_t right_paren);
rastr_node_t rastr_node_group_left_paren(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_group_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_group_right_paren(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
Statement
********************************************************************************/
rastr_node_t rastr_node_statement(rastr_ast_t ast,
                                  rastr_node_t expr,
                                  rastr_node_t terminator);
rastr_node_t rastr_node_statement_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_statement_terminator(rastr_ast_t ast,
                                             rastr_node_t node);

/********************************************************************************
 Program
********************************************************************************/
rastr_node_t rastr_node_program(rastr_ast_t ast, rastr_node_t statements);
rastr_node_t rastr_node_program_statements(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 RepeatLoop
********************************************************************************/
rastr_node_t
rastr_node_rloop(rastr_ast_t ast, rastr_node_t kw, rastr_node_t body);
rastr_node_t rastr_node_rloop_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_rloop_body(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 WhileLoop
********************************************************************************/
rastr_node_t rastr_node_wloop(rastr_ast_t ast,
                              rastr_node_t kw,
                              rastr_node_t cond,
                              rastr_node_t body);
rastr_node_t rastr_node_wloop_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_wloop_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_wloop_body(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 If
********************************************************************************/
rastr_node_t rastr_node_ifcond(rastr_ast_t ast,
                               rastr_node_t if_kw,
                               rastr_node_t cond,
                               rastr_node_t csq);
rastr_node_t rastr_node_ifcond_if_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifcond_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifcond_csq(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 IfElse
********************************************************************************/
rastr_node_t rastr_node_ifelsecond(rastr_ast_t ast,
                                   rastr_node_t if_kw,
                                   rastr_node_t cond,
                                   rastr_node_t csq,
                                   rastr_node_t else_kw,
                                   rastr_node_t alt);
rastr_node_t rastr_node_ifelsecond_if_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifelsecond_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifelsecond_csq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifelsecond_else_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_ifelsecond_alt(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Named
********************************************************************************/
rastr_node_t rastr_node_named(rastr_ast_t ast,
                              rastr_node_t name,
                              rastr_node_t op,
                              rastr_node_t expr);
rastr_node_t rastr_node_named_name(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_named_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_named_expr(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Missing
********************************************************************************/
rastr_node_t rastr_node_missing(rastr_ast_t ast);

/********************************************************************************
 Arguments
********************************************************************************/
rastr_node_t rastr_node_arguments(rastr_ast_t ast,
                                  rastr_node_t ldelim,
                                  rastr_node_t args,
                                  rastr_node_t rdelim);
rastr_node_t rastr_node_arguments_ldelim(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_arguments_args(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_arguments_rdelim(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
Call
********************************************************************************/
rastr_node_t
rastr_node_call(rastr_ast_t ast, rastr_node_t fun, rastr_node_t args);
rastr_node_t rastr_node_call_fun(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_call_args(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Indices
********************************************************************************/
rastr_node_t rastr_node_indices(rastr_ast_t ast,
                                rastr_node_t ldelim,
                                rastr_node_t nodes,
                                rastr_node_t rdelim);
rastr_node_t rastr_node_indices_ldelim(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_indices_nodes(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_indices_rdelim(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Indexing
********************************************************************************/
rastr_node_t
rastr_node_indexing(rastr_ast_t ast, rastr_node_t obj, rastr_node_t indices);
rastr_node_t rastr_node_indexing_obj(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_indexing_indices(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
Parameters
********************************************************************************/
rastr_node_t rastr_node_parameters(rastr_ast_t ast,
                                   rastr_node_t ldelim,
                                   rastr_node_t seq,
                                   rastr_node_t rdelim);
rastr_node_t rastr_node_parameters_ldelim(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_parameters_seq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_parameters_rdelim(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 FunctionDefinition
********************************************************************************/
rastr_node_t rastr_node_fndef(rastr_ast_t ast,
                              rastr_node_t kw,
                              rastr_node_t params,
                              rastr_node_t body);
rastr_node_t rastr_node_fndef_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_fndef_params(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_fndef_body(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Parsing
********************************************************************************/
rastr_ast_t rastr_parse_str(const char* str);
rastr_ast_t rastr_parse_file(const char* filepath);

SEXP r_rastr_ast_to_sexp(rastr_ast_t ast);
rastr_ast_t rastr_ast_from_sexp(SEXP r_ast);
SEXP r_rastr_parse_file(SEXP r_filepath);
SEXP r_rastr_parse_str(SEXP r_string);
SEXP r_rastr_ast_print(SEXP r_ast);

SEXP r_rastr_initialize(SEXP r_pack_env);
SEXP r_rastr_finalize(SEXP r_pack_env);

/********************************************************************************
Export
********************************************************************************/

void rastr_export_to_dot(rastr_ast_t ast, const char* filepath, int depth);
SEXP r_rastr_export_to_dot(SEXP r_ast, SEXP r_filepath, SEXP r_depth);

#ifdef __cplusplus
}
#endif

#endif /* RASTR_API_H */