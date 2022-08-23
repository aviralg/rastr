#include <rastr/api.h>
#include "internal_api.h"
#include "utilities.h"
#include "logger.h"
#include "Pool.h"
#include "interop.h"
#include "r_api.h"
#include <vector>

int id_counter = 0;

#define NODE_TYPE_ERROR(expected, actual)                 \
    fail_with("incorrect node type; expected %s, got %s", \
              expected,                                   \
              rastr_node_type_to_string(actual));

struct rastr_node_impl_t {
    rastr_node_type_t type;
    int id;

    union {
        struct {
            char* syn;
            rastr_node_t gap;
            rastr_node_t loc;
        } op_node;

        struct {
            char* message;
        } error_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } null_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } dlmtr_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } terminator_node;

        struct {
            char* syntax;
            int value;
            rastr_node_t gap;
            rastr_node_t loc;
        } logical_node;

        struct {
            char* syntax;
            int value;
            rastr_node_t gap;
            rastr_node_t loc;
        } integer_node;

        struct {
            char* syntax;
            double value;
            rastr_node_t gap;
            rastr_node_t loc;
        } real_node;

        struct {
            char* syntax;
            Rcomplex value;
            rastr_node_t gap;
            rastr_node_t loc;
        } complex_node;

        struct {
            char* syntax;
            char* value;
            rastr_node_t gap;
            rastr_node_t loc;
        } string_node;

        struct {
            char* syntax;
            char* value;
            rastr_node_t gap;
            rastr_node_t loc;
        } symbol_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t* seq;
            int len;
            rastr_node_t rbrack;
        } blk_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t expr;
            rastr_node_t rbrack;
        } grp_node;

        struct {
            rastr_node_t op;
        } nuop_node;

        struct {
            rastr_node_t op;
            rastr_node_t expr;
        } unop_node;

        struct {
            rastr_node_t lexpr;
            rastr_node_t op;
            rastr_node_t rexpr;
        } binop_node;

        struct {
            rastr_node_t kw;
            rastr_node_t body;
        } rlp_node;

        struct {
            rastr_node_t kw;
            rastr_node_t cond;
            rastr_node_t body;
        } wlp_node;

        struct {
            rastr_node_t kw;
            rastr_node_t iter;
            rastr_node_t body;
        } flp_node;

        struct {
            rastr_node_t ikw;
            rastr_node_t cond;
            rastr_node_t ibody;
        } icnd_node;

        struct {
            rastr_node_t ikw;
            rastr_node_t cond;
            rastr_node_t ibody;
            rastr_node_t ekw;
            rastr_node_t ebody;
        } iecnd_node;

        struct {
            rastr_node_t hd;
            rastr_node_t params;
            rastr_node_t body;
        } fndefn_node;

        struct {
            rastr_node_t fun;
            rastr_node_t args;
        } fncall_node;

        struct {
            rastr_node_t obj;
            rastr_node_t inds;
        } sub_node;

        struct {
            rastr_node_t obj;
            rastr_node_t inds;
        } idx_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t* seq;
            int len;
            rastr_node_t rbrack;
        } params_node;

        struct {
            rastr_node_t name;
            rastr_node_t op;
            rastr_node_t expr;
        } dparam_node;

        struct {
            rastr_node_t name;
        } ndparam_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t* seq;
            int len;
            rastr_node_t rbrack;
        } args_node;

        struct {
            rastr_node_t name;
            rastr_node_t op;
            rastr_node_t expr;
        } narg_node;

        struct {
            rastr_node_t expr;
        } parg_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t expr;
            rastr_node_t rbrack;
        } cnd_node;

        struct {
            rastr_node_t lbrack;
            rastr_node_t var;
            rastr_node_t kw;
            rastr_node_t expr;
            rastr_node_t rbrack;
        } iter_node;

        struct {
            rastr_node_t beg;
            rastr_node_t* seq;
            int len;
            rastr_node_t end;
        } pgm_node;

        struct {
            rastr_node_t expr;
            rastr_node_t dlmtr;
        } dlmtd_node;

        struct {
            char* msg;
        } err_node;

        struct {
            char* val;
            rastr_node_t loc;
        } gap_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } end_node;

        struct {
            rastr_node_t loc;
        } beg_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } msng_node;

        struct {
            int lrow;
            int lcol;
            int lchr;
            int lbyte;
            int rrow;
            int rcol;
            int rchr;
            int rbyte;
        } loc_node;

    } node;
};

SEXP R_RASTR_AST_CLASS = R_NilValue;
SEXP R_RASTR_NODE_CLASS = R_NilValue;

void r_rastr_ast_destroy(SEXP r_ast) {
    rastr_ast_t ast = (rastr_ast_t) rastr_r_externalptr_to_c_pointer(r_ast);
    if (ast == NULL) {
        rastr_log_error("encountered NULL ast reference");
    }
    R_ClearExternalPtr(r_ast);
    rastr_ast_destroy(ast);
}

SEXP rastr_ast_wrap(rastr_ast_t ast) {
    SEXP r_ast = rastr_c_pointer_to_r_externalptr(
        ast, R_NilValue, R_NilValue, r_rastr_ast_destroy);
    PROTECT(r_ast);
    rastr_sexp_set_class(r_ast, R_RASTR_AST_CLASS);
    UNPROTECT(1);
    return r_ast;
}

rastr_ast_t rastr_ast_unwrap(SEXP r_ast) {
    rastr_ast_t ast = (rastr_ast_t) rastr_r_externalptr_to_c_pointer(r_ast);
    return ast;
}

void r_rastr_node_destroy(SEXP r_node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) rastr_r_externalptr_to_c_pointer(r_node);
    if (node_ptr == NULL) {
        rastr_log_error("encountered NULL node reference");
    }
    R_ClearExternalPtr(r_node);
    free(node_ptr);
}

SEXP rastr_node_wrap(rastr_node_t node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t));
    node_ptr->index = node.index;

    SEXP r_node = rastr_c_pointer_to_r_externalptr(
        node_ptr, R_NilValue, R_NilValue, r_rastr_node_destroy);
    PROTECT(r_node);
    rastr_sexp_set_class(r_node, R_RASTR_NODE_CLASS);
    UNPROTECT(1);
    return r_node;
}

SEXP rastr_node_seq_wrap(const rastr_node_t* seq, int len) {
    SEXP r_list = PROTECT(allocVector(VECSXP, len));

    for (int i = 0; i < len; ++i) {
        rastr_node_t node = seq[i];
        SEXP r_node = PROTECT(rastr_node_wrap(node));
        SET_VECTOR_ELT(r_list, i, r_node);
        UNPROTECT(1);
    }

    UNPROTECT(1);
    return r_list;
}

