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

    /********************************************************************************
      Expressions
    ********************************************************************************/
    Block,
    Group,
    UnaryOperation,
    BinaryOperation,
    RepeatLoop,
    WhileLoop,
    ForLoop,
    IfConditional,
    IfElseConditional,
    FunctionDefinition,
    FunctionCall,
    Subset,
    Index,

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    Parameters,
    DefaultParameter,
    NonDefaultParameter,
    Arguments,
    NamedArgument,
    PositionalArgument,
    Condition,
    Iteration,
    Program,
    Delimited,
    Missing,
    Error,
    End

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
APIGEN
********************************************************************************/

/********************************************************************************
 Ast
********************************************************************************/

rastr_ast_t rastr_ast_create(std::size_t capacity);
void rastr_ast_destroy(rastr_ast_t ast);
rastr_node_t rastr_ast_root(rastr_ast_t ast);
const char* rastr_ast_to_string(rastr_ast_t ast);
int rastr_is_empty(rastr_ast_t ast);
int rastr_ast_size(rastr_ast_t ast);

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
rastr_node_complex(rastr_ast_t ast, const char* syntax, const Rcomplex& value);
Rcomplex rastr_node_complex_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_complex_syntax(rastr_ast_t ast, rastr_node_t node);

// string
rastr_node_t
rastr_node_string(rastr_ast_t ast, const char* syntax, const char* value);
const char* rastr_node_string_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_string_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_string_is_raw(rastr_ast_t ast, rastr_node_t node);

// symbol
rastr_node_t
rastr_node_symbol(rastr_ast_t ast, const char* syntax, const char* value);
const char* rastr_node_symbol_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_symbol_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_symbol_is_quoted(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_blk_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            int len,
                            const rastr_node_t* seq,
                            rastr_node_t rbrack);
rastr_node_t rastr_blk_lbrack(rastr_ast_t ast, rastr_node_t node);
int rastr_blk_len(rastr_ast_t ast, rastr_node_t node);
const rastr_node_t* rastr_blk_seq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_blk_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_grp_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            rastr_node_t expr,
                            rastr_node_t rbrack);
