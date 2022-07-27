#include <rastr/api.h>
#include <R_ext/Rdynload.h>
#include "r_api.h"

extern "C" {
void R_init_rastr(DllInfo* dll);
void R_unload_rastr(DllInfo* info);
}

#define DECLARE_BINDING(NAME, PARAMETERS) \
    { #NAME, (DL_FUNC) &r_##NAME, PARAMETERS }

const R_CallMethodDef CallEntries[] = {
    /* init */
    DECLARE_BINDING(rastr_initialize, 1),
    DECLARE_BINDING(rastr_finalize, 1),

    /* parsing */
    DECLARE_BINDING(rastr_parse_str, 1),
    DECLARE_BINDING(rastr_parse_file, 1),

    DECLARE_BINDING(rastr_blk_lbrack, 2),
    DECLARE_BINDING(rastr_blk_len, 2),
    DECLARE_BINDING(rastr_blk_seq, 2),
    DECLARE_BINDING(rastr_blk_rbrack, 2),
    DECLARE_BINDING(rastr_grp_lbrack, 2),
    DECLARE_BINDING(rastr_grp_expr, 2),
    DECLARE_BINDING(rastr_grp_rbrack, 2),
    DECLARE_BINDING(rastr_unop_op, 2),
    DECLARE_BINDING(rastr_unop_expr, 2),
    DECLARE_BINDING(rastr_binop_lexpr, 2),
    DECLARE_BINDING(rastr_binop_op, 2),
    DECLARE_BINDING(rastr_binop_rexpr, 2),
    DECLARE_BINDING(rastr_rlp_kw, 2),
    DECLARE_BINDING(rastr_rlp_body, 2),
    DECLARE_BINDING(rastr_wlp_kw, 2),
    DECLARE_BINDING(rastr_wlp_cond, 2),
    DECLARE_BINDING(rastr_wlp_body, 2),
    DECLARE_BINDING(rastr_flp_kw, 2),
    DECLARE_BINDING(rastr_flp_iter, 2),
    DECLARE_BINDING(rastr_flp_body, 2),
    DECLARE_BINDING(rastr_icnd_ikw, 2),
    DECLARE_BINDING(rastr_icnd_cond, 2),
    DECLARE_BINDING(rastr_icnd_ibody, 2),
    DECLARE_BINDING(rastr_iecnd_ikw, 2),
    DECLARE_BINDING(rastr_iecnd_cond, 2),
    DECLARE_BINDING(rastr_iecnd_ibody, 2),
    DECLARE_BINDING(rastr_iecnd_ekw, 2),
    DECLARE_BINDING(rastr_iecnd_ebody, 2),
    DECLARE_BINDING(rastr_fndefn_hd, 2),
    DECLARE_BINDING(rastr_fndefn_params, 2),
    DECLARE_BINDING(rastr_fndefn_body, 2),
    DECLARE_BINDING(rastr_fncall_fun, 2),
    DECLARE_BINDING(rastr_fncall_args, 2),
    DECLARE_BINDING(rastr_sub_obj, 2),
    DECLARE_BINDING(rastr_sub_inds, 2),
    DECLARE_BINDING(rastr_idx_obj, 2),
    DECLARE_BINDING(rastr_idx_inds, 2),
    DECLARE_BINDING(rastr_params_lbrack, 2),
    DECLARE_BINDING(rastr_params_len, 2),
    DECLARE_BINDING(rastr_params_seq, 2),
    DECLARE_BINDING(rastr_params_rbrack, 2),
    DECLARE_BINDING(rastr_dparam_name, 2),
    DECLARE_BINDING(rastr_dparam_op, 2),
    DECLARE_BINDING(rastr_dparam_expr, 2),
    DECLARE_BINDING(rastr_ndparam_name, 2),
    DECLARE_BINDING(rastr_args_lbrack, 2),
    DECLARE_BINDING(rastr_args_len, 2),
    DECLARE_BINDING(rastr_args_seq, 2),
    DECLARE_BINDING(rastr_args_rbrack, 2),
    DECLARE_BINDING(rastr_narg_name, 2),
    DECLARE_BINDING(rastr_narg_op, 2),
    DECLARE_BINDING(rastr_narg_expr, 2),
    DECLARE_BINDING(rastr_parg_expr, 2),
    DECLARE_BINDING(rastr_cnd_lbrack, 2),
    DECLARE_BINDING(rastr_cnd_expr, 2),
    DECLARE_BINDING(rastr_cnd_rbrack, 2),
    DECLARE_BINDING(rastr_iter_lbrack, 2),
    DECLARE_BINDING(rastr_iter_var, 2),
    DECLARE_BINDING(rastr_iter_kw, 2),
    DECLARE_BINDING(rastr_iter_expr, 2),
    DECLARE_BINDING(rastr_iter_rbrack, 2),
    DECLARE_BINDING(rastr_pgm_len, 2),
    DECLARE_BINDING(rastr_pgm_seq, 2),
    DECLARE_BINDING(rastr_dlmtd_expr, 2),
    DECLARE_BINDING(rastr_dlmtd_dlmtr, 2),
    DECLARE_BINDING(rastr_err_msg, 2),

    /* export */
    DECLARE_BINDING(rastr_export_to_dot, 3),
    {NULL, NULL, 0}};

void R_init_rastr(DllInfo* dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);

    R_RegisterCCallable(
        "rastr", "rastr_parse_str", (DL_FUNC) (rastr_parse_str));
    R_RegisterCCallable(
        "rastr", "rastr_parse_file", (DL_FUNC) (rastr_parse_file));
    R_RegisterCCallable(
        "rastr", "rastr_export_to_dot", (DL_FUNC) (rastr_export_to_dot));
}

void R_unload_rastr(DllInfo* info) {
}