rastr_node_t rastr_node_unwrap(SEXP r_node) {
    rastr_node_t* node_ptr =
        (rastr_node_t*) rastr_r_externalptr_to_c_pointer(r_node);
    return *node_ptr;
}

SEXP r_rastr_initialize(SEXP r_pack_env) {
    R_RASTR_AST_CLASS = rastr_str_wrap("rastr_ast");
    rastr_sexp_acquire(R_RASTR_AST_CLASS);
    R_RASTR_NODE_CLASS = rastr_str_wrap("rastr_node");
    rastr_sexp_acquire(R_RASTR_NODE_CLASS);
    return R_NilValue;
}

SEXP r_rastr_finalize(SEXP r_pack_env) {
    rastr_sexp_release(R_RASTR_AST_CLASS);
    rastr_sexp_release(R_RASTR_NODE_CLASS);
    return R_NilValue;
}

SEXP r_rastr_ast_print(SEXP r_ast) {
    return R_NilValue;
}

typedef rastr_node_impl_t* rastr_node_ptr_t;

void rastr_node_destroy_shallow(rastr_node_ptr_t ptr);

typedef Pool<rastr_node_impl_t, rastr_node_destroy_shallow> AstPool;

struct rastr_ast_impl_t {
    AstPool* pool;
    rastr_node_t root;
};

const int INDENTATION = 4;

