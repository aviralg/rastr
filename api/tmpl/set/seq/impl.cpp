// set
void rastr__NODE__set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t _CHILD_) {
    rastr_node_t result = rastr__NODE__rep(ast, node, index, _CHILD_);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr__NODE__set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r__CHILD_) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r__CHILD_);
    rastr_node_t _CHILD_ = rastr_node_unwrap(r__CHILD_);

    ensure_numeric_sexp(r_index, 1);
    int index = (int) num_get(r_index, 0);

    rastr__NODE__set(ast, node, index, _CHILD_);
    return R_NilValue;
}
