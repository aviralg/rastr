#include <rastr/api.h>
#include "internal_api.h"
#include "utilities.h"
#include "logger.h"
#include "Pool.h"
#include "interop.h"
#include "r_api.h"
#include <vector>
#include <iostream>

int id_counter = 0;

#define NODE_TYPE_ERROR(expected, actual)                 \
    fail_with("incorrect node type; expected %s, got %s", \
              expected,                                   \
              rastr_node_type_to_string(actual));

struct rastr_node_impl_t {
    rastr_node_type_t type;
    int id;
    int pid;

    union {
        struct {
            char* syn;
            rastr_node_t gap;
            rastr_node_t loc;
        } op_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } dlmtr_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } bkt_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } null_node;

        struct {
            int val;
            rastr_node_t gap;
            rastr_node_t loc;
        } lgl_node;

        struct {
            char* syn;
            int val;
            rastr_node_t gap;
            rastr_node_t loc;
        } int_node;

        struct {
            char* syn;
            double val;
            rastr_node_t gap;
            rastr_node_t loc;
        } dbl_node;

        struct {
            char* syn;
            Rcomplex val;
            rastr_node_t gap;
            rastr_node_t loc;
        } cpx_node;

        struct {
            char* syn;
            char* val;
            rastr_node_t gap;
            rastr_node_t loc;
        } chr_node;

        struct {
            char* syn;
            char* val;
            rastr_node_t gap;
            rastr_node_t loc;
        } sym_node;

        struct {
            rastr_node_t lbkt;
            rastr_node_t exprs;
            rastr_node_t rbkt;
        } blk_node;

        struct {
            rastr_node_t lbkt;
            rastr_node_t expr;
            rastr_node_t rbkt;
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
            rastr_node_t op;
            rastr_node_t body;
        } rlp_node;

        struct {
            rastr_node_t op;
            rastr_node_t cond;
            rastr_node_t body;
        } wlp_node;

        struct {
            rastr_node_t op;
            rastr_node_t iter;
            rastr_node_t body;
        } flp_node;

        struct {
            rastr_node_t iop;
            rastr_node_t cond;
            rastr_node_t ibody;
        } icond_node;

        struct {
            rastr_node_t iop;
            rastr_node_t cond;
            rastr_node_t ibody;
            rastr_node_t eop;
            rastr_node_t ebody;
        } iecond_node;

        struct {
            rastr_node_t op;
            rastr_node_t lbkt;
            rastr_node_t pars;
            rastr_node_t rbkt;
            rastr_node_t body;
        } fndefn_node;

        struct {
            rastr_node_t fn;
            rastr_node_t lbkt;
            rastr_node_t args;
            rastr_node_t rbkt;
        } fncall_node;

        struct {
            rastr_node_t obj;
            rastr_node_t lbkt;
            rastr_node_t args;
            rastr_node_t rbkt;
        } sub_node;

        struct {
            rastr_node_t obj;
            rastr_node_t lbkt;
            rastr_node_t args;
            rastr_node_t rbkt1;
            rastr_node_t rbkt2;
        } idx_node;

        struct {
            rastr_node_t ann;
            rastr_node_t expr;
        } aexpr_node;

        struct {
            int len;
            rastr_node_t* seq;
        } exprs_node;

        struct {
            int len;
            rastr_node_t* seq;
        } pars_node;

        struct {
            rastr_node_t name;
            rastr_node_t op;
            rastr_node_t expr;
        } dpar_node;

        struct {
            rastr_node_t name;
        } ndpar_node;

        struct {
            int len;
            rastr_node_t* seq;
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
            rastr_node_t lbkt;
            rastr_node_t expr;
            rastr_node_t rbkt;
        } cond_node;

        struct {
            rastr_node_t lbkt;
            rastr_node_t var;
            rastr_node_t op;
            rastr_node_t expr;
            rastr_node_t rbkt;
        } iter_node;

        struct {
            rastr_node_t beg;
            rastr_node_t exprs;
            rastr_node_t end;
        } pgm_node;

        struct {
            rastr_node_t expr;
            rastr_node_t dlmtr;
        } dlmtd_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } msng_node;

        struct {
            char* bom;
            rastr_node_t loc;
        } beg_node;

        struct {
            rastr_node_t gap;
            rastr_node_t loc;
        } end_node;

        struct {
            char* val;
            rastr_node_t loc;
        } gap_node;

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

        struct {
            char* msg;
            rastr_node_t loc;
        } err_node;

    } node;
};

void ensure_class(SEXP r_obj, const char* cls) {
    if (!class_has(r_obj, cls)) {
        Rf_error("expected object of class '%s'", cls);
    }
}

void ensure_ast_class(SEXP r_obj) {
    ensure_class(r_obj, "rastr_ast");
}

void ensure_node_class(SEXP r_obj) {
    ensure_class(r_obj, "rastr_node");
}

rastr_node_t RASTR_NODE_UNDEFINED{-1};

int rastr_node_is_undefined(rastr_node_t node) {
    return node.index == RASTR_NODE_UNDEFINED.index;
}

int rastr_node_is_newline(rastr_node_t node) {
    return node.index == RASTR_NODE_NEWLINE.index;
}

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

typedef rastr_node_impl_t* rastr_node_ptr_t;

void rastr_node_destroy_shallow(rastr_node_ptr_t ptr);

typedef Pool<rastr_node_impl_t, rastr_node_destroy_shallow> AstPool;

struct rastr_ast_impl_t {
    int id;
    AstPool* pool;
    rastr_node_t root;
};

const int INDENTATION = 4;