bool rastr_node_type_is_delimiter(rastr_node_type_t type) {
    switch (type) {
    case LeftParen:
    case RightParen:
    case LeftBrace:
    case RightBrace:
    case LeftBracket:
    case RightBracket:
    case DoubleLeftBracket:
    case DoubleRightBracket:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_terminator(rastr_node_type_t type) {
    switch (type) {
    case Semicolon:
    case Newline:
    case Comma:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_literal(rastr_node_type_t type) {
    switch (type) {
    case Null:
    case Logical:
    case Integer:
    case Real:
    case Complex:
    case String:
    case Symbol:
        return true;
    default:
        return false;
    }
}

const char* rastr_node_type_to_string(rastr_node_type_t type) {
    switch (type) {
    case Special:
        return "Special";
    case Plus:
        return "Plus";
    case Minus:
        return "Minus";
    case Multiplication:
        return "Multiplication";
    case Division:
        return "Division";
    case Power:
        return "Power";
    case Power2:
        return "Power2";
    case LessThan:
        return "LessThan";
    case LessThanEqual:
        return "LessThanEqual";
    case GreaterThan:
        return "GreaterThan";
    case GreaterThanEqual:
        return "GreaterThanEqual";
    case Equal:
        return "Equal";
    case NotEqual:
        return "NotEqual";
    case Not:
        return "Not";
    case And:
        return "And";
    case VecAnd:
        return "VectorizedAnd";
    case Or:
        return "Or";
    case VecOr:
        return "VectorizedOr";
    case EqualAssign:
        return "EqualAssign";
    case LeftAssign:
        return "LeftAssign";
    case RightAssign:
        return "RightAssign";
    case LeftSuperAssign:
        return "LeftSuperAssign";
    case RightSuperAssign:
        return "RightSuperAssign";
    case ColonAssign:
        return "ColonAssign";
    case PipeForward:
        return "PipeForward";
    case PipeBind:
        return "PipeBind";
    case PublicNamespace:
        return "PublicNamespace";
    case PrivateNamespace:
        return "PrivateNamespace";
    case Range:
        return "Range";
    case Help:
        return "Help";
    case SlotExtract:
        return "SlotExtract";
    case Formula:
        return "Formula";
    case PartExtract:
        return "PartExtract";
    case Function:
        return "Function";
    case Function2:
        return "Function2";
    case While:
        return "While";
    case Repeat:
        return "Repeat";
    case For:
        return "For";
    case In:
        return "In";
    case If:
        return "If";
    case Else:
        return "Else";
    case Next:
        return "Next";
    case Break:
        return "Break";
    case LeftParen:
        return "LeftParen";
    case RightParen:
        return "RightParen";
    case LeftBrace:
        return "LeftBrace";
    case RightBrace:
        return "RightBrace";
    case LeftBracket:
        return "LeftBracket";
    case RightBracket:
        return "RightBracket";
    case DoubleLeftBracket:
        return "DoubleLeftBracket";
    case DoubleRightBracket:
        return "DoubleRightBracket";
    case Semicolon:
        return "Semicolon";
    case Newline:
        return "Newline";
    case Comma:
        return "Comma";
    case Null:
        return "Null";
    case Logical:
        return "Logical";
    case Integer:
        return "Integer";
    case Real:
        return "Real";
    case Complex:
        return "Complex";
    case String:
        return "String";
    case Symbol:
        return "Symbol";
    case Block:
        return "Block";
    case Group:
        return "Group";
    case NullaryOperation:
        return "NullaryOperation";
    case UnaryOperation:
        return "UnaryOperation";
    case BinaryOperation:
        return "BinaryOperation";
    case RepeatLoop:
        return "RepeatLoop";
    case WhileLoop:
        return "WhileLoop";
    case ForLoop:
        return "ForLoop";
    case IfConditional:
        return "IfConditional";
    case IfElseConditional:
        return "IfElseConditional";
    case FunctionDefinition:
        return "FunctionDefinition";
    case FunctionCall:
        return "FunctionCall";
    case Subset:
        return "Subset";
    case Index:
        return "Index";
    case Parameters:
        return "Parameters";
    case DefaultParameter:
        return "DefaultParameter";
    case NonDefaultParameter:
        return "NonDefaultParameter";
    case Arguments:
        return "Arguments";
    case NamedArgument:
        return "NamedArgument";
    case PositionalArgument:
        return "PositionalArgument";
    case Condition:
        return "Condition";
    case Iteration:
        return "Iteration";
    case Program:
        return "Program";
    case Delimited:
        return "Delimited";
    case Missing:
        return "Missing";
    case Error:
        return "Error";
    case Gap:
        return "Gap";
    case Beg:
        return "Beg";
    case End:
        return "End";
    case Location:
        return "Location";
    }
    fail_with("Unhandled node type %d", type);
}

/********************************************************************************
 Ast
********************************************************************************/

rastr_ast_t rastr_ast_create(std::size_t capacity) {
    rastr_ast_t ast = (rastr_ast_t) malloc_or_fail(sizeof(rastr_ast_impl_t));
    ast->pool =
        new Pool<rastr_node_impl_t, rastr_node_destroy_shallow>(capacity);
    ast->root = rastr_node_t{(std::size_t)(-1)};
    return ast;
}

int rastr_is_empty(rastr_ast_t ast) {
    return ast->pool->get_size() == 0;
}

int rastr_ast_size(rastr_ast_t ast) {
    return ast->pool->get_size();
}

void rastr_ast_destroy(rastr_ast_t ast) {
    ast->pool->clear();
    delete ast->pool;
    free(ast);
}

rastr_node_t rastr_ast_root(rastr_ast_t ast) {
    return ast->root;
}

void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root) {
    ast->root = root;
}

rastr_node_ptr_t rastr_ast_get_impl(rastr_ast_t ast, rastr_node_t node) {
    return ast->pool->at(node.index);
}

struct rastr_node_pair_t {
    rastr_node_ptr_t ptr;
    rastr_node_t node;
};

rastr_node_pair_t rastr_node_create(rastr_ast_t ast, rastr_node_type_t type) {
    AstPool::slot_t slot = ast->pool->allocate();

    rastr_node_pair_t pair;
    pair.ptr = slot.data;
    pair.node = rastr_node_t{slot.index};

    pair.ptr->type = type;
    pair.ptr->id = id_counter++;

    return pair;
}

void rastr_node_destroy_shallow(rastr_node_ptr_t ptr) {
    switch (ptr->type) {
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
        free(ptr->node.op_node.syn);
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
        break;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case Semicolon:
    case Newline:
    case Comma:
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case Null:
        break;

    case Logical:
        free(ptr->node.logical_node.syntax);
        break;

    case Integer:
        free(ptr->node.integer_node.syntax);
        break;

    case Real:
        free(ptr->node.real_node.syntax);
        break;

    case Complex:
        free(ptr->node.complex_node.syntax);
        break;

    case String:
        free(ptr->node.string_node.syntax);
        free(ptr->node.string_node.value);
        break;

    case Symbol: {
        char* syn = ptr->node.symbol_node.syntax;
        char* val = ptr->node.symbol_node.value;

        free(syn);
        if (syn != val) {
            free(val);
        }
    }

    break;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case Block:
        free(ptr->node.blk_node.seq);
        break;

    case Group:
    case NullaryOperation:
    case UnaryOperation:
    case BinaryOperation:
    case RepeatLoop:
    case WhileLoop:
    case ForLoop:
    case IfConditional:
    case IfElseConditional:
    case FunctionDefinition:
    case FunctionCall:
    case Subset:
    case Index:
        break;

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    case Parameters:
        free(ptr->node.params_node.seq);
        break;

    case DefaultParameter:
    case NonDefaultParameter:
        break;

    case Arguments:
        free(ptr->node.args_node.seq);
        break;

    case NamedArgument:
    case PositionalArgument:
    case Condition:
    case Iteration:
        break;

    case Program:
        free(ptr->node.pgm_node.seq);
        break;

    case Delimited:
    case Missing:
    case Beg:
    case End:
        break;

    case Gap:
        free(ptr->node.gap_node.val);
        break;

    case Error:
        free(ptr->node.err_node.msg);
        break;
    }
}

#define DESTROY_0(NODE) rastr_node_destroy(ast, rastr_##NODE##_gap(ast, node));

#define DESTROY_1(NODE, CHILD1) \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1(ast, node));

#define DESTROY_2(NODE, CHILD1, CHILD2)                          \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2(ast, node));

#define DESTROY_3(NODE, CHILD1, CHILD2, CHILD3)                  \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3(ast, node));

#define DESTROY_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4)          \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD4(ast, node));

#define DESTROY_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5)  \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD4(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD5(ast, node));

#define HANDLE_SEQ(NODE, LEN, SEQ)                                 \
    {                                                              \
        int len = rastr_##NODE##_##LEN(ast, node);                 \
        const rastr_node_t* seq = rastr_##NODE##_##SEQ(ast, node); \
        for (int i = 0; i < len; ++i) {                            \
            rastr_node_destroy(ast, seq[i]);                       \
        }                                                          \
    }

#define DESTROY_BRACK_SEQ(NODE, LBRACK, LEN, SEQ, RBRACK)        \
    rastr_node_destroy(ast, rastr_##NODE##_##LBRACK(ast, node)); \
    HANDLE_SEQ(NODE, LEN, SEQ);                                  \
    rastr_node_destroy(ast, rastr_##NODE##_##RBRACK(ast, node));

#define DESTROY_SEQ(NODE, LEN, SEQ) HANDLE_SEQ(NODE, LEN, SEQ);

void rastr_node_destroy(rastr_ast_t ast, rastr_node_t node) {
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
        DESTROY_0(op);
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
        DESTROY_0(dlmtr);
        break;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case Semicolon:
    case Newline:
    case Comma:
        DESTROY_0(term);
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case Null:
        DESTROY_0(null);
        break;

    case Logical:
        DESTROY_0(logical);
        break;

    case Integer:
        DESTROY_0(integer);
        break;

    case Real:
        DESTROY_0(real);
        break;

    case Complex:
        DESTROY_0(complex);
        break;

    case String:
        DESTROY_0(string);
        break;

    case Symbol:
        DESTROY_0(symbol);
        break;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case Block:
        DESTROY_BRACK_SEQ(blk, lbrack, len, seq, rbrack)
        break;

    case Group:
        DESTROY_3(grp, lbrack, expr, rbrack);
        break;

    case NullaryOperation:
        DESTROY_1(nuop, op);
        break;

    case UnaryOperation:
        DESTROY_2(unop, op, expr);
        break;

    case BinaryOperation:
        DESTROY_3(binop, lexpr, op, rexpr);
        break;

    case RepeatLoop:
        DESTROY_2(rlp, kw, body);
        break;

    case WhileLoop:
        DESTROY_3(wlp, kw, cond, body);
        break;

    case ForLoop:
        DESTROY_3(flp, kw, iter, body);
        break;

    case IfConditional:
        DESTROY_3(icnd, ikw, cond, ibody);
        break;

    case IfElseConditional:
        DESTROY_5(iecnd, ikw, cond, ibody, ekw, ebody);
        break;

    case FunctionDefinition:
        DESTROY_3(fndefn, hd, params, body);
        break;

    case FunctionCall:
        DESTROY_2(fncall, fun, args);
        break;

    case Subset:
        DESTROY_2(sub, obj, inds);
        break;

    case Index:
        DESTROY_2(idx, obj, inds);
        break;

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    case Parameters:
        DESTROY_BRACK_SEQ(params, lbrack, len, seq, rbrack)
        break;

    case DefaultParameter:
        DESTROY_3(dparam, name, op, expr)
        break;

    case NonDefaultParameter:
        DESTROY_1(ndparam, name)
        break;

    case Arguments:
        DESTROY_BRACK_SEQ(args, lbrack, len, seq, rbrack)
        break;

    case NamedArgument:
        DESTROY_3(narg, name, op, expr)
        break;

    case PositionalArgument:
        DESTROY_1(parg, expr)
        break;

    case Condition:
        DESTROY_3(cnd, lbrack, expr, rbrack)
        break;

    case Iteration:
        DESTROY_5(iter, lbrack, var, kw, expr, rbrack)
        break;

    case Program:
        DESTROY_SEQ(pgm, len, seq)
        break;

    case Delimited:
        DESTROY_2(dlmtd, expr, dlmtr)
        break;

    case Missing:
        DESTROY_0(msng)
        break;

    case End:
        DESTROY_0(end)
        break;

    case Gap:
        break;

    case Error:
        break;
    }

    ast->pool->deallocate(node.index);
}

const char* rastr_ast_to_string(rastr_ast_t ast) {
    const char* root_str = StringView::duplicate(
        rastr_node_to_string(ast, rastr_ast_root(ast), INDENTATION));

    const char* result = bufprintf("ast {\n"
                                   "%s\n"
                                   "}\n",
                                   root_str);

    free((void*) root_str);
    return result;
}

/********************************************************************************
 Node
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->type;
}

int rastr_node_id(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->id;
}

/********************************************************************************
 Operator
********************************************************************************/

rastr_node_t rastr_op_node(rastr_ast_t ast,
                           rastr_node_type_t type,
                           rastr_node_t gap,
                           rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    pair.ptr->node.op_node.syn = nullptr;
    pair.ptr->node.op_node.gap = gap;
    pair.ptr->node.op_node.loc = loc;
    pair.ptr->node.op_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_special_op_node(rastr_ast_t ast,
                                   const StringView& syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Special);
    pair.ptr->node.op_node.syn = syn.materialize();
    pair.ptr->node.op_node.gap = gap;
    pair.ptr->node.op_node.loc = loc;
    return pair.node;
}

const char* rastr_op_val(rastr_ast_t ast, rastr_node_t node) {
    return rastr_op_syn(ast, node);
}

SEXP r_rastr_op_val(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_op_val(ast, node);
    return str_vec1(result);
}

const char* rastr_op_syn(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_type_t type = ptr->type;

    switch (type) {
    case Special:
        return ptr->node.op_node.syn;
    case Plus:
        return "+";
    case Minus:
        return "-";
    case Multiplication:
        return "*";
    case Division:
        return "/";
    case Power:
        return "^";
    case Power2:
        return "**";
    case LessThan:
        return "<";
    case LessThanEqual:
        return "<=";
    case GreaterThan:
        return ">";
    case GreaterThanEqual:
        return ">=";
    case Equal:
        return "==";
    case NotEqual:
        return "!=";
    case Not:
        return "!";
    case And:
        return "&&";
    case VecAnd:
        return "&";
    case Or:
        return "||";
    case VecOr:
        return "|";
    case EqualAssign:
        return "=";
    case LeftAssign:
        return "<-";
    case RightAssign:
        return "->";
    case LeftSuperAssign:
        return "<<-";
    case RightSuperAssign:
        return "->>";
    case ColonAssign:
        return ":=";
    case PipeForward:
        return "|>";
    case PipeBind:
        return "=>";
    case PublicNamespace:
        return "::";
    case PrivateNamespace:
        return ":::";
    case Range:
        return ":";
    case Help:
        return "?";
    case SlotExtract:
        return "@";
    case Formula:
        return "~";
    case PartExtract:
        return "$";
    case Function2:
        return "\\";
    case Function:
        return "function";
    case While:
        return "while";
    case Repeat:
        return "repeat";
    case For:
        return "for";
    case In:
        return "in";
    case If:
        return "if";
    case Else:
        return "else";
    case Next:
        return "next";
    case Break:
        return "break";
    default:
        rastr_log_error("node '%s' is not an operator",
                        rastr_node_type_to_string(type));
        return "error!";
    }
}

SEXP r_rastr_op_syn(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_op_syn(ast, node);
    return str_vec1(result);
}

rastr_node_t rastr_op_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.op_node.gap;
}

rastr_node_t rastr_op_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.op_node.loc;
}

SEXP r_rastr_op_gap(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t gap = rastr_op_gap(ast, node);
    return rastr_node_wrap(gap);
}

/********************************************************************************
 Delimiters
********************************************************************************/
bool rastr_node_is_delimiter(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_delimiter(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_delimiter(rastr_ast_t ast,
                                  rastr_node_type_t type,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    pair.ptr->node.dlmtr_node.gap = gap;
    pair.ptr->node.dlmtr_node.loc = loc;
    return pair.node;
}

/* TODO: remove */
void rastr_dlmtr_set_type(rastr_ast_t ast,
                          rastr_node_t node,
                          rastr_node_type_t type) {
    rastr_ast_get_impl(ast, node)->type = type;
}

const char* rastr_node_delimiter_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_delimiter_syntax(ast, node);
}

rastr_node_t rastr_dlmtr_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dlmtr_node.gap;
}

rastr_node_t rastr_dlmtr_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dlmtr_node.loc;
}

const char* rastr_node_delimiter_syntax(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
    case LeftParen:
        return "(";
    case RightParen:
        return ")";
    case LeftBrace:
        return "{";
    case RightBrace:
        return "}";
    case LeftBracket:
        return "[";
    case RightBracket:
        return "]";
    case DoubleLeftBracket:
        return "[[";
    case DoubleRightBracket:
        return "]]";
    default:
        NODE_TYPE_ERROR("delimiter", type);
    }
}

