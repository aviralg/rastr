#ifndef RASTR_API_H
#define RASTR_API_H

#include <rastr/RIncludes.h>

/* WARN: do not change this enum, entries are order sensitive! */
enum rastr_node_type_t {
    Special = 0,

    /* Arithmetic:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Arithmetic.html
     */
    Plus,           // unary or binary +
    Minus,          // unary or binary -
    Multiplication, // *
    Division,       // /
    Power,          // ^
    Power2,         // **

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
    Not,    // !
    And,    // &&
    VecAnd, // &
    Or,     // ||
    VecOr,  // |

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
    Function2, /* \ */

    Function, // function
    While,    // while
    Repeat,   // repeat
    For,      // for
    In,       // in
    If,       // if
    Else,     // else
    Next,     // next
    Break,    // break

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
    NullaryOperation,
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
    Beg,
    End,
    Gap,
    Location,
    Error

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
Operator
********************************************************************************/
rastr_node_t rastr_op_node(rastr_ast_t ast,
                           rastr_node_type_t type,
                           rastr_node_t gap,
                           rastr_node_t loc);

// val
const char* rastr_op_val(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_val(SEXP r_ast, SEXP r_node);

// syn
const char* rastr_op_syn(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_syn(SEXP r_ast, SEXP r_node);

// gap
rastr_node_t rastr_op_gap(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_gap(SEXP r_ast, SEXP r_node);
rastr_node_t rastr_op_loc(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Delimiters
********************************************************************************/

bool rastr_node_is_delimiter(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_delimiter(rastr_ast_t ast,
                                  rastr_node_type_t type,
                                  rastr_node_t gap,
                                  rastr_node_t loc);
const char* rastr_node_delimiter_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_delimiter_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dlmtr_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dlmtr_loc(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Terminators
********************************************************************************/

bool rastr_node_is_terminator(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_node_terminator(rastr_ast_t ast,
                                   rastr_node_type_t type,
                                   rastr_node_t gap,
                                   rastr_node_t loc);
const char* rastr_node_terminator_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_terminator_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_term_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_term_loc(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Meta
********************************************************************************/

// End
rastr_node_t
rastr_node_end(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);

// Error
rastr_node_t rastr_node_error(rastr_ast_t ast, const char* fmt, ...);
const char* rastr_node_error_message(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Literals
********************************************************************************/
bool rastr_node_is_literal(rastr_ast_t ast, rastr_node_t node);

// null
rastr_node_t
rastr_node_null(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);
const char* rastr_node_null_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_null_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_null_loc(rastr_ast_t ast, rastr_node_t node);

// logical
rastr_node_t rastr_node_logical(rastr_ast_t ast,
                                const char* syntax,
                                int value,
                                rastr_node_t gap,
                                rastr_node_t loc);
int rastr_node_logical_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_logical_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_logical_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_logical_loc(rastr_ast_t ast, rastr_node_t node);

// integer
rastr_node_t rastr_node_integer(rastr_ast_t ast,
                                const char* syntax,
                                int value,
                                rastr_node_t gap,
                                rastr_node_t loc);
int rastr_node_integer_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_integer_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_integer_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_integer_loc(rastr_ast_t ast, rastr_node_t node);

// real
rastr_node_t rastr_node_real(rastr_ast_t ast,
                             const char* syntax,
                             double value,
                             rastr_node_t gap,
                             rastr_node_t loc);
double rastr_node_real_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_real_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_real_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_real_loc(rastr_ast_t ast, rastr_node_t node);

// complex
rastr_node_t rastr_node_complex(rastr_ast_t ast,
                                const char* syntax,
                                const Rcomplex& value,
                                rastr_node_t gap,
                                rastr_node_t loc);
Rcomplex rastr_node_complex_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_complex_syntax(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_complex_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_complex_loc(rastr_ast_t ast, rastr_node_t node);

// string
rastr_node_t rastr_node_string(rastr_ast_t ast,
                               const char* syntax,
                               const char* value,
                               rastr_node_t gap,
                               rastr_node_t loc);
const char* rastr_node_string_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_string_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_string_is_raw(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_string_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_string_loc(rastr_ast_t ast, rastr_node_t node);

// symbol
rastr_node_t rastr_node_symbol(rastr_ast_t ast,
                               const char* syntax,
                               const char* value,
                               rastr_node_t gap,
                               rastr_node_t loc);
const char* rastr_node_symbol_value(rastr_ast_t ast, rastr_node_t node);
const char* rastr_node_symbol_syntax(rastr_ast_t ast, rastr_node_t node);
bool rastr_node_symbol_is_quoted(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_symbol_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_symbol_loc(rastr_ast_t ast, rastr_node_t node);

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

rastr_node_t rastr_nuop_node(rastr_ast_t ast, rastr_node_t op);
rastr_node_t rastr_nuop_op(rastr_ast_t ast, rastr_node_t node);

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

rastr_node_t rastr_pgm_node(rastr_ast_t ast,
                            rastr_node_t beg,
                            int len,
                            const rastr_node_t* seq,
                            rastr_node_t end);
rastr_node_t rastr_pgm_beg(rastr_ast_t ast, rastr_node_t node);
int rastr_pgm_len(rastr_ast_t ast, rastr_node_t node);
const rastr_node_t* rastr_pgm_seq(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_pgm_end(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_dlmtd_node(rastr_ast_t ast, rastr_node_t expr, rastr_node_t dlmtr);
rastr_node_t rastr_dlmtd_expr(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_dlmtd_dlmtr(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_err_node(rastr_ast_t ast, const char* msg);
const char* rastr_err_msg(rastr_ast_t ast, rastr_node_t node);

rastr_node_t
rastr_msng_node(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);
rastr_node_t rastr_msng_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_msng_loc(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_beg_node(rastr_ast_t ast, rastr_node_t loc);
rastr_node_t rastr_beg_loc(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_end_node(rastr_ast_t ast);
rastr_node_t rastr_end_gap(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_end_loc(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_gap_node_owner(rastr_ast_t ast, char* val, rastr_node_t loc);
const char* rastr_gap_val(rastr_ast_t ast, rastr_node_t node);
rastr_node_t rastr_gap_loc(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_loc_node(rastr_ast_t ast,
                            int lrow,
                            int lcol,
                            int lchr,
                            int lbyte,
                            int rrow,
                            int rcol,
                            int rchr,
                            int rbyte);
int rastr_pos_lrow(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_lcol(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_lchr(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_lbyte(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_rrow(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_rcol(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_rchr(rastr_ast_t ast, rastr_node_t node);
int rastr_pos_rbyte(rastr_ast_t ast, rastr_node_t node);

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

char* rastr_ast_unparse_str(rastr_ast_t ast);
char* rastr_node_unparse_str(rastr_ast_t ast, rastr_node_t node);

/********************************************************************************
 Export
********************************************************************************/

void rastr_export_to_dot(rastr_ast_t ast, const char* filepath, int depth);
SEXP r_rastr_export_to_dot(SEXP r_ast, SEXP r_filepath, SEXP r_depth);

/********************************************************************************
 SEXP
********************************************************************************/

SEXP rastr_as_sexp(rastr_ast_t ast);
SEXP rastr_node_as_sexp(rastr_ast_t ast, rastr_node_t node);

SEXP rastr_as_df(rastr_ast_t ast);
SEXP rastr_node_as_df(rastr_ast_t ast, rastr_node_t node);

SEXP rastr_ast_wrap(rastr_ast_t ast);
SEXP rastr_node_wrap(rastr_node_t node);

rastr_ast_t rastr_ast_unwrap(SEXP r_ast);
rastr_node_t rastr_node_unwrap(SEXP r_node);

class AstWalker {
  public:
    AstWalker() {
    }

    virtual ~AstWalker() {
    }

    virtual bool pre_op(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_op(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_dlmtr(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_term(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_term(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_null(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_null(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_logical(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_logical(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_integer(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_integer(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_real(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_real(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_complex(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_complex(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_string(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_string(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_symbol(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_symbol(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_blk(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_blk(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_grp(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_grp(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_nuop(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_nuop(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_unop(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_unop(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_binop(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_binop(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_rlp(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_rlp(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_wlp(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_wlp(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_flp(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_flp(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_icnd(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_icnd(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_iecnd(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_iecnd(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_fndefn(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_fncall(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_fncall(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_sub(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_sub(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_idx(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_idx(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_params(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_params(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_dparam(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_dparam(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_ndparam(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_ndparam(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_args(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_args(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_narg(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_narg(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_parg(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_parg(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_cnd(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_cnd(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_iter(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_iter(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_pgm(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_pgm(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_dlmtd(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_dlmtd(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_msng(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_msng(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_beg(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_beg(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_end(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_end(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_gap(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_gap(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_loc(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_loc(rastr_ast_t ast, rastr_node_t node) {
    }

#define CALL_WALKER_0(NODE)            \
    if (this->pre_##NODE(ast, node)) { \
        this->post_##NODE(ast, node);  \
    }

#define CALL_WALKER_1(NODE, CHILD1)                          \
    if (this->pre_##NODE(ast, node)) {                       \
        this->walk(ast, rastr_##NODE##_##CHILD1(ast, node)); \
        this->post_##NODE(ast, node);                        \
    }

#define CALL_WALKER_2(NODE, CHILD1, CHILD2)                  \
    if (this->pre_##NODE(ast, node)) {                       \
        this->walk(ast, rastr_##NODE##_##CHILD1(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD2(ast, node)); \
        this->post_##NODE(ast, node);                        \
    }

#define CALL_WALKER_3(NODE, CHILD1, CHILD2, CHILD3)          \
    if (this->pre_##NODE(ast, node)) {                       \
        this->walk(ast, rastr_##NODE##_##CHILD1(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD2(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD3(ast, node)); \
        this->post_##NODE(ast, node);                        \
    }

#define CALL_WALKER_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4)  \
    if (this->pre_##NODE(ast, node)) {                       \
        this->walk(ast, rastr_##NODE##_##CHILD1(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD2(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD3(ast, node)); \
        this->walk(ast, rastr_##NODE##_##CHILD4(ast, node)); \
        this->post_##NODE(ast, node);                        \
    }

#define CALL_WALKER_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
    if (this->pre_##NODE(ast, node)) {                              \
        this->walk(ast, rastr_##NODE##_##CHILD1(ast, node));        \
        this->walk(ast, rastr_##NODE##_##CHILD2(ast, node));        \
        this->walk(ast, rastr_##NODE##_##CHILD3(ast, node));        \
        this->walk(ast, rastr_##NODE##_##CHILD4(ast, node));        \
        this->walk(ast, rastr_##NODE##_##CHILD5(ast, node));        \
        this->post_##NODE(ast, node);                               \
    }

#define HANDLE_SEQ(NODE, LEN, SEQ)                                 \
    {                                                              \
        int len = rastr_##NODE##_##LEN(ast, node);                 \
        const rastr_node_t* seq = rastr_##NODE##_##SEQ(ast, node); \
        for (int i = 0; i < len; ++i) {                            \
            this->walk(ast, seq[i]);                               \
        }                                                          \
    }

#define CALL_WALKER_BRACK_SEQ(NODE, LBRACK, LEN, SEQ, RBRACK) \
    if (this->pre_##NODE(ast, node)) {                        \
        this->walk(ast, rastr_##NODE##_##LBRACK(ast, node));  \
        HANDLE_SEQ(NODE, LEN, SEQ);                           \
        this->walk(ast, rastr_##NODE##_##RBRACK(ast, node));  \
        this->post_##NODE(ast, node);                         \
    }

#define CALL_WALKER_SEQ(NODE, LEN, SEQ) \
    if (this->pre_##NODE(ast, node)) {  \
        HANDLE_SEQ(NODE, LEN, SEQ);     \
        this->post_##NODE(ast, node);   \
    }

    virtual void walk(rastr_ast_t ast, rastr_node_t node) {
        rastr_node_type_t type = rastr_node_type(ast, node);
        switch (type) {
            /********************************************************************************
             Operators
            ********************************************************************************/
        case Special:
        case Plus:
        case Minus:
        case Multiplication:
        case Division:
        case Power:
        case Power2:
        case LessThan:
        case LessThanEqual:
        case GreaterThan:
        case GreaterThanEqual:
        case Equal:
        case NotEqual:
        case Not:
        case And:
        case VecAnd:
        case Or:
        case VecOr:
        case EqualAssign:
        case LeftAssign:
        case RightAssign:
        case LeftSuperAssign:
        case RightSuperAssign:
        case ColonAssign:
        case PipeForward:
        case PipeBind:
        case PublicNamespace:
        case PrivateNamespace:
        case Range:
        case Help:
        case SlotExtract:
        case Formula:
        case PartExtract:
        case Function:
        case Function2:
        case While:
        case Repeat:
        case For:
        case In:
        case If:
        case Else:
        case Next:
        case Break:
            CALL_WALKER_2(op, gap, loc);
            break;

            /********************************************************************************
             Delimiters
            ********************************************************************************/
        case LeftParen:
        case RightParen:
        case LeftBrace:
        case RightBrace:
        case LeftBracket:
        case RightBracket:
        case DoubleLeftBracket:
        case DoubleRightBracket:
            CALL_WALKER_2(dlmtr, gap, loc);
            break;

            /********************************************************************************
             Terminators
            ********************************************************************************/
        case Semicolon:
        case Newline:
        case Comma:
            CALL_WALKER_2(term, gap, loc);
            break;

            /********************************************************************************
              Literals
            ********************************************************************************/
        case Null:
            CALL_WALKER_2(null, gap, loc);
            break;

        case Logical:
            CALL_WALKER_2(logical, gap, loc);
            break;

        case Integer:
            CALL_WALKER_2(integer, gap, loc);
            break;

        case Real:
            CALL_WALKER_2(real, gap, loc);
            break;

        case Complex:
            CALL_WALKER_2(complex, gap, loc);
            break;

        case String:
            CALL_WALKER_2(string, gap, loc);
            break;

        case Symbol:
            CALL_WALKER_2(symbol, gap, loc);
            break;

        /********************************************************************************
          Expressions
        ********************************************************************************/
        case Block:
            CALL_WALKER_BRACK_SEQ(blk, lbrack, len, seq, rbrack)
            break;

        case Group:
            CALL_WALKER_3(grp, lbrack, expr, rbrack);
            break;

        case NullaryOperation:
            CALL_WALKER_1(nuop, op);
            break;

        case UnaryOperation:
            CALL_WALKER_2(unop, op, expr);
            break;

        case BinaryOperation:
            CALL_WALKER_3(binop, lexpr, op, rexpr);
            break;

        case RepeatLoop:
            CALL_WALKER_2(rlp, kw, body);
            break;

        case WhileLoop:
            CALL_WALKER_3(wlp, kw, cond, body);
            break;

        case ForLoop:
            CALL_WALKER_3(flp, kw, iter, body);
            break;

        case IfConditional:
            CALL_WALKER_3(icnd, ikw, cond, ibody);
            break;

        case IfElseConditional:
            CALL_WALKER_5(iecnd, ikw, cond, ibody, ekw, ebody);
            break;

        case FunctionDefinition:
            CALL_WALKER_3(fndefn, hd, params, body);
            break;

        case FunctionCall:
            CALL_WALKER_2(fncall, fun, args);
            break;

        case Subset:
            CALL_WALKER_2(sub, obj, inds);
            break;

        case Index:
            CALL_WALKER_2(idx, obj, inds);
            break;

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
        case Parameters:
            CALL_WALKER_BRACK_SEQ(params, lbrack, len, seq, rbrack)
            break;

        case DefaultParameter:
            CALL_WALKER_3(dparam, name, op, expr)
            break;

        case NonDefaultParameter:
            CALL_WALKER_1(ndparam, name)
            break;

        case Arguments:
            CALL_WALKER_BRACK_SEQ(args, lbrack, len, seq, rbrack)
            break;

        case NamedArgument:
            CALL_WALKER_3(narg, name, op, expr)
            break;

        case PositionalArgument:
            CALL_WALKER_1(parg, expr)
            break;

        case Condition:
            CALL_WALKER_3(cnd, lbrack, expr, rbrack)
            break;

        case Iteration:
            CALL_WALKER_5(iter, lbrack, var, kw, expr, rbrack)
            break;

        case Program:
            CALL_WALKER_BRACK_SEQ(pgm, beg, len, seq, end)
            break;

        case Delimited:
            CALL_WALKER_2(dlmtd, expr, dlmtr)
            break;

        case Missing:
            CALL_WALKER_2(msng, gap, loc)
            break;

        case Beg:
            CALL_WALKER_1(beg, loc)
            break;

        case End:
            CALL_WALKER_2(end, gap, loc)
            break;

        case Gap:
            CALL_WALKER_1(gap, loc)
            break;

        case Location:
            CALL_WALKER_0(loc)
            break;

        case Error:
            Rf_error("unexpected rastr node of type 'Error'");
            break;
        }
    }
#undef CALL_WALKER_0
#undef CALL_WALKER_1
#undef CALL_WALKER_2
#undef CALL_WALKER_3
#undef CALL_WALKER_4
#undef CALL_WALKER_5
#undef HANDLE_SEQ
#undef CALL_WALKER_BRACK_SEQ
#undef CALL_WALKER_SEQ
};

#ifdef __cplusplus
}
#endif

#endif /* RASTR_API_H */