const char* rastr_node_type_to_string(rastr_node_type_t type) {
    switch (type) {
    case RASTR_OP_SP:
        return "OP_SP";

    case RASTR_OP_PLUS:
        return "OP_PLUS";

    case RASTR_OP_MINUS:
        return "OP_MINUS";

    case RASTR_OP_MUL:
        return "OP_MUL";

    case RASTR_OP_DIV:
        return "OP_DIV";

    case RASTR_OP_POW:
        return "OP_POW";

    case RASTR_OP_POW2:
        return "OP_POW2";

    case RASTR_OP_LESS:
        return "OP_LESS";

    case RASTR_OP_LESS_EQ:
        return "OP_LESS_EQ";

    case RASTR_OP_GREAT:
        return "OP_GREAT";

    case RASTR_OP_GREAT_EQ:
        return "OP_GREAT_EQ";

    case RASTR_OP_EQ:
        return "OP_EQ";

    case RASTR_OP_NOT_EQ:
        return "OP_NOT_EQ";

    case RASTR_OP_NOT:
        return "OP_NOT";

    case RASTR_OP_AND:
        return "OP_AND";

    case RASTR_OP_VEC_AND:
        return "OP_VEC_AND";

    case RASTR_OP_OR:
        return "OP_OR";

    case RASTR_OP_VEC_OR:
        return "OP_VEC_OR";

    case RASTR_OP_EQ_ASGN:
        return "OP_EQ_ASGN";

    case RASTR_OP_LT_ASGN:
        return "OP_LT_ASGN";

    case RASTR_OP_RT_ASGN:
        return "OP_RT_ASGN";

    case RASTR_OP_LT_SUP_ASGN:
        return "OP_LT_SUP_ASGN";

    case RASTR_OP_RT_SUP_ASGN:
        return "OP_RT_SUP_ASGN";

    case RASTR_OP_COLON_ASGN:
        return "OP_COLON_ASGN";

    case RASTR_OP_PIPE_FWD:
        return "OP_PIPE_FWD";

    case RASTR_OP_PIPE_BIND:
        return "OP_PIPE_BIND";

    case RASTR_OP_PUB_NS:
        return "OP_PUB_NS";

    case RASTR_OP_PVT_NS:
        return "OP_PVT_NS";

    case RASTR_OP_RANGE:
        return "OP_RANGE";

    case RASTR_OP_HELP:
        return "OP_HELP";

    case RASTR_OP_SLOT:
        return "OP_SLOT";

    case RASTR_OP_FORMULA:
        return "OP_FORMULA";

    case RASTR_OP_PART:
        return "OP_PART";

    case RASTR_OP_FN:
        return "OP_FN";

    case RASTR_OP_FN2:
        return "OP_FN2";

    case RASTR_OP_WHILE:
        return "OP_WHILE";

    case RASTR_OP_REPEAT:
        return "OP_REPEAT";

    case RASTR_OP_FOR:
        return "OP_FOR";

    case RASTR_OP_IN:
        return "OP_IN";

    case RASTR_OP_IF:
        return "OP_IF";

    case RASTR_OP_ELSE:
        return "OP_ELSE";

    case RASTR_OP_NEXT:
        return "OP_NEXT";

    case RASTR_OP_BREAK:
        return "OP_BREAK";

    case RASTR_DLMTR_SCOL:
        return "DLMTR_SCOL";

    case RASTR_DLMTR_COM:
        return "DLMTR_COM";

    case RASTR_BKT_LT_RND:
        return "BKT_LT_RND";

    case RASTR_BKT_RT_RND:
        return "BKT_RT_RND";

    case RASTR_BKT_LT_CURL:
        return "BKT_LT_CURL";

    case RASTR_BKT_RT_CURL:
        return "BKT_RT_CURL";

    case RASTR_BKT_LT_SQR:
        return "BKT_LT_SQR";

    case RASTR_BKT_RT_SQR:
        return "BKT_RT_SQR";

    case RASTR_BKT_LT_DBL_SQR:
        return "BKT_LT_DBL_SQR";

    case RASTR_NULL:
        return "NULL";

    case RASTR_LGL:
        return "LGL";

    case RASTR_INT:
        return "INT";

    case RASTR_DBL:
        return "DBL";

    case RASTR_CPX:
        return "CPX";

    case RASTR_CHR:
        return "CHR";

    case RASTR_SYM:
        return "SYM";

    case RASTR_BLK:
        return "BLK";

    case RASTR_GRP:
        return "GRP";

    case RASTR_NUOP:
        return "NUOP";

    case RASTR_UNOP:
        return "UNOP";

    case RASTR_BINOP:
        return "BINOP";

    case RASTR_RLP:
        return "RLP";

    case RASTR_WLP:
        return "WLP";

    case RASTR_FLP:
        return "FLP";

    case RASTR_ICOND:
        return "ICOND";

    case RASTR_IECOND:
        return "IECOND";

    case RASTR_FNDEFN:
        return "FNDEFN";

    case RASTR_FNCALL:
        return "FNCALL";

    case RASTR_SUB:
        return "SUB";

    case RASTR_IDX:
        return "IDX";

    case RASTR_AEXPR:
        return "AEXPR";

    case RASTR_EXPRS:
        return "EXPRS";

    case RASTR_PARS:
        return "PARS";

    case RASTR_DPAR:
        return "DPAR";

    case RASTR_NDPAR:
        return "NDPAR";

    case RASTR_ARGS:
        return "ARGS";

    case RASTR_NARG:
        return "NARG";

    case RASTR_PARG:
        return "PARG";

    case RASTR_COND:
        return "COND";

    case RASTR_ITER:
        return "ITER";

    case RASTR_PGM:
        return "PGM";

    case RASTR_DLMTD:
        return "DLMTD";

    case RASTR_MSNG:
        return "MSNG";

    case RASTR_BEG:
        return "BEG";

    case RASTR_END:
        return "END";

    case RASTR_GAP:
        return "GAP";

    case RASTR_LOC:
        return "LOC";

    case RASTR_ERR:
        return "ERR";
    }
    fail_with("Unhandled node type %d", type);
}

/********************************************************************************
 Ast
********************************************************************************/
rastr_node_ptr_t rastr_ast_get_impl(rastr_ast_t ast, rastr_node_t node) {
    return ast->pool->at(node.index);
}

rastr_ast_t rastr_ast_new(int capacity) {
    if (capacity <= 0) {
        Rf_error("capacity should be greater than 0");
    }

    rastr_ast_t ast = (rastr_ast_t) malloc_or_fail(sizeof(rastr_ast_impl_t));

    ast->id = id_counter++;

    ast->pool = new Pool<rastr_node_impl_t, rastr_node_destroy_shallow>(
        (std::size_t) capacity);

    ast->root = RASTR_NODE_UNDEFINED;

    return ast;
}

SEXP r_rastr_ast_new(SEXP r_capacity) {
    int capacity = num_get(r_capacity, 0);
    rastr_ast_t ast = rastr_ast_new(capacity);
    return rastr_ast_wrap(ast);
}

void rastr_ast_destroy(rastr_ast_t ast) {
    ast->pool->clear();
    delete ast->pool;
    free(ast);
}

int rastr_ast_id(rastr_ast_t ast) {
    return ast->id;
}

SEXP r_rastr_ast_id(SEXP r_ast) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    int id = rastr_ast_id(ast);

    return int_vec1(id);
}

int rastr_ast_size(rastr_ast_t ast) {
    return ast->pool->get_size();
}

SEXP r_rastr_ast_size(SEXP r_ast) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    int size = rastr_ast_size(ast);

    return int_vec1(size);
}

rastr_node_t rastr_ast_root_get(rastr_ast_t ast) {
    rastr_node_t root = ast->root;

    if (rastr_node_is_undefined(root)) {
        Rf_error("cannot access root of empty ast");
    }

    return root;
}

SEXP r_rastr_ast_root_get(SEXP r_ast) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    rastr_node_t root = rastr_ast_root_get(ast);

    return rastr_node_wrap(root);
}

rastr_node_t rastr_ast_root_rep(rastr_ast_t ast, rastr_node_t root) {
    rastr_node_t prev_root = ast->root;

    if (rastr_node_is_undefined(prev_root)) {
        Rf_error("cannot replace root of empty ast");
    }

    rastr_node_pid_unset(ast, prev_root);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, root);
    ptr->pid = ast->id;

    ast->root = root;

    return prev_root;
}

SEXP r_rastr_ast_root_rep(SEXP r_ast, SEXP r_root) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_root);
    rastr_node_t root = rastr_node_unwrap(r_root);

    rastr_node_t result = rastr_ast_root_rep(ast, root);

    return rastr_node_wrap(result);
}

void rastr_ast_root_set(rastr_ast_t ast, rastr_node_t root) {
    rastr_node_t prev_root = ast->root;

    if (!rastr_node_is_undefined(prev_root)) {
        rastr_node_pid_unset(ast, prev_root);
        rastr_node_destroy(ast, prev_root);
    }

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, root);
    ptr->pid = ast->id;

    ast->root = root;
}

SEXP r_rastr_ast_root_set(SEXP r_ast, SEXP r_root) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_root);
    rastr_node_t root = rastr_node_unwrap(r_root);

    rastr_ast_root_set(ast, root);

    return R_NilValue;
}

struct rastr_node_pair_t {
    rastr_node_ptr_t ptr;
    rastr_node_t node;
};

rastr_node_pair_t rastr_node_create(rastr_ast_t ast, rastr_node_type_t type) {
    AstPool::slot_t slot = ast->pool->allocate();

    rastr_node_pair_t pair;
    pair.ptr = slot.data;
    pair.node = rastr_node_t{(int) slot.index};

    pair.ptr->type = type;
    pair.ptr->id = id_counter++;
    pair.ptr->pid = -1;

    return pair;
}

