#ifndef RASTR_INTEROP_H
#define RASTR_INTEROP_H

#include <rastr/RIncludes.h>

#ifdef __cplusplus
extern "C" {
#endif

void rastr_log_error(const char* fmt, ...);
void rastr_log_errorcall(SEXP call, const char* fmt, ...);
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

SEXP rastr_cplx_wrap(Rcomplex value);
Rcomplex rastr_cplx_unwrap(SEXP r_cplx);

SEXP rastr_str_wrap(const char* string);
const char* rastr_str_unwrap(SEXP r_character);

SEXP rastr_sym_wrap(const char* sym);
const char* rastr_sym_unwrap(SEXP r_sym);

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

int vec_len(SEXP r_vec);

SEXP chr_vec1(const char* val);
SEXP chr_vec(int size, const char* val);
const char* chr_get(SEXP r_vec, int index);
void chr_set(SEXP r_vec, int index, const char* val);

SEXP lgl_vec1(int val);
SEXP lgl_vec(int size, int val);
int lgl_get(SEXP r_vec, int index);
void lgl_set(SEXP r_vec, int index, int val);

SEXP int_vec1(int val);
SEXP int_vec(int size, int val);
int int_get(SEXP r_vec, int index);
void int_set(SEXP r_vec, int index, int val);

SEXP dbl_vec1(double val);
SEXP dbl_vec(int size, double val);
double dbl_get(SEXP r_vec, int index);
void dbl_set(SEXP r_vec, int index, double val);

double num_get(SEXP r_vec, int index);

SEXP cpx_vec1(const Rcomplex& val);
SEXP cpx_vec(int size, const Rcomplex& val);
Rcomplex cpx_get(SEXP r_vec, int index);
void cpx_set(SEXP r_vec, int index, const Rcomplex& val);

SEXP attr_get(SEXP r_obj, SEXP r_attr);
SEXP class_get(SEXP r_obj);
bool class_has(SEXP r_obj, const char* cls);

#ifdef __cplusplus
}
#endif

#endif /* RASTR_INTEROP_H */