/********************************************************************************
 Terminators
********************************************************************************/
bool rastr_node_is_terminator(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_terminator(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_terminator(rastr_ast_t ast,
                                   rastr_node_type_t type,
                                   rastr_node_t gap,
                                   rastr_node_t loc) {
    /* TODO: return error if not delimiter */
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    pair.ptr->node.terminator_node.gap = gap;
    pair.ptr->node.terminator_node.loc = loc;
    return pair.node;
}

const char* rastr_node_terminator_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_terminator_syntax(ast, node);
}

const char* rastr_node_terminator_syntax(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
    case Semicolon:
        return ";";
    case Newline:
        return "\n";
    case Comma:
        return ",";
    default:
        NODE_TYPE_ERROR("terminator", type);
    }
}

rastr_node_t rastr_term_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.terminator_node.gap;
}

rastr_node_t rastr_term_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.terminator_node.loc;
}

/*******************************************************************************
 Meta
*******************************************************************************/

// End
rastr_node_t
rastr_node_end(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, End);
    pair.ptr->node.end_node.gap = gap;
    pair.ptr->node.end_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_end_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.end_node.gap;
}

rastr_node_t rastr_end_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.end_node.loc;
}

// Error
rastr_node_t rastr_node_error(rastr_ast_t ast, const char* fmt, ...) {
    rastr_node_pair_t pair = rastr_node_create(ast, Error);

    std::va_list args;
    va_start(args, fmt);
    pair.ptr->node.error_node.message =
        StringView::duplicate(vbufprintf(fmt, args));
    va_end(args);

    return pair.node;
}

