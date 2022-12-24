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

    /*******************************************************************************
     * ast
     *******************************************************************************/

    DECLARE_BINDING(rastr_ast_new, 1),
    DECLARE_BINDING(rastr_ast_id, 1),
    DECLARE_BINDING(rastr_ast_size, 1),
    DECLARE_BINDING(rastr_ast_root_get, 1),
    DECLARE_BINDING(rastr_ast_root_rep, 2),
    DECLARE_BINDING(rastr_ast_root_set, 2),

    /*******************************************************************************
     * op
     *******************************************************************************/

    DECLARE_BINDING(rastr_op_new, 4),
    DECLARE_BINDING(rastr_op_syn_get, 2),

    /*******************************************************************************
     * bkt
     *******************************************************************************/

    DECLARE_BINDING(rastr_bkt_new, 4),
    DECLARE_BINDING(rastr_bkt_syn_get, 2),

    /*******************************************************************************
     * dlmtr
     *******************************************************************************/

    DECLARE_BINDING(rastr_dlmtr_new, 4),
    DECLARE_BINDING(rastr_dlmtr_syn_get, 2),

    /*******************************************************************************
     * lgl
     *******************************************************************************/

    DECLARE_BINDING(rastr_lgl_new, 4),
    DECLARE_BINDING(rastr_lgl_syn_get, 2),

    /*******************************************************************************
     * int
     *******************************************************************************/

    DECLARE_BINDING(rastr_int_new, 4),

    /*******************************************************************************
     * dbl
     *******************************************************************************/

    DECLARE_BINDING(rastr_dbl_new, 4),

    /*******************************************************************************
     * cpx
     *******************************************************************************/

    DECLARE_BINDING(rastr_cpx_new, 4),

    /*******************************************************************************
     * chr
     *******************************************************************************/

    DECLARE_BINDING(rastr_chr_new, 4),

    /*******************************************************************************
     * sym
     *******************************************************************************/

    DECLARE_BINDING(rastr_sym_new, 5),

    // pred
    DECLARE_BINDING(rastr_lit_type, 2),

    /*******************************************************************************
     * gap
     *******************************************************************************/

    DECLARE_BINDING(rastr_gap_new, 3),

    /*******************************************************************************
     * beg
     *******************************************************************************/

    DECLARE_BINDING(rastr_beg_new, 3),
#include "autogen_init.h"

    /* export */
    DECLARE_BINDING(rastr_export_to_dot, 3),

    DECLARE_BINDING(rastr_ast_unparse_str, 1),
    DECLARE_BINDING(rastr_node_unparse_str, 2),

    /* as_sexp */
    DECLARE_BINDING(rastr_ast_as_sexp, 1),
    DECLARE_BINDING(rastr_node_as_sexp, 2),

    /* as_df */
    DECLARE_BINDING(rastr_ast_as_df, 1),
    DECLARE_BINDING(rastr_node_as_df, 2),
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
