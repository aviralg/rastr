#ifndef RASTR_API_H
#    define RASTR_API_H

#    include <rastr/RIncludes.h>

/* WARN: do not change this enum, entries are order sensitive! */
enum rastr_node_type_t {
    RASTR_OP_SP = 0,

    /* Arithmetic:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Arithmetic.html
     */
    RASTR_OP_PLUS,  // unary or binary +
    RASTR_OP_MINUS, // unary or binary -
    RASTR_OP_MUL,   // *
    RASTR_OP_DIV,   // /
    RASTR_OP_POW,   // ^
    RASTR_OP_POW2,  // **

    /* Comparison:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Comparison.html
     */
    RASTR_OP_LESS,     // <
    RASTR_OP_LESS_EQ,  // <=
    RASTR_OP_GREAT,    // >
    RASTR_OP_GREAT_EQ, // >=
    RASTR_OP_EQ,       // ==
    RASTR_OP_NOT_EQ,   // !=

    /* Logic: https://stat.ethz.ch/R-manual/R-devel/library/base/html/Logic.html
     */
    RASTR_OP_NOT,     // !
    RASTR_OP_AND,     // &&
    RASTR_OP_VEC_AND, // &
    RASTR_OP_OR,      // ||
    RASTR_OP_VEC_OR,  // |

    /* Assignments:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/assignOps.html */
    RASTR_OP_EQ_ASGN,     // =
    RASTR_OP_LT_ASGN,     // <-
    RASTR_OP_RT_ASGN,     // ->
    RASTR_OP_LT_SUP_ASGN, // <<-
    RASTR_OP_RT_SUP_ASGN, // ->>
    RASTR_OP_COLON_ASGN,  // :=

    /* Pipe: https://stat.ethz.ch/R-manual/R-devel/library/base/html/pipeOp.html
     */
    RASTR_OP_PIPE_FWD,  // |>
    RASTR_OP_PIPE_BIND, // =>

    /* Namespace:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/ns-dblcolon.html
     */
    RASTR_OP_PUB_NS, // ::
    RASTR_OP_PVT_NS, // :::

    /* Range:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Colon.html */
    RASTR_OP_RANGE, // :

    /* Help */
    RASTR_OP_HELP, // ?

    /* Slot: https://stat.ethz.ch/R-manual/R-devel/library/base/html/slotOp.html
     */
    RASTR_OP_SLOT, // @

    /* Formula:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/tilde.html */
    RASTR_OP_FORMULA, // ~

    /* Extract:
       https://stat.ethz.ch/R-manual/R-devel/library/base/html/Extract.html */
    RASTR_OP_PART, // $

    /* Function */
    RASTR_OP_FN,  // function
    RASTR_OP_FN2, /* \ */

    RASTR_OP_WHILE,  // while
    RASTR_OP_REPEAT, // repeat
    RASTR_OP_FOR,    // for
    RASTR_OP_IN,     // in
    RASTR_OP_IF,     // if
    RASTR_OP_ELSE,   // else
    RASTR_OP_NEXT,   // next
    RASTR_OP_BREAK,  // break

    /********************************************************************************
      Brackets
    ********************************************************************************/
    RASTR_BKT_LT_RND,     // (
    RASTR_BKT_RT_RND,     // )
    RASTR_BKT_LT_CURL,    // {
    RASTR_BKT_RT_CURL,    // }
    RASTR_BKT_LT_SQR,     // [
    RASTR_BKT_RT_SQR,     // ]
    RASTR_BKT_LT_DBL_SQR, // [[

    /********************************************************************************
      Delimiters
    ********************************************************************************/
    RASTR_DLMTR_SCOL, // ;
    RASTR_DLMTR_COM,  // ,

    /********************************************************************************
      Literals
    ********************************************************************************/
    RASTR_NULL,
    RASTR_LGL,
    RASTR_INT,
    RASTR_DBL,
    RASTR_CPX,
    RASTR_CHR,
    RASTR_SYM,

    /********************************************************************************
      Expressions
    ********************************************************************************/
    RASTR_BLK,
    RASTR_GRP,
    RASTR_NUOP,
    RASTR_UNOP,
    RASTR_BINOP,
    RASTR_RLP,
    RASTR_WLP,
    RASTR_FLP,
    RASTR_ICOND,
    RASTR_IECOND,
    RASTR_FNDEFN,
    RASTR_FNCALL,
    RASTR_SUB,
    RASTR_IDX,

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    RASTR_AEXPR,
    RASTR_EXPRS,
    RASTR_PARS,
    RASTR_DPAR,
    RASTR_NDPAR,
    RASTR_ARGS,
    RASTR_NARG,
    RASTR_PARG,
    RASTR_COND,
    RASTR_ITER,
    RASTR_PGM,
    RASTR_DLMTD,
    RASTR_MSNG,
    RASTR_BEG,
    RASTR_END,
    RASTR_GAP,
    RASTR_LOC,
    RASTR_ERR

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
    int index;
};