rastr_node_t rastr_grp_lbrack(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_grp_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_grp_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_unop_node(rastr_ast_t ast, rastr_node_t op, rastr_node_t expr);
rastr_node_t rastr_unop_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_unop_expr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_binop_node(rastr_ast_t ast,
                              rastr_node_t lexpr,
                              rastr_node_t op,
                              rastr_node_t rexpr);
rastr_node_t rastr_binop_lexpr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_binop_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_binop_rexpr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_rlp_node(rastr_ast_t ast, rastr_node_t kw, rastr_node_t body);
rastr_node_t rastr_rlp_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_rlp_body(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_wlp_node(rastr_ast_t ast,
                            rastr_node_t kw,
                            rastr_node_t cond,
                            rastr_node_t body);
rastr_node_t rastr_wlp_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_wlp_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_wlp_body(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_flp_node(rastr_ast_t ast,
                            rastr_node_t kw,
                            rastr_node_t iter,
                            rastr_node_t body);
rastr_node_t rastr_flp_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_flp_iter(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_flp_body(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_icnd_node(rastr_ast_t ast,
                             rastr_node_t ikw,
                             rastr_node_t cond,
                             rastr_node_t ibody);
rastr_node_t rastr_icnd_ikw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_icnd_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_icnd_ibody(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_iecnd_node(rastr_ast_t ast,
                              rastr_node_t ikw,
                              rastr_node_t cond,
                              rastr_node_t ibody,
                              rastr_node_t ekw,
                              rastr_node_t ebody);
rastr_node_t rastr_iecnd_ikw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iecnd_cond(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iecnd_ibody(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iecnd_ekw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iecnd_ebody(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_fndefn_node(rastr_ast_t ast,
                               rastr_node_t hd,
                               rastr_node_t params,
                               rastr_node_t body);
rastr_node_t rastr_fndefn_hd(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_fndefn_params(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_fndefn_body(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_fncall_node(rastr_ast_t ast, rastr_node_t fun, rastr_node_t args);
rastr_node_t rastr_fncall_fun(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_fncall_args(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_sub_node(rastr_ast_t ast, rastr_node_t obj, rastr_node_t inds);
rastr_node_t rastr_sub_obj(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_sub_inds(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_idx_node(rastr_ast_t ast, rastr_node_t obj, rastr_node_t inds);
rastr_node_t rastr_idx_obj(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_idx_inds(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_params_node(rastr_ast_t ast,
                               rastr_node_t lbrack,
                               int len,
                               const rastr_node_t* seq,
                               rastr_node_t rbrack);
rastr_node_t rastr_params_lbrack(rastr_ast_t ast, rastr_node_t node);
int rastr_params_len(rastr_ast_t ast, rastr_node_t node);
const rastr_node_t* rastr_params_seq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_params_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_dparam_node(rastr_ast_t ast,
                               rastr_node_t name,
                               rastr_node_t op,
                               rastr_node_t expr);
rastr_node_t rastr_dparam_name(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dparam_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dparam_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_ndparam_node(rastr_ast_t ast, rastr_node_t name);
rastr_node_t rastr_ndparam_name(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_args_node(rastr_ast_t ast,
                             rastr_node_t lbrack,
                             int len,
                             const rastr_node_t* seq,
                             rastr_node_t rbrack);
rastr_node_t rastr_args_lbrack(rastr_ast_t ast, rastr_node_t node);
int rastr_args_len(rastr_ast_t ast, rastr_node_t node);
const rastr_node_t* rastr_args_seq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_args_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_narg_node(rastr_ast_t ast,
                             rastr_node_t name,
                             rastr_node_t op,
                             rastr_node_t expr);
rastr_node_t rastr_narg_name(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_narg_op(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_narg_expr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_parg_node(rastr_ast_t ast, rastr_node_t expr);
rastr_node_t rastr_parg_expr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_cnd_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            rastr_node_t expr,
                            rastr_node_t rbrack);
rastr_node_t rastr_cnd_lbrack(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_cnd_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_cnd_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_iter_node(rastr_ast_t ast,
                             rastr_node_t lbrack,
                             rastr_node_t var,
                             rastr_node_t kw,
                             rastr_node_t expr,
                             rastr_node_t rbrack);
rastr_node_t rastr_iter_lbrack(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iter_var(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iter_kw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iter_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_iter_rbrack(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_pgm_node(rastr_ast_t ast, int len, const rastr_node_t* seq);
int rastr_pgm_len(rastr_ast_t ast, rastr_node_t node);
const rastr_node_t* rastr_pgm_seq(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_dlmtd_node(rastr_ast_t ast, rastr_node_t expr, rastr_node_t dlmtr);
rastr_node_t rastr_dlmtd_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dlmtd_dlmtr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_err_node(rastr_ast_t ast, const char* msg);
const char* rastr_err_msg(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_msng_node(rastr_ast_t ast);

rastr_node_t rastr_end_node(rastr_ast_t ast);

/********************************************************************************
 Parsing
********************************************************************************/
rastr_ast_t rastr_parse_str(const char* str);
rastr_ast_t rastr_parse_file(const char* filepath);

SEXP rastr_ast_wrap(rastr_ast_t ast);
rastr_ast_t rastr_ast_unwrap(SEXP r_ast);
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

/********************************************************************************
 SEXP
********************************************************************************/

SEXP rastr_to_sexp(rastr_ast_t ast);
SEXP rastr_node_to_sexp(rastr_ast_t ast, rastr_node_t node);

SEXP rastr_ast_wrap(rastr_ast_t ast);
SEXP rastr_node_wrap(rastr_node_t node);

rastr_ast_t rastr_ast_unwrap(SEXP r_ast);
rastr_node_t rastr_node_unwrap(SEXP r_node);

#ifdef __cplusplus
}
#endif

#endif /* RASTR_API_H */
