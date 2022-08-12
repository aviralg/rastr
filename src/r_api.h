extern "C" {

SEXP r_rastr_blk_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_blk_len(SEXP r_ast, SEXP r_node);
SEXP r_rastr_blk_seq(SEXP r_ast, SEXP r_node);
SEXP r_rastr_blk_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_grp_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_grp_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_grp_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_nuop_op(SEXP r_ast, SEXP r_node);
SEXP r_rastr_unop_op(SEXP r_ast, SEXP r_node);
SEXP r_rastr_unop_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_binop_lexpr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_binop_op(SEXP r_ast, SEXP r_node);
SEXP r_rastr_binop_rexpr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_rlp_kw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_rlp_body(SEXP r_ast, SEXP r_node);
SEXP r_rastr_wlp_kw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_wlp_cond(SEXP r_ast, SEXP r_node);
SEXP r_rastr_wlp_body(SEXP r_ast, SEXP r_node);
SEXP r_rastr_flp_kw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_flp_iter(SEXP r_ast, SEXP r_node);
SEXP r_rastr_flp_body(SEXP r_ast, SEXP r_node);
SEXP r_rastr_icnd_ikw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_icnd_cond(SEXP r_ast, SEXP r_node);
SEXP r_rastr_icnd_ibody(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iecnd_ikw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iecnd_cond(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iecnd_ibody(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iecnd_ekw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iecnd_ebody(SEXP r_ast, SEXP r_node);
SEXP r_rastr_fndefn_hd(SEXP r_ast, SEXP r_node);
SEXP r_rastr_fndefn_params(SEXP r_ast, SEXP r_node);
SEXP r_rastr_fndefn_body(SEXP r_ast, SEXP r_node);
SEXP r_rastr_fncall_fun(SEXP r_ast, SEXP r_node);
SEXP r_rastr_fncall_args(SEXP r_ast, SEXP r_node);
SEXP r_rastr_sub_obj(SEXP r_ast, SEXP r_node);
SEXP r_rastr_sub_inds(SEXP r_ast, SEXP r_node);
SEXP r_rastr_idx_obj(SEXP r_ast, SEXP r_node);
SEXP r_rastr_idx_inds(SEXP r_ast, SEXP r_node);
SEXP r_rastr_params_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_params_len(SEXP r_ast, SEXP r_node);
SEXP r_rastr_params_seq(SEXP r_ast, SEXP r_node);
SEXP r_rastr_params_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_dparam_name(SEXP r_ast, SEXP r_node);
SEXP r_rastr_dparam_op(SEXP r_ast, SEXP r_node);
SEXP r_rastr_dparam_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_ndparam_name(SEXP r_ast, SEXP r_node);
SEXP r_rastr_args_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_args_len(SEXP r_ast, SEXP r_node);
SEXP r_rastr_args_seq(SEXP r_ast, SEXP r_node);
SEXP r_rastr_args_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_narg_name(SEXP r_ast, SEXP r_node);
SEXP r_rastr_narg_op(SEXP r_ast, SEXP r_node);
SEXP r_rastr_narg_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_parg_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_cnd_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_cnd_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_cnd_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iter_lbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iter_var(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iter_kw(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iter_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_iter_rbrack(SEXP r_ast, SEXP r_node);
SEXP r_rastr_pgm_len(SEXP r_ast, SEXP r_node);
SEXP r_rastr_pgm_seq(SEXP r_ast, SEXP r_node);
SEXP r_rastr_dlmtd_expr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_dlmtd_dlmtr(SEXP r_ast, SEXP r_node);
SEXP r_rastr_err_msg(SEXP r_ast, SEXP r_node);
SEXP r_rastr_to_sexp(SEXP r_ast);
SEXP r_rastr_node_to_sexp(SEXP r_ast, SEXP r_node);

SEXP r_rastr_ast_unparse_str(SEXP r_ast);
SEXP r_rastr_node_unparse_str(SEXP r_ast, SEXP r_node);

/* as_sexp */
SEXP r_rastr_ast_as_sexp(SEXP r_ast);
SEXP r_rastr_node_as_sexp(SEXP r_ast, SEXP r_node);

/* as_df */
SEXP r_rastr_ast_as_df(SEXP r_ast);
SEXP r_rastr_node_as_df(SEXP r_ast, SEXP r_node);
}
