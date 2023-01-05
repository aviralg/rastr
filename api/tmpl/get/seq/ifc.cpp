// get
const rastr_node_t* rastr__NODE__seq_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr__NODE__seq_get(SEXP r_ast, SEXP r_node);
rastr_node_t rastr__NODE__get(rastr_ast_t ast, rastr_node_t node, int index);
SEXP r_rastr__NODE__get(SEXP r_ast, SEXP r_node, SEXP r_index);
