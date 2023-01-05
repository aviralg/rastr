// get
_CHILD_TYPE_ rastr__NODE___CHILD__get(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);
    CHECK_NODETYPE(rastr__NODE__type, node);
    return ptr->node._NODE__node._CHILD_;
}

SEXP r_rastr__NODE___CHILD__get(SEXP r_ast, SEXP r_node) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);
    _CHILD_TYPE_ result = rastr__NODE___CHILD__get(ast, node);
    _RETCODE_
}
