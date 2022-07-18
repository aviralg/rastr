#ifndef RASTR_AST_H
#define RASTR_AST_H

#include "RIncludes.h"

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

    /* Sequence:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Colon.html */
    Sequence, // :

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
    AnonymousFunction, //                       \

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
      Meta
    ********************************************************************************/
    End,
    Error,

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
    Placeholder

    // Group,
    // Block,
    // Help,
    // Special,
    // Assignment,
    // Arithmetic,
    // Logical,
    // Formula,
    // Sequence,
    // Comparison,
    // Namespace,
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
    // Program,
    // Library,
    // Expressions
};

struct rastr_node_t {
    rastr_node_type_t type;

    union {
        struct {
            const char* syntax;
        } keyword_node;

        struct {
            const char* syntax;
        } operator_node;

        /* null_node has no fields since null is represented only as NULL */

        struct {
            const char* syntax;
            int value;
        } logical_node;

        struct {
            const char* syntax;
            int value;
        } integer_node;

        struct {
            const char* syntax;
            double value;
        } real_node;

        struct {
            const char* syntax;
            Rcomplex value;
        } complex_node;

        struct {
            const char* syntax;
            const char* value;
        } string_node;

        struct {
            const char* syntax;
            const char* value;
        } symbol_node;

        struct {
            const char* message;
        } error_node;
    };
};

/********************************************************************************
 Node
********************************************************************************/

const char* rastr_node_to_string(rastr_node_t node);

/********************************************************************************
 Node Type
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_node_t node);
const char* rastr_node_type_to_string(rastr_node_type_t type);

/********************************************************************************
 Operators
********************************************************************************/

bool rastr_node_is_operator(rastr_node_t node);
rastr_node_t rastr_node_operator(const char* syntax, rastr_node_type_t type);
const char* rastr_node_operator_value(rastr_node_t node);
const char* rastr_node_operator_syntax(rastr_node_t node);

/********************************************************************************
 Keywords
********************************************************************************/

bool rastr_node_is_keyword(rastr_node_t node);
rastr_node_t rastr_node_keyword(const char* syntax, rastr_node_type_t type);
const char* rastr_node_keyword_value(rastr_node_t node);
const char* rastr_node_keyword_syntax(rastr_node_t node);

/********************************************************************************
 Delimiters
********************************************************************************/

bool rastr_node_is_delimiter(rastr_node_t node);
rastr_node_t rastr_node_delimiter(rastr_node_type_t type);
const char* rastr_node_delimiter_value(rastr_node_t node);
const char* rastr_node_delimiter_syntax(rastr_node_t node);

/********************************************************************************
 Terminators
********************************************************************************/

bool rastr_node_is_terminator(rastr_node_t node);
rastr_node_t rastr_node_terminator(rastr_node_type_t type);
const char* rastr_node_terminator_value(rastr_node_t node);
const char* rastr_node_terminator_syntax(rastr_node_t node);

/********************************************************************************
 Meta
********************************************************************************/

// End
rastr_node_t rastr_node_end();

// Error
rastr_node_t rastr_node_error(const char* fmt, ...);
const char* rastr_node_error_message(rastr_node_t node);

/********************************************************************************
 Literals
********************************************************************************/
bool rastr_node_is_literal(rastr_node_t node);

// null
rastr_node_t rastr_node_null();
const char* rastr_node_null_syntax(rastr_node_t node);

// logical
rastr_node_t rastr_node_logical(const char* syntax, int value);
int rastr_node_logical_value(rastr_node_t node);
const char* rastr_node_logical_syntax(rastr_node_t node);

// integer
rastr_node_t rastr_node_integer(const char* syntax, int value);
int rastr_node_integer_value(rastr_node_t node);
const char* rastr_node_integer_syntax(rastr_node_t node);

// real
rastr_node_t rastr_node_real(const char* syntax, double value);
double rastr_node_real_value(rastr_node_t node);
const char* rastr_node_real_syntax(rastr_node_t node);

// complex
rastr_node_t rastr_node_complex(const char* syntax, Rcomplex value);
Rcomplex rastr_node_complex_value(rastr_node_t node);
const char* rastr_node_complex_syntax(rastr_node_t node);

// string
rastr_node_t rastr_node_string(const char* syntax, const char* value);
const char* rastr_node_string_value(rastr_node_t node);
const char* rastr_node_string_syntax(rastr_node_t node);
bool rastr_node_string_is_raw(rastr_node_t node);

// symbol
rastr_node_t rastr_node_symbol(const char* syntax);
const char* rastr_node_symbol_value(rastr_node_t node);
const char* rastr_node_symbol_syntax(rastr_node_t node);
bool rastr_node_symbol_is_quoted(rastr_node_t node);

// placeholder
rastr_node_t rastr_node_placeholder();
const char* rastr_node_placeholder_value(rastr_node_t node);
const char* rastr_node_placeholder_syntax(rastr_node_t node);

#endif /* RASTR_AST_H */
