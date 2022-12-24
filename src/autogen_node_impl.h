/*******************************************************************************
* op
*******************************************************************************/
// pred
int rastr_op_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_OP_SP || type == RASTR_OP_PLUS || type == RASTR_OP_MINUS || type == RASTR_OP_MUL || type == RASTR_OP_DIV || type == RASTR_OP_POW || type == RASTR_OP_POW2 || type == RASTR_OP_LESS || type == RASTR_OP_LESS_EQ || type == RASTR_OP_GREAT || type == RASTR_OP_GREAT_EQ || type == RASTR_OP_EQ || type == RASTR_OP_NOT_EQ || type == RASTR_OP_NOT || type == RASTR_OP_AND || type == RASTR_OP_VEC_AND || type == RASTR_OP_OR || type == RASTR_OP_VEC_OR || type == RASTR_OP_EQ_ASGN || type == RASTR_OP_LT_ASGN || type == RASTR_OP_RT_ASGN || type == RASTR_OP_LT_SUP_ASGN || type == RASTR_OP_RT_SUP_ASGN || type == RASTR_OP_COLON_ASGN || type == RASTR_OP_PIPE_FWD || type == RASTR_OP_PIPE_BIND || type == RASTR_OP_PUB_NS || type == RASTR_OP_PVT_NS || type == RASTR_OP_RANGE || type == RASTR_OP_HELP || type == RASTR_OP_SLOT || type == RASTR_OP_FORMULA || type == RASTR_OP_PART || type == RASTR_OP_FN || type == RASTR_OP_FN2 || type == RASTR_OP_WHILE || type == RASTR_OP_REPEAT || type == RASTR_OP_FOR || type == RASTR_OP_IN || type == RASTR_OP_IF || type == RASTR_OP_ELSE || type == RASTR_OP_NEXT || type == RASTR_OP_BREAK);
}

SEXP r_rastr_op_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_op_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_op_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_op_type, node);
    return ptr->node.op_node.gap;
}

SEXP r_rastr_op_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_op_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_op_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_op_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.op_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(op, gap, id)

    return result;
}

SEXP r_rastr_op_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_op_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_op_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_op_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_op_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_op_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_op_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_op_type, node);
    return ptr->node.op_node.loc;
}

SEXP r_rastr_op_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_op_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* dlmtr
*******************************************************************************/
// pred
int rastr_dlmtr_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_DLMTR_SCOL || type == RASTR_DLMTR_COM);
}

SEXP r_rastr_dlmtr_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_dlmtr_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_dlmtr_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dlmtr_type, node);
    return ptr->node.dlmtr_node.gap;
}

SEXP r_rastr_dlmtr_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtr_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dlmtr_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_dlmtr_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dlmtr_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dlmtr, gap, id)

    return result;
}

SEXP r_rastr_dlmtr_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_dlmtr_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_dlmtr_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_dlmtr_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dlmtr_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_dlmtr_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_dlmtr_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dlmtr_type, node);
    return ptr->node.dlmtr_node.loc;
}

SEXP r_rastr_dlmtr_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtr_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* bkt
*******************************************************************************/
// pred
int rastr_bkt_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_BKT_LT_RND || type == RASTR_BKT_RT_RND || type == RASTR_BKT_LT_CURL || type == RASTR_BKT_RT_CURL || type == RASTR_BKT_LT_SQR || type == RASTR_BKT_RT_SQR || type == RASTR_BKT_LT_DBL_SQR);
}

SEXP r_rastr_bkt_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_bkt_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_bkt_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_bkt_type, node);
    return ptr->node.bkt_node.gap;
}

SEXP r_rastr_bkt_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_bkt_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_bkt_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_bkt_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.bkt_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(bkt, gap, id)

    return result;
}

SEXP r_rastr_bkt_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_bkt_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_bkt_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_bkt_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_bkt_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_bkt_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_bkt_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_bkt_type, node);
    return ptr->node.bkt_node.loc;
}

SEXP r_rastr_bkt_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_bkt_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* null
*******************************************************************************/
rastr_node_t rastr_null_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_NULL);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(null, gap, id)
    ASSIGN_CHILD(null, loc, id)

    return pair.node;
}

SEXP r_rastr_null_new(SEXP r_ast, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);
    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    rastr_node_t result = rastr_null_new(ast, gap, loc);
    return rastr_node_wrap(result);
}

// pred
int rastr_null_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_NULL);
}

SEXP r_rastr_null_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_null_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_null_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_null_type, node);
    return ptr->node.null_node.gap;
}

SEXP r_rastr_null_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_null_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_null_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_null_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.null_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(null, gap, id)

    return result;
}

SEXP r_rastr_null_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_null_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_null_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_null_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_null_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_null_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_null_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_null_type, node);
    return ptr->node.null_node.loc;
}

SEXP r_rastr_null_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_null_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* lgl
*******************************************************************************/
// pred
int rastr_lgl_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_LGL);
}

SEXP r_rastr_lgl_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_lgl_type(ast, node);
    return lgl_vec1(result);
}
/* val ************************************************************************/
// get
int rastr_lgl_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_lgl_type, node);
    return ptr->node.lgl_node.val;
}

SEXP r_rastr_lgl_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_lgl_val_get(ast, node);
    return lgl_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_lgl_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_lgl_type, node);
    return ptr->node.lgl_node.gap;
}

SEXP r_rastr_lgl_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_lgl_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_lgl_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_lgl_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.lgl_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(lgl, gap, id)

    return result;
}

SEXP r_rastr_lgl_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_lgl_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_lgl_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_lgl_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_lgl_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_lgl_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_lgl_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_lgl_type, node);
    return ptr->node.lgl_node.loc;
}

SEXP r_rastr_lgl_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_lgl_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* int
*******************************************************************************/
// pred
int rastr_int_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_INT);
}

SEXP r_rastr_int_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_int_type(ast, node);
    return lgl_vec1(result);
}
/* syn ************************************************************************/
// get
const char* rastr_int_syn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_int_type, node);
    return ptr->node.int_node.syn;
}

SEXP r_rastr_int_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_int_syn_get(ast, node);
    return chr_vec1(result);
}


/* val ************************************************************************/
// get
int rastr_int_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_int_type, node);
    return ptr->node.int_node.val;
}

SEXP r_rastr_int_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_int_val_get(ast, node);
    return int_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_int_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_int_type, node);
    return ptr->node.int_node.gap;
}

SEXP r_rastr_int_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_int_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_int_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_int_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.int_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(int, gap, id)

    return result;
}

SEXP r_rastr_int_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_int_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_int_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_int_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_int_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_int_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_int_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_int_type, node);
    return ptr->node.int_node.loc;
}

SEXP r_rastr_int_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_int_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* dbl
*******************************************************************************/
// pred
int rastr_dbl_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_DBL);
}

SEXP r_rastr_dbl_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_dbl_type(ast, node);
    return lgl_vec1(result);
}
/* syn ************************************************************************/
// get
const char* rastr_dbl_syn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dbl_type, node);
    return ptr->node.dbl_node.syn;
}

SEXP r_rastr_dbl_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_dbl_syn_get(ast, node);
    return chr_vec1(result);
}


/* val ************************************************************************/
// get
double rastr_dbl_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dbl_type, node);
    return ptr->node.dbl_node.val;
}

SEXP r_rastr_dbl_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    double result = rastr_dbl_val_get(ast, node);
    return dbl_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_dbl_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dbl_type, node);
    return ptr->node.dbl_node.gap;
}

SEXP r_rastr_dbl_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dbl_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dbl_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_dbl_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dbl_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dbl, gap, id)

    return result;
}

SEXP r_rastr_dbl_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_dbl_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_dbl_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_dbl_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dbl_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_dbl_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_dbl_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dbl_type, node);
    return ptr->node.dbl_node.loc;
}

SEXP r_rastr_dbl_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dbl_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* cpx
*******************************************************************************/
// pred
int rastr_cpx_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_CPX);
}

SEXP r_rastr_cpx_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_cpx_type(ast, node);
    return lgl_vec1(result);
}
/* syn ************************************************************************/
// get
const char* rastr_cpx_syn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cpx_type, node);
    return ptr->node.cpx_node.syn;
}

SEXP r_rastr_cpx_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_cpx_syn_get(ast, node);
    return chr_vec1(result);
}


/* val ************************************************************************/
// get
Rcomplex rastr_cpx_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cpx_type, node);
    return ptr->node.cpx_node.val;
}

SEXP r_rastr_cpx_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    Rcomplex result = rastr_cpx_val_get(ast, node);
    return cpx_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_cpx_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cpx_type, node);
    return ptr->node.cpx_node.gap;
}

SEXP r_rastr_cpx_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cpx_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_cpx_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_cpx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.cpx_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(cpx, gap, id)

    return result;
}

SEXP r_rastr_cpx_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_cpx_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_cpx_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_cpx_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_cpx_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_cpx_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_cpx_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cpx_type, node);
    return ptr->node.cpx_node.loc;
}

SEXP r_rastr_cpx_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cpx_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* chr
*******************************************************************************/
// pred
int rastr_chr_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_CHR);
}

SEXP r_rastr_chr_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_chr_type(ast, node);
    return lgl_vec1(result);
}
/* syn ************************************************************************/
// get
const char* rastr_chr_syn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_chr_type, node);
    return ptr->node.chr_node.syn;
}

SEXP r_rastr_chr_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_chr_syn_get(ast, node);
    return chr_vec1(result);
}


/* val ************************************************************************/
// get
const char* rastr_chr_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_chr_type, node);
    return ptr->node.chr_node.val;
}

SEXP r_rastr_chr_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_chr_val_get(ast, node);
    return chr_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_chr_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_chr_type, node);
    return ptr->node.chr_node.gap;
}

SEXP r_rastr_chr_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_chr_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_chr_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_chr_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.chr_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(chr, gap, id)

    return result;
}

SEXP r_rastr_chr_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_chr_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_chr_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_chr_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_chr_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_chr_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_chr_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_chr_type, node);
    return ptr->node.chr_node.loc;
}

SEXP r_rastr_chr_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_chr_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* sym
*******************************************************************************/
// pred
int rastr_sym_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_SYM);
}

SEXP r_rastr_sym_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_sym_type(ast, node);
    return lgl_vec1(result);
}
/* syn ************************************************************************/
// get
const char* rastr_sym_syn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sym_type, node);
    return ptr->node.sym_node.syn;
}

SEXP r_rastr_sym_syn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_sym_syn_get(ast, node);
    return chr_vec1(result);
}


/* val ************************************************************************/
// get
const char* rastr_sym_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sym_type, node);
    return ptr->node.sym_node.val;
}

SEXP r_rastr_sym_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_sym_val_get(ast, node);
    return chr_vec1(result);
}


/* gap ************************************************************************/
// get
rastr_node_t rastr_sym_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sym_type, node);
    return ptr->node.sym_node.gap;
}

SEXP r_rastr_sym_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sym_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_sym_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_sym_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.sym_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(sym, gap, id)

    return result;
}

SEXP r_rastr_sym_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_sym_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_sym_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_sym_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_sym_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_sym_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_sym_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sym_type, node);
    return ptr->node.sym_node.loc;
}

