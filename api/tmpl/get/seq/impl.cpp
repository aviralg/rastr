// get
const rastr_node_t* rastr__NODE__seq_get(rastr_ast_t ast, rastr_node_t node) {
    CHECK_NODETYPE(rastr__NODE__type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node._NODE__node.seq;
}

SEXP r_rastr__NODE__seq_get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    int len = rastr__NODE__len_get(ast, node);
    const rastr_node_t* seq = rastr__NODE__seq_get(ast, node);

    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, len));

    for(int i = 0; i < len; ++i) {
        SET_VECTOR_ELT(r_result, i, rastr_node_wrap(seq[i]));
    }

    UNPROTECT(1);
    return r_result;
}

rastr_node_t rastr__NODE__get(rastr_ast_t ast, rastr_node_t node, int index) {
    CHECK_NODETYPE(rastr__NODE__type, node);
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    return ptr->node._NODE__node.seq[index];
}

SEXP r_rastr__NODE__get(SEXP r_ast, SEXP r_node, SEXP r_index) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr_node_t result = rastr__NODE__get(ast, node, index);
    return rastr_node_wrap(result);
}