void rastr_node_destroy_shallow(rastr_node_ptr_t ptr) {
    switch (ptr->type) {
    /********************************************************************************
     Operators
    ********************************************************************************/
    case RASTR_OP_SP:
        free(ptr->node.op_node.syn);
        break;

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
        break;

        /********************************************************************************
         Delimiters
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        break;

    case RASTR_LGL:
        break;

    case RASTR_INT:
        free(ptr->node.int_node.syn);
        break;

    case RASTR_DBL:
        free(ptr->node.dbl_node.syn);
        break;

    case RASTR_CPX:
        free(ptr->node.cpx_node.syn);
        break;

    case RASTR_CHR:
        free(ptr->node.chr_node.syn);
        free(ptr->node.chr_node.val);
        break;

    case RASTR_SYM: {
        char* syn = ptr->node.sym_node.syn;
        char* val = ptr->node.sym_node.val;

        if (syn != val) {
            free(syn);
            free(val);
        } else {
            free(syn);
        }
    }

    break;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
    case RASTR_GRP:
    case RASTR_NUOP:
    case RASTR_UNOP:
    case RASTR_BINOP:
    case RASTR_RLP:
    case RASTR_WLP:
    case RASTR_FLP:
    case RASTR_ICOND:
    case RASTR_IECOND:
    case RASTR_FNDEFN:
    case RASTR_FNCALL:
    case RASTR_SUB:
    case RASTR_IDX:
        break;

    /********************************************************************************
      Miscellaneous
    ********************************************************************************/
    case RASTR_AEXPR:
        break;

    case RASTR_EXPRS:
        free(ptr->node.exprs_node.seq);
        break;

    case RASTR_PARS:
        free(ptr->node.pars_node.seq);
        break;

    case RASTR_DPAR:
    case RASTR_NDPAR:
        break;

    case RASTR_ARGS:
        free(ptr->node.args_node.seq);
        break;

    case RASTR_NARG:
    case RASTR_PARG:
    case RASTR_COND:
    case RASTR_ITER:
    case RASTR_PGM:
    case RASTR_DLMTD:
    case RASTR_MSNG:
        break;

    case RASTR_BEG:
        free(ptr->node.beg_node.bom);
        break;

    case RASTR_END:
        break;

    case RASTR_GAP:
        free(ptr->node.gap_node.val);
        break;

    case RASTR_LOC:
        break;

    case RASTR_ERR:
        free(ptr->node.err_node.msg);
        break;
    }
}

#define DESTROY_1(NODE, CHILD1) \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1##_get(ast, node));

#define DESTROY_2(NODE, CHILD1, CHILD2)                                \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2##_get(ast, node));

#define DESTROY_3(NODE, CHILD1, CHILD2, CHILD3)                        \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3##_get(ast, node));

#define DESTROY_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4)                \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD4##_get(ast, node));