SEXP r_rastr_sym_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sym_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* blk
*******************************************************************************/
rastr_node_t rastr_blk_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t exprs, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_BLK);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(blk, lbkt, id)
    ASSIGN_CHILD(blk, exprs, id)
    ASSIGN_CHILD(blk, rbkt, id)

    return pair.node;
}

SEXP r_rastr_blk_new(SEXP r_ast, SEXP r_lbkt, SEXP r_exprs, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_blk_new(ast, lbkt, exprs, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_blk_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_BLK);
}

SEXP r_rastr_blk_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_blk_type(ast, node);
    return lgl_vec1(result);
}
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_blk_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_blk_type, node);
    return ptr->node.blk_node.lbkt;
}

SEXP r_rastr_blk_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_blk_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_blk_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_blk_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.blk_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(blk, lbkt, id)

    return result;
}

SEXP r_rastr_blk_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_blk_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_blk_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_blk_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_blk_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_blk_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* exprs **********************************************************************/
// get
rastr_node_t rastr_blk_exprs_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_blk_type, node);
    return ptr->node.blk_node.exprs;
}

SEXP r_rastr_blk_exprs_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_blk_exprs_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_blk_exprs_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs) {
    ENSURE_NODE_TYPE(rastr_blk_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.blk_node.exprs;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(blk, exprs, id)

    return result;
}

SEXP r_rastr_blk_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_exprs) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);

    rastr_node_t result = rastr_blk_exprs_rep(ast, node, exprs);
    return rastr_node_wrap(result);
}
// set
void rastr_blk_exprs_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs) {
    rastr_node_t result = rastr_blk_exprs_rep(ast, node, exprs);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_blk_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_exprs) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);

    rastr_blk_exprs_set(ast, node, exprs);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_blk_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_blk_type, node);
    return ptr->node.blk_node.rbkt;
}

SEXP r_rastr_blk_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_blk_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_blk_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_blk_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.blk_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(blk, rbkt, id)

    return result;
}

SEXP r_rastr_blk_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_blk_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_blk_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_blk_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_blk_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_blk_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* grp
*******************************************************************************/
rastr_node_t rastr_grp_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t expr, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_GRP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(grp, lbkt, id)
    ASSIGN_CHILD(grp, expr, id)
    ASSIGN_CHILD(grp, rbkt, id)

    return pair.node;
}

SEXP r_rastr_grp_new(SEXP r_ast, SEXP r_lbkt, SEXP r_expr, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_grp_new(ast, lbkt, expr, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_grp_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_GRP);
}

SEXP r_rastr_grp_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_grp_type(ast, node);
    return lgl_vec1(result);
}
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_grp_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_grp_type, node);
    return ptr->node.grp_node.lbkt;
}

SEXP r_rastr_grp_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_grp_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_grp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.grp_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(grp, lbkt, id)

    return result;
}

SEXP r_rastr_grp_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_grp_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_grp_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_grp_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_grp_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_grp_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_grp_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_grp_type, node);
    return ptr->node.grp_node.expr;
}

SEXP r_rastr_grp_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_grp_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_grp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.grp_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(grp, expr, id)

    return result;
}

SEXP r_rastr_grp_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_grp_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_grp_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_grp_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_grp_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_grp_expr_set(ast, node, expr);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_grp_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_grp_type, node);
    return ptr->node.grp_node.rbkt;
}

SEXP r_rastr_grp_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_grp_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_grp_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_grp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.grp_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(grp, rbkt, id)

    return result;
}

SEXP r_rastr_grp_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_grp_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_grp_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_grp_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_grp_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_grp_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* nuop
*******************************************************************************/
rastr_node_t rastr_nuop_new(rastr_ast_t ast, rastr_node_t op) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_NUOP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(nuop, op, id)

    return pair.node;
}

SEXP r_rastr_nuop_new(SEXP r_ast, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_nuop_new(ast, op);
    return rastr_node_wrap(result);
}

// pred
int rastr_nuop_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_NUOP);
}

SEXP r_rastr_nuop_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_nuop_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_nuop_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_nuop_type, node);
    return ptr->node.nuop_node.op;
}

SEXP r_rastr_nuop_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_nuop_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_nuop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_nuop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.nuop_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(nuop, op, id)

    return result;
}

SEXP r_rastr_nuop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_nuop_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_nuop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_nuop_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_nuop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_nuop_op_set(ast, node, op);
    return R_NilValue;
}




/*******************************************************************************
* unop
*******************************************************************************/
rastr_node_t rastr_unop_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_UNOP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(unop, op, id)
    ASSIGN_CHILD(unop, expr, id)

    return pair.node;
}

SEXP r_rastr_unop_new(SEXP r_ast, SEXP r_op, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_unop_new(ast, op, expr);
    return rastr_node_wrap(result);
}

// pred
int rastr_unop_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_UNOP);
}

SEXP r_rastr_unop_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_unop_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_unop_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_unop_type, node);
    return ptr->node.unop_node.op;
}

SEXP r_rastr_unop_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_unop_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_unop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_unop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.unop_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(unop, op, id)

    return result;
}

SEXP r_rastr_unop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_unop_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_unop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_unop_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_unop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_unop_op_set(ast, node, op);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_unop_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_unop_type, node);
    return ptr->node.unop_node.expr;
}

SEXP r_rastr_unop_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_unop_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_unop_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_unop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.unop_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(unop, expr, id)

    return result;
}

SEXP r_rastr_unop_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_unop_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_unop_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_unop_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_unop_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_unop_expr_set(ast, node, expr);
    return R_NilValue;
}




/*******************************************************************************
* binop
*******************************************************************************/
rastr_node_t rastr_binop_new(rastr_ast_t ast, rastr_node_t lexpr, rastr_node_t op, rastr_node_t rexpr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_BINOP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(binop, lexpr, id)
    ASSIGN_CHILD(binop, op, id)
    ASSIGN_CHILD(binop, rexpr, id)

    return pair.node;
}

SEXP r_rastr_binop_new(SEXP r_ast, SEXP r_lexpr, SEXP r_op, SEXP r_rexpr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_lexpr);
    rastr_node_t lexpr = rastr_node_unwrap(r_lexpr);
    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_rexpr);
    rastr_node_t rexpr = rastr_node_unwrap(r_rexpr);

    rastr_node_t result = rastr_binop_new(ast, lexpr, op, rexpr);
    return rastr_node_wrap(result);
}

// pred
int rastr_binop_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_BINOP);
}

SEXP r_rastr_binop_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_binop_type(ast, node);
    return lgl_vec1(result);
}
/* lexpr **********************************************************************/
// get
rastr_node_t rastr_binop_lexpr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_binop_type, node);
    return ptr->node.binop_node.lexpr;
}

SEXP r_rastr_binop_lexpr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_lexpr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_binop_lexpr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lexpr) {
    ENSURE_NODE_TYPE(rastr_binop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.binop_node.lexpr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(binop, lexpr, id)

    return result;
}

SEXP r_rastr_binop_lexpr_rep(SEXP r_ast, SEXP r_node, SEXP r_lexpr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lexpr);
    rastr_node_t lexpr = rastr_node_unwrap(r_lexpr);

    rastr_node_t result = rastr_binop_lexpr_rep(ast, node, lexpr);
    return rastr_node_wrap(result);
}
// set
void rastr_binop_lexpr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lexpr) {
    rastr_node_t result = rastr_binop_lexpr_rep(ast, node, lexpr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_binop_lexpr_set(SEXP r_ast, SEXP r_node, SEXP r_lexpr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lexpr);
    rastr_node_t lexpr = rastr_node_unwrap(r_lexpr);

    rastr_binop_lexpr_set(ast, node, lexpr);
    return R_NilValue;
}


/* op *************************************************************************/
// get
rastr_node_t rastr_binop_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_binop_type, node);
    return ptr->node.binop_node.op;
}

SEXP r_rastr_binop_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_binop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_binop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.binop_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(binop, op, id)

    return result;
}

SEXP r_rastr_binop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_binop_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_binop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_binop_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_binop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_binop_op_set(ast, node, op);
    return R_NilValue;
}


/* rexpr **********************************************************************/
// get
rastr_node_t rastr_binop_rexpr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_binop_type, node);
    return ptr->node.binop_node.rexpr;
}

SEXP r_rastr_binop_rexpr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_binop_rexpr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_binop_rexpr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rexpr) {
    ENSURE_NODE_TYPE(rastr_binop_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.binop_node.rexpr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(binop, rexpr, id)

    return result;
}

SEXP r_rastr_binop_rexpr_rep(SEXP r_ast, SEXP r_node, SEXP r_rexpr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rexpr);
    rastr_node_t rexpr = rastr_node_unwrap(r_rexpr);

    rastr_node_t result = rastr_binop_rexpr_rep(ast, node, rexpr);
    return rastr_node_wrap(result);
}
// set
void rastr_binop_rexpr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rexpr) {
    rastr_node_t result = rastr_binop_rexpr_rep(ast, node, rexpr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_binop_rexpr_set(SEXP r_ast, SEXP r_node, SEXP r_rexpr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rexpr);
    rastr_node_t rexpr = rastr_node_unwrap(r_rexpr);

    rastr_binop_rexpr_set(ast, node, rexpr);
    return R_NilValue;
}




/*******************************************************************************
* rlp
*******************************************************************************/
rastr_node_t rastr_rlp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_RLP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(rlp, op, id)
    ASSIGN_CHILD(rlp, body, id)

    return pair.node;
}

SEXP r_rastr_rlp_new(SEXP r_ast, SEXP r_op, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_rlp_new(ast, op, body);
    return rastr_node_wrap(result);
}

// pred
int rastr_rlp_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_RLP);
}

SEXP r_rastr_rlp_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_rlp_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_rlp_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_rlp_type, node);
    return ptr->node.rlp_node.op;
}

SEXP r_rastr_rlp_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_rlp_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_rlp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_rlp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.rlp_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(rlp, op, id)

    return result;
}

SEXP r_rastr_rlp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_rlp_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_rlp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_rlp_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_rlp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_rlp_op_set(ast, node, op);
    return R_NilValue;
}


/* body ***********************************************************************/
// get
rastr_node_t rastr_rlp_body_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_rlp_type, node);
    return ptr->node.rlp_node.body;
}

SEXP r_rastr_rlp_body_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_rlp_body_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_rlp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    ENSURE_NODE_TYPE(rastr_rlp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.rlp_node.body;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(rlp, body, id)

    return result;
}

SEXP r_rastr_rlp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_rlp_body_rep(ast, node, body);
    return rastr_node_wrap(result);
}
// set
void rastr_rlp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    rastr_node_t result = rastr_rlp_body_rep(ast, node, body);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_rlp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_rlp_body_set(ast, node, body);
    return R_NilValue;
}




/*******************************************************************************
* wlp
*******************************************************************************/
rastr_node_t rastr_wlp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t cond, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_WLP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(wlp, op, id)
    ASSIGN_CHILD(wlp, cond, id)
    ASSIGN_CHILD(wlp, body, id)

    return pair.node;
}

SEXP r_rastr_wlp_new(SEXP r_ast, SEXP r_op, SEXP r_cond, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);
    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_wlp_new(ast, op, cond, body);
    return rastr_node_wrap(result);
}

