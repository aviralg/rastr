rastr_node_t rastr__NODE__new(rastr_ast_t ast, int len, const rastr_node_t* seq) {
    rastr_node_pair_t pair = rastr_node_create(ast, _TYPE_);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    ptr->node._NODE__node.len = len;
    ptr->node._NODE__node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = seq[i];
        ASSIGN_SEQ_CHILD(_NODE_, i, child, id)
    }

    return pair.node;
}

SEXP r_rastr__NODE__new(SEXP r_ast, SEXP r_seq) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    rastr_node_pair_t pair = rastr_node_create(ast, _TYPE_);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;

    int len = Rf_length(r_seq);
    ptr->node._NODE__node.len = len;
    ptr->node._NODE__node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);

    for (int i = 0; i < len; ++i) {
        rastr_node_t child = rastr_node_unwrap(VECTOR_ELT(r_seq, i));
        ASSIGN_SEQ_CHILD(_NODE_, i, child, id)
    }

    return rastr_node_wrap(pair.node);
}
