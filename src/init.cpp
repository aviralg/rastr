#include <rastr/api.h>
#include <R_ext/Rdynload.h>

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