// pred
int rastr_wlp_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_WLP);
}

SEXP r_rastr_wlp_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_wlp_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_wlp_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_wlp_type, node);
    return ptr->node.wlp_node.op;
}

SEXP r_rastr_wlp_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_wlp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_wlp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.wlp_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(wlp, op, id)

    return result;
}

SEXP r_rastr_wlp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_wlp_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_wlp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_wlp_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_wlp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_wlp_op_set(ast, node, op);
    return R_NilValue;
}


/* cond ***********************************************************************/
// get
rastr_node_t rastr_wlp_cond_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_wlp_type, node);
    return ptr->node.wlp_node.cond;
}

SEXP r_rastr_wlp_cond_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_cond_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_wlp_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    ENSURE_NODE_TYPE(rastr_wlp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.wlp_node.cond;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(wlp, cond, id)

    return result;
}

SEXP r_rastr_wlp_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_node_t result = rastr_wlp_cond_rep(ast, node, cond);
    return rastr_node_wrap(result);
}
// set
void rastr_wlp_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    rastr_node_t result = rastr_wlp_cond_rep(ast, node, cond);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_wlp_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_wlp_cond_set(ast, node, cond);
    return R_NilValue;
}


/* body ***********************************************************************/
// get
rastr_node_t rastr_wlp_body_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_wlp_type, node);
    return ptr->node.wlp_node.body;
}

SEXP r_rastr_wlp_body_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_wlp_body_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_wlp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    ENSURE_NODE_TYPE(rastr_wlp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.wlp_node.body;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(wlp, body, id)

    return result;
}

SEXP r_rastr_wlp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_wlp_body_rep(ast, node, body);
    return rastr_node_wrap(result);
}
// set
void rastr_wlp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    rastr_node_t result = rastr_wlp_body_rep(ast, node, body);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_wlp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_wlp_body_set(ast, node, body);
    return R_NilValue;
}




/*******************************************************************************
* flp
*******************************************************************************/
rastr_node_t rastr_flp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t iter, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_FLP);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(flp, op, id)
    ASSIGN_CHILD(flp, iter, id)
    ASSIGN_CHILD(flp, body, id)

    return pair.node;
}

SEXP r_rastr_flp_new(SEXP r_ast, SEXP r_op, SEXP r_iter, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_iter);
    rastr_node_t iter = rastr_node_unwrap(r_iter);
    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_flp_new(ast, op, iter, body);
    return rastr_node_wrap(result);
}

// pred
int rastr_flp_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_FLP);
}

SEXP r_rastr_flp_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_flp_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_flp_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_flp_type, node);
    return ptr->node.flp_node.op;
}

SEXP r_rastr_flp_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_flp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_flp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.flp_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(flp, op, id)

    return result;
}

SEXP r_rastr_flp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_flp_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_flp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_flp_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_flp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_flp_op_set(ast, node, op);
    return R_NilValue;
}


/* iter ***********************************************************************/
// get
rastr_node_t rastr_flp_iter_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_flp_type, node);
    return ptr->node.flp_node.iter;
}

SEXP r_rastr_flp_iter_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_iter_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_flp_iter_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iter) {
    ENSURE_NODE_TYPE(rastr_flp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.flp_node.iter;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(flp, iter, id)

    return result;
}

SEXP r_rastr_flp_iter_rep(SEXP r_ast, SEXP r_node, SEXP r_iter) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iter);
    rastr_node_t iter = rastr_node_unwrap(r_iter);

    rastr_node_t result = rastr_flp_iter_rep(ast, node, iter);
    return rastr_node_wrap(result);
}
// set
void rastr_flp_iter_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iter) {
    rastr_node_t result = rastr_flp_iter_rep(ast, node, iter);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_flp_iter_set(SEXP r_ast, SEXP r_node, SEXP r_iter) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iter);
    rastr_node_t iter = rastr_node_unwrap(r_iter);

    rastr_flp_iter_set(ast, node, iter);
    return R_NilValue;
}


/* body ***********************************************************************/
// get
rastr_node_t rastr_flp_body_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_flp_type, node);
    return ptr->node.flp_node.body;
}

SEXP r_rastr_flp_body_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_flp_body_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_flp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    ENSURE_NODE_TYPE(rastr_flp_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.flp_node.body;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(flp, body, id)

    return result;
}

SEXP r_rastr_flp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_flp_body_rep(ast, node, body);
    return rastr_node_wrap(result);
}
// set
void rastr_flp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    rastr_node_t result = rastr_flp_body_rep(ast, node, body);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_flp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_flp_body_set(ast, node, body);
    return R_NilValue;
}




/*******************************************************************************
* icond
*******************************************************************************/
rastr_node_t rastr_icond_new(rastr_ast_t ast, rastr_node_t iop, rastr_node_t cond, rastr_node_t ibody) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_ICOND);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(icond, iop, id)
    ASSIGN_CHILD(icond, cond, id)
    ASSIGN_CHILD(icond, ibody, id)

    return pair.node;
}

SEXP r_rastr_icond_new(SEXP r_ast, SEXP r_iop, SEXP r_cond, SEXP r_ibody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);
    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);
    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);

    rastr_node_t result = rastr_icond_new(ast, iop, cond, ibody);
    return rastr_node_wrap(result);
}

// pred
int rastr_icond_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_ICOND);
}

SEXP r_rastr_icond_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_icond_type(ast, node);
    return lgl_vec1(result);
}
/* iop ************************************************************************/
// get
rastr_node_t rastr_icond_iop_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_icond_type, node);
    return ptr->node.icond_node.iop;
}

SEXP r_rastr_icond_iop_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icond_iop_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_icond_iop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop) {
    ENSURE_NODE_TYPE(rastr_icond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.icond_node.iop;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(icond, iop, id)

    return result;
}

SEXP r_rastr_icond_iop_rep(SEXP r_ast, SEXP r_node, SEXP r_iop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);

    rastr_node_t result = rastr_icond_iop_rep(ast, node, iop);
    return rastr_node_wrap(result);
}
// set
void rastr_icond_iop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop) {
    rastr_node_t result = rastr_icond_iop_rep(ast, node, iop);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_icond_iop_set(SEXP r_ast, SEXP r_node, SEXP r_iop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);

    rastr_icond_iop_set(ast, node, iop);
    return R_NilValue;
}


/* cond ***********************************************************************/
// get
rastr_node_t rastr_icond_cond_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_icond_type, node);
    return ptr->node.icond_node.cond;
}

SEXP r_rastr_icond_cond_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icond_cond_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_icond_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    ENSURE_NODE_TYPE(rastr_icond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.icond_node.cond;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(icond, cond, id)

    return result;
}

SEXP r_rastr_icond_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_node_t result = rastr_icond_cond_rep(ast, node, cond);
    return rastr_node_wrap(result);
}
// set
void rastr_icond_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    rastr_node_t result = rastr_icond_cond_rep(ast, node, cond);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_icond_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_icond_cond_set(ast, node, cond);
    return R_NilValue;
}


/* ibody **********************************************************************/
// get
rastr_node_t rastr_icond_ibody_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_icond_type, node);
    return ptr->node.icond_node.ibody;
}

SEXP r_rastr_icond_ibody_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_icond_ibody_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_icond_ibody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody) {
    ENSURE_NODE_TYPE(rastr_icond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.icond_node.ibody;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(icond, ibody, id)

    return result;
}

SEXP r_rastr_icond_ibody_rep(SEXP r_ast, SEXP r_node, SEXP r_ibody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);

    rastr_node_t result = rastr_icond_ibody_rep(ast, node, ibody);
    return rastr_node_wrap(result);
}
// set
void rastr_icond_ibody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody) {
    rastr_node_t result = rastr_icond_ibody_rep(ast, node, ibody);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_icond_ibody_set(SEXP r_ast, SEXP r_node, SEXP r_ibody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);

    rastr_icond_ibody_set(ast, node, ibody);
    return R_NilValue;
}




/*******************************************************************************
* iecond
*******************************************************************************/
rastr_node_t rastr_iecond_new(rastr_ast_t ast, rastr_node_t iop, rastr_node_t cond, rastr_node_t ibody, rastr_node_t eop, rastr_node_t ebody) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_IECOND);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(iecond, iop, id)
    ASSIGN_CHILD(iecond, cond, id)
    ASSIGN_CHILD(iecond, ibody, id)
    ASSIGN_CHILD(iecond, eop, id)
    ASSIGN_CHILD(iecond, ebody, id)

    return pair.node;
}

SEXP r_rastr_iecond_new(SEXP r_ast, SEXP r_iop, SEXP r_cond, SEXP r_ibody, SEXP r_eop, SEXP r_ebody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);
    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);
    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);
    ensure_node_class(r_eop);
    rastr_node_t eop = rastr_node_unwrap(r_eop);
    ensure_node_class(r_ebody);
    rastr_node_t ebody = rastr_node_unwrap(r_ebody);

    rastr_node_t result = rastr_iecond_new(ast, iop, cond, ibody, eop, ebody);
    return rastr_node_wrap(result);
}

// pred
int rastr_iecond_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_IECOND);
}

SEXP r_rastr_iecond_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_iecond_type(ast, node);
    return lgl_vec1(result);
}
/* iop ************************************************************************/
// get
rastr_node_t rastr_iecond_iop_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iecond_type, node);
    return ptr->node.iecond_node.iop;
}

SEXP r_rastr_iecond_iop_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecond_iop_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iecond_iop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop) {
    ENSURE_NODE_TYPE(rastr_iecond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iecond_node.iop;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iecond, iop, id)

    return result;
}

SEXP r_rastr_iecond_iop_rep(SEXP r_ast, SEXP r_node, SEXP r_iop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);

    rastr_node_t result = rastr_iecond_iop_rep(ast, node, iop);
    return rastr_node_wrap(result);
}
// set
void rastr_iecond_iop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop) {
    rastr_node_t result = rastr_iecond_iop_rep(ast, node, iop);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iecond_iop_set(SEXP r_ast, SEXP r_node, SEXP r_iop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_iop);
    rastr_node_t iop = rastr_node_unwrap(r_iop);

    rastr_iecond_iop_set(ast, node, iop);
    return R_NilValue;
}


/* cond ***********************************************************************/
// get
rastr_node_t rastr_iecond_cond_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iecond_type, node);
    return ptr->node.iecond_node.cond;
}

SEXP r_rastr_iecond_cond_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecond_cond_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iecond_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    ENSURE_NODE_TYPE(rastr_iecond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iecond_node.cond;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iecond, cond, id)

    return result;
}

SEXP r_rastr_iecond_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_node_t result = rastr_iecond_cond_rep(ast, node, cond);
    return rastr_node_wrap(result);
}
// set
void rastr_iecond_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond) {
    rastr_node_t result = rastr_iecond_cond_rep(ast, node, cond);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iecond_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_cond);
    rastr_node_t cond = rastr_node_unwrap(r_cond);

    rastr_iecond_cond_set(ast, node, cond);
    return R_NilValue;
}


/* ibody **********************************************************************/
// get
rastr_node_t rastr_iecond_ibody_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iecond_type, node);
    return ptr->node.iecond_node.ibody;
}