typedef struct rastr_ast_impl_t* rastr_ast_t;

#    ifdef __cplusplus
extern "C" {
#    endif

/********************************************************************************
 Ast
********************************************************************************/
rastr_ast_t rastr_ast_new(int capacity);
SEXP r_rastr_ast_new(SEXP r_capacity);
void rastr_ast_destroy(rastr_ast_t ast);
int rastr_ast_id(rastr_ast_t ast);
SEXP r_rastr_ast_id(SEXP r_ast);
int rastr_ast_size(rastr_ast_t ast);
SEXP r_rastr_ast_size(SEXP r_ast);
rastr_node_t rastr_ast_root_get(rastr_ast_t ast);
SEXP r_rastr_ast_root_get(SEXP r_ast);
rastr_node_t rastr_ast_root_rep(rastr_ast_t ast, rastr_node_t root);
SEXP r_rastr_ast_root_rep(SEXP r_ast, SEXP r_root);
void rastr_ast_root_set(rastr_ast_t ast, rastr_node_t root);
SEXP r_rastr_ast_root_set(SEXP r_ast, SEXP r_root);

/********************************************************************************
 Node
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_ast_t ast, rastr_node_t node);
int rastr_node_id(rastr_ast_t ast, rastr_node_t node);
const char*
rastr_node_to_string(rastr_ast_t ast, rastr_node_t node, int spaces);
rastr_node_t rastr_node_clone(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_node_leftmost(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_node_leftmost(SEXP r_ast, SEXP r_node);

rastr_node_t rastr_node_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_node_gap_get(SEXP r_ast, SEXP r_node);

void rastr_node_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_node_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);

rastr_node_t
rastr_node_desugar(rastr_ast_t ast, rastr_node_t node, int strictness);

rastr_ast_t rastr_ast_desugar(rastr_ast_t ast, int strictness);
SEXP r_rastr_node_desugar(SEXP r_ast, SEXP r_node, SEXP r_strictness);
SEXP r_rastr_ast_desugar(SEXP r_ast, SEXP r_strictness);

/********************************************************************************
 Node Type
********************************************************************************/
const char* rastr_node_type_to_string(rastr_node_type_t type);

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

rastr_node_t rastr_op_node(rastr_ast_t ast,
                           const char* syn,
                           rastr_node_t gap,
                           rastr_node_t loc);
const char* rastr_op_syn_get(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_bkt_node(rastr_ast_t ast,
                            const char* syn,
                            rastr_node_t gap,
                            rastr_node_t loc);

const char* rastr_bkt_syn_get(rastr_ast_t ast, rastr_node_t node);

rastr_node_t rastr_dlmtr_node(rastr_ast_t ast,
                              const char* syn,
                              rastr_node_t gap,
                              rastr_node_t loc);
const char* rastr_dlmtr_syn_get(rastr_ast_t ast, rastr_node_t node);

const char* rastr_null_syn_get(rastr_ast_t ast, rastr_node_t node);

#    include <rastr/autogen_node_ifc.h>

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

    virtual bool pre_bkt(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_bkt(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_null(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_null(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_lgl(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_lgl(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_int(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_int(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_dbl(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_dbl(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_cpx(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_cpx(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_chr(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_chr(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_sym(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_sym(rastr_ast_t ast, rastr_node_t node) {
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

    virtual bool pre_icond(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_icond(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_iecond(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_iecond(rastr_ast_t ast, rastr_node_t node) {
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

    virtual bool pre_aexpr(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_aexpr(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_exprs(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_exprs(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_pars(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_pars(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_dpar(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_dpar(rastr_ast_t ast, rastr_node_t node) {
    }

    virtual bool pre_ndpar(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_ndpar(rastr_ast_t ast, rastr_node_t node) {
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

    virtual bool pre_cond(rastr_ast_t ast, rastr_node_t node) {
        return true;
    }

    virtual void post_cond(rastr_ast_t ast, rastr_node_t node) {
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

#    define CALL_WALKER_0(NODE)            \
        if (this->pre_##NODE(ast, node)) { \
            this->post_##NODE(ast, node);  \
        }

#    define CALL_WALKER_1(NODE, CHILD1)                                \
        if (this->pre_##NODE(ast, node)) {                             \
            this->walk(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
            this->post_##NODE(ast, node);                              \
        }

#    define CALL_WALKER_2(NODE, CHILD1, CHILD2)                        \
        if (this->pre_##NODE(ast, node)) {                             \
            this->walk(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
            this->post_##NODE(ast, node);                              \
        }

#    define CALL_WALKER_3(NODE, CHILD1, CHILD2, CHILD3)                \
        if (this->pre_##NODE(ast, node)) {                             \
            this->walk(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD3##_get(ast, node)); \
            this->post_##NODE(ast, node);                              \
        }

#    define CALL_WALKER_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4)        \
        if (this->pre_##NODE(ast, node)) {                             \
            this->walk(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD3##_get(ast, node)); \
            this->walk(ast, rastr_##NODE##_##CHILD4##_get(ast, node)); \
            this->post_##NODE(ast, node);                              \
        }

#    define CALL_WALKER_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
        if (this->pre_##NODE(ast, node)) {                              \
            this->walk(ast, rastr_##NODE##_##CHILD1##_get(ast, node));  \
            this->walk(ast, rastr_##NODE##_##CHILD2##_get(ast, node));  \
            this->walk(ast, rastr_##NODE##_##CHILD3##_get(ast, node));  \
            this->walk(ast, rastr_##NODE##_##CHILD4##_get(ast, node));  \
            this->walk(ast, rastr_##NODE##_##CHILD5##_get(ast, node));  \
            this->post_##NODE(ast, node);                               \
        }

#    define CALL_WALKER_SEQ(NODE, LEN, SEQ)                            \
        if (this->pre_##NODE(ast, node)) {                             \
            int len = rastr_##NODE##_##LEN##_get(ast, node);           \
            for (int i = 0; i < len; ++i) {                            \
                rastr_node_t child = rastr_##NODE##_get(ast, node, i); \
                this->walk(ast, child);                                \
            }                                                          \
            this->post_##NODE(ast, node);                              \
        }

    virtual void walk(rastr_ast_t ast, rastr_node_t node) {
        rastr_node_type_t type = rastr_node_type(ast, node);
        switch (type) {
            /********************************************************************************
             Operators
            ********************************************************************************/
        case RASTR_OP_SP:
        case RASTR_OP_PLUS:
        case RASTR_OP_MINUS:
        case RASTR_OP_MUL:
        case RASTR_OP_DIV:
        case RASTR_OP_POW:
        case RASTR_OP_POW2:
        case RASTR_OP_LESS:
        case RASTR_OP_LESS_EQ:
        case RASTR_OP_GREAT:
        case RASTR_OP_GREAT_EQ:
        case RASTR_OP_EQ:
        case RASTR_OP_NOT_EQ:
        case RASTR_OP_NOT:
        case RASTR_OP_AND:
        case RASTR_OP_VEC_AND:
        case RASTR_OP_OR:
        case RASTR_OP_VEC_OR:
        case RASTR_OP_EQ_ASGN:
        case RASTR_OP_LT_ASGN:
        case RASTR_OP_RT_ASGN:
        case RASTR_OP_LT_SUP_ASGN:
        case RASTR_OP_RT_SUP_ASGN:
        case RASTR_OP_COLON_ASGN:
        case RASTR_OP_PIPE_FWD:
        case RASTR_OP_PIPE_BIND:
        case RASTR_OP_PUB_NS:
        case RASTR_OP_PVT_NS:
        case RASTR_OP_RANGE:
        case RASTR_OP_HELP:
        case RASTR_OP_SLOT:
        case RASTR_OP_FORMULA:
        case RASTR_OP_PART:
        case RASTR_OP_FN:
        case RASTR_OP_FN2:
        case RASTR_OP_WHILE:
        case RASTR_OP_REPEAT:
        case RASTR_OP_FOR:
        case RASTR_OP_IN:
        case RASTR_OP_IF:
        case RASTR_OP_ELSE:
        case RASTR_OP_NEXT:
        case RASTR_OP_BREAK:
            CALL_WALKER_2(op, gap, loc);
            break;

            /********************************************************************************
             Brackets
            ********************************************************************************/
        case RASTR_BKT_LT_RND:
        case RASTR_BKT_RT_RND:
        case RASTR_BKT_LT_CURL:
        case RASTR_BKT_RT_CURL:
        case RASTR_BKT_LT_SQR:
        case RASTR_BKT_RT_SQR:
        case RASTR_BKT_LT_DBL_SQR:
            CALL_WALKER_2(bkt, gap, loc);
            break;

            /********************************************************************************
             Delimiters
            ********************************************************************************/
        case RASTR_DLMTR_SCOL:
        case RASTR_DLMTR_COM:
            CALL_WALKER_2(dlmtr, gap, loc);
            break;

            /********************************************************************************
              Literals
            ********************************************************************************/
        case RASTR_NULL:
            CALL_WALKER_2(null, gap, loc);
            break;

        case RASTR_LGL:
            CALL_WALKER_2(lgl, gap, loc);
            break;

        case RASTR_INT:
            CALL_WALKER_2(int, gap, loc);
            break;

        case RASTR_DBL:
            CALL_WALKER_2(dbl, gap, loc);
            break;

        case RASTR_CPX:
            CALL_WALKER_2(cpx, gap, loc);
            break;

        case RASTR_CHR:
            CALL_WALKER_2(chr, gap, loc);
            break;

        case RASTR_SYM:
            CALL_WALKER_2(sym, gap, loc);
            break;

        /********************************************************************************
          Expressions
        ********************************************************************************/
        case RASTR_BLK:
            CALL_WALKER_3(blk, lbkt, exprs, rbkt)
            break;

        case RASTR_GRP:
            CALL_WALKER_3(grp, lbkt, expr, rbkt);
            break;

        case RASTR_NUOP:
            CALL_WALKER_1(nuop, op);
            break;

        case RASTR_UNOP:
            CALL_WALKER_2(unop, op, expr);
            break;

        case RASTR_BINOP:
            CALL_WALKER_3(binop, lexpr, op, rexpr);
            break;

        case RASTR_RLP:
            CALL_WALKER_2(rlp, op, body);
            break;

        case RASTR_WLP:
            CALL_WALKER_3(wlp, op, cond, body);
            break;

        case RASTR_FLP:
            CALL_WALKER_3(flp, op, iter, body);
            break;

        case RASTR_ICOND:
            CALL_WALKER_3(icond, iop, cond, ibody);
            break;

        case RASTR_IECOND:
            CALL_WALKER_5(iecond, iop, cond, ibody, eop, ebody);
            break;

        case RASTR_FNDEFN:
            CALL_WALKER_5(fndefn, op, lbkt, pars, rbkt, body);
            break;

        case RASTR_FNCALL:
            CALL_WALKER_4(fncall, fn, lbkt, args, rbkt);
            break;

        case RASTR_SUB:
            CALL_WALKER_4(sub, obj, lbkt, args, rbkt);
            break;

        case RASTR_IDX:
            CALL_WALKER_5(idx, obj, lbkt, args, rbkt1, rbkt2);
            break;

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
        case RASTR_AEXPR:
            CALL_WALKER_2(aexpr, ann, expr)
            break;

        case RASTR_EXPRS:
            CALL_WALKER_SEQ(exprs, len, seq)
            break;

        case RASTR_PARS:
            CALL_WALKER_SEQ(pars, len, seq)
            break;

        case RASTR_DPAR:
            CALL_WALKER_3(dpar, name, op, expr)
            break;

        case RASTR_NDPAR:
            CALL_WALKER_1(ndpar, name)
            break;

        case RASTR_ARGS:
            CALL_WALKER_SEQ(args, len, seq)
            break;

        case RASTR_NARG:
            CALL_WALKER_3(narg, name, op, expr)
            break;

        case RASTR_PARG:
            CALL_WALKER_1(parg, expr)
            break;

        case RASTR_COND:
            CALL_WALKER_3(cond, lbkt, expr, rbkt)
            break;

        case RASTR_ITER:
            CALL_WALKER_5(iter, lbkt, var, op, expr, rbkt)
            break;

        case RASTR_PGM:
            CALL_WALKER_3(pgm, beg, exprs, end)
            break;

        case RASTR_DLMTD:
            CALL_WALKER_2(dlmtd, expr, dlmtr)
            break;

        case RASTR_MSNG:
            CALL_WALKER_2(msng, gap, loc)
            break;

        case RASTR_BEG:
            CALL_WALKER_1(beg, loc)
            break;

        case RASTR_END:
            CALL_WALKER_2(end, gap, loc)
            break;

        case RASTR_GAP:
            CALL_WALKER_1(gap, loc)
            break;

        case RASTR_LOC:
            CALL_WALKER_0(loc)
            break;

        case RASTR_ERR:
            Rf_error("unexpected rastr node of type 'Error'");
            break;
        }
    }
#    undef CALL_WALKER_0
#    undef CALL_WALKER_1
#    undef CALL_WALKER_2
#    undef CALL_WALKER_3
#    undef CALL_WALKER_4
#    undef CALL_WALKER_5
#    undef HANDLE_SEQ
#    undef CALL_WALKER_SEQ
};

#    ifdef __cplusplus
}
#    endif

#endif /* RASTR_API_H */

/*******************************************************************************
 * op
 *******************************************************************************/

rastr_node_t rastr_op_new(rastr_ast_t ast,
                          const char* syn,
                          rastr_node_t gap,
                          rastr_node_t loc);
SEXP r_rastr_op_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc);
const char* rastr_op_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_syn_get(SEXP r_ast, SEXP r_node);

/*******************************************************************************
 * bkt
 *******************************************************************************/

rastr_node_t rastr_bkt_new(rastr_ast_t ast,
                           const char* syn,
                           rastr_node_t gap,
                           rastr_node_t loc);
SEXP r_rastr_bkt_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc);
const char* rastr_bkt_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_bkt_syn_get(SEXP r_ast, SEXP r_node);

/*******************************************************************************
 * dlmtr
 *******************************************************************************/

rastr_node_t rastr_dlmtr_new(rastr_ast_t ast,
                             const char* syn,
                             rastr_node_t gap,
                             rastr_node_t loc);
SEXP r_rastr_dlmtr_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc);
const char* rastr_dlmtr_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtr_syn_get(SEXP r_ast, SEXP r_node);

/*******************************************************************************
 * lgl
 *******************************************************************************/

rastr_node_t
rastr_lgl_new(rastr_ast_t ast, int val, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_lgl_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc);

const char* rastr_lgl_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lgl_syn_get(SEXP r_ast, SEXP r_node);

/*******************************************************************************
 * int
 *******************************************************************************/

rastr_node_t
rastr_int_new(rastr_ast_t ast, int val, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_int_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc);

/*******************************************************************************
 * dbl
 *******************************************************************************/

rastr_node_t
rastr_dbl_new(rastr_ast_t ast, double val, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_dbl_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc);

/*******************************************************************************
 * cpx
 *******************************************************************************/

rastr_node_t
rastr_cpx_new(rastr_ast_t ast, double img, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_cpx_new(SEXP r_ast, SEXP r_img, SEXP r_gap, SEXP r_loc);

/*******************************************************************************
 * chr
 *******************************************************************************/

rastr_node_t rastr_chr_new_unsafe(rastr_ast_t ast,
                                  const char* val,
                                  const char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc);
rastr_node_t rastr_chr_new(rastr_ast_t ast,
                           const char* val,
                           rastr_node_t gap,
                           rastr_node_t loc);
SEXP r_rastr_chr_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc);

/*******************************************************************************
 * sym
 *******************************************************************************/

rastr_node_t rastr_sym_new_unsafe(rastr_ast_t ast,
                                  const char* val,
                                  const char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc);
rastr_node_t rastr_sym_new(rastr_ast_t ast,
                           const char* val,
                           int quote,
                           rastr_node_t gap,
                           rastr_node_t loc);
SEXP r_rastr_sym_new(SEXP r_ast,
                     SEXP r_val,
                     SEXP r_quote,
                     SEXP r_gap,
                     SEXP r_loc);

/*******************************************************************************
 * gap
 *******************************************************************************/

rastr_node_t rastr_gap_new(rastr_ast_t ast, const char* val, rastr_node_t loc);

SEXP r_rastr_gap_new(SEXP r_ast, SEXP r_val, SEXP r_loc);

/*******************************************************************************
 * beg
 *******************************************************************************/

rastr_node_t rastr_beg_new(rastr_ast_t ast, const char* bom, rastr_node_t loc);

SEXP r_rastr_beg_new(SEXP r_ast, SEXP r_bom, SEXP r_loc);

/*******************************************************************************
 * err
 *******************************************************************************/

rastr_node_t rastr_err_new(rastr_ast_t ast, const char* msg, rastr_node_t loc);

SEXP r_rastr_err_new(SEXP r_ast, SEXP r_msg, SEXP r_loc);

// pred
int rastr_lit_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lit_type(SEXP r_ast, SEXP r_node);