#define DESTROY_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5)        \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD1##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD2##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD3##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD4##_get(ast, node)); \
    rastr_node_destroy(ast, rastr_##NODE##_##CHILD5##_get(ast, node));

#define DESTROY_SEQ(NODE, LEN, SEQ)                                \
    {                                                              \
        int len = rastr_##NODE##_##LEN##_get(ast, node);           \
        for (int i = 0; i < len; ++i) {                            \
            rastr_node_t child = rastr_##NODE##_get(ast, node, i); \
            rastr_node_destroy(ast, child);                        \
        }                                                          \
    }

void rastr_node_destroy(rastr_ast_t ast, rastr_node_t node) {
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
        DESTROY_2(op, gap, loc);
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
        DESTROY_2(bkt, gap, loc);
        break;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        DESTROY_2(dlmtr, gap, loc);
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        DESTROY_2(null, gap, loc);
        break;

    case RASTR_LGL:
        DESTROY_2(lgl, gap, loc);
        break;

    case RASTR_INT:
        DESTROY_2(int, gap, loc);
        break;

    case RASTR_DBL:
        DESTROY_2(dbl, gap, loc);
        break;

    case RASTR_CPX:
        DESTROY_2(cpx, gap, loc);
        break;

    case RASTR_CHR:
        DESTROY_2(chr, gap, loc);
        break;

    case RASTR_SYM:
        DESTROY_2(sym, gap, loc);
        break;

        /********************************************************************************
          Expressions
        ********************************************************************************/
    case RASTR_BLK:
        DESTROY_3(blk, lbkt, exprs, rbkt)
        break;

    case RASTR_GRP:
        DESTROY_3(grp, lbkt, expr, rbkt);
        break;

    case RASTR_NUOP:
        DESTROY_1(nuop, op);
        break;

    case RASTR_UNOP:
        DESTROY_2(unop, op, expr);
        break;

    case RASTR_BINOP:
        DESTROY_3(binop, lexpr, op, rexpr);
        break;

    case RASTR_RLP:
        DESTROY_2(rlp, op, body);
        break;

    case RASTR_WLP:
        DESTROY_3(wlp, op, cond, body);
        break;

    case RASTR_FLP:
        DESTROY_3(flp, op, iter, body);
        break;

    case RASTR_ICOND:
        DESTROY_3(icond, iop, cond, ibody);
        break;

    case RASTR_IECOND:
        DESTROY_5(iecond, iop, cond, ibody, eop, ebody);
        break;

    case RASTR_FNDEFN:
        DESTROY_5(fndefn, op, lbkt, pars, rbkt, body);
        break;

    case RASTR_FNCALL:
        DESTROY_4(fncall, fn, lbkt, args, rbkt);
        break;

    case RASTR_SUB:
        DESTROY_4(sub, obj, lbkt, args, rbkt);
        break;

    case RASTR_IDX:
        DESTROY_5(idx, obj, lbkt, args, rbkt1, rbkt2);
        break;

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
    case RASTR_AEXPR:
        DESTROY_2(aexpr, ann, expr)
        break;

    case RASTR_EXPRS:
        DESTROY_SEQ(exprs, len, seq)
        break;

    case RASTR_PARS:
        DESTROY_SEQ(pars, len, seq)
        break;

    case RASTR_DPAR:
        DESTROY_3(dpar, name, op, expr)
        break;

    case RASTR_NDPAR:
        DESTROY_1(ndpar, name)
        break;

    case RASTR_ARGS:
        DESTROY_SEQ(args, len, seq)
        break;

    case RASTR_NARG:
        DESTROY_3(narg, name, op, expr)
        break;

    case RASTR_PARG:
        DESTROY_1(parg, expr)
        break;

    case RASTR_COND:
        DESTROY_3(cond, lbkt, expr, rbkt)
        break;

    case RASTR_ITER:
        DESTROY_5(iter, lbkt, var, op, expr, rbkt)
        break;

    case RASTR_PGM:
        DESTROY_3(pgm, beg, exprs, end)
        break;

    case RASTR_DLMTD:
        DESTROY_2(dlmtd, expr, dlmtr)
        break;

    case RASTR_MSNG:
        DESTROY_2(msng, gap, loc)
        break;

    case RASTR_BEG:
        DESTROY_1(beg, loc)
        break;

    case RASTR_END:
        DESTROY_2(end, gap, loc)
        break;

    case RASTR_GAP:
        DESTROY_1(gap, loc)
        break;

    case RASTR_LOC:
    case RASTR_ERR:
        break;
    }

    ast->pool->deallocate(node.index);
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

int rastr_node_pid(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->pid;
}

void rastr_node_pid_set(rastr_ast_t ast, rastr_node_t node, int pid) {
    rastr_ast_get_impl(ast, node)->pid = pid;
}

void rastr_node_pid_unset(rastr_ast_t ast, rastr_node_t node) {
    rastr_ast_get_impl(ast, node)->pid = -1;
}

int rastr_is_orphan(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->pid == -1;
}

#define CLONE_1(NODE, CHILD1) \
    return rastr_##NODE##_new(ast, rastr_##NODE##_##CHILD1##_get(ast, node));

#define CLONE_2(NODE, CHILD1, CHILD2)                                   \
    return rastr_##NODE##_new(ast,                                      \
                              rastr_##NODE##_##CHILD1##_get(ast, node), \
                              rastr_##NODE##_##CHILD2##_get(ast, node));

#define CLONE_3(NODE, CHILD1, CHILD2, CHILD3)                           \
    return rastr_##NODE##_new(ast,                                      \
                              rastr_##NODE##_##CHILD1##_get(ast, node), \
                              rastr_##NODE##_##CHILD2##_get(ast, node), \
                              rastr_##NODE##_##CHILD3##_get(ast, node));

#define CLONE_4(NODE, CHILD1, CHILD2, CHILD3, CHILD4)                   \
    return rastr_##NODE##_new(ast,                                      \
                              rastr_##NODE##_##CHILD1##_get(ast, node), \
                              rastr_##NODE##_##CHILD2##_get(ast, node), \
                              rastr_##NODE##_##CHILD3##_get(ast, node), \
                              rastr_##NODE##_##CHILD4##_get(ast, node));

#define CLONE_5(NODE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5)           \
    return rastr_##NODE##_new(ast,                                      \
                              rastr_##NODE##_##CHILD1##_get(ast, node), \
                              rastr_##NODE##_##CHILD2##_get(ast, node), \
                              rastr_##NODE##_##CHILD3##_get(ast, node), \
                              rastr_##NODE##_##CHILD4##_get(ast, node), \
                              rastr_##NODE##_##CHILD5##_get(ast, node));

#define CLONE_SEQ(NODE, LEN, SEQ)                                    \
    return rastr_##NODE##_new(ast,                                   \
                              rastr_##NODE##_##LEN##_get(ast, node), \
                              rastr_##NODE##_##SEQ##_get(ast, node));

rastr_node_t rastr_node_clone(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
    /********************************************************************************
     Operators
    ********************************************************************************/
    case RASTR_OP_SP:
        return rastr_sp_new_unsafe(ast,
                                   str_dup(rastr_op_syn_get(ast, node)),
                                   rastr_op_gap_get(ast, node),
                                   rastr_op_loc_get(ast, node));
        break;
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
        return rastr_op_new_unsafe(ast,
                                   type,
                                   rastr_op_gap_get(ast, node),
                                   rastr_op_loc_get(ast, node));

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
        return rastr_bkt_new_unsafe(ast,
                                    type,
                                    rastr_bkt_gap_get(ast, node),
                                    rastr_bkt_loc_get(ast, node));
        break;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        return rastr_dlmtr_new_unsafe(ast,
                                      type,
                                      rastr_dlmtr_gap_get(ast, node),
                                      rastr_dlmtr_loc_get(ast, node));
        break;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        CLONE_2(null, gap, loc);
        break;

    case RASTR_LGL:
        return rastr_lgl_new(ast,
                             rastr_lgl_val_get(ast, node),
                             rastr_lgl_gap_get(ast, node),
                             rastr_lgl_loc_get(ast, node));
        break;

    case RASTR_INT:
        return rastr_int_new_unsafe(ast,
                                    rastr_int_val_get(ast, node),
                                    str_dup(rastr_int_syn_get(ast, node)),
                                    rastr_int_gap_get(ast, node),
                                    rastr_int_loc_get(ast, node));
        break;

    case RASTR_DBL:
        return rastr_dbl_new_unsafe(ast,
                                    rastr_dbl_val_get(ast, node),
                                    str_dup(rastr_dbl_syn_get(ast, node)),
                                    rastr_dbl_gap_get(ast, node),
                                    rastr_dbl_loc_get(ast, node));
        break;

    case RASTR_CPX:
        return rastr_cpx_new_unsafe(ast,
                                    rastr_cpx_val_get(ast, node),
                                    str_dup(rastr_cpx_syn_get(ast, node)),
                                    rastr_cpx_gap_get(ast, node),
                                    rastr_cpx_loc_get(ast, node));
        break;

    case RASTR_CHR:
        return rastr_chr_new_unsafe(ast,
                                    str_dup(rastr_chr_val_get(ast, node)),
                                    str_dup(rastr_chr_syn_get(ast, node)),
                                    rastr_chr_gap_get(ast, node),
                                    rastr_chr_loc_get(ast, node));
        break;

    case RASTR_SYM:
        return rastr_sym_new_unsafe(ast,
                                    str_dup(rastr_sym_val_get(ast, node)),
                                    str_dup(rastr_sym_syn_get(ast, node)),
                                    rastr_sym_gap_get(ast, node),
                                    rastr_sym_loc_get(ast, node));
        break;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
        CLONE_3(blk, lbkt, exprs, rbkt);
        break;

    case RASTR_GRP:
        CLONE_3(grp, lbkt, expr, rbkt);
        break;

    case RASTR_NUOP:
        CLONE_1(nuop, op);
        break;

    case RASTR_UNOP:
        CLONE_2(unop, op, expr);
        break;

    case RASTR_BINOP:
        CLONE_3(binop, lexpr, op, rexpr);
        break;

    case RASTR_RLP:
        CLONE_2(rlp, op, body);
        break;

    case RASTR_WLP:
        CLONE_3(wlp, op, cond, body);
        break;

    case RASTR_FLP:
        CLONE_3(flp, op, iter, body);
        break;

    case RASTR_ICOND:
        CLONE_3(icond, iop, cond, ibody);
        break;

    case RASTR_IECOND:
        CLONE_5(iecond, iop, cond, ibody, eop, ebody);
        break;

    case RASTR_FNDEFN:
        CLONE_5(fndefn, op, lbkt, pars, rbkt, body);
        break;

    case RASTR_FNCALL:
        CLONE_4(fncall, fn, lbkt, args, rbkt);
        break;

    case RASTR_SUB:
        CLONE_4(sub, obj, lbkt, args, rbkt);
        break;

    case RASTR_IDX:
        CLONE_5(idx, obj, lbkt, args, rbkt1, rbkt2);
        break;

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
    case RASTR_AEXPR:
        CLONE_2(aexpr, ann, expr)
        break;

    case RASTR_EXPRS:
        CLONE_SEQ(exprs, len, seq)
        break;

    case RASTR_PARS:
        CLONE_SEQ(pars, len, seq)
        break;

    case RASTR_DPAR:
        CLONE_3(dpar, name, op, expr)
        break;

    case RASTR_NDPAR:
        CLONE_1(ndpar, name)
        break;

    case RASTR_ARGS:
        CLONE_SEQ(args, len, seq)
        break;

    case RASTR_NARG:
        CLONE_3(narg, name, op, expr)
        break;

    case RASTR_PARG:
        CLONE_1(parg, expr)
        break;

    case RASTR_COND:
        CLONE_3(cond, lbkt, expr, rbkt)
        break;

    case RASTR_ITER:
        CLONE_5(iter, lbkt, var, op, expr, rbkt)
        break;

    case RASTR_PGM:
        CLONE_3(pgm, beg, exprs, end)
        break;

    case RASTR_DLMTD:
        CLONE_2(dlmtd, expr, dlmtr)
        break;

    case RASTR_MSNG:
        CLONE_2(msng, gap, loc)
        break;

    case RASTR_BEG:
        return rastr_beg_new_unsafe(ast,
                                    str_dup(rastr_beg_bom_get(ast, node)),
                                    rastr_dlmtr_loc_get(ast, node));
        break;

    case RASTR_END:
        CLONE_2(end, gap, loc)
        break;

    case RASTR_GAP:
        return rastr_gap_new(ast,
                             str_dup(rastr_gap_val_get(ast, node)),
                             rastr_gap_loc_get(ast, node));
        break;

    case RASTR_LOC:
        return rastr_loc_new(ast,
                             rastr_loc_lrow_get(ast, node),
                             rastr_loc_lcol_get(ast, node),
                             rastr_loc_lchr_get(ast, node),
                             rastr_loc_lbyte_get(ast, node),
                             rastr_loc_rrow_get(ast, node),
                             rastr_loc_rcol_get(ast, node),
                             rastr_loc_rchr_get(ast, node),
                             rastr_loc_rbyte_get(ast, node));
        break;

    case RASTR_ERR:
        Rf_error("cannot clone err node");
        return RASTR_NODE_UNDEFINED;
        break;
    }

    Rf_error("unhandled node type for cloning");
    return RASTR_NODE_UNDEFINED;
}

