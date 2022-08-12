#include "interop.h"
#include <stdio.h>
#include "utilities.h"
#include <stdarg.h>

#define MESSAGE_BUFFER_SIZE 4096

char message_buffer[MESSAGE_BUFFER_SIZE];

char* get_message_buffer() {
    return message_buffer;
}

void rastr_log_error(const char* fmt, ...) {
    char* buffer = get_message_buffer();
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    Rf_error("%s", buffer);
}

void rastr_log_errorcall(SEXP call, const char* fmt, ...) {
    char* buffer = get_message_buffer();
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    Rf_errorcall(call, "%s", buffer);
}

void rastr_log_warning(const char* fmt, ...) {
    char* buffer = get_message_buffer();
    va_list args;
    va_start(args, fmt);
    vsprintf(buffer, fmt, args);
    va_end(args);
    Rf_warning(buffer);
}

void rastr_sexp_acquire(SEXP r_object) {
    if (r_object != NULL) {
        R_PreserveObject(r_object);
    }
}

void rastr_sexp_release(SEXP r_object) {
    if (r_object != NULL) {
        R_ReleaseObject(r_object);
    }
}

SEXP rastr_sexp_set_class(SEXP r_object, SEXP r_class) {
    Rf_setAttrib(r_object, R_ClassSymbol, r_class);
    return r_object;
}

SEXP rastr_sexp_set_names(SEXP r_object, SEXP r_names) {
    Rf_setAttrib(r_object, R_NamesSymbol, r_names);
    return r_object;
}

SEXP rastr_sexp_set_row_names(SEXP r_object, SEXP r_row_names) {
    Rf_setAttrib(r_object, R_RowNamesSymbol, r_row_names);
    return r_object;
}

SEXP rastr_lgl_wrap(int value) {
    return ScalarLogical(value);
}

int rastr_lgl_unwrap(SEXP r_value) {
    return asLogical(r_value);
}

SEXP rastr_int_wrap(int value) {
    return ScalarInteger(value);
}

int rastr_int_unwrap(SEXP r_value) {
    return asInteger(r_value);
}

SEXP rastr_dbl_wrap(double value) {
    return ScalarReal(value);
}

double rastr_dbl_unwrap(SEXP r_value) {
    return asReal(r_value);
}

SEXP rastr_cplx_wrap(Rcomplex value) {
    return ScalarComplex(value);
}

Rcomplex rastr_cplx_unwrap(SEXP r_cplx) {
    return asComplex(r_cplx);
}

SEXP rastr_c_pointer_to_r_externalptr(void* pointer,
                                      SEXP r_tag,
                                      SEXP r_prot,
                                      R_CFinalizer_t finalizer) {
    SEXP r_value = R_MakeExternalPtr(pointer, r_tag, r_prot);
    if (finalizer != NULL) {
        R_RegisterCFinalizerEx(r_value, finalizer, TRUE);
    }
    return r_value;
}

SEXP rastr_str_wrap(const char* string) {
    SEXP r_str = Rf_allocVector(STRSXP, 1);
    SET_STRING_ELT(r_str, 0, string == nullptr ? NA_STRING : mkChar(string));
    return r_str;
}

const char* rastr_str_unwrap(SEXP r_character) {
    SEXP r_chr = STRING_ELT(r_character, 0);
    return r_chr == NA_STRING ? nullptr : CHAR(r_chr);
}

SEXP rastr_sym_wrap(const char* sym) {
    return Rf_install(sym);
}

const char* rastr_sym_unwrap(SEXP r_sym) {
    return CHAR(PRINTNAME(r_sym));
}

void* rastr_r_externalptr_to_c_pointer(SEXP r_pointer) {
    return R_ExternalPtrAddr(r_pointer);
}

void rastr_r_externalptr_clear(SEXP r_externalptr) {
    return R_ClearExternalPtr(r_externalptr);
}

SEXP create_list(int column_count, va_list columns) {
    va_list protection;

    va_copy(protection, columns);

    /* NOTE: protect all arguments before allocating memory */
    for (int i = 0; i < column_count; ++i) {
        const char* name = va_arg(protection, const char*);
        SEXP column = va_arg(protection, SEXP);
        PROTECT(column);
    }

    va_end(protection);

    SEXP r_list = PROTECT(allocVector(VECSXP, column_count));

    SEXP r_column_names = PROTECT(allocVector(STRSXP, column_count));

    for (int i = 0; i < column_count; ++i) {
        const char* name = va_arg(columns, const char*);
        SEXP column = va_arg(columns, SEXP);
        SET_STRING_ELT(r_column_names, i, mkChar(name));
        SET_VECTOR_ELT(r_list, i, column);
    }

    rastr_sexp_set_names(r_list, r_column_names);

    UNPROTECT(2 + column_count);

    return r_list;
}

SEXP set_row_names(SEXP r_data_frame) {
    int row_count = 0;

    if (LENGTH(r_data_frame) > 0) {
        row_count = LENGTH(VECTOR_ELT(r_data_frame, 0));
    }

    SEXP r_row_names = PROTECT(allocVector(STRSXP, row_count));

    for (int i = 0; i < row_count; ++i) {
        SET_STRING_ELT(r_row_names, i, mkChar(int_to_string(i + 1)));
    }

    rastr_sexp_set_row_names(r_data_frame, r_row_names);

    UNPROTECT(1);

    return r_data_frame;
}

