rastr_node_t rastr__NODE__new(rastr_ast_t ast, _C_PARS_) {
    rastr_node_pair_t pair = rastr_node_create(ast, _TYPE_);
    rastr_node_ptr_t ptr = pair.ptr;
    int id = ptr->id;
    _CPP_ASSIGNS_
    return pair.node;
}

SEXP r_rastr__NODE__new(SEXP r_ast, _SEXP_PARS_) {
    ensure_ast_class(r_ast);
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    _R_ASSIGNS_
    rastr_node_t result = rastr__NODE__new(ast, _PAR_NAMES_);
    return rastr_node_wrap(result);
}