SEXP r_rastr_iecond_ibody_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecond_ibody_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iecond_ibody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody) {
    ENSURE_NODE_TYPE(rastr_iecond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iecond_node.ibody;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iecond, ibody, id)

    return result;
}

SEXP r_rastr_iecond_ibody_rep(SEXP r_ast, SEXP r_node, SEXP r_ibody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);

    rastr_node_t result = rastr_iecond_ibody_rep(ast, node, ibody);
    return rastr_node_wrap(result);
}
// set
void rastr_iecond_ibody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody) {
    rastr_node_t result = rastr_iecond_ibody_rep(ast, node, ibody);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iecond_ibody_set(SEXP r_ast, SEXP r_node, SEXP r_ibody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ibody);
    rastr_node_t ibody = rastr_node_unwrap(r_ibody);

    rastr_iecond_ibody_set(ast, node, ibody);
    return R_NilValue;
}


/* eop ************************************************************************/
// get
rastr_node_t rastr_iecond_eop_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iecond_type, node);
    return ptr->node.iecond_node.eop;
}

SEXP r_rastr_iecond_eop_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecond_eop_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iecond_eop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t eop) {
    ENSURE_NODE_TYPE(rastr_iecond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iecond_node.eop;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iecond, eop, id)

    return result;
}

SEXP r_rastr_iecond_eop_rep(SEXP r_ast, SEXP r_node, SEXP r_eop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_eop);
    rastr_node_t eop = rastr_node_unwrap(r_eop);

    rastr_node_t result = rastr_iecond_eop_rep(ast, node, eop);
    return rastr_node_wrap(result);
}
// set
void rastr_iecond_eop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t eop) {
    rastr_node_t result = rastr_iecond_eop_rep(ast, node, eop);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iecond_eop_set(SEXP r_ast, SEXP r_node, SEXP r_eop) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_eop);
    rastr_node_t eop = rastr_node_unwrap(r_eop);

    rastr_iecond_eop_set(ast, node, eop);
    return R_NilValue;
}


/* ebody **********************************************************************/
// get
rastr_node_t rastr_iecond_ebody_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iecond_type, node);
    return ptr->node.iecond_node.ebody;
}

SEXP r_rastr_iecond_ebody_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iecond_ebody_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iecond_ebody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ebody) {
    ENSURE_NODE_TYPE(rastr_iecond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iecond_node.ebody;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iecond, ebody, id)

    return result;
}

SEXP r_rastr_iecond_ebody_rep(SEXP r_ast, SEXP r_node, SEXP r_ebody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ebody);
    rastr_node_t ebody = rastr_node_unwrap(r_ebody);

    rastr_node_t result = rastr_iecond_ebody_rep(ast, node, ebody);
    return rastr_node_wrap(result);
}
// set
void rastr_iecond_ebody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ebody) {
    rastr_node_t result = rastr_iecond_ebody_rep(ast, node, ebody);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iecond_ebody_set(SEXP r_ast, SEXP r_node, SEXP r_ebody) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ebody);
    rastr_node_t ebody = rastr_node_unwrap(r_ebody);

    rastr_iecond_ebody_set(ast, node, ebody);
    return R_NilValue;
}




/*******************************************************************************
* fndefn
*******************************************************************************/
rastr_node_t rastr_fndefn_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t lbkt, rastr_node_t pars, rastr_node_t rbkt, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_FNDEFN);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(fndefn, op, id)
    ASSIGN_CHILD(fndefn, lbkt, id)
    ASSIGN_CHILD(fndefn, pars, id)
    ASSIGN_CHILD(fndefn, rbkt, id)
    ASSIGN_CHILD(fndefn, body, id)

    return pair.node;
}

SEXP r_rastr_fndefn_new(SEXP r_ast, SEXP r_op, SEXP r_lbkt, SEXP r_pars, SEXP r_rbkt, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_pars);
    rastr_node_t pars = rastr_node_unwrap(r_pars);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);
    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_fndefn_new(ast, op, lbkt, pars, rbkt, body);
    return rastr_node_wrap(result);
}

// pred
int rastr_fndefn_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_FNDEFN);
}

SEXP r_rastr_fndefn_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_fndefn_type(ast, node);
    return lgl_vec1(result);
}
/* op *************************************************************************/
// get
rastr_node_t rastr_fndefn_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);
    return ptr->node.fndefn_node.op;
}

SEXP r_rastr_fndefn_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fndefn_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fndefn_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fndefn, op, id)

    return result;
}

SEXP r_rastr_fndefn_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_fndefn_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_fndefn_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_fndefn_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fndefn_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_fndefn_op_set(ast, node, op);
    return R_NilValue;
}


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_fndefn_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);
    return ptr->node.fndefn_node.lbkt;
}

SEXP r_rastr_fndefn_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fndefn_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fndefn_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fndefn, lbkt, id)

    return result;
}

SEXP r_rastr_fndefn_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_fndefn_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_fndefn_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_fndefn_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fndefn_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_fndefn_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* pars ***********************************************************************/
// get
rastr_node_t rastr_fndefn_pars_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);
    return ptr->node.fndefn_node.pars;
}

SEXP r_rastr_fndefn_pars_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_pars_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fndefn_pars_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t pars) {
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fndefn_node.pars;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fndefn, pars, id)

    return result;
}

SEXP r_rastr_fndefn_pars_rep(SEXP r_ast, SEXP r_node, SEXP r_pars) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_pars);
    rastr_node_t pars = rastr_node_unwrap(r_pars);

    rastr_node_t result = rastr_fndefn_pars_rep(ast, node, pars);
    return rastr_node_wrap(result);
}
// set
void rastr_fndefn_pars_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t pars) {
    rastr_node_t result = rastr_fndefn_pars_rep(ast, node, pars);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fndefn_pars_set(SEXP r_ast, SEXP r_node, SEXP r_pars) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_pars);
    rastr_node_t pars = rastr_node_unwrap(r_pars);

    rastr_fndefn_pars_set(ast, node, pars);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_fndefn_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);
    return ptr->node.fndefn_node.rbkt;
}

SEXP r_rastr_fndefn_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fndefn_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fndefn_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fndefn, rbkt, id)

    return result;
}

SEXP r_rastr_fndefn_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_fndefn_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_fndefn_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_fndefn_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fndefn_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_fndefn_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}


/* body ***********************************************************************/
// get
rastr_node_t rastr_fndefn_body_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);
    return ptr->node.fndefn_node.body;
}

SEXP r_rastr_fndefn_body_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fndefn_body_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fndefn_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    ENSURE_NODE_TYPE(rastr_fndefn_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fndefn_node.body;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fndefn, body, id)

    return result;
}

SEXP r_rastr_fndefn_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_node_t result = rastr_fndefn_body_rep(ast, node, body);
    return rastr_node_wrap(result);
}
// set
void rastr_fndefn_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body) {
    rastr_node_t result = rastr_fndefn_body_rep(ast, node, body);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fndefn_body_set(SEXP r_ast, SEXP r_node, SEXP r_body) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_body);
    rastr_node_t body = rastr_node_unwrap(r_body);

    rastr_fndefn_body_set(ast, node, body);
    return R_NilValue;
}




/*******************************************************************************
* fncall
*******************************************************************************/
rastr_node_t rastr_fncall_new(rastr_ast_t ast, rastr_node_t fn, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_FNCALL);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(fncall, fn, id)
    ASSIGN_CHILD(fncall, lbkt, id)
    ASSIGN_CHILD(fncall, args, id)
    ASSIGN_CHILD(fncall, rbkt, id)

    return pair.node;
}

SEXP r_rastr_fncall_new(SEXP r_ast, SEXP r_fn, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_fn);
    rastr_node_t fn = rastr_node_unwrap(r_fn);
    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_fncall_new(ast, fn, lbkt, args, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_fncall_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_FNCALL);
}

SEXP r_rastr_fncall_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_fncall_type(ast, node);
    return lgl_vec1(result);
}
/* fn *************************************************************************/
// get
rastr_node_t rastr_fncall_fn_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fncall_type, node);
    return ptr->node.fncall_node.fn;
}

SEXP r_rastr_fncall_fn_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_fn_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fncall_fn_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t fn) {
    ENSURE_NODE_TYPE(rastr_fncall_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fncall_node.fn;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fncall, fn, id)

    return result;
}

SEXP r_rastr_fncall_fn_rep(SEXP r_ast, SEXP r_node, SEXP r_fn) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_fn);
    rastr_node_t fn = rastr_node_unwrap(r_fn);

    rastr_node_t result = rastr_fncall_fn_rep(ast, node, fn);
    return rastr_node_wrap(result);
}
// set
void rastr_fncall_fn_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t fn) {
    rastr_node_t result = rastr_fncall_fn_rep(ast, node, fn);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fncall_fn_set(SEXP r_ast, SEXP r_node, SEXP r_fn) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_fn);
    rastr_node_t fn = rastr_node_unwrap(r_fn);

    rastr_fncall_fn_set(ast, node, fn);
    return R_NilValue;
}


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_fncall_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fncall_type, node);
    return ptr->node.fncall_node.lbkt;
}

SEXP r_rastr_fncall_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fncall_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_fncall_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fncall_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fncall, lbkt, id)

    return result;
}

SEXP r_rastr_fncall_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_fncall_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_fncall_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_fncall_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fncall_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_fncall_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* args ***********************************************************************/
// get
rastr_node_t rastr_fncall_args_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fncall_type, node);
    return ptr->node.fncall_node.args;
}

SEXP r_rastr_fncall_args_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_args_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fncall_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    ENSURE_NODE_TYPE(rastr_fncall_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fncall_node.args;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fncall, args, id)

    return result;
}

SEXP r_rastr_fncall_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_node_t result = rastr_fncall_args_rep(ast, node, args);
    return rastr_node_wrap(result);
}
// set
void rastr_fncall_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    rastr_node_t result = rastr_fncall_args_rep(ast, node, args);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fncall_args_set(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_fncall_args_set(ast, node, args);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_fncall_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_fncall_type, node);
    return ptr->node.fncall_node.rbkt;
}

SEXP r_rastr_fncall_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_fncall_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_fncall_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_fncall_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.fncall_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(fncall, rbkt, id)

    return result;
}

SEXP r_rastr_fncall_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_fncall_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_fncall_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_fncall_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_fncall_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_fncall_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* sub
*******************************************************************************/
rastr_node_t rastr_sub_new(rastr_ast_t ast, rastr_node_t obj, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_SUB);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(sub, obj, id)
    ASSIGN_CHILD(sub, lbkt, id)
    ASSIGN_CHILD(sub, args, id)
    ASSIGN_CHILD(sub, rbkt, id)

    return pair.node;
}

SEXP r_rastr_sub_new(SEXP r_ast, SEXP r_obj, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);
    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_sub_new(ast, obj, lbkt, args, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_sub_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_SUB);
}

SEXP r_rastr_sub_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_sub_type(ast, node);
    return lgl_vec1(result);
}
/* obj ************************************************************************/
// get
rastr_node_t rastr_sub_obj_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sub_type, node);
    return ptr->node.sub_node.obj;
}