SEXP rastr_create_list(int column_count, ...) {
    va_list columns;
    va_start(columns, column_count);

    SEXP r_list = PROTECT(create_list(column_count, columns));

    va_end(columns);

    UNPROTECT(1);

    return r_list;
}

SEXP rastr_create_data_frame(int column_count, ...) {
    va_list columns;
    va_start(columns, column_count);

    SEXP r_data_frame = PROTECT(create_list(column_count, columns));

    va_end(columns);

    set_row_names(r_data_frame);

    rastr_sexp_set_class(r_data_frame, mkString("data.frame"));

    UNPROTECT(1);

    return r_data_frame;
}

SEXP r_rastr_get_object_details(SEXP r_value,
                                SEXP r_variable,
                                SEXP r_environment,
                                SEXP r_peek) {
    SEXP r_actual_value = r_value;

    if (r_variable != R_NilValue) {
        const char* variable = CHAR(STRING_ELT(r_variable, 0));

        r_actual_value = Rf_findVarInFrame(r_environment, Rf_install(variable));

        int peek = LOGICAL(r_peek)[0];

        if (peek && TYPEOF(r_actual_value) == PROMSXP) {
            r_actual_value = PREXPR(r_actual_value);
        }
    }

    char address[1024];

    if (sprintf(address, "%p", (void*) r_actual_value) == -1) {
        Rf_error("Getting address of SEXP failed");
    }

    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, 2));
    SET_VECTOR_ELT(r_result, 0, Rf_mkString(address));
    SET_VECTOR_ELT(
        r_result, 1, Rf_mkString(Rf_type2char(TYPEOF(r_actual_value))));

    SEXP r_names = PROTECT(Rf_allocVector(STRSXP, 2));
    SET_STRING_ELT(r_names, 0, mkChar("address"));
    SET_STRING_ELT(r_names, 1, mkChar("type"));

    Rf_setAttrib(r_result, R_NamesSymbol, r_names);

    UNPROTECT(2);

    return r_result;
}

SEXP str_scl(const char* val) {
    SEXP r_str = Rf_allocVector(STRSXP, 1);
    SET_STRING_ELT(r_str, 0, val == nullptr ? NA_STRING : mkChar(val));
    return r_str;
}

SEXP str_vec(int size, const char* val) {
    SEXP r_str = PROTECT(allocVector(STRSXP, size));
    SEXP r_val = PROTECT(val == nullptr ? NA_STRING : mkChar(val));

    for (int i = 0; i < size; ++i) {
        SET_STRING_ELT(r_str, i, r_val);
    }

    UNPROTECT(2);
    return r_str;
}

const char* str_get(SEXP r_vec, int index) {
    SEXP r_char = STRING_ELT(r_vec, index);
    return r_char == NA_STRING ? nullptr : CHAR(r_char);
}

void str_set(SEXP r_vec, int index, const char* val) {
    SEXP r_val = PROTECT(val == nullptr ? NA_STRING : mkChar(val));
    SET_STRING_ELT(r_vec, index, r_val);
    UNPROTECT(1);
}

SEXP lgl_scl(int value) {
    return ScalarLogical(value);
}

SEXP lgl_vec(int size, int val) {
    SEXP r_lgl = allocVector(LGLSXP, size);

    for (int i = 0; i < size; ++i) {
        lgl_set(r_lgl, i, val);
    }

    return r_lgl;
}

int lgl_get(SEXP r_vec, int index) {
    return LOGICAL(r_vec)[index];
}

void lgl_set(SEXP r_vec, int index, int val) {
    LOGICAL(r_vec)[index] = val;
}

SEXP int_scl(int value) {
    return ScalarInteger(value);
}

SEXP int_vec(int size, int val) {
    SEXP r_int = allocVector(INTSXP, size);

    for (int i = 0; i < size; ++i) {
        INTEGER(r_int)[i] = val;
    }
    return r_int;
}

int int_get(SEXP r_vec, int index) {
    return INTEGER(r_vec)[index];
}

void int_set(SEXP r_vec, int index, int val) {
    INTEGER(r_vec)[index] = val;
}

SEXP dbl_scl(double value) {
    return ScalarReal(value);
}

SEXP dbl_vec(int size, double val) {
    SEXP r_dbl = allocVector(REALSXP, size);

    for (int i = 0; i < size; ++i) {
        REAL(r_dbl)[i] = val;
    }

    return r_dbl;
}

double dbl_get(SEXP r_vec, int index) {
    return REAL(r_vec)[index];
}

void dbl_set(SEXP r_vec, int index, double val) {
    REAL(r_vec)[index] = val;
}

SEXP cplx_scl(const Rcomplex& value) {
    return ScalarComplex(value);
}

SEXP cplx_vec(int size, const Rcomplex& val) {
    SEXP r_cplx = allocVector(CPLXSXP, size);

    for (int i = 0; i < size; ++i) {
        COMPLEX(r_cplx)[i] = val;
    }

    return r_cplx;
}

const Rcomplex& cplx_get(SEXP r_vec, int index) {
    return COMPLEX(r_vec)[index];
}

void cplx_set(SEXP r_vec, int index, const Rcomplex& val) {
    COMPLEX(r_vec)[index] = val;
}