#undef CLONE_1
#undef CLONE_2
#undef CLONE_3
#undef CLONE_4
#undef CLONE_5
#undef CLONE_SEQ

rastr_node_t rastr_node_leftmost(rastr_ast_t ast, rastr_node_t node) {
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
        return node;

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
        return node;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        return node;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
    case RASTR_LGL:
    case RASTR_INT:
    case RASTR_DBL:
    case RASTR_CPX:
    case RASTR_CHR:
    case RASTR_SYM:
        return node;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
        return rastr_blk_lbkt_get(ast, node);

    case RASTR_GRP:
        return rastr_grp_lbkt_get(ast, node);

    case RASTR_NUOP:
        return rastr_node_leftmost(ast, rastr_nuop_op_get(ast, node));

    case RASTR_UNOP:
        return rastr_node_leftmost(ast, rastr_unop_op_get(ast, node));

    case RASTR_BINOP:
        return rastr_node_leftmost(ast, rastr_binop_lexpr_get(ast, node));

    case RASTR_RLP:
        return rastr_node_leftmost(ast, rastr_rlp_op_get(ast, node));

    case RASTR_WLP:
        return rastr_node_leftmost(ast, rastr_wlp_op_get(ast, node));

    case RASTR_FLP:
        return rastr_node_leftmost(ast, rastr_flp_op_get(ast, node));

    case RASTR_ICOND:
        return rastr_node_leftmost(ast, rastr_icond_iop_get(ast, node));

    case RASTR_IECOND:
        return rastr_node_leftmost(ast, rastr_iecond_iop_get(ast, node));

    case RASTR_FNDEFN:
        return rastr_node_leftmost(ast, rastr_fndefn_op_get(ast, node));

    case RASTR_FNCALL:
        return rastr_node_leftmost(ast, rastr_fncall_fn_get(ast, node));

    case RASTR_SUB:
        return rastr_node_leftmost(ast, rastr_sub_obj_get(ast, node));

    case RASTR_IDX:
        return rastr_node_leftmost(ast, rastr_idx_obj_get(ast, node));

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
    case RASTR_AEXPR:
        return rastr_node_leftmost(ast, rastr_aexpr_ann_get(ast, node));

    case RASTR_EXPRS: {
        int len = rastr_exprs_len_get(ast, node);
        if (len == 0)
            return node;
        const rastr_node_t* seq = rastr_exprs_seq_get(ast, node);
        return seq[0];
    }

    case RASTR_PARS: {
        int len = rastr_pars_len_get(ast, node);
        if (len == 0)
            return node;
        const rastr_node_t* seq = rastr_pars_seq_get(ast, node);
        return seq[0];
    }

    case RASTR_DPAR:
        return rastr_node_leftmost(ast, rastr_dpar_name_get(ast, node));

    case RASTR_NDPAR:
        return rastr_node_leftmost(ast, rastr_ndpar_name_get(ast, node));

    case RASTR_ARGS: {
        int len = rastr_args_len_get(ast, node);
        if (len == 0)
            return node;
        const rastr_node_t* seq = rastr_args_seq_get(ast, node);
        return seq[0];
    }

    case RASTR_NARG:
        return rastr_node_leftmost(ast, rastr_narg_name_get(ast, node));

    case RASTR_PARG:
        return rastr_node_leftmost(ast, rastr_parg_expr_get(ast, node));

    case RASTR_COND:
        return rastr_cond_lbkt_get(ast, node);

    case RASTR_ITER:
        return rastr_iter_lbkt_get(ast, node);

    case RASTR_PGM:
        return rastr_node_leftmost(ast, rastr_pgm_exprs_get(ast, node));

    case RASTR_DLMTD:
        return rastr_dlmtd_expr_get(ast, node);

    case RASTR_MSNG:
        return node;

    case RASTR_BEG:
        return node;

    case RASTR_END:
        return node;

    case RASTR_GAP:
        return node;

    case RASTR_LOC:
        return node;

    case RASTR_ERR:
        Rf_error("unexpected node of type RASTR_ERR");
    }

    Rf_error("unhandled node type");
    return RASTR_NODE_UNDEFINED;
}

SEXP r_rastr_node_leftmost(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return rastr_node_wrap(rastr_node_leftmost(ast, node));
}

rastr_node_t rastr_node_gap_get(rastr_ast_t ast, rastr_node_t node) {
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
        return rastr_op_gap_get(ast, node);

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
        return rastr_bkt_gap_get(ast, node);

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        return rastr_dlmtr_gap_get(ast, node);

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        return rastr_null_gap_get(ast, node);
    case RASTR_LGL:
        return rastr_lgl_gap_get(ast, node);
    case RASTR_INT:
        return rastr_int_gap_get(ast, node);
    case RASTR_DBL:
        return rastr_dbl_gap_get(ast, node);
    case RASTR_CPX:
        return rastr_cpx_gap_get(ast, node);
    case RASTR_CHR:
        return rastr_chr_gap_get(ast, node);
    case RASTR_SYM:
        return rastr_sym_gap_get(ast, node);

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
    case RASTR_GRP:
    case RASTR_NUOP:
    case RASTR_UNOP:
    case RASTR_BINOP:
    case RASTR_RLP:
    case RASTR_WLP:
    case RASTR_FLP:
    case RASTR_ICOND:
    case RASTR_IECOND:
    case RASTR_FNDEFN:
    case RASTR_FNCALL:
    case RASTR_SUB:
    case RASTR_IDX:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
    case RASTR_AEXPR:
    case RASTR_EXPRS:
    case RASTR_PARS:
    case RASTR_DPAR:
    case RASTR_NDPAR:
    case RASTR_ARGS:
    case RASTR_NARG:
    case RASTR_PARG:
    case RASTR_COND:
    case RASTR_ITER:
    case RASTR_PGM:
    case RASTR_DLMTD:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

    case RASTR_MSNG:
        return rastr_msng_gap_get(ast, node);

    case RASTR_BEG:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

    case RASTR_END:
        return rastr_end_gap_get(ast, node);

    case RASTR_GAP:
        return node;

    case RASTR_LOC:
    case RASTR_ERR:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));
    }

    Rf_error("unhandled node type");
    return RASTR_NODE_UNDEFINED;
}

SEXP r_rastr_node_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return rastr_node_wrap(rastr_node_gap_get(ast, node));
}