SEXP r_rastr_sub_obj_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_obj_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_sub_obj_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj) {
    ENSURE_NODE_TYPE(rastr_sub_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.sub_node.obj;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(sub, obj, id)

    return result;
}

SEXP r_rastr_sub_obj_rep(SEXP r_ast, SEXP r_node, SEXP r_obj) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);

    rastr_node_t result = rastr_sub_obj_rep(ast, node, obj);
    return rastr_node_wrap(result);
}
// set
void rastr_sub_obj_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj) {
    rastr_node_t result = rastr_sub_obj_rep(ast, node, obj);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_sub_obj_set(SEXP r_ast, SEXP r_node, SEXP r_obj) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);

    rastr_sub_obj_set(ast, node, obj);
    return R_NilValue;
}


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_sub_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sub_type, node);
    return ptr->node.sub_node.lbkt;
}

SEXP r_rastr_sub_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_sub_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_sub_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.sub_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(sub, lbkt, id)

    return result;
}

SEXP r_rastr_sub_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_sub_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_sub_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_sub_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_sub_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_sub_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* args ***********************************************************************/
// get
rastr_node_t rastr_sub_args_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sub_type, node);
    return ptr->node.sub_node.args;
}

SEXP r_rastr_sub_args_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_args_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_sub_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    ENSURE_NODE_TYPE(rastr_sub_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.sub_node.args;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(sub, args, id)

    return result;
}

SEXP r_rastr_sub_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_node_t result = rastr_sub_args_rep(ast, node, args);
    return rastr_node_wrap(result);
}
// set
void rastr_sub_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    rastr_node_t result = rastr_sub_args_rep(ast, node, args);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_sub_args_set(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_sub_args_set(ast, node, args);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_sub_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_sub_type, node);
    return ptr->node.sub_node.rbkt;
}

SEXP r_rastr_sub_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_sub_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_sub_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_sub_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.sub_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(sub, rbkt, id)

    return result;
}

SEXP r_rastr_sub_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_sub_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_sub_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_sub_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_sub_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_sub_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* idx
*******************************************************************************/
rastr_node_t rastr_idx_new(rastr_ast_t ast, rastr_node_t obj, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt1, rastr_node_t rbkt2) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_IDX);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(idx, obj, id)
    ASSIGN_CHILD(idx, lbkt, id)
    ASSIGN_CHILD(idx, args, id)
    ASSIGN_CHILD(idx, rbkt1, id)
    ASSIGN_CHILD(idx, rbkt2, id)

    return pair.node;
}

SEXP r_rastr_idx_new(SEXP r_ast, SEXP r_obj, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt1, SEXP r_rbkt2) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);
    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);
    ensure_node_class(r_rbkt1);
    rastr_node_t rbkt1 = rastr_node_unwrap(r_rbkt1);
    ensure_node_class(r_rbkt2);
    rastr_node_t rbkt2 = rastr_node_unwrap(r_rbkt2);

    rastr_node_t result = rastr_idx_new(ast, obj, lbkt, args, rbkt1, rbkt2);
    return rastr_node_wrap(result);
}

// pred
int rastr_idx_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_IDX);
}

SEXP r_rastr_idx_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_idx_type(ast, node);
    return lgl_vec1(result);
}
/* obj ************************************************************************/
// get
rastr_node_t rastr_idx_obj_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_idx_type, node);
    return ptr->node.idx_node.obj;
}

SEXP r_rastr_idx_obj_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_obj_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_idx_obj_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj) {
    ENSURE_NODE_TYPE(rastr_idx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.idx_node.obj;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(idx, obj, id)

    return result;
}

SEXP r_rastr_idx_obj_rep(SEXP r_ast, SEXP r_node, SEXP r_obj) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);

    rastr_node_t result = rastr_idx_obj_rep(ast, node, obj);
    return rastr_node_wrap(result);
}
// set
void rastr_idx_obj_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj) {
    rastr_node_t result = rastr_idx_obj_rep(ast, node, obj);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_idx_obj_set(SEXP r_ast, SEXP r_node, SEXP r_obj) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_obj);
    rastr_node_t obj = rastr_node_unwrap(r_obj);

    rastr_idx_obj_set(ast, node, obj);
    return R_NilValue;
}


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_idx_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_idx_type, node);
    return ptr->node.idx_node.lbkt;
}

SEXP r_rastr_idx_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_idx_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_idx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.idx_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(idx, lbkt, id)

    return result;
}

SEXP r_rastr_idx_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_idx_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_idx_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_idx_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_idx_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_idx_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* args ***********************************************************************/
// get
rastr_node_t rastr_idx_args_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_idx_type, node);
    return ptr->node.idx_node.args;
}

SEXP r_rastr_idx_args_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_args_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_idx_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    ENSURE_NODE_TYPE(rastr_idx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.idx_node.args;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(idx, args, id)

    return result;
}

SEXP r_rastr_idx_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_node_t result = rastr_idx_args_rep(ast, node, args);
    return rastr_node_wrap(result);
}
// set
void rastr_idx_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args) {
    rastr_node_t result = rastr_idx_args_rep(ast, node, args);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_idx_args_set(SEXP r_ast, SEXP r_node, SEXP r_args) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_args);
    rastr_node_t args = rastr_node_unwrap(r_args);

    rastr_idx_args_set(ast, node, args);
    return R_NilValue;
}


/* rbkt1 **********************************************************************/
// get
rastr_node_t rastr_idx_rbkt1_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_idx_type, node);
    return ptr->node.idx_node.rbkt1;
}

SEXP r_rastr_idx_rbkt1_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_rbkt1_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_idx_rbkt1_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt1) {
    ENSURE_NODE_TYPE(rastr_idx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.idx_node.rbkt1;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(idx, rbkt1, id)

    return result;
}

SEXP r_rastr_idx_rbkt1_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt1) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt1);
    rastr_node_t rbkt1 = rastr_node_unwrap(r_rbkt1);

    rastr_node_t result = rastr_idx_rbkt1_rep(ast, node, rbkt1);
    return rastr_node_wrap(result);
}
// set
void rastr_idx_rbkt1_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt1) {
    rastr_node_t result = rastr_idx_rbkt1_rep(ast, node, rbkt1);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_idx_rbkt1_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt1) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt1);
    rastr_node_t rbkt1 = rastr_node_unwrap(r_rbkt1);

    rastr_idx_rbkt1_set(ast, node, rbkt1);
    return R_NilValue;
}


/* rbkt2 **********************************************************************/
// get
rastr_node_t rastr_idx_rbkt2_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_idx_type, node);
    return ptr->node.idx_node.rbkt2;
}

SEXP r_rastr_idx_rbkt2_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_idx_rbkt2_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_idx_rbkt2_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt2) {
    ENSURE_NODE_TYPE(rastr_idx_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.idx_node.rbkt2;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(idx, rbkt2, id)

    return result;
}

SEXP r_rastr_idx_rbkt2_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt2) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt2);
    rastr_node_t rbkt2 = rastr_node_unwrap(r_rbkt2);

    rastr_node_t result = rastr_idx_rbkt2_rep(ast, node, rbkt2);
    return rastr_node_wrap(result);
}
// set
void rastr_idx_rbkt2_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt2) {
    rastr_node_t result = rastr_idx_rbkt2_rep(ast, node, rbkt2);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_idx_rbkt2_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt2) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt2);
    rastr_node_t rbkt2 = rastr_node_unwrap(r_rbkt2);

    rastr_idx_rbkt2_set(ast, node, rbkt2);
    return R_NilValue;
}




/*******************************************************************************
* aexpr
*******************************************************************************/
rastr_node_t rastr_aexpr_new(rastr_ast_t ast, rastr_node_t ann, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_AEXPR);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(aexpr, ann, id)
    ASSIGN_CHILD(aexpr, expr, id)

    return pair.node;
}

SEXP r_rastr_aexpr_new(SEXP r_ast, SEXP r_ann, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_ann);
    rastr_node_t ann = rastr_node_unwrap(r_ann);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_aexpr_new(ast, ann, expr);
    return rastr_node_wrap(result);
}

// pred
int rastr_aexpr_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_AEXPR);
}

SEXP r_rastr_aexpr_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_aexpr_type(ast, node);
    return lgl_vec1(result);
}
/* ann ************************************************************************/
// get
rastr_node_t rastr_aexpr_ann_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_aexpr_type, node);
    return ptr->node.aexpr_node.ann;
}

SEXP r_rastr_aexpr_ann_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_aexpr_ann_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_aexpr_ann_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ann) {
    ENSURE_NODE_TYPE(rastr_aexpr_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.aexpr_node.ann;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(aexpr, ann, id)

    return result;
}

SEXP r_rastr_aexpr_ann_rep(SEXP r_ast, SEXP r_node, SEXP r_ann) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ann);
    rastr_node_t ann = rastr_node_unwrap(r_ann);

    rastr_node_t result = rastr_aexpr_ann_rep(ast, node, ann);
    return rastr_node_wrap(result);
}
// set
void rastr_aexpr_ann_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ann) {
    rastr_node_t result = rastr_aexpr_ann_rep(ast, node, ann);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_aexpr_ann_set(SEXP r_ast, SEXP r_node, SEXP r_ann) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_ann);
    rastr_node_t ann = rastr_node_unwrap(r_ann);

    rastr_aexpr_ann_set(ast, node, ann);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_aexpr_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_aexpr_type, node);
    return ptr->node.aexpr_node.expr;
}

SEXP r_rastr_aexpr_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_aexpr_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_aexpr_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_aexpr_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.aexpr_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(aexpr, expr, id)

    return result;
}

SEXP r_rastr_aexpr_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_aexpr_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_aexpr_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_aexpr_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_aexpr_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_aexpr_expr_set(ast, node, expr);
    return R_NilValue;
}




/*******************************************************************************
* exprs
*******************************************************************************/
rastr_node_t rastr_exprs_new(rastr_ast_t ast, int len, const rastr_node_t* seq) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_EXPRS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ptr->node.exprs_node.len = len;
    ptr->node.exprs_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = seq[i];
        ASSIGN_SEQ_CHILD(exprs, i, child, id)
    }

    return pair.node;
}

SEXP r_rastr_exprs_new(SEXP r_ast, SEXP r_seq) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_EXPRS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    int len = Rf_length(r_seq);
    ptr->node.exprs_node.len = len;
    ptr->node.exprs_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = rastr_node_unwrap(VECTOR_ELT(r_seq, i));
        ASSIGN_SEQ_CHILD(exprs, i, child, id)
    }

    return rastr_node_wrap(pair.node);
}
// pred
int rastr_exprs_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_EXPRS);
}

SEXP r_rastr_exprs_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_exprs_type(ast, node);
    return lgl_vec1(result);
}
/* len ************************************************************************/
// get
int rastr_exprs_len_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_exprs_type, node);
    return ptr->node.exprs_node.len;
}

SEXP r_rastr_exprs_len_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_exprs_len_get(ast, node);
    return int_vec1(result);
}


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_exprs_seq_get(rastr_ast_t ast, rastr_node_t node) {
    ENSURE_NODE_TYPE(rastr_exprs_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.exprs_node.seq;
}

SEXP r_rastr_exprs_seq_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    int len = rastr_exprs_len_get(ast, node);
    const rastr_node_t* seq = rastr_exprs_seq_get(ast, node);

    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, len));

    for(int i = 0; i < len; ++i) {
        SET_VECTOR_ELT(r_result, i, rastr_node_wrap(seq[i]));
    }

    UNPROTECT(1);
    return r_result;
}

