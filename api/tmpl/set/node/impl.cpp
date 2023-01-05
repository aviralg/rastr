// set
void rastr__NODE___CHILD__set(rastr_ast_t ast, rastr_node_t node, rastr_node_t _CHILD_) {
    rastr_node_t result = rastr__NODE___CHILD__rep(ast, node, _CHILD_);
    rastr_node_destroy(ast, result);
}

SEXP r_rastr__NODE___CHILD__set(SEXP r_ast, SEXP r_node, SEXP r__CHILD_) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r__CHILD_);
    rastr_node_t _CHILD_ = rastr_node_unwrap(r__CHILD_);

    rastr__NODE___CHILD__set(ast, node, _CHILD_);
    return R_NilValue;
}