const char* rastr_node_error_message(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.error_node.message;
}

/********************************************************************************
 Literals
********************************************************************************/
bool rastr_node_is_literal(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_literal(rastr_node_type(ast, node));
}

// null
rastr_node_t
rastr_node_null(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Null);
    pair.ptr->node.null_node.gap = gap;
    pair.ptr->node.null_node.loc = loc;
    return pair.node;
}

const char* rastr_node_null_syntax(rastr_ast_t ast, rastr_node_t node) {
    return "NULL";
}

rastr_node_t rastr_null_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.null_node.gap;
}

rastr_node_t rastr_null_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.null_node.loc;
}

// logical
rastr_node_t rastr_node_logical(rastr_ast_t ast,
                                const char* syntax,
                                int value,
                                rastr_node_t gap,
                                rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Logical);
    pair.ptr->node.logical_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.logical_node.value = value;
    pair.ptr->node.logical_node.gap = gap;
    pair.ptr->node.logical_node.loc = loc;
    return pair.node;
}

int rastr_node_logical_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.value;
}

const char* rastr_node_logical_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.syntax;
}

rastr_node_t rastr_logical_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.gap;
}

rastr_node_t rastr_logical_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.loc;
}

// integer
rastr_node_t rastr_node_integer_from_view(rastr_ast_t ast,
                                          const StringView& syntax_view,
                                          rastr_node_t gap,
                                          rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Integer);
    char* syntax = syntax_view.materialize();
    pair.ptr->node.integer_node.syntax = syntax;
    pair.ptr->node.integer_node.value = (int) R_atof(syntax);
    pair.ptr->node.integer_node.gap = gap;
    pair.ptr->node.integer_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_node_integer(rastr_ast_t ast,
                                const char* syntax,
                                int value,
                                rastr_node_t gap,
                                rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Integer);
    pair.ptr->node.integer_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.integer_node.value = value;
    pair.ptr->node.integer_node.gap = gap;
    pair.ptr->node.integer_node.loc = loc;
    return pair.node;
}

int rastr_node_integer_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.value;
}

const char* rastr_node_integer_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.syntax;
}

rastr_node_t rastr_integer_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.gap;
}

rastr_node_t rastr_integer_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.loc;
}

// real
rastr_node_t rastr_node_double_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         rastr_node_t gap,
                                         rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Real);
    char* syntax = syntax_view.materialize();
    pair.ptr->node.real_node.syntax = syntax;
    pair.ptr->node.real_node.value = R_atof(syntax);
    pair.ptr->node.real_node.gap = gap;
    pair.ptr->node.real_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_node_real(rastr_ast_t ast,
                             const char* syntax,
                             double value,
                             rastr_node_t gap,
                             rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Real);
    pair.ptr->node.real_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.real_node.value = value;
    pair.ptr->node.real_node.gap = gap;
    pair.ptr->node.real_node.loc = loc;
    return pair.node;
}

double rastr_node_real_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.value;
}

const char* rastr_node_real_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.syntax;
}

rastr_node_t rastr_real_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.gap;
}

rastr_node_t rastr_real_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.loc;
}

// complex
rastr_node_t rastr_node_complex_from_view(rastr_ast_t ast,
                                          const StringView& syntax_view,
                                          rastr_node_t gap,
                                          rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Complex);
    char* syntax = syntax_view.materialize();
    pair.ptr->node.complex_node.syntax = syntax;
    pair.ptr->node.complex_node.value.r = 0;
    pair.ptr->node.complex_node.value.i = R_atof(syntax);
    pair.ptr->node.complex_node.gap = gap;
    pair.ptr->node.complex_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_node_complex(rastr_ast_t ast,
                                const char* syntax,
                                const Rcomplex& value,
                                rastr_node_t gap,
                                rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Complex);
    pair.ptr->node.complex_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.complex_node.value = value;
    pair.ptr->node.complex_node.gap = gap;
    pair.ptr->node.complex_node.loc = loc;
    return pair.node;
}

Rcomplex rastr_node_complex_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.value;
}

const char* rastr_node_complex_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.syntax;
}

rastr_node_t rastr_complex_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.gap;
}

rastr_node_t rastr_complex_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.loc;
}

// string
rastr_node_t rastr_node_string_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         const StringView& value_view,
                                         rastr_node_t gap,
                                         rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, String);
    pair.ptr->node.string_node.syntax = syntax_view.materialize();
    pair.ptr->node.string_node.value = value_view.materialize();
    pair.ptr->node.string_node.gap = gap;
    pair.ptr->node.string_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_node_string(rastr_ast_t ast,
                               const char* syntax,
                               const char* value,
                               rastr_node_t gap,
                               rastr_node_t loc) {
    return rastr_node_string_from_view(
        ast, StringView(syntax), StringView(value), gap, loc);
}

const char* rastr_node_string_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.syntax;
}

const char* rastr_node_string_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.value;
}

bool rastr_node_string_is_raw(rastr_ast_t ast, rastr_node_t node) {
    const char* syntax = rastr_node_string_syntax(ast, node);
    const char first = syntax[0];
    return first == 'r' || first == 'R';
}

rastr_node_t rastr_string_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.gap;
}

rastr_node_t rastr_string_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.loc;
}

// symbol
rastr_node_t rastr_node_symbol_unsafe(rastr_ast_t ast,
                                      char* syntax,
                                      char* value,
                                      rastr_node_t gap,
                                      rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Symbol);
    pair.ptr->node.symbol_node.syntax = syntax;
    pair.ptr->node.symbol_node.value = value;
    pair.ptr->node.symbol_node.gap = gap;
    pair.ptr->node.symbol_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_node_symbol(rastr_ast_t ast,
                               const char* syntax,
                               const char* value,
                               rastr_node_t gap,
                               rastr_node_t loc) {
    return rastr_node_symbol_unsafe(ast,
                                    StringView(syntax).materialize(),
                                    StringView(value).materialize(),
                                    gap,
                                    loc);
}

const char* rastr_node_symbol_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.value;
}

const char* rastr_node_symbol_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.syntax;
}

bool rastr_node_symbol_is_quoted(rastr_ast_t ast, rastr_node_t node) {
    const char* syntax = rastr_node_symbol_syntax(ast, node);
    return syntax[0] == '`';
}

rastr_node_t rastr_symbol_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.gap;
}

rastr_node_t rastr_symbol_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.loc;
}