rastr_node_t rastr_exprs_get(rastr_ast_t ast, rastr_node_t node, int index) {
    ENSURE_NODE_TYPE(rastr_exprs_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.exprs_node.seq[index];
}

SEXP r_rastr_exprs_get(SEXP r_ast, SEXP r_node, SEXP r_index) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_node_t result = rastr_exprs_get(ast, node, index);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_exprs_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_exprs_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    int id = ptr->id;

    rastr_node_t result = ptr->node.exprs_node.seq[index];
    rastr_node_pid_unset(ast, result);

    ASSIGN_SEQ_CHILD(exprs, index, expr, id)

    return result;
}

SEXP r_rastr_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_exprs_rep(ast, node, index, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_exprs_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t expr) {
    rastr_node_t result = rastr_exprs_rep(ast, node, index, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_exprs_set(ast, node, index, expr);
    return R_NilValue;
}




/*******************************************************************************
* pars
*******************************************************************************/
rastr_node_t rastr_pars_new(rastr_ast_t ast, int len, const rastr_node_t* seq) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_PARS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ptr->node.pars_node.len = len;
    ptr->node.pars_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = seq[i];
        ASSIGN_SEQ_CHILD(pars, i, child, id)
    }

    return pair.node;
}

SEXP r_rastr_pars_new(SEXP r_ast, SEXP r_seq) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_PARS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    int len = Rf_length(r_seq);
    ptr->node.pars_node.len = len;
    ptr->node.pars_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = rastr_node_unwrap(VECTOR_ELT(r_seq, i));
        ASSIGN_SEQ_CHILD(pars, i, child, id)
    }

    return rastr_node_wrap(pair.node);
}
// pred
int rastr_pars_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_PARS);
}

SEXP r_rastr_pars_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_pars_type(ast, node);
    return lgl_vec1(result);
}
/* len ************************************************************************/
// get
int rastr_pars_len_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_pars_type, node);
    return ptr->node.pars_node.len;
}

SEXP r_rastr_pars_len_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_pars_len_get(ast, node);
    return int_vec1(result);
}


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_pars_seq_get(rastr_ast_t ast, rastr_node_t node) {
    ENSURE_NODE_TYPE(rastr_pars_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.pars_node.seq;
}

SEXP r_rastr_pars_seq_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    int len = rastr_pars_len_get(ast, node);
    const rastr_node_t* seq = rastr_pars_seq_get(ast, node);

    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, len));

    for(int i = 0; i < len; ++i) {
        SET_VECTOR_ELT(r_result, i, rastr_node_wrap(seq[i]));
    }

    UNPROTECT(1);
    return r_result;
}

rastr_node_t rastr_pars_get(rastr_ast_t ast, rastr_node_t node, int index) {
    ENSURE_NODE_TYPE(rastr_pars_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.pars_node.seq[index];
}

SEXP r_rastr_pars_get(SEXP r_ast, SEXP r_node, SEXP r_index) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_node_t result = rastr_pars_get(ast, node, index);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_pars_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t par) {
    ENSURE_NODE_TYPE(rastr_pars_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    int id = ptr->id;

    rastr_node_t result = ptr->node.pars_node.seq[index];
    rastr_node_pid_unset(ast, result);

    ASSIGN_SEQ_CHILD(pars, index, par, id)

    return result;
}

SEXP r_rastr_pars_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_par) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    ensure_node_class(r_par);
    rastr_node_t par = rastr_node_unwrap(r_par);

    rastr_node_t result = rastr_pars_rep(ast, node, index, par);
    return rastr_node_wrap(result);
}
// set
void rastr_pars_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t par) {
    rastr_node_t result = rastr_pars_rep(ast, node, index, par);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_pars_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_par) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_par);
    rastr_node_t par = rastr_node_unwrap(r_par);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_pars_set(ast, node, index, par);
    return R_NilValue;
}




/*******************************************************************************
* dpar
*******************************************************************************/
rastr_node_t rastr_dpar_new(rastr_ast_t ast, rastr_node_t name, rastr_node_t op, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_DPAR);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(dpar, name, id)
    ASSIGN_CHILD(dpar, op, id)
    ASSIGN_CHILD(dpar, expr, id)

    return pair.node;
}

SEXP r_rastr_dpar_new(SEXP r_ast, SEXP r_name, SEXP r_op, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);
    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_dpar_new(ast, name, op, expr);
    return rastr_node_wrap(result);
}

// pred
int rastr_dpar_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_DPAR);
}

SEXP r_rastr_dpar_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_dpar_type(ast, node);
    return lgl_vec1(result);
}
/* name ***********************************************************************/
// get
rastr_node_t rastr_dpar_name_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dpar_type, node);
    return ptr->node.dpar_node.name;
}

SEXP r_rastr_dpar_name_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dpar_name_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dpar_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    ENSURE_NODE_TYPE(rastr_dpar_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dpar_node.name;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dpar, name, id)

    return result;
}

SEXP r_rastr_dpar_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_node_t result = rastr_dpar_name_rep(ast, node, name);
    return rastr_node_wrap(result);
}
// set
void rastr_dpar_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    rastr_node_t result = rastr_dpar_name_rep(ast, node, name);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dpar_name_set(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_dpar_name_set(ast, node, name);
    return R_NilValue;
}


/* op *************************************************************************/
// get
rastr_node_t rastr_dpar_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dpar_type, node);
    return ptr->node.dpar_node.op;
}

SEXP r_rastr_dpar_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dpar_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dpar_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_dpar_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dpar_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dpar, op, id)

    return result;
}

SEXP r_rastr_dpar_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_dpar_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_dpar_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_dpar_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dpar_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_dpar_op_set(ast, node, op);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_dpar_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dpar_type, node);
    return ptr->node.dpar_node.expr;
}

SEXP r_rastr_dpar_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dpar_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dpar_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_dpar_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dpar_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dpar, expr, id)

    return result;
}

SEXP r_rastr_dpar_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_dpar_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_dpar_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_dpar_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dpar_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_dpar_expr_set(ast, node, expr);
    return R_NilValue;
}




/*******************************************************************************
* ndpar
*******************************************************************************/
rastr_node_t rastr_ndpar_new(rastr_ast_t ast, rastr_node_t name) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_NDPAR);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(ndpar, name, id)

    return pair.node;
}

SEXP r_rastr_ndpar_new(SEXP r_ast, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_node_t result = rastr_ndpar_new(ast, name);
    return rastr_node_wrap(result);
}

// pred
int rastr_ndpar_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_NDPAR);
}

SEXP r_rastr_ndpar_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_ndpar_type(ast, node);
    return lgl_vec1(result);
}
/* name ***********************************************************************/
// get
rastr_node_t rastr_ndpar_name_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_ndpar_type, node);
    return ptr->node.ndpar_node.name;
}

SEXP r_rastr_ndpar_name_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_ndpar_name_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_ndpar_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    ENSURE_NODE_TYPE(rastr_ndpar_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.ndpar_node.name;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(ndpar, name, id)

    return result;
}

SEXP r_rastr_ndpar_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_node_t result = rastr_ndpar_name_rep(ast, node, name);
    return rastr_node_wrap(result);
}
// set
void rastr_ndpar_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    rastr_node_t result = rastr_ndpar_name_rep(ast, node, name);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_ndpar_name_set(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_ndpar_name_set(ast, node, name);
    return R_NilValue;
}




/*******************************************************************************
* args
*******************************************************************************/
rastr_node_t rastr_args_new(rastr_ast_t ast, int len, const rastr_node_t* seq) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_ARGS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ptr->node.args_node.len = len;
    ptr->node.args_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = seq[i];
        ASSIGN_SEQ_CHILD(args, i, child, id)
    }

    return pair.node;
}

SEXP r_rastr_args_new(SEXP r_ast, SEXP r_seq) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_ARGS);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    int len = Rf_length(r_seq);
    ptr->node.args_node.len = len;
    ptr->node.args_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = rastr_node_unwrap(VECTOR_ELT(r_seq, i));
        ASSIGN_SEQ_CHILD(args, i, child, id)
    }

    return rastr_node_wrap(pair.node);
}
// pred
int rastr_args_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_ARGS);
}

SEXP r_rastr_args_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_args_type(ast, node);
    return lgl_vec1(result);
}
/* len ************************************************************************/
// get
int rastr_args_len_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_args_type, node);
    return ptr->node.args_node.len;
}

SEXP r_rastr_args_len_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_args_len_get(ast, node);
    return int_vec1(result);
}


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_args_seq_get(rastr_ast_t ast, rastr_node_t node) {
    ENSURE_NODE_TYPE(rastr_args_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.args_node.seq;
}

SEXP r_rastr_args_seq_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    int len = rastr_args_len_get(ast, node);
    const rastr_node_t* seq = rastr_args_seq_get(ast, node);

    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, len));

    for(int i = 0; i < len; ++i) {
        SET_VECTOR_ELT(r_result, i, rastr_node_wrap(seq[i]));
    }

    UNPROTECT(1);
    return r_result;
}

rastr_node_t rastr_args_get(rastr_ast_t ast, rastr_node_t node, int index) {
    ENSURE_NODE_TYPE(rastr_args_type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node.args_node.seq[index];
}

SEXP r_rastr_args_get(SEXP r_ast, SEXP r_node, SEXP r_index) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_node_t result = rastr_args_get(ast, node, index);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_args_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t arg) {
    ENSURE_NODE_TYPE(rastr_args_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    int id = ptr->id;

    rastr_node_t result = ptr->node.args_node.seq[index];
    rastr_node_pid_unset(ast, result);

    ASSIGN_SEQ_CHILD(args, index, arg, id)

    return result;
}

SEXP r_rastr_args_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_arg) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    ensure_node_class(r_arg);
    rastr_node_t arg = rastr_node_unwrap(r_arg);

    rastr_node_t result = rastr_args_rep(ast, node, index, arg);
    return rastr_node_wrap(result);
}
// set
void rastr_args_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t arg) {
    rastr_node_t result = rastr_args_rep(ast, node, index, arg);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_args_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_arg) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_arg);
    rastr_node_t arg = rastr_node_unwrap(r_arg);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_args_set(ast, node, index, arg);
    return R_NilValue;
}




/*******************************************************************************
* narg
*******************************************************************************/
rastr_node_t rastr_narg_new(rastr_ast_t ast, rastr_node_t name, rastr_node_t op, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_NARG);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(narg, name, id)
    ASSIGN_CHILD(narg, op, id)
    ASSIGN_CHILD(narg, expr, id)

    return pair.node;
}

SEXP r_rastr_narg_new(SEXP r_ast, SEXP r_name, SEXP r_op, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);
    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_narg_new(ast, name, op, expr);
    return rastr_node_wrap(result);
}

// pred
int rastr_narg_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_NARG);
}

SEXP r_rastr_narg_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_narg_type(ast, node);
    return lgl_vec1(result);
}
/* name ***********************************************************************/
// get
rastr_node_t rastr_narg_name_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_narg_type, node);
    return ptr->node.narg_node.name;
}