void rastr_node_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
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
        rastr_op_gap_set(ast, node, gap);
        return;

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
        rastr_bkt_gap_set(ast, node, gap);
        return;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case RASTR_DLMTR_SCOL:
    case RASTR_DLMTR_COM:
        rastr_dlmtr_gap_set(ast, node, gap);
        return;

        /********************************************************************************
          Literals
        ********************************************************************************/
    case RASTR_NULL:
        rastr_null_gap_set(ast, node, gap);
        return;

    case RASTR_LGL:
        rastr_lgl_gap_set(ast, node, gap);
        return;

    case RASTR_INT:
        rastr_int_gap_set(ast, node, gap);
        return;

    case RASTR_DBL:
        rastr_dbl_gap_set(ast, node, gap);
        return;

    case RASTR_CPX:
        rastr_cpx_gap_set(ast, node, gap);
        return;

    case RASTR_CHR:
        rastr_chr_gap_set(ast, node, gap);
        return;

    case RASTR_SYM:
        rastr_sym_gap_set(ast, node, gap);
        return;

    /********************************************************************************
      Expressions
    ********************************************************************************/
    case RASTR_BLK:
    case RASTR_GRP:
    case RASTR_NUOP:
    case RASTR_UNOP:
    case RASTR_BINOP:
    case RASTR_RLP:
    case RASTR_WLP:
    case RASTR_FLP:
    case RASTR_ICOND:
    case RASTR_IECOND:
    case RASTR_FNDEFN:
    case RASTR_FNCALL:
    case RASTR_SUB:
    case RASTR_IDX:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
    case RASTR_AEXPR:
    case RASTR_EXPRS:
    case RASTR_PARS:
    case RASTR_DPAR:
    case RASTR_NDPAR:
    case RASTR_ARGS:
    case RASTR_NARG:
    case RASTR_PARG:
    case RASTR_COND:
    case RASTR_ITER:
    case RASTR_PGM:
    case RASTR_DLMTD:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

    case RASTR_MSNG:
        rastr_msng_gap_set(ast, node, gap);
        return;

    case RASTR_BEG:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));

    case RASTR_END:
        rastr_end_gap_set(ast, node, gap);
        return;

    case RASTR_GAP:
    case RASTR_LOC:
    case RASTR_ERR:
        Rf_error("unexpected node of type: %s",
                 rastr_node_type_to_string(type));
    }

    Rf_error("unhandled node type");
}

SEXP r_rastr_node_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_gap_set(ast, node, gap);

    return R_NilValue;
}

#define CHECK_NODETYPE(PRED, NODE)                     \
    if (!PRED(ast, NODE)) {                              \
        Rf_error(#PRED " : received invalid node type"); \
    }

void ensure_numeric_sexp(SEXP r_obj, int length) {
    SEXPTYPE t = TYPEOF(r_obj);

    if (t != REALSXP && t != INTSXP) {
        Rf_error("expected a numeric value of length");
    }

    int l = Rf_length(r_obj);

    if (l != length) {
        Rf_error("expected a numeric vector of length %d", l);
    }
}

void ensure_vec_sexp(SEXP r_obj, SEXPTYPE type, int length) {
    SEXPTYPE t = TYPEOF(r_obj);

    if (t != type) {
        Rf_error("expected a %s vector", Rf_type2str(type));
    }

    int l = Rf_length(r_obj);

    if (l != length) {
        Rf_error("expected a %s vector of length %d", Rf_type2str(type), l);
    }
}

#define ASSIGN_CHILD(NODE, CHILD, ID)                                       \
    {                                                                       \
        CHILD = rastr_is_orphan(ast, CHILD) ? CHILD                         \
                                            : rastr_node_clone(ast, CHILD); \
        rastr_node_pid_set(ast, CHILD, ID);                                 \
        ptr->node.NODE##_node.CHILD = CHILD;                                \
    }

#define ASSIGN_SEQ_CHILD(NODE, INDEX, CHILD, ID)                            \
    {                                                                       \
        CHILD = rastr_is_orphan(ast, CHILD) ? CHILD                         \
                                            : rastr_node_clone(ast, CHILD); \
        rastr_node_pid_set(ast, CHILD, ID);                                 \
        ptr->node.NODE##_node.seq[INDEX] = CHILD;                           \
    }

struct node_type_syn_t {
    rastr_node_type_t type;
    const char* syn;
};

/*******************************************************************************
 * op
 *******************************************************************************/

node_type_syn_t op_syn[] = {
    {RASTR_OP_PLUS, "+"},          {RASTR_OP_MINUS, "-"},
    {RASTR_OP_MUL, "*"},           {RASTR_OP_DIV, "/"},
    {RASTR_OP_POW, "^"},           {RASTR_OP_POW2, "**"},
    {RASTR_OP_LESS, "<"},          {RASTR_OP_LESS_EQ, "<="},
    {RASTR_OP_GREAT, ">"},         {RASTR_OP_GREAT_EQ, ">="},
    {RASTR_OP_EQ, "=="},           {RASTR_OP_NOT_EQ, "!="},
    {RASTR_OP_NOT, "!"},           {RASTR_OP_AND, "&&"},
    {RASTR_OP_VEC_AND, "&"},       {RASTR_OP_OR, "||"},
    {RASTR_OP_VEC_OR, "|"},        {RASTR_OP_EQ_ASGN, "="},
    {RASTR_OP_LT_ASGN, "<-"},      {RASTR_OP_RT_ASGN, "->"},
    {RASTR_OP_LT_SUP_ASGN, "<<-"}, {RASTR_OP_RT_SUP_ASGN, "->>"},
    {RASTR_OP_COLON_ASGN, ":="},   {RASTR_OP_PIPE_FWD, "|>"},
    {RASTR_OP_PIPE_BIND, "=>"},    {RASTR_OP_PUB_NS, "::"},
    {RASTR_OP_PVT_NS, ":::"},      {RASTR_OP_RANGE, ":"},
    {RASTR_OP_HELP, "?"},          {RASTR_OP_SLOT, "@"},
    {RASTR_OP_FORMULA, "~"},       {RASTR_OP_PART, "$"},
    {RASTR_OP_FN, "function"},     {RASTR_OP_FN2, "\\"},
    {RASTR_OP_WHILE, "while"},     {RASTR_OP_REPEAT, "repeat"},
    {RASTR_OP_FOR, "for"},         {RASTR_OP_IN, "in"},
    {RASTR_OP_IF, "if"},           {RASTR_OP_ELSE, "else"},
    {RASTR_OP_NEXT, "next"},       {RASTR_OP_BREAK, "break"},
    {RASTR_ERR, nullptr}};

rastr_node_t rastr_op_new_unsafe(rastr_ast_t ast,
                                 rastr_node_type_t type,
                                 rastr_node_t gap,
                                 rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.op_node.syn = nullptr;
    int id = ptr->id;

    ASSIGN_CHILD(op, gap, id)
    ASSIGN_CHILD(op, loc, id)

    return pair.node;
}

rastr_node_t rastr_sp_new_unsafe(rastr_ast_t ast,
                                 char* syn,
                                 rastr_node_t gap,
                                 rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_OP_SP);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.op_node.syn = syn;
    int id = ptr->id;

    ASSIGN_CHILD(op, gap, id)
    ASSIGN_CHILD(op, loc, id)

    return pair.node;
}

rastr_node_t rastr_op_new(rastr_ast_t ast,
                          const char* syn,
                          rastr_node_t gap,
                          rastr_node_t loc) {
    if (syn == nullptr) {
        Rf_error("operator syntax cannot be null");
    }

    if (syn[0] == '%') {
        int n = std::strlen(syn);

        if (syn[n] == '%') {
            return rastr_sp_new_unsafe(ast, str_dup(syn, n), gap, loc);
        }
    }

    for (int i = 0;; ++i) {
        const char* syn2 = op_syn[i].syn;

        if (syn2 == nullptr) {
            break;
        }

        if (!strcmp(syn2, syn)) {
            return rastr_op_new_unsafe(ast, op_syn[i].type, gap, loc);
        }
    }

    Rf_error("invalid operator syntax '%s'", syn);
}

SEXP r_rastr_op_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_syn, STRSXP, 1);
    const char* val = chr_get(r_syn, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_op_new(ast, val, gap, loc));
}

const char* rastr_op_syn_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr_op_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    if (ptr->node.op_node.syn != nullptr) {
        return ptr->node.op_node.syn;
    }

    rastr_node_type_t type = ptr->type;

    for (int i = 0;; ++i) {
        rastr_node_type_t op_type = op_syn[i].type;

        if (op_type == type) {
            return op_syn[i].syn;
        }
    }

    Rf_error("invalid operator type '%s'", rastr_node_type_to_string(type));
}

