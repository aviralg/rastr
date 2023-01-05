// pred
int rastr__NODE__type(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    rastr_node_type_t type = ptr -> type;
    return (_CHECKS_);
}

SEXP r_rastr__NODE__type(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    int result = rastr__NODE__type(ast, node);
    return lgl_vec1(result);
}