SEXP r_rastr_narg_name_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_name_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_narg_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    ENSURE_NODE_TYPE(rastr_narg_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.narg_node.name;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(narg, name, id)

    return result;
}

SEXP r_rastr_narg_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_node_t result = rastr_narg_name_rep(ast, node, name);
    return rastr_node_wrap(result);
}
// set
void rastr_narg_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name) {
    rastr_node_t result = rastr_narg_name_rep(ast, node, name);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_narg_name_set(SEXP r_ast, SEXP r_node, SEXP r_name) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_name);
    rastr_node_t name = rastr_node_unwrap(r_name);

    rastr_narg_name_set(ast, node, name);
    return R_NilValue;
}


/* op *************************************************************************/
// get
rastr_node_t rastr_narg_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_narg_type, node);
    return ptr->node.narg_node.op;
}

SEXP r_rastr_narg_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_narg_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_narg_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.narg_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(narg, op, id)

    return result;
}

SEXP r_rastr_narg_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_narg_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_narg_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_narg_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_narg_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_narg_op_set(ast, node, op);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_narg_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_narg_type, node);
    return ptr->node.narg_node.expr;
}

SEXP r_rastr_narg_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_narg_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_narg_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_narg_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.narg_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(narg, expr, id)

    return result;
}

SEXP r_rastr_narg_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_narg_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_narg_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_narg_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_narg_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_narg_expr_set(ast, node, expr);
    return R_NilValue;
}




/*******************************************************************************
* parg
*******************************************************************************/
rastr_node_t rastr_parg_new(rastr_ast_t ast, rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_PARG);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(parg, expr, id)

    return pair.node;
}

SEXP r_rastr_parg_new(SEXP r_ast, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_parg_new(ast, expr);
    return rastr_node_wrap(result);
}

// pred
int rastr_parg_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_PARG);
}

SEXP r_rastr_parg_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_parg_type(ast, node);
    return lgl_vec1(result);
}
/* expr ***********************************************************************/
// get
rastr_node_t rastr_parg_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_parg_type, node);
    return ptr->node.parg_node.expr;
}

SEXP r_rastr_parg_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_parg_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_parg_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_parg_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.parg_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(parg, expr, id)

    return result;
}

SEXP r_rastr_parg_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_parg_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_parg_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_parg_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_parg_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_parg_expr_set(ast, node, expr);
    return R_NilValue;
}




/*******************************************************************************
* cond
*******************************************************************************/
rastr_node_t rastr_cond_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t expr, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_COND);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(cond, lbkt, id)
    ASSIGN_CHILD(cond, expr, id)
    ASSIGN_CHILD(cond, rbkt, id)

    return pair.node;
}

SEXP r_rastr_cond_new(SEXP r_ast, SEXP r_lbkt, SEXP r_expr, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_cond_new(ast, lbkt, expr, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_cond_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_COND);
}

SEXP r_rastr_cond_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_cond_type(ast, node);
    return lgl_vec1(result);
}
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_cond_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cond_type, node);
    return ptr->node.cond_node.lbkt;
}

SEXP r_rastr_cond_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cond_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_cond_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_cond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.cond_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(cond, lbkt, id)

    return result;
}

SEXP r_rastr_cond_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_cond_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_cond_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_cond_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_cond_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_cond_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_cond_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cond_type, node);
    return ptr->node.cond_node.expr;
}

SEXP r_rastr_cond_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cond_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_cond_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_cond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.cond_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(cond, expr, id)

    return result;
}

SEXP r_rastr_cond_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_cond_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_cond_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_cond_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_cond_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_cond_expr_set(ast, node, expr);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_cond_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_cond_type, node);
    return ptr->node.cond_node.rbkt;
}

SEXP r_rastr_cond_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_cond_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_cond_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_cond_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.cond_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(cond, rbkt, id)

    return result;
}

SEXP r_rastr_cond_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_cond_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_cond_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_cond_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_cond_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_cond_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* iter
*******************************************************************************/
rastr_node_t rastr_iter_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t var, rastr_node_t op, rastr_node_t expr, rastr_node_t rbkt) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_ITER);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(iter, lbkt, id)
    ASSIGN_CHILD(iter, var, id)
    ASSIGN_CHILD(iter, op, id)
    ASSIGN_CHILD(iter, expr, id)
    ASSIGN_CHILD(iter, rbkt, id)

    return pair.node;
}

SEXP r_rastr_iter_new(SEXP r_ast, SEXP r_lbkt, SEXP r_var, SEXP r_op, SEXP r_expr, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);
    ensure_node_class(r_var);
    rastr_node_t var = rastr_node_unwrap(r_var);
    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);
    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);
    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_iter_new(ast, lbkt, var, op, expr, rbkt);
    return rastr_node_wrap(result);
}

// pred
int rastr_iter_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_ITER);
}

SEXP r_rastr_iter_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_iter_type(ast, node);
    return lgl_vec1(result);
}
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_iter_lbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iter_type, node);
    return ptr->node.iter_node.lbkt;
}

SEXP r_rastr_iter_lbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_lbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iter_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    ENSURE_NODE_TYPE(rastr_iter_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iter_node.lbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iter, lbkt, id)

    return result;
}

SEXP r_rastr_iter_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_node_t result = rastr_iter_lbkt_rep(ast, node, lbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_iter_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt) {
    rastr_node_t result = rastr_iter_lbkt_rep(ast, node, lbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iter_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_lbkt);
    rastr_node_t lbkt = rastr_node_unwrap(r_lbkt);

    rastr_iter_lbkt_set(ast, node, lbkt);
    return R_NilValue;
}


/* var ************************************************************************/
// get
rastr_node_t rastr_iter_var_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iter_type, node);
    return ptr->node.iter_node.var;
}

SEXP r_rastr_iter_var_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_var_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iter_var_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t var) {
    ENSURE_NODE_TYPE(rastr_iter_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iter_node.var;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iter, var, id)

    return result;
}

SEXP r_rastr_iter_var_rep(SEXP r_ast, SEXP r_node, SEXP r_var) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_var);
    rastr_node_t var = rastr_node_unwrap(r_var);

    rastr_node_t result = rastr_iter_var_rep(ast, node, var);
    return rastr_node_wrap(result);
}
// set
void rastr_iter_var_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t var) {
    rastr_node_t result = rastr_iter_var_rep(ast, node, var);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iter_var_set(SEXP r_ast, SEXP r_node, SEXP r_var) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_var);
    rastr_node_t var = rastr_node_unwrap(r_var);

    rastr_iter_var_set(ast, node, var);
    return R_NilValue;
}


/* op *************************************************************************/
// get
rastr_node_t rastr_iter_op_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iter_type, node);
    return ptr->node.iter_node.op;
}

SEXP r_rastr_iter_op_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_op_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iter_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    ENSURE_NODE_TYPE(rastr_iter_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iter_node.op;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iter, op, id)

    return result;
}

SEXP r_rastr_iter_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_node_t result = rastr_iter_op_rep(ast, node, op);
    return rastr_node_wrap(result);
}
// set
void rastr_iter_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op) {
    rastr_node_t result = rastr_iter_op_rep(ast, node, op);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iter_op_set(SEXP r_ast, SEXP r_node, SEXP r_op) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_op);
    rastr_node_t op = rastr_node_unwrap(r_op);

    rastr_iter_op_set(ast, node, op);
    return R_NilValue;
}


/* expr ***********************************************************************/
// get
rastr_node_t rastr_iter_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iter_type, node);
    return ptr->node.iter_node.expr;
}

SEXP r_rastr_iter_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iter_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_iter_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iter_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iter, expr, id)

    return result;
}

SEXP r_rastr_iter_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_iter_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_iter_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_iter_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iter_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_iter_expr_set(ast, node, expr);
    return R_NilValue;
}


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_iter_rbkt_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_iter_type, node);
    return ptr->node.iter_node.rbkt;
}

SEXP r_rastr_iter_rbkt_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_iter_rbkt_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_iter_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    ENSURE_NODE_TYPE(rastr_iter_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.iter_node.rbkt;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(iter, rbkt, id)

    return result;
}

SEXP r_rastr_iter_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_node_t result = rastr_iter_rbkt_rep(ast, node, rbkt);
    return rastr_node_wrap(result);
}
// set
void rastr_iter_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt) {
    rastr_node_t result = rastr_iter_rbkt_rep(ast, node, rbkt);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_iter_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_rbkt);
    rastr_node_t rbkt = rastr_node_unwrap(r_rbkt);

    rastr_iter_rbkt_set(ast, node, rbkt);
    return R_NilValue;
}




/*******************************************************************************
* pgm
*******************************************************************************/
rastr_node_t rastr_pgm_new(rastr_ast_t ast, rastr_node_t beg, rastr_node_t exprs, rastr_node_t end) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_PGM);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(pgm, beg, id)
    ASSIGN_CHILD(pgm, exprs, id)
    ASSIGN_CHILD(pgm, end, id)

    return pair.node;
}

SEXP r_rastr_pgm_new(SEXP r_ast, SEXP r_beg, SEXP r_exprs, SEXP r_end) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_beg);
    rastr_node_t beg = rastr_node_unwrap(r_beg);
    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);
    ensure_node_class(r_end);
    rastr_node_t end = rastr_node_unwrap(r_end);

    rastr_node_t result = rastr_pgm_new(ast, beg, exprs, end);
    return rastr_node_wrap(result);
}

// pred
int rastr_pgm_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_PGM);
}

SEXP r_rastr_pgm_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_pgm_type(ast, node);
    return lgl_vec1(result);
}
/* beg ************************************************************************/
// get
rastr_node_t rastr_pgm_beg_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_pgm_type, node);
    return ptr->node.pgm_node.beg;
}

SEXP r_rastr_pgm_beg_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_pgm_beg_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_pgm_beg_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t beg) {
    ENSURE_NODE_TYPE(rastr_pgm_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.pgm_node.beg;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(pgm, beg, id)

    return result;
}

SEXP r_rastr_pgm_beg_rep(SEXP r_ast, SEXP r_node, SEXP r_beg) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_beg);
    rastr_node_t beg = rastr_node_unwrap(r_beg);

    rastr_node_t result = rastr_pgm_beg_rep(ast, node, beg);
    return rastr_node_wrap(result);
}
// set
void rastr_pgm_beg_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t beg) {
    rastr_node_t result = rastr_pgm_beg_rep(ast, node, beg);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_pgm_beg_set(SEXP r_ast, SEXP r_node, SEXP r_beg) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_beg);
    rastr_node_t beg = rastr_node_unwrap(r_beg);

    rastr_pgm_beg_set(ast, node, beg);
    return R_NilValue;
}


/* exprs **********************************************************************/
// get
rastr_node_t rastr_pgm_exprs_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_pgm_type, node);
    return ptr->node.pgm_node.exprs;
}

