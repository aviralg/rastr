#ifndef RASTR_INTEROP_H
#define RASTR_INTEROP_H

#include <rastr/RIncludes.h>

#ifdef __cplusplus
extern "C" {
#endif

void rastr_log_error(const char* fmt, ...);

void rastr_log_warning(const char* fmt, ...);

void rastr_sexp_acquire(SEXP r_object);
void rastr_sexp_release(SEXP r_object);

SEXP rastr_sexp_set_class(SEXP r_object, SEXP r_class);

SEXP rastr_lgl_wrap(int value);
int rastr_lgl_unwrap(SEXP r_value);

SEXP rastr_int_wrap(int value);
int rastr_int_unwrap(SEXP r_value);

SEXP rastr_dbl_wrap(double value);
double rastr_dbl_unwrap(SEXP r_value);

SEXP rastr_str_wrap(const char* string);
const char* rastr_str_unwrap(SEXP r_character);

SEXP rastr_c_pointer_to_r_externalptr(void* pointer,
                                      SEXP r_tag,
                                      SEXP r_prot,
                                      R_CFinalizer_t finalizer);
void* rastr_r_externalptr_to_c_pointer(SEXP r_pointer);

void rastr_r_externalptr_clear(SEXP r_externalptr);

SEXP rastr_create_list(int column_count, ...);

SEXP rastr_create_data_frame(int column_count, ...);

SEXP r_rastr_get_object_details(SEXP r_value,
                                SEXP r_variable,
                                SEXP r_environment,
                                SEXP r_peek);

#ifdef __cplusplus
}
#endif

#endif /* RASTR_INTEROP_H */