rastr_node_t rastr_blk_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            int len,
                            const rastr_node_t* seq,
                            rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Block);
    pair.ptr->node.blk_node.lbrack = lbrack;
    pair.ptr->node.blk_node.len = len;
    pair.ptr->node.blk_node.seq =
        (rastr_node_t*) memclone_or_fail(seq, len * sizeof(rastr_node_t));
    pair.ptr->node.blk_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_blk_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.blk_node.lbrack;
}
SEXP r_rastr_blk_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_blk_lbrack(ast, node);
    return rastr_node_wrap(result);
}
int rastr_blk_len(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.blk_node.len;
}
SEXP r_rastr_blk_len(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_blk_len(ast, node);
    return rastr_int_wrap(result);
}
const rastr_node_t* rastr_blk_seq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.blk_node.seq;
}
SEXP r_rastr_blk_seq(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const rastr_node_t* result = rastr_blk_seq(ast, node);
    return rastr_node_seq_wrap(result, rastr_blk_len(ast, node));
}
rastr_node_t rastr_blk_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.blk_node.rbrack;
}
SEXP r_rastr_blk_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_blk_rbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_grp_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            rastr_node_t expr,
                            rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Group);
    pair.ptr->node.grp_node.lbrack = lbrack;
    pair.ptr->node.grp_node.expr = expr;
    pair.ptr->node.grp_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_grp_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.grp_node.lbrack;
}
SEXP r_rastr_grp_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_lbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_grp_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.grp_node.expr;
}
SEXP r_rastr_grp_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_grp_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.grp_node.rbrack;
}
SEXP r_rastr_grp_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_rbrack(ast, node);
    return rastr_node_wrap(result);
}

rastr_node_t rastr_nuop_node(rastr_ast_t ast, rastr_node_t op) {
    rastr_node_pair_t pair = rastr_node_create(ast, NullaryOperation);
    pair.ptr->node.nuop_node.op = op;
    return pair.node;
}
rastr_node_t rastr_nuop_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.nuop_node.op;
}
SEXP r_rastr_nuop_op(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_nuop_op(ast, node);
    return rastr_node_wrap(result);
}