SEXP r_rastr_pgm_exprs_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_pgm_exprs_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_pgm_exprs_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs) {
    ENSURE_NODE_TYPE(rastr_pgm_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.pgm_node.exprs;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(pgm, exprs, id)

    return result;
}

SEXP r_rastr_pgm_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_exprs) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);

    rastr_node_t result = rastr_pgm_exprs_rep(ast, node, exprs);
    return rastr_node_wrap(result);
}
// set
void rastr_pgm_exprs_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs) {
    rastr_node_t result = rastr_pgm_exprs_rep(ast, node, exprs);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_pgm_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_exprs) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_exprs);
    rastr_node_t exprs = rastr_node_unwrap(r_exprs);

    rastr_pgm_exprs_set(ast, node, exprs);
    return R_NilValue;
}


/* end ************************************************************************/
// get
rastr_node_t rastr_pgm_end_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_pgm_type, node);
    return ptr->node.pgm_node.end;
}

SEXP r_rastr_pgm_end_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_pgm_end_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_pgm_end_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t end) {
    ENSURE_NODE_TYPE(rastr_pgm_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.pgm_node.end;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(pgm, end, id)

    return result;
}

SEXP r_rastr_pgm_end_rep(SEXP r_ast, SEXP r_node, SEXP r_end) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_end);
    rastr_node_t end = rastr_node_unwrap(r_end);

    rastr_node_t result = rastr_pgm_end_rep(ast, node, end);
    return rastr_node_wrap(result);
}
// set
void rastr_pgm_end_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t end) {
    rastr_node_t result = rastr_pgm_end_rep(ast, node, end);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_pgm_end_set(SEXP r_ast, SEXP r_node, SEXP r_end) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_end);
    rastr_node_t end = rastr_node_unwrap(r_end);

    rastr_pgm_end_set(ast, node, end);
    return R_NilValue;
}




/*******************************************************************************
* dlmtd
*******************************************************************************/
rastr_node_t rastr_dlmtd_new(rastr_ast_t ast, rastr_node_t expr, rastr_node_t dlmtr) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_DLMTD);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(dlmtd, expr, id)
    ASSIGN_CHILD(dlmtd, dlmtr, id)

    return pair.node;
}

SEXP r_rastr_dlmtd_new(SEXP r_ast, SEXP r_expr, SEXP r_dlmtr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);
    ensure_node_class(r_dlmtr);
    rastr_node_t dlmtr = rastr_node_unwrap(r_dlmtr);

    rastr_node_t result = rastr_dlmtd_new(ast, expr, dlmtr);
    return rastr_node_wrap(result);
}

// pred
int rastr_dlmtd_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_DLMTD);
}

SEXP r_rastr_dlmtd_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_dlmtd_type(ast, node);
    return lgl_vec1(result);
}
/* expr ***********************************************************************/
// get
rastr_node_t rastr_dlmtd_expr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dlmtd_type, node);
    return ptr->node.dlmtd_node.expr;
}

SEXP r_rastr_dlmtd_expr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtd_expr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dlmtd_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    ENSURE_NODE_TYPE(rastr_dlmtd_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dlmtd_node.expr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dlmtd, expr, id)

    return result;
}

SEXP r_rastr_dlmtd_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_node_t result = rastr_dlmtd_expr_rep(ast, node, expr);
    return rastr_node_wrap(result);
}
// set
void rastr_dlmtd_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr) {
    rastr_node_t result = rastr_dlmtd_expr_rep(ast, node, expr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dlmtd_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_expr);
    rastr_node_t expr = rastr_node_unwrap(r_expr);

    rastr_dlmtd_expr_set(ast, node, expr);
    return R_NilValue;
}


/* dlmtr **********************************************************************/
// get
rastr_node_t rastr_dlmtd_dlmtr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_dlmtd_type, node);
    return ptr->node.dlmtd_node.dlmtr;
}

SEXP r_rastr_dlmtd_dlmtr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_dlmtd_dlmtr_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_dlmtd_dlmtr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t dlmtr) {
    ENSURE_NODE_TYPE(rastr_dlmtd_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.dlmtd_node.dlmtr;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(dlmtd, dlmtr, id)

    return result;
}

SEXP r_rastr_dlmtd_dlmtr_rep(SEXP r_ast, SEXP r_node, SEXP r_dlmtr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_dlmtr);
    rastr_node_t dlmtr = rastr_node_unwrap(r_dlmtr);

    rastr_node_t result = rastr_dlmtd_dlmtr_rep(ast, node, dlmtr);
    return rastr_node_wrap(result);
}
// set
void rastr_dlmtd_dlmtr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t dlmtr) {
    rastr_node_t result = rastr_dlmtd_dlmtr_rep(ast, node, dlmtr);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_dlmtd_dlmtr_set(SEXP r_ast, SEXP r_node, SEXP r_dlmtr) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_dlmtr);
    rastr_node_t dlmtr = rastr_node_unwrap(r_dlmtr);

    rastr_dlmtd_dlmtr_set(ast, node, dlmtr);
    return R_NilValue;
}




/*******************************************************************************
* msng
*******************************************************************************/
rastr_node_t rastr_msng_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_MSNG);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(msng, gap, id)
    ASSIGN_CHILD(msng, loc, id)

    return pair.node;
}

SEXP r_rastr_msng_new(SEXP r_ast, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);
    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    rastr_node_t result = rastr_msng_new(ast, gap, loc);
    return rastr_node_wrap(result);
}

// pred
int rastr_msng_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_MSNG);
}

SEXP r_rastr_msng_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_msng_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_msng_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_msng_type, node);
    return ptr->node.msng_node.gap;
}

SEXP r_rastr_msng_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_msng_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_msng_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_msng_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.msng_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(msng, gap, id)

    return result;
}

SEXP r_rastr_msng_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_msng_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_msng_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_msng_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_msng_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_msng_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_msng_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_msng_type, node);
    return ptr->node.msng_node.loc;
}

SEXP r_rastr_msng_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_msng_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* beg
*******************************************************************************/
// pred
int rastr_beg_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_BEG);
}

SEXP r_rastr_beg_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_beg_type(ast, node);
    return lgl_vec1(result);
}
/* bom ************************************************************************/
// get
const char* rastr_beg_bom_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_beg_type, node);
    return ptr->node.beg_node.bom;
}

SEXP r_rastr_beg_bom_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_beg_bom_get(ast, node);
    return chr_vec1(result);
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_beg_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_beg_type, node);
    return ptr->node.beg_node.loc;
}

SEXP r_rastr_beg_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_beg_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* end
*******************************************************************************/
rastr_node_t rastr_end_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc) {
    rastr_node_pair_t pair = rastr_node_create(ast, RASTR_END);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ASSIGN_CHILD(end, gap, id)
    ASSIGN_CHILD(end, loc, id)

    return pair.node;
}

SEXP r_rastr_end_new(SEXP r_ast, SEXP r_gap, SEXP r_loc) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);
    ensure_node_class(r_loc);
    rastr_node_t loc = rastr_node_unwrap(r_loc);

    rastr_node_t result = rastr_end_new(ast, gap, loc);
    return rastr_node_wrap(result);
}

// pred
int rastr_end_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_END);
}

SEXP r_rastr_end_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_end_type(ast, node);
    return lgl_vec1(result);
}
/* gap ************************************************************************/
// get
rastr_node_t rastr_end_gap_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_end_type, node);
    return ptr->node.end_node.gap;
}

SEXP r_rastr_end_gap_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_end_gap_get(ast, node);
    return rastr_node_wrap(result);
}
// rep
rastr_node_t rastr_end_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    ENSURE_NODE_TYPE(rastr_end_type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node.end_node.gap;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(end, gap, id)

    return result;
}

SEXP r_rastr_end_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_node_t result = rastr_end_gap_rep(ast, node, gap);
    return rastr_node_wrap(result);
}
// set
void rastr_end_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap) {
    rastr_node_t result = rastr_end_gap_rep(ast, node, gap);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr_end_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r_gap);
    rastr_node_t gap = rastr_node_unwrap(r_gap);

    rastr_end_gap_set(ast, node, gap);
    return R_NilValue;
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_end_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_end_type, node);
    return ptr->node.end_node.loc;
}

SEXP r_rastr_end_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_end_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* gap
*******************************************************************************/
// pred
int rastr_gap_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_GAP);
}

SEXP r_rastr_gap_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_gap_type(ast, node);
    return lgl_vec1(result);
}
/* val ************************************************************************/
// get
const char* rastr_gap_val_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_gap_type, node);
    return ptr->node.gap_node.val;
}

SEXP r_rastr_gap_val_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_gap_val_get(ast, node);
    return chr_vec1(result);
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_gap_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_gap_type, node);
    return ptr->node.gap_node.loc;
}

SEXP r_rastr_gap_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_gap_loc_get(ast, node);
    return rastr_node_wrap(result);
}




/*******************************************************************************
* loc
*******************************************************************************/
// pred
int rastr_loc_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_LOC);
}

SEXP r_rastr_loc_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_type(ast, node);
    return lgl_vec1(result);
}
/* lrow ***********************************************************************/
// get
int rastr_loc_lrow_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.lrow;
}

SEXP r_rastr_loc_lrow_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_lrow_get(ast, node);
    return int_vec1(result);
}


/* lcol ***********************************************************************/
// get
int rastr_loc_lcol_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.lcol;
}

SEXP r_rastr_loc_lcol_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_lcol_get(ast, node);
    return int_vec1(result);
}


/* lchr ***********************************************************************/
// get
int rastr_loc_lchr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.lchr;
}

SEXP r_rastr_loc_lchr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_lchr_get(ast, node);
    return int_vec1(result);
}


/* lbyte **********************************************************************/
// get
int rastr_loc_lbyte_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.lbyte;
}

SEXP r_rastr_loc_lbyte_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_lbyte_get(ast, node);
    return int_vec1(result);
}


/* rrow ***********************************************************************/
// get
int rastr_loc_rrow_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.rrow;
}

SEXP r_rastr_loc_rrow_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_rrow_get(ast, node);
    return int_vec1(result);
}


/* rcol ***********************************************************************/
// get
int rastr_loc_rcol_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.rcol;
}

SEXP r_rastr_loc_rcol_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_rcol_get(ast, node);
    return int_vec1(result);
}


/* rchr ***********************************************************************/
// get
int rastr_loc_rchr_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.rchr;
}

SEXP r_rastr_loc_rchr_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_rchr_get(ast, node);
    return int_vec1(result);
}


/* rbyte **********************************************************************/
// get
int rastr_loc_rbyte_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_loc_type, node);
    return ptr->node.loc_node.rbyte;
}

SEXP r_rastr_loc_rbyte_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_loc_rbyte_get(ast, node);
    return int_vec1(result);
}




/*******************************************************************************
* err
*******************************************************************************/
// pred
int rastr_err_type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (type == RASTR_ERR);
}

SEXP r_rastr_err_type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr_err_type(ast, node);
    return lgl_vec1(result);
}
/* msg ************************************************************************/
// get
const char* rastr_err_msg_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_err_type, node);
    return ptr->node.err_node.msg;
}

SEXP r_rastr_err_msg_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    const char* result = rastr_err_msg_get(ast, node);
    return chr_vec1(result);
}


/* loc ************************************************************************/
// get
rastr_node_t rastr_err_loc_get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    ENSURE_NODE_TYPE(rastr_err_type, node);
    return ptr->node.err_node.loc;
}

SEXP r_rastr_err_loc_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    rastr_node_t result = rastr_err_loc_get(ast, node);
    return rastr_node_wrap(result);
}




