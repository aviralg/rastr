#ifndef RASTR_INTERNAL_API_H
#define RASTR_INTERNAL_API_H

#include "StringView.h"

extern rastr_node_t RASTR_NODE_UNDEFINED;
extern rastr_node_t RASTR_NODE_NEWLINE;

int rastr_node_is_undefined(rastr_node_t node);
int rastr_node_is_newline(rastr_node_t node);

/*******************************************************************************
 * op
 *******************************************************************************/

rastr_node_t rastr_op_new_unsafe(rastr_ast_t ast,
                                  rastr_node_type_t type,
                                  rastr_node_t gap,
                                  rastr_node_t loc);

rastr_node_t rastr_sp_new_unsafe(rastr_ast_t ast,
                                  char* syn,
                                  rastr_node_t gap,
                                  rastr_node_t loc);

/*******************************************************************************
 * bkt
 *******************************************************************************/

rastr_node_t rastr_bkt_new_unsafe(rastr_ast_t ast,
                                   rastr_node_type_t type,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

/*******************************************************************************
 * dlmtr
 *******************************************************************************/

rastr_node_t rastr_dlmtr_new_unsafe(rastr_ast_t ast,
                                     rastr_node_type_t type,
                                     rastr_node_t gap,
                                     rastr_node_t loc);

/*******************************************************************************
 * int
 *******************************************************************************/

rastr_node_t rastr_int_new_unsafe(rastr_ast_t ast,
                                   int val,
                                   char* syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

/*******************************************************************************
 * dbl
 *******************************************************************************/

rastr_node_t rastr_dbl_new_unsafe(rastr_ast_t ast,
                                   double val,
                                   char* syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

/*******************************************************************************
 * cpx
 *******************************************************************************/

rastr_node_t rastr_cpx_new_unsafe(rastr_ast_t ast,
                                   Rcomplex val,
                                   char* syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

/*******************************************************************************
 * chr
 *******************************************************************************/

rastr_node_t rastr_chr_new_unsafe(rastr_ast_t ast,
                                   char* val,
                                   char* syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

/*******************************************************************************
 * sym
 *******************************************************************************/

rastr_node_t rastr_sym_new_unsafe(rastr_ast_t ast,
                                   char* val,
                                   char* syn,
                                   rastr_node_t gap,
                                   rastr_node_t loc);

void rastr_node_destroy(rastr_ast_t ast, rastr_node_t node);

/*******************************************************************************
 * gap
 *******************************************************************************/

rastr_node_t
rastr_gap_new_unsafe(rastr_ast_t ast, char* val, rastr_node_t loc);

/*******************************************************************************
 * beg
 *******************************************************************************/

rastr_node_t
rastr_beg_new_unsafe(rastr_ast_t ast, char* bom, rastr_node_t loc);

/*******************************************************************************
 * err
 *******************************************************************************/

rastr_node_t
rastr_err_new_unsafe(rastr_ast_t ast, char* msg, rastr_node_t loc);

/*******************************************************************************
 * loc
 *******************************************************************************/

rastr_node_t rastr_loc_new(rastr_ast_t ast,
                           int lrow,
                           int lcol,
                           int lchr,
                           int lbyte,
                           int rrow,
                           int rcol,
                           int rchr,
                           int rbyte);

#endif /* RASTR_INTERNAL_API_H */