SEXP r_rastr_op_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return chr_vec1(rastr_op_syn_get(ast, node));
}

/*******************************************************************************
 * bkt
 *******************************************************************************/

node_type_syn_t bkt_syn[] = {{RASTR_BKT_LT_RND, "("},
                             {RASTR_BKT_RT_RND, ")"},
                             {RASTR_BKT_LT_CURL, "{"},
                             {RASTR_BKT_RT_CURL, "}"},
                             {RASTR_BKT_LT_SQR, "["},
                             {RASTR_BKT_RT_SQR, "]"},
                             {RASTR_BKT_LT_DBL_SQR, "[["},
                             {RASTR_ERR, nullptr}};

rastr_node_t rastr_bkt_new_unsafe(rastr_ast_t ast,
                                  rastr_node_type_t type,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    rastr_node_ptr_t ptr = pair.ptr;

    int id = ptr->id;

    ASSIGN_CHILD(bkt, gap, id)
    ASSIGN_CHILD(bkt, loc, id)
    return pair.node;
}

rastr_node_t rastr_bkt_new(rastr_ast_t ast,
                           const char* syn,
                           rastr_node_t gap,
                           rastr_node_t loc) {
    if (syn == nullptr) {
        Rf_error("bracket syntax cannot be null");
    }

    for (int i = 0;; ++i) {
        const char* syn2 = bkt_syn[i].syn;

        if (syn2 == nullptr) {
            break;
        }

        if (!strcmp(syn2, syn)) {
            return rastr_bkt_new_unsafe(ast, bkt_syn[i].type, gap, loc);
        }
    }

    Rf_error("invalid bracket syntax '%s'", syn);
}

SEXP r_rastr_bkt_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_syn, STRSXP, 1);
    const char* val = chr_get(r_syn, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_bkt_new(ast, val, gap, loc));
}

const char* rastr_bkt_syn_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr_bkt_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_type_t type = ptr->type;

    for (int i = 0;; ++i) {
        rastr_node_type_t bkt_type = bkt_syn[i].type;

        if (bkt_type == type) {
            return bkt_syn[i].syn;
        }
    }

    Rf_error("invalid bracket type '%s'", rastr_node_type_to_string(type));
}

SEXP r_rastr_bkt_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return chr_vec1(rastr_bkt_syn_get(ast, node));
}

/*******************************************************************************
 * dlmtr
 *******************************************************************************/

node_type_syn_t dlmtr_syn[] = {{RASTR_DLMTR_SCOL, ";"},
                               {RASTR_DLMTR_COM, ","},
                               {RASTR_ERR, nullptr}};

rastr_node_t rastr_dlmtr_new_unsafe(rastr_ast_t ast,
                                    rastr_node_type_t type,
                                    rastr_node_t gap,
                                    rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    rastr_node_ptr_t ptr = pair.ptr;

    int id = ptr->id;
    ASSIGN_CHILD(dlmtr, gap, id)
    ASSIGN_CHILD(dlmtr, loc, id)
    return pair.node;
}

rastr_node_t rastr_dlmtr_new(rastr_ast_t ast,
                             const char* syn,
                             rastr_node_t gap,
                             rastr_node_t loc) {
    if (syn == nullptr) {
        Rf_error("delimiter syntax cannot be null");
    }

    for (int i = 0;; ++i) {
        const char* syn2 = dlmtr_syn[i].syn;

        if (syn2 == nullptr) {
            break;
        }

        if (!strcmp(syn2, syn)) {
            return rastr_dlmtr_new_unsafe(ast, dlmtr_syn[i].type, gap, loc);
        }
    }

    Rf_error("invalid delimiter syntax '%s'", syn);
}

SEXP r_rastr_dlmtr_new(SEXP r_ast, SEXP r_syn, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_syn, STRSXP, 1);
    const char* val = chr_get(r_syn, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_dlmtr_new(ast, val, gap, loc));
}

const char* rastr_dlmtr_syn_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr_dlmtr_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_type_t type = ptr->type;

    for (int i = 0;; ++i) {
        rastr_node_type_t dlmtr_type = dlmtr_syn[i].type;

        if (dlmtr_type == type) {
            return dlmtr_syn[i].syn;
        }
    }

    Rf_error("invalid delimiter type '%s'", rastr_node_type_to_string(type));
}

SEXP r_rastr_dlmtr_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return chr_vec1(rastr_dlmtr_syn_get(ast, node));
}

const char* rastr_null_syn_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr_null_type, node);
    return "NULL";
}

/*******************************************************************************
 * lgl
 *******************************************************************************/

rastr_node_t
rastr_lgl_new(rastr_ast_t ast, int val, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_LGL);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.lgl_node.val = val;

    int id = ptr->id;
    ASSIGN_CHILD(lgl, gap, id)
    ASSIGN_CHILD(lgl, loc, id)
    return pair.node;
}

SEXP r_rastr_lgl_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, LGLSXP, 1);
    int val = lgl_get(r_val, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_lgl_new(ast, val, gap, loc));
}

const char* rastr_lgl_syn_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr_lgl_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    int val = ptr->node.lgl_node.val;

    if (val == NA_LOGICAL) {
        return "NA";
    } else if (val == 1) {
        return "TRUE";
    } else if (val == 0) {
        return "FALSE";
    } else {
        Rf_error("invalid lgl value %d", val);
    }
}

SEXP r_rastr_lgl_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    return chr_vec1(rastr_lgl_syn_get(ast, node));
}

/*******************************************************************************
 * int
 *******************************************************************************/

rastr_node_t rastr_int_new_unsafe(rastr_ast_t ast,
                                  int val,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_INT);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.int_node.val = val;
    ptr->node.int_node.syn = syn;

    int id = ptr->id;
    ASSIGN_CHILD(int, gap, id)
    ASSIGN_CHILD(int, loc, id)
    return pair.node;
}

rastr_node_t
rastr_int_new(rastr_ast_t ast, int val, rastr_node_t gap, rastr_node_t loc) {
    char* syn = nullptr;

    if (val == NA_INTEGER) {
        syn = str_dup("NA_integer_");
    } else {
        std::string rep = std::to_string(val);
        int len = rep.size();
        syn = (char*) malloc_or_fail(sizeof(char) * (len + 2));
        std::strcpy(syn, rep.c_str());
        syn[len] = 'L';
        syn[len + 1] = '\0';
    }

    return rastr_int_new_unsafe(ast, val, syn, gap, loc);
}

SEXP r_rastr_int_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, INTSXP, 1);
    int val = dbl_get(r_val, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_int_new(ast, val, gap, loc));
}

/*******************************************************************************
 * dbl
 *******************************************************************************/

rastr_node_t rastr_dbl_new_unsafe(rastr_ast_t ast,
                                  double val,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_DBL);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.dbl_node.val = val;
    ptr->node.dbl_node.syn = syn;

    int id = ptr->id;
    ASSIGN_CHILD(dbl, gap, id)
    ASSIGN_CHILD(dbl, loc, id)
    return pair.node;
}

rastr_node_t
rastr_dbl_new(rastr_ast_t ast, double val, rastr_node_t gap, rastr_node_t loc) {
    char* syn = nullptr;

    if (val == R_PosInf) {
        syn = str_dup("Inf");
    } else if (R_IsNaN(val)) {
        syn = str_dup("NaN");
    } else if (R_IsNA(val)) {
        syn = str_dup("NA_real_");
    } else {
        std::string rep = std::to_string(val);
        syn = str_dup(rep.c_str(), rep.size());
    }

    return rastr_dbl_new_unsafe(ast, val, syn, gap, loc);
}