rastr_node_t
rastr_unop_node(rastr_ast_t ast, rastr_node_t op, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, UnaryOperation);
    pair.ptr->node.unop_node.op = op;
    pair.ptr->node.unop_node.expr = expr;
    return pair.node;
}
rastr_node_t rastr_unop_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.unop_node.op;
}
SEXP r_rastr_unop_op(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_unop_op(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_unop_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.unop_node.expr;
}

SEXP r_rastr_unop_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_unop_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_binop_node(rastr_ast_t ast,
                              rastr_node_t lexpr,
                              rastr_node_t op,
                              rastr_node_t rexpr) {
    rastr_node_pair_t pair = rastr_node_create(ast, BinaryOperation);
    pair.ptr->node.binop_node.lexpr = lexpr;
    pair.ptr->node.binop_node.op = op;
    pair.ptr->node.binop_node.rexpr = rexpr;
    return pair.node;
}
rastr_node_t rastr_binop_lexpr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binop_node.lexpr;
}
SEXP r_rastr_binop_lexpr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_lexpr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_binop_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binop_node.op;
}
SEXP r_rastr_binop_op(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_op(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_binop_rexpr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binop_node.rexpr;
}
SEXP r_rastr_binop_rexpr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_rexpr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t
rastr_rlp_node(rastr_ast_t ast, rastr_node_t kw, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RepeatLoop);
    pair.ptr->node.rlp_node.kw = kw;
    pair.ptr->node.rlp_node.body = body;
    return pair.node;
}
rastr_node_t rastr_rlp_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.rlp_node.kw;
}
SEXP r_rastr_rlp_kw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_rlp_kw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_rlp_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.rlp_node.body;
}
SEXP r_rastr_rlp_body(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_rlp_body(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_wlp_node(rastr_ast_t ast,
                            rastr_node_t kw,
                            rastr_node_t cond,
                            rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, WhileLoop);
    pair.ptr->node.wlp_node.kw = kw;
    pair.ptr->node.wlp_node.cond = cond;
    pair.ptr->node.wlp_node.body = body;
    return pair.node;
}
rastr_node_t rastr_wlp_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wlp_node.kw;
}
SEXP r_rastr_wlp_kw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_kw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_wlp_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wlp_node.cond;
}
SEXP r_rastr_wlp_cond(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_cond(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_wlp_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wlp_node.body;
}
SEXP r_rastr_wlp_body(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_body(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_flp_node(rastr_ast_t ast,
                            rastr_node_t kw,
                            rastr_node_t iter,
                            rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, ForLoop);
    pair.ptr->node.flp_node.kw = kw;
    pair.ptr->node.flp_node.iter = iter;
    pair.ptr->node.flp_node.body = body;
    return pair.node;
}
rastr_node_t rastr_flp_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.flp_node.kw;
}
SEXP r_rastr_flp_kw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_kw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_flp_iter(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.flp_node.iter;
}
SEXP r_rastr_flp_iter(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_iter(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_flp_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.flp_node.body;
}
SEXP r_rastr_flp_body(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_body(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_icnd_node(rastr_ast_t ast,
                             rastr_node_t ikw,
                             rastr_node_t cond,
                             rastr_node_t ibody) {
    rastr_node_pair_t pair = rastr_node_create(ast, IfConditional);
    pair.ptr->node.icnd_node.ikw = ikw;
    pair.ptr->node.icnd_node.cond = cond;
    pair.ptr->node.icnd_node.ibody = ibody;
    return pair.node;
}
rastr_node_t rastr_icnd_ikw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.icnd_node.ikw;
}
SEXP r_rastr_icnd_ikw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icnd_ikw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_icnd_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.icnd_node.cond;
}
SEXP r_rastr_icnd_cond(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icnd_cond(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_icnd_ibody(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.icnd_node.ibody;
}
SEXP r_rastr_icnd_ibody(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icnd_ibody(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iecnd_node(rastr_ast_t ast,
                              rastr_node_t ikw,
                              rastr_node_t cond,
                              rastr_node_t ibody,
                              rastr_node_t ekw,
                              rastr_node_t ebody) {
    rastr_node_pair_t pair = rastr_node_create(ast, IfElseConditional);
    pair.ptr->node.iecnd_node.ikw = ikw;
    pair.ptr->node.iecnd_node.cond = cond;
    pair.ptr->node.iecnd_node.ibody = ibody;
    pair.ptr->node.iecnd_node.ekw = ekw;
    pair.ptr->node.iecnd_node.ebody = ebody;
    return pair.node;
}
rastr_node_t rastr_iecnd_ikw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iecnd_node.ikw;
}
SEXP r_rastr_iecnd_ikw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecnd_ikw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iecnd_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iecnd_node.cond;
}
SEXP r_rastr_iecnd_cond(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecnd_cond(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iecnd_ibody(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iecnd_node.ibody;
}
SEXP r_rastr_iecnd_ibody(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecnd_ibody(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iecnd_ekw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iecnd_node.ekw;
}
SEXP r_rastr_iecnd_ekw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecnd_ekw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iecnd_ebody(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iecnd_node.ebody;
}
SEXP r_rastr_iecnd_ebody(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecnd_ebody(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_fndefn_node(rastr_ast_t ast,
                               rastr_node_t hd,
                               rastr_node_t params,
                               rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, FunctionDefinition);
    pair.ptr->node.fndefn_node.hd = hd;
    pair.ptr->node.fndefn_node.params = params;
    pair.ptr->node.fndefn_node.body = body;
    return pair.node;
}
rastr_node_t rastr_fndefn_hd(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.fndefn_node.hd;
}
SEXP r_rastr_fndefn_hd(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_hd(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_fndefn_params(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.fndefn_node.params;
}
SEXP r_rastr_fndefn_params(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_params(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_fndefn_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.fndefn_node.body;
}
SEXP r_rastr_fndefn_body(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_body(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t
rastr_fncall_node(rastr_ast_t ast, rastr_node_t fun, rastr_node_t args) {
    rastr_node_pair_t pair = rastr_node_create(ast, FunctionCall);
    pair.ptr->node.fncall_node.fun = fun;
    pair.ptr->node.fncall_node.args = args;
    return pair.node;
}
rastr_node_t rastr_fncall_fun(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.fncall_node.fun;
}
SEXP r_rastr_fncall_fun(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_fun(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_fncall_args(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.fncall_node.args;
}
SEXP r_rastr_fncall_args(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_args(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t
rastr_sub_node(rastr_ast_t ast, rastr_node_t obj, rastr_node_t inds) {
    rastr_node_pair_t pair = rastr_node_create(ast, Subset);
    pair.ptr->node.sub_node.obj = obj;
    pair.ptr->node.sub_node.inds = inds;
    return pair.node;
}
rastr_node_t rastr_sub_obj(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.sub_node.obj;
}
SEXP r_rastr_sub_obj(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_obj(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_sub_inds(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.sub_node.inds;
}
SEXP r_rastr_sub_inds(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_inds(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t
rastr_idx_node(rastr_ast_t ast, rastr_node_t obj, rastr_node_t inds) {
    rastr_node_pair_t pair = rastr_node_create(ast, Index);
    pair.ptr->node.idx_node.obj = obj;
    pair.ptr->node.idx_node.inds = inds;
    return pair.node;
}
rastr_node_t rastr_idx_obj(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.idx_node.obj;
}
SEXP r_rastr_idx_obj(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_obj(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_idx_inds(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.idx_node.inds;
}
SEXP r_rastr_idx_inds(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_inds(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_params_node(rastr_ast_t ast,
                               rastr_node_t lbrack,
                               int len,
                               const rastr_node_t* seq,
                               rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Parameters);
    pair.ptr->node.params_node.lbrack = lbrack;
    pair.ptr->node.params_node.len = len;
    pair.ptr->node.params_node.seq =
        (rastr_node_t*) memclone_or_fail(seq, len * sizeof(rastr_node_t));
    ;
    pair.ptr->node.params_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_params_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.params_node.lbrack;
}
SEXP r_rastr_params_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_params_lbrack(ast, node);
    return rastr_node_wrap(result);
}
int rastr_params_len(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.params_node.len;
}
SEXP r_rastr_params_len(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_params_len(ast, node);
    return rastr_int_wrap(result);
}
const rastr_node_t* rastr_params_seq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.params_node.seq;
}
SEXP r_rastr_params_seq(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const rastr_node_t* result = rastr_params_seq(ast, node);
    return rastr_node_seq_wrap(result, rastr_params_len(ast, node));
}
rastr_node_t rastr_params_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.params_node.rbrack;
}
SEXP r_rastr_params_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_params_rbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_dparam_node(rastr_ast_t ast,
                               rastr_node_t name,
                               rastr_node_t op,
                               rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, DefaultParameter);
    pair.ptr->node.dparam_node.name = name;
    pair.ptr->node.dparam_node.op = op;
    pair.ptr->node.dparam_node.expr = expr;
    return pair.node;
}
rastr_node_t rastr_dparam_name(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dparam_node.name;
}
SEXP r_rastr_dparam_name(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dparam_name(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_dparam_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dparam_node.op;
}
SEXP r_rastr_dparam_op(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dparam_op(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_dparam_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dparam_node.expr;
}
SEXP r_rastr_dparam_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dparam_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_ndparam_node(rastr_ast_t ast, rastr_node_t name) {
    rastr_node_pair_t pair = rastr_node_create(ast, NonDefaultParameter);
    pair.ptr->node.ndparam_node.name = name;
    return pair.node;
}
rastr_node_t rastr_ndparam_name(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ndparam_node.name;
}
SEXP r_rastr_ndparam_name(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_ndparam_name(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_args_node(rastr_ast_t ast,
                             rastr_node_t lbrack,
                             int len,
                             const rastr_node_t* seq,
                             rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Arguments);
    pair.ptr->node.args_node.lbrack = lbrack;
    pair.ptr->node.args_node.len = len;
    pair.ptr->node.args_node.seq =
        (rastr_node_t*) memclone_or_fail(seq, len * sizeof(rastr_node_t));
    pair.ptr->node.args_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_args_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.args_node.lbrack;
}
SEXP r_rastr_args_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_args_lbrack(ast, node);
    return rastr_node_wrap(result);
}
int rastr_args_len(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.args_node.len;
}
SEXP r_rastr_args_len(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_args_len(ast, node);
    return rastr_int_wrap(result);
}
const rastr_node_t* rastr_args_seq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.args_node.seq;
}
SEXP r_rastr_args_seq(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const rastr_node_t* result = rastr_args_seq(ast, node);
    return rastr_node_seq_wrap(result, rastr_args_len(ast, node));
}
rastr_node_t rastr_args_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.args_node.rbrack;
}
SEXP r_rastr_args_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_args_rbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_narg_node(rastr_ast_t ast,
                             rastr_node_t name,
                             rastr_node_t op,
                             rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, NamedArgument);
    pair.ptr->node.narg_node.name = name;
    pair.ptr->node.narg_node.op = op;
    pair.ptr->node.narg_node.expr = expr;
    return pair.node;
}
rastr_node_t rastr_narg_name(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.narg_node.name;
}
SEXP r_rastr_narg_name(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_name(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_narg_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.narg_node.op;
}
SEXP r_rastr_narg_op(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_op(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_narg_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.narg_node.expr;
}
SEXP r_rastr_narg_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_parg_node(rastr_ast_t ast, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, PositionalArgument);
    pair.ptr->node.parg_node.expr = expr;
    return pair.node;
}
rastr_node_t rastr_parg_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.parg_node.expr;
}
SEXP r_rastr_parg_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_parg_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_cnd_node(rastr_ast_t ast,
                            rastr_node_t lbrack,
                            rastr_node_t expr,
                            rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Condition);
    pair.ptr->node.cnd_node.lbrack = lbrack;
    pair.ptr->node.cnd_node.expr = expr;
    pair.ptr->node.cnd_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_cnd_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.cnd_node.lbrack;
}
SEXP r_rastr_cnd_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cnd_lbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_cnd_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.cnd_node.expr;
}
SEXP r_rastr_cnd_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cnd_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_cnd_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.cnd_node.rbrack;
}
SEXP r_rastr_cnd_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cnd_rbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iter_node(rastr_ast_t ast,
                             rastr_node_t lbrack,
                             rastr_node_t var,
                             rastr_node_t kw,
                             rastr_node_t expr,
                             rastr_node_t rbrack) {
    rastr_node_pair_t pair = rastr_node_create(ast, Iteration);
    pair.ptr->node.iter_node.lbrack = lbrack;
    pair.ptr->node.iter_node.var = var;
    pair.ptr->node.iter_node.kw = kw;
    pair.ptr->node.iter_node.expr = expr;
    pair.ptr->node.iter_node.rbrack = rbrack;
    return pair.node;
}
rastr_node_t rastr_iter_lbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iter_node.lbrack;
}
SEXP r_rastr_iter_lbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_lbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iter_var(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iter_node.var;
}
SEXP r_rastr_iter_var(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_var(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iter_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iter_node.kw;
}
SEXP r_rastr_iter_kw(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_kw(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iter_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iter_node.expr;
}
SEXP r_rastr_iter_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_iter_rbrack(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.iter_node.rbrack;
}
SEXP r_rastr_iter_rbrack(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_rbrack(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_pgm_node(rastr_ast_t ast,
                            rastr_node_t beg,
                            int len,
                            const rastr_node_t* seq,
                            rastr_node_t end) {
    rastr_node_pair_t pair = rastr_node_create(ast, Program);
    pair.ptr->node.pgm_node.beg = beg;
    pair.ptr->node.pgm_node.len = len;
    pair.ptr->node.pgm_node.seq =
        (rastr_node_t*) memclone_or_fail(seq, len * sizeof(rastr_node_t));
    pair.ptr->node.pgm_node.end = end;
    return pair.node;
}
rastr_node_t rastr_pgm_beg(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.pgm_node.beg;
}
int rastr_pgm_len(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.pgm_node.len;
}
SEXP r_rastr_pgm_len(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_pgm_len(ast, node);
    return rastr_int_wrap(result);
}
const rastr_node_t* rastr_pgm_seq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.pgm_node.seq;
}
rastr_node_t rastr_pgm_end(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.pgm_node.end;
}
SEXP r_rastr_pgm_seq(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const rastr_node_t* result = rastr_pgm_seq(ast, node);
    return rastr_node_seq_wrap(result, rastr_pgm_len(ast, node));
}

rastr_node_t
rastr_dlmtd_node(rastr_ast_t ast, rastr_node_t expr, rastr_node_t dlmtr) {
    rastr_node_pair_t pair = rastr_node_create(ast, Delimited);
    pair.ptr->node.dlmtd_node.expr = expr;
    pair.ptr->node.dlmtd_node.dlmtr = dlmtr;
    return pair.node;
}
rastr_node_t rastr_dlmtd_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dlmtd_node.expr;
}
SEXP r_rastr_dlmtd_expr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtd_expr(ast, node);
    return rastr_node_wrap(result);
}
rastr_node_t rastr_dlmtd_dlmtr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.dlmtd_node.dlmtr;
}
SEXP r_rastr_dlmtd_dlmtr(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtd_dlmtr(ast, node);
    return rastr_node_wrap(result);
}

rastr_node_t rastr_err_node(rastr_ast_t ast, const char* msg) {
    rastr_node_pair_t pair = rastr_node_create(ast, Error);
    pair.ptr->node.err_node.msg = StringView::duplicate(msg);
    return pair.node;
}

const char* rastr_err_msg(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.err_node.msg;
}
SEXP r_rastr_err_msg(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_err_msg(ast, node);
    return rastr_str_wrap(result);
}

rastr_node_t
rastr_msng_node(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Missing);
    pair.ptr->node.msng_node.gap = gap;
    pair.ptr->node.msng_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_msng_gap(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.msng_node.gap;
}

rastr_node_t rastr_msng_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.msng_node.loc;
}

rastr_node_t rastr_beg_node(rastr_ast_t ast, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Beg);
    pair.ptr->node.beg_node.loc = loc;
    return pair.node;
}

rastr_node_t rastr_beg_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.beg_node.loc;
}

rastr_node_t
rastr_gap_node_owner(rastr_ast_t ast, char* val, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, Gap);
    pair.ptr->node.gap_node.val = val;
    pair.ptr->node.gap_node.loc = loc;
    return pair.node;
}

const char* rastr_gap_val(rastr_ast_t ast, rastr_node_t node) {
    const char* res = rastr_ast_get_impl(ast, node)->node.gap_node.val;
    return res == nullptr ? "" : res;
}

rastr_node_t rastr_gap_loc(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.gap_node.loc;
}

rastr_node_t rastr_loc_node(rastr_ast_t ast,
                            int lrow,
                            int lcol,
                            int lchr,
                            int lbyte,
                            int rrow,
                            int rcol,
                            int rchr,
                            int rbyte) {
    rastr_node_pair_t pair = rastr_node_create(ast, Location);
    pair.ptr->node.loc_node.lrow = lrow;
    pair.ptr->node.loc_node.lcol = lcol;
    pair.ptr->node.loc_node.lchr = lchr;
    pair.ptr->node.loc_node.lbyte = lbyte;
    pair.ptr->node.loc_node.rrow = rrow;
    pair.ptr->node.loc_node.rcol = rcol;
    pair.ptr->node.loc_node.rchr = rchr;
    pair.ptr->node.loc_node.rbyte = rbyte;
    return pair.node;
}

int rastr_pos_lrow(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.lrow;
}

int rastr_pos_lcol(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.lcol;
}

int rastr_pos_lchr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.lchr;
}

int rastr_pos_lbyte(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.lbyte;
}

int rastr_pos_rrow(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.rrow;
}

int rastr_pos_rcol(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.rcol;
}

int rastr_pos_rchr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.rchr;
}

int rastr_pos_rbyte(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.loc_node.rbyte;
}
