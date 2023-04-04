// ins

void rastr__NODE__ins(rastr_ast_t ast, rastr_node_t node, int index, int len, rastr_node_t* seq) {

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    int id = ptr->id;

    int orig_len = ptr->node._NODE__node.len;
    rastr_node_t* orig_seq = ptr->node._NODE__node.seq;

    int tot_len = orig_len + len;
    rastr_node_t* tot_seq = (rastr_node_t*) std::realloc(orig_seq, sizeof(rastr_node_t) * tot_len);

    ptr->node._NODE__node.len = tot_len;
    ptr->node._NODE__node.seq = tot_seq;

    /* move existing nodes to the right to make space for new nodes*/
    std::memmove(tot_seq + index + len, tot_seq + index, sizeof(rastr_node_t) * (orig_len - index));

    /* copy new nodes at their rightful place*/
    for(int i = 0; i < len; ++i) {
        ASSIGN_SEQ_CHILD(_NODE_, i + index, seq[i], id)
    }
}

SEXP r_rastr__NODE__ins(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_seq) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    int len = Rf_length(r_seq);

    rastr_node_t* seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);
    for (int i = 0; i < len; ++i) {
        seq[i] = rastr_node_unwrap(VECTOR_ELT(r_seq, i));
    }

    rastr__NODE__ins(ast, node, index, len, seq);

    free(seq);

    return R_NilValue;
}