SEXP r_rastr_dbl_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, REALSXP, 1);
    double val = dbl_get(r_val, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_dbl_new(ast, val, gap, loc));
}

/*******************************************************************************
 * cpx
 *******************************************************************************/

rastr_node_t rastr_cpx_new_unsafe(rastr_ast_t ast,
                                  Rcomplex val,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_CPX);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.cpx_node.val = val;
    ptr->node.cpx_node.syn = syn;

    int id = ptr->id;
    ASSIGN_CHILD(cpx, gap, id)
    ASSIGN_CHILD(cpx, loc, id)
    return pair.node;
}

rastr_node_t
rastr_cpx_new(rastr_ast_t ast, double img, rastr_node_t gap, rastr_node_t loc) {
    char* syn = nullptr;
    Rcomplex val;

    if (R_IsNA(img)) {
        syn = str_dup("NA_complex_");
        val = Rcomplex{NA_REAL, NA_REAL};
    } else {
        std::string rep = std::to_string(img);
        int len = rep.size();
        syn = str_dup(rep.c_str(), len + 1);
        syn[len] = 'i';
        syn[len + 1] = '\0';
        val = Rcomplex{0, img};
    }

    return rastr_cpx_new_unsafe(ast, val, syn, gap, loc);
}

SEXP r_rastr_cpx_new(SEXP r_ast, SEXP r_img, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_img, REALSXP, 1);
    double img = dbl_get(r_img, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_cpx_new(ast, img, gap, loc));
}

/*******************************************************************************
 * chr
 *******************************************************************************/

rastr_node_t rastr_chr_new_unsafe(rastr_ast_t ast,
                                  char* val,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_CHR);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.chr_node.val = val;
    ptr->node.chr_node.syn = syn;
    int id = ptr->id;
    ASSIGN_CHILD(chr, gap, id)
    ASSIGN_CHILD(chr, loc, id)
    return pair.node;
}

rastr_node_t rastr_chr_new(rastr_ast_t ast,
                           const char* val,
                           rastr_node_t gap,
                           rastr_node_t loc) {
    char* val2 = nullptr;
    char* syn = nullptr;

    if (val == nullptr) {
        syn = str_dup("NA_character_");
    } else {
        int len = std::strlen(val);

        val2 = str_dup(val, len);

        syn = (char*) malloc(sizeof(char) * (len + 3));

        syn[0] = '"';
        std::strcpy(syn + 1, val);
        syn[len + 1] = '"';
        syn[len + 2] = '\0';
    }

    return rastr_chr_new_unsafe(ast, val2, syn, gap, loc);
}

SEXP r_rastr_chr_new(SEXP r_ast, SEXP r_val, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, STRSXP, 1);
    const char* val = chr_get(r_val, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_chr_new(ast, val, gap, loc));
}

/*******************************************************************************
 * sym
 *******************************************************************************/

rastr_node_t rastr_sym_new_unsafe(rastr_ast_t ast,
                                  char* val,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_SYM);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.sym_node.val = val;
    ptr->node.sym_node.syn = syn;
    int id = ptr->id;
    ASSIGN_CHILD(sym, gap, id)
    ASSIGN_CHILD(sym, loc, id)
    return pair.node;
}

rastr_node_t rastr_sym_new(rastr_ast_t ast,
                           const char* val,
                           int quote,
                           rastr_node_t gap,
                           rastr_node_t loc) {
    int len = std::strlen(val);

    char* val2 = str_dup(val, len);

    char* syn = nullptr;

    if (quote) {
        syn = (char*) malloc(sizeof(char) * (len + 3));
        syn[0] = '`';
        std::strcpy(syn + 1, val);
        syn[len + 1] = '`';
        syn[len + 2] = '\0';
    } else {
        syn = val2;
    }

    return rastr_sym_new_unsafe(ast, val2, syn, gap, loc);
}

SEXP r_rastr_sym_new(SEXP r_ast,
                     SEXP r_val,
                     SEXP r_quote,
                     SEXP r_gap,
                     SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, STRSXP, 1);
    const char* val = chr_get(r_val, 0);

    ensure_vec_sexp(r_quote, LGLSXP, 1);
    int quote = lgl_get(r_quote, 0);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_sym_new(ast, val, quote, gap, loc));
}

/*******************************************************************************
 * gap
 *******************************************************************************/

rastr_node_t
rastr_gap_new_unsafe(rastr_ast_t ast, char* val, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_GAP);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.gap_node.val = val;

    int id = ptr->id;
    ASSIGN_CHILD(gap, loc, id)
    return pair.node;
}

rastr_node_t rastr_gap_new(rastr_ast_t ast, const char* val, rastr_node_t loc) {
    char* val2 = str_dup(val);
    return rastr_gap_new_unsafe(ast, val2, loc);
}

SEXP r_rastr_gap_new(SEXP r_ast, SEXP r_val, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_val, STRSXP, 1);
    const char* val = chr_get(r_val, 0);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_gap_new(ast, val, loc));
}

/*******************************************************************************
 * beg
 *******************************************************************************/

rastr_node_t
rastr_beg_new_unsafe(rastr_ast_t ast, char* bom, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_BEG);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.beg_node.bom = bom;

    int id = ptr->id;
    ASSIGN_CHILD(beg, loc, id)
    return pair.node;
}

rastr_node_t rastr_beg_new(rastr_ast_t ast, const char* bom, rastr_node_t loc) {
    char* bom2 = str_dup(bom);
    return rastr_beg_new_unsafe(ast, bom2, loc);
}

SEXP r_rastr_beg_new(SEXP r_ast, SEXP r_bom, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_bom, STRSXP, 1);
    const char* bom = chr_get(r_bom, 0);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_beg_new(ast, bom, loc));
}

/*******************************************************************************
 * err
 *******************************************************************************/

rastr_node_t
rastr_err_new_unsafe(rastr_ast_t ast, char* msg, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_ERR);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.err_node.msg = msg;

    int id = ptr->id;
    ASSIGN_CHILD(err, loc, id)
    return pair.node;
}

rastr_node_t rastr_err_new(rastr_ast_t ast, const char* msg, rastr_node_t loc) {
    char* msg2 = str_dup(msg);
    return rastr_err_new_unsafe(ast, msg2, loc);
}

SEXP r_rastr_err_new(SEXP r_ast, SEXP r_msg, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_vec_sexp(r_msg, STRSXP, 1);
    const char* msg = chr_get(r_msg, 0);

    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    return rastr_node_wrap(rastr_err_new(ast, msg, loc));
}

/*******************************************************************************
 * loc
 *******************************************************************************/

rastr_node_t rastr_loc_new(rastr_ast_t ast,
                           int lrow,
                           int lcol,
                           int lchr,
                           int lbyte,
                           int rrow,
                           int rcol,
                           int rchr,
                           int rbyte) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_LOC);
    rastr_node_ptr_t ptr = pair.ptr;

    ptr->node.loc_node.lrow = lrow;
    ptr->node.loc_node.lcol = lcol;
    ptr->node.loc_node.lchr = lchr;
    ptr->node.loc_node.lbyte = lbyte;
    ptr->node.loc_node.rrow = rrow;
    ptr->node.loc_node.rcol = rcol;
    ptr->node.loc_node.rchr = rchr;
    ptr->node.loc_node.rbyte = rbyte;

    return pair.node;
}

// pred
int rastr_lit_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr->type;
    return (type == RASTR_NULL || type == RASTR_LGL || type == RASTR_DBL ||
            type == RASTR_INT || type == RASTR_CPX || type == RASTR_CHR ||
            type == RASTR_SYM);
}

SEXP r_rastr_lit_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_lit_type(ast, node);
    return lgl_vec1(result);
}

#include "autogen_node_impl.h"
