// rep
rastr_node_t rastr__NODE___CHILD__rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t _CHILD_) {
    CHECK_NODETYPE(rastr__NODE__type, node);

    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);

    rastr_node_t result = ptr->node._NODE__node._CHILD_;
    rastr_node_pid_unset(ast, result);

    int id = ptr->id;
    ASSIGN_CHILD(_NODE_, _CHILD_, id)

    return result;
}

SEXP r_rastr__NODE___CHILD__rep(SEXP r_ast, SEXP r_node, SEXP r__CHILD_) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

    ensure_node_class(r_node);
    rastr_node_t node = rastr_node_unwrap(r_node);

    ensure_node_class(r__CHILD_);
    rastr_node_t _CHILD_ = rastr_node_unwrap(r__CHILD_);

    rastr_node_t result = rastr__NODE___CHILD__rep(ast, node, _CHILD_);
    return rastr_node_wrap(result);
}
