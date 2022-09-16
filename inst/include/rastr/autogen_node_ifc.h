/*******************************************************************************
* op
*******************************************************************************/
// pred
int rastr_op_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_op_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_op_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_op_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_op_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_op_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_op_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_op_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* dlmtr
*******************************************************************************/
// pred
int rastr_dlmtr_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtr_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_dlmtr_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtr_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dlmtr_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_dlmtr_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_dlmtr_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_dlmtr_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_dlmtr_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtr_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* bkt
*******************************************************************************/
// pred
int rastr_bkt_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_bkt_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_bkt_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_bkt_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_bkt_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_bkt_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_bkt_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_bkt_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_bkt_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_bkt_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* null
*******************************************************************************/
rastr_node_t rastr_null_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_null_new(SEXP r_ast, SEXP r_gap, SEXP r_loc);
// pred
int rastr_null_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_null_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_null_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_null_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_null_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_null_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_null_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_null_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_null_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_null_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* lgl
*******************************************************************************/
// pred
int rastr_lgl_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lgl_type(SEXP r_ast, SEXP r_node);
/* val ************************************************************************/
// get
int rastr_lgl_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lgl_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_lgl_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lgl_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_lgl_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_lgl_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_lgl_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_lgl_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_lgl_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_lgl_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* int
*******************************************************************************/
// pred
int rastr_int_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_int_type(SEXP r_ast, SEXP r_node);
/* syn ************************************************************************/
// get
const char* rastr_int_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_int_syn_get(SEXP r_ast, SEXP r_node);


/* val ************************************************************************/
// get
int rastr_int_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_int_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_int_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_int_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_int_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_int_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_int_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_int_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_int_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_int_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* dbl
*******************************************************************************/
// pred
int rastr_dbl_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dbl_type(SEXP r_ast, SEXP r_node);
/* syn ************************************************************************/
// get
const char* rastr_dbl_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dbl_syn_get(SEXP r_ast, SEXP r_node);


/* val ************************************************************************/
// get
double rastr_dbl_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dbl_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_dbl_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dbl_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dbl_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_dbl_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_dbl_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_dbl_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_dbl_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dbl_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* cpx
*******************************************************************************/
// pred
int rastr_cpx_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cpx_type(SEXP r_ast, SEXP r_node);
/* syn ************************************************************************/
// get
const char* rastr_cpx_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cpx_syn_get(SEXP r_ast, SEXP r_node);


/* val ************************************************************************/
// get
Rcomplex rastr_cpx_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cpx_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_cpx_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cpx_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_cpx_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_cpx_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_cpx_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_cpx_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_cpx_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cpx_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* chr
*******************************************************************************/
// pred
int rastr_chr_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_chr_type(SEXP r_ast, SEXP r_node);
/* syn ************************************************************************/
// get
const char* rastr_chr_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_chr_syn_get(SEXP r_ast, SEXP r_node);


/* val ************************************************************************/
// get
const char* rastr_chr_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_chr_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_chr_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_chr_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_chr_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_chr_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_chr_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_chr_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_chr_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_chr_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* sym
*******************************************************************************/
// pred
int rastr_sym_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sym_type(SEXP r_ast, SEXP r_node);
/* syn ************************************************************************/
// get
const char* rastr_sym_syn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sym_syn_get(SEXP r_ast, SEXP r_node);


/* val ************************************************************************/
// get
const char* rastr_sym_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sym_val_get(SEXP r_ast, SEXP r_node);


/* gap ************************************************************************/
// get
rastr_node_t rastr_sym_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sym_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_sym_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_sym_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_sym_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_sym_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_sym_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sym_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* blk
*******************************************************************************/
rastr_node_t rastr_blk_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t exprs, rastr_node_t rbkt);
SEXP r_rastr_blk_new(SEXP r_ast, SEXP r_lbkt, SEXP r_exprs, SEXP r_rbkt);
// pred
int rastr_blk_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_blk_type(SEXP r_ast, SEXP r_node);
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_blk_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_blk_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_blk_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_blk_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_blk_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_blk_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* exprs **********************************************************************/
// get
rastr_node_t rastr_blk_exprs_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_blk_exprs_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_blk_exprs_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs);
SEXP r_rastr_blk_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_exprs);
// set
void rastr_blk_exprs_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs);
SEXP r_rastr_blk_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_exprs);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_blk_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_blk_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_blk_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_blk_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_blk_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_blk_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* grp
*******************************************************************************/
rastr_node_t rastr_grp_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t expr, rastr_node_t rbkt);
SEXP r_rastr_grp_new(SEXP r_ast, SEXP r_lbkt, SEXP r_expr, SEXP r_rbkt);
// pred
int rastr_grp_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_grp_type(SEXP r_ast, SEXP r_node);
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_grp_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_grp_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_grp_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_grp_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_grp_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_grp_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_grp_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_grp_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_grp_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_grp_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_grp_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_grp_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_grp_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_grp_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_grp_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_grp_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_grp_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_grp_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* nuop
*******************************************************************************/
rastr_node_t rastr_nuop_new(rastr_ast_t ast, rastr_node_t op);
SEXP r_rastr_nuop_new(SEXP r_ast, SEXP r_op);
// pred
int rastr_nuop_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_nuop_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_nuop_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_nuop_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_nuop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_nuop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_nuop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_nuop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);




/*******************************************************************************
* unop
*******************************************************************************/
rastr_node_t rastr_unop_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t expr);
SEXP r_rastr_unop_new(SEXP r_ast, SEXP r_op, SEXP r_expr);
// pred
int rastr_unop_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_unop_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_unop_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_unop_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_unop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_unop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_unop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_unop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_unop_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_unop_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_unop_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_unop_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_unop_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_unop_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);




/*******************************************************************************
* binop
*******************************************************************************/
rastr_node_t rastr_binop_new(rastr_ast_t ast, rastr_node_t lexpr, rastr_node_t op, rastr_node_t rexpr);
SEXP r_rastr_binop_new(SEXP r_ast, SEXP r_lexpr, SEXP r_op, SEXP r_rexpr);
// pred
int rastr_binop_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_binop_type(SEXP r_ast, SEXP r_node);
/* lexpr **********************************************************************/
// get
rastr_node_t rastr_binop_lexpr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_binop_lexpr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_binop_lexpr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lexpr);
SEXP r_rastr_binop_lexpr_rep(SEXP r_ast, SEXP r_node, SEXP r_lexpr);
// set
void rastr_binop_lexpr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lexpr);
SEXP r_rastr_binop_lexpr_set(SEXP r_ast, SEXP r_node, SEXP r_lexpr);


/* op *************************************************************************/
// get
rastr_node_t rastr_binop_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_binop_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_binop_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_binop_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_binop_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_binop_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* rexpr **********************************************************************/
// get
rastr_node_t rastr_binop_rexpr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_binop_rexpr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_binop_rexpr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rexpr);
SEXP r_rastr_binop_rexpr_rep(SEXP r_ast, SEXP r_node, SEXP r_rexpr);
// set
void rastr_binop_rexpr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rexpr);
SEXP r_rastr_binop_rexpr_set(SEXP r_ast, SEXP r_node, SEXP r_rexpr);




/*******************************************************************************
* rlp
*******************************************************************************/
rastr_node_t rastr_rlp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t body);
SEXP r_rastr_rlp_new(SEXP r_ast, SEXP r_op, SEXP r_body);
// pred
int rastr_rlp_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_rlp_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_rlp_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_rlp_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_rlp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_rlp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_rlp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_rlp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* body ***********************************************************************/
// get
rastr_node_t rastr_rlp_body_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_rlp_body_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_rlp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_rlp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body);
// set
void rastr_rlp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_rlp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body);




/*******************************************************************************
* wlp
*******************************************************************************/
rastr_node_t rastr_wlp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t cond, rastr_node_t body);
SEXP r_rastr_wlp_new(SEXP r_ast, SEXP r_op, SEXP r_cond, SEXP r_body);
// pred
int rastr_wlp_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_wlp_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_wlp_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_wlp_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_wlp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_wlp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_wlp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_wlp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* cond ***********************************************************************/
// get
rastr_node_t rastr_wlp_cond_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_wlp_cond_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_wlp_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_wlp_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond);
// set
void rastr_wlp_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_wlp_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond);


/* body ***********************************************************************/
// get
rastr_node_t rastr_wlp_body_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_wlp_body_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_wlp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_wlp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body);
// set
void rastr_wlp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_wlp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body);




/*******************************************************************************
* flp
*******************************************************************************/
rastr_node_t rastr_flp_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t iter, rastr_node_t body);
SEXP r_rastr_flp_new(SEXP r_ast, SEXP r_op, SEXP r_iter, SEXP r_body);
// pred
int rastr_flp_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_flp_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_flp_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_flp_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_flp_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_flp_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_flp_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_flp_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* iter ***********************************************************************/
// get
rastr_node_t rastr_flp_iter_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_flp_iter_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_flp_iter_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iter);
SEXP r_rastr_flp_iter_rep(SEXP r_ast, SEXP r_node, SEXP r_iter);
// set
void rastr_flp_iter_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iter);
SEXP r_rastr_flp_iter_set(SEXP r_ast, SEXP r_node, SEXP r_iter);


/* body ***********************************************************************/
// get
rastr_node_t rastr_flp_body_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_flp_body_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_flp_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_flp_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body);
// set
void rastr_flp_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_flp_body_set(SEXP r_ast, SEXP r_node, SEXP r_body);




/*******************************************************************************
* icond
*******************************************************************************/
rastr_node_t rastr_icond_new(rastr_ast_t ast, rastr_node_t iop, rastr_node_t cond, rastr_node_t ibody);
SEXP r_rastr_icond_new(SEXP r_ast, SEXP r_iop, SEXP r_cond, SEXP r_ibody);
// pred
int rastr_icond_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_icond_type(SEXP r_ast, SEXP r_node);
/* iop ************************************************************************/
// get
rastr_node_t rastr_icond_iop_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_icond_iop_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_icond_iop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop);
SEXP r_rastr_icond_iop_rep(SEXP r_ast, SEXP r_node, SEXP r_iop);
// set
void rastr_icond_iop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop);
SEXP r_rastr_icond_iop_set(SEXP r_ast, SEXP r_node, SEXP r_iop);


/* cond ***********************************************************************/
// get
rastr_node_t rastr_icond_cond_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_icond_cond_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_icond_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_icond_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond);
// set
void rastr_icond_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_icond_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond);


/* ibody **********************************************************************/
// get
rastr_node_t rastr_icond_ibody_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_icond_ibody_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_icond_ibody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody);
SEXP r_rastr_icond_ibody_rep(SEXP r_ast, SEXP r_node, SEXP r_ibody);
// set
void rastr_icond_ibody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody);
SEXP r_rastr_icond_ibody_set(SEXP r_ast, SEXP r_node, SEXP r_ibody);




/*******************************************************************************
* iecond
*******************************************************************************/
rastr_node_t rastr_iecond_new(rastr_ast_t ast, rastr_node_t iop, rastr_node_t cond, rastr_node_t ibody, rastr_node_t eop, rastr_node_t ebody);
SEXP r_rastr_iecond_new(SEXP r_ast, SEXP r_iop, SEXP r_cond, SEXP r_ibody, SEXP r_eop, SEXP r_ebody);
// pred
int rastr_iecond_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_type(SEXP r_ast, SEXP r_node);
/* iop ************************************************************************/
// get
rastr_node_t rastr_iecond_iop_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_iop_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iecond_iop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop);
SEXP r_rastr_iecond_iop_rep(SEXP r_ast, SEXP r_node, SEXP r_iop);
// set
void rastr_iecond_iop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t iop);
SEXP r_rastr_iecond_iop_set(SEXP r_ast, SEXP r_node, SEXP r_iop);


/* cond ***********************************************************************/
// get
rastr_node_t rastr_iecond_cond_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_cond_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iecond_cond_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_iecond_cond_rep(SEXP r_ast, SEXP r_node, SEXP r_cond);
// set
void rastr_iecond_cond_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t cond);
SEXP r_rastr_iecond_cond_set(SEXP r_ast, SEXP r_node, SEXP r_cond);


/* ibody **********************************************************************/
// get
rastr_node_t rastr_iecond_ibody_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_ibody_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iecond_ibody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody);
SEXP r_rastr_iecond_ibody_rep(SEXP r_ast, SEXP r_node, SEXP r_ibody);
// set
void rastr_iecond_ibody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ibody);
SEXP r_rastr_iecond_ibody_set(SEXP r_ast, SEXP r_node, SEXP r_ibody);


/* eop ************************************************************************/
// get
rastr_node_t rastr_iecond_eop_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_eop_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iecond_eop_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t eop);
SEXP r_rastr_iecond_eop_rep(SEXP r_ast, SEXP r_node, SEXP r_eop);
// set
void rastr_iecond_eop_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t eop);
SEXP r_rastr_iecond_eop_set(SEXP r_ast, SEXP r_node, SEXP r_eop);


/* ebody **********************************************************************/
// get
rastr_node_t rastr_iecond_ebody_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iecond_ebody_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iecond_ebody_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t ebody);
SEXP r_rastr_iecond_ebody_rep(SEXP r_ast, SEXP r_node, SEXP r_ebody);
// set
void rastr_iecond_ebody_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t ebody);
SEXP r_rastr_iecond_ebody_set(SEXP r_ast, SEXP r_node, SEXP r_ebody);




/*******************************************************************************
* fndefn
*******************************************************************************/
rastr_node_t rastr_fndefn_new(rastr_ast_t ast, rastr_node_t op, rastr_node_t lbkt, rastr_node_t pars, rastr_node_t rbkt, rastr_node_t body);
SEXP r_rastr_fndefn_new(SEXP r_ast, SEXP r_op, SEXP r_lbkt, SEXP r_pars, SEXP r_rbkt, SEXP r_body);
// pred
int rastr_fndefn_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_type(SEXP r_ast, SEXP r_node);
/* op *************************************************************************/
// get
rastr_node_t rastr_fndefn_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fndefn_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_fndefn_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_fndefn_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_fndefn_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_fndefn_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fndefn_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_fndefn_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_fndefn_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_fndefn_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* pars ***********************************************************************/
// get
rastr_node_t rastr_fndefn_pars_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_pars_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fndefn_pars_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t pars);
SEXP r_rastr_fndefn_pars_rep(SEXP r_ast, SEXP r_node, SEXP r_pars);
// set
void rastr_fndefn_pars_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t pars);
SEXP r_rastr_fndefn_pars_set(SEXP r_ast, SEXP r_node, SEXP r_pars);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_fndefn_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fndefn_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_fndefn_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_fndefn_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_fndefn_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);


/* body ***********************************************************************/
// get
rastr_node_t rastr_fndefn_body_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fndefn_body_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fndefn_body_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_fndefn_body_rep(SEXP r_ast, SEXP r_node, SEXP r_body);
// set
void rastr_fndefn_body_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t body);
SEXP r_rastr_fndefn_body_set(SEXP r_ast, SEXP r_node, SEXP r_body);




/*******************************************************************************
* fncall
*******************************************************************************/
rastr_node_t rastr_fncall_new(rastr_ast_t ast, rastr_node_t fn, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt);
SEXP r_rastr_fncall_new(SEXP r_ast, SEXP r_fn, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt);
// pred
int rastr_fncall_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fncall_type(SEXP r_ast, SEXP r_node);
/* fn *************************************************************************/
// get
rastr_node_t rastr_fncall_fn_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fncall_fn_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fncall_fn_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t fn);
SEXP r_rastr_fncall_fn_rep(SEXP r_ast, SEXP r_node, SEXP r_fn);
// set
void rastr_fncall_fn_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t fn);
SEXP r_rastr_fncall_fn_set(SEXP r_ast, SEXP r_node, SEXP r_fn);


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_fncall_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fncall_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fncall_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_fncall_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_fncall_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_fncall_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* args ***********************************************************************/
// get
rastr_node_t rastr_fncall_args_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fncall_args_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fncall_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_fncall_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args);
// set
void rastr_fncall_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_fncall_args_set(SEXP r_ast, SEXP r_node, SEXP r_args);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_fncall_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_fncall_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_fncall_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_fncall_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_fncall_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_fncall_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* sub
*******************************************************************************/
rastr_node_t rastr_sub_new(rastr_ast_t ast, rastr_node_t obj, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt);
SEXP r_rastr_sub_new(SEXP r_ast, SEXP r_obj, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt);
// pred
int rastr_sub_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sub_type(SEXP r_ast, SEXP r_node);
/* obj ************************************************************************/
// get
rastr_node_t rastr_sub_obj_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sub_obj_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_sub_obj_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj);
SEXP r_rastr_sub_obj_rep(SEXP r_ast, SEXP r_node, SEXP r_obj);
// set
void rastr_sub_obj_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj);
SEXP r_rastr_sub_obj_set(SEXP r_ast, SEXP r_node, SEXP r_obj);


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_sub_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sub_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_sub_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_sub_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_sub_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_sub_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* args ***********************************************************************/
// get
rastr_node_t rastr_sub_args_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sub_args_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_sub_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_sub_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args);
// set
void rastr_sub_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_sub_args_set(SEXP r_ast, SEXP r_node, SEXP r_args);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_sub_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_sub_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_sub_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_sub_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_sub_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_sub_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* idx
*******************************************************************************/
rastr_node_t rastr_idx_new(rastr_ast_t ast, rastr_node_t obj, rastr_node_t lbkt, rastr_node_t args, rastr_node_t rbkt1, rastr_node_t rbkt2);
SEXP r_rastr_idx_new(SEXP r_ast, SEXP r_obj, SEXP r_lbkt, SEXP r_args, SEXP r_rbkt1, SEXP r_rbkt2);
// pred
int rastr_idx_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_type(SEXP r_ast, SEXP r_node);
/* obj ************************************************************************/
// get
rastr_node_t rastr_idx_obj_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_obj_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_idx_obj_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj);
SEXP r_rastr_idx_obj_rep(SEXP r_ast, SEXP r_node, SEXP r_obj);
// set
void rastr_idx_obj_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t obj);
SEXP r_rastr_idx_obj_set(SEXP r_ast, SEXP r_node, SEXP r_obj);


/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_idx_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_idx_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_idx_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_idx_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_idx_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* args ***********************************************************************/
// get
rastr_node_t rastr_idx_args_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_args_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_idx_args_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_idx_args_rep(SEXP r_ast, SEXP r_node, SEXP r_args);
// set
void rastr_idx_args_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t args);
SEXP r_rastr_idx_args_set(SEXP r_ast, SEXP r_node, SEXP r_args);


/* rbkt1 **********************************************************************/
// get
rastr_node_t rastr_idx_rbkt1_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_rbkt1_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_idx_rbkt1_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt1);
SEXP r_rastr_idx_rbkt1_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt1);
// set
void rastr_idx_rbkt1_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt1);
SEXP r_rastr_idx_rbkt1_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt1);


/* rbkt2 **********************************************************************/
// get
rastr_node_t rastr_idx_rbkt2_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_idx_rbkt2_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_idx_rbkt2_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt2);
SEXP r_rastr_idx_rbkt2_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt2);
// set
void rastr_idx_rbkt2_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt2);
SEXP r_rastr_idx_rbkt2_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt2);




/*******************************************************************************
* exprs
*******************************************************************************/
rastr_node_t rastr_exprs_new(rastr_ast_t ast, int len, const rastr_node_t* seq);
SEXP r_rastr_exprs_new(SEXP r_ast, SEXP r_seq);
// pred
int rastr_exprs_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_exprs_type(SEXP r_ast, SEXP r_node);
/* len ************************************************************************/
// get
int rastr_exprs_len_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_exprs_len_get(SEXP r_ast, SEXP r_node);


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_exprs_seq_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_exprs_seq_get(SEXP r_ast, SEXP r_node);
rastr_node_t rastr_exprs_get(rastr_ast_t ast, rastr_node_t node, int index);
SEXP r_rastr_exprs_get(SEXP r_ast, SEXP r_node, SEXP r_index);
// rep
rastr_node_t rastr_exprs_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t expr);
SEXP r_rastr_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_expr);
// set
void rastr_exprs_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t expr);
SEXP r_rastr_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_expr);




/*******************************************************************************
* pars
*******************************************************************************/
rastr_node_t rastr_pars_new(rastr_ast_t ast, int len, const rastr_node_t* seq);
SEXP r_rastr_pars_new(SEXP r_ast, SEXP r_seq);
// pred
int rastr_pars_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pars_type(SEXP r_ast, SEXP r_node);
/* len ************************************************************************/
// get
int rastr_pars_len_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pars_len_get(SEXP r_ast, SEXP r_node);


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_pars_seq_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pars_seq_get(SEXP r_ast, SEXP r_node);
rastr_node_t rastr_pars_get(rastr_ast_t ast, rastr_node_t node, int index);
SEXP r_rastr_pars_get(SEXP r_ast, SEXP r_node, SEXP r_index);
// rep
rastr_node_t rastr_pars_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t par);
SEXP r_rastr_pars_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_par);
// set
void rastr_pars_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t par);
SEXP r_rastr_pars_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_par);




/*******************************************************************************
* dpar
*******************************************************************************/
rastr_node_t rastr_dpar_new(rastr_ast_t ast, rastr_node_t name, rastr_node_t op, rastr_node_t expr);
SEXP r_rastr_dpar_new(SEXP r_ast, SEXP r_name, SEXP r_op, SEXP r_expr);
// pred
int rastr_dpar_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dpar_type(SEXP r_ast, SEXP r_node);
/* name ***********************************************************************/
// get
rastr_node_t rastr_dpar_name_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dpar_name_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dpar_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_dpar_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name);
// set
void rastr_dpar_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_dpar_name_set(SEXP r_ast, SEXP r_node, SEXP r_name);


/* op *************************************************************************/
// get
rastr_node_t rastr_dpar_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dpar_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dpar_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_dpar_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_dpar_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_dpar_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_dpar_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dpar_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dpar_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_dpar_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_dpar_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_dpar_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);




/*******************************************************************************
* ndpar
*******************************************************************************/
rastr_node_t rastr_ndpar_new(rastr_ast_t ast, rastr_node_t name);
SEXP r_rastr_ndpar_new(SEXP r_ast, SEXP r_name);
// pred
int rastr_ndpar_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_ndpar_type(SEXP r_ast, SEXP r_node);
/* name ***********************************************************************/
// get
rastr_node_t rastr_ndpar_name_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_ndpar_name_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_ndpar_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_ndpar_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name);
// set
void rastr_ndpar_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_ndpar_name_set(SEXP r_ast, SEXP r_node, SEXP r_name);




/*******************************************************************************
* args
*******************************************************************************/
rastr_node_t rastr_args_new(rastr_ast_t ast, int len, const rastr_node_t* seq);
SEXP r_rastr_args_new(SEXP r_ast, SEXP r_seq);
// pred
int rastr_args_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_args_type(SEXP r_ast, SEXP r_node);
/* len ************************************************************************/
// get
int rastr_args_len_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_args_len_get(SEXP r_ast, SEXP r_node);


/* seq ************************************************************************/
// get
const rastr_node_t* rastr_args_seq_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_args_seq_get(SEXP r_ast, SEXP r_node);
rastr_node_t rastr_args_get(rastr_ast_t ast, rastr_node_t node, int index);
SEXP r_rastr_args_get(SEXP r_ast, SEXP r_node, SEXP r_index);
// rep
rastr_node_t rastr_args_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t arg);
SEXP r_rastr_args_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_arg);
// set
void rastr_args_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t arg);
SEXP r_rastr_args_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_arg);




/*******************************************************************************
* narg
*******************************************************************************/
rastr_node_t rastr_narg_new(rastr_ast_t ast, rastr_node_t name, rastr_node_t op, rastr_node_t expr);
SEXP r_rastr_narg_new(SEXP r_ast, SEXP r_name, SEXP r_op, SEXP r_expr);
// pred
int rastr_narg_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_narg_type(SEXP r_ast, SEXP r_node);
/* name ***********************************************************************/
// get
rastr_node_t rastr_narg_name_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_narg_name_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_narg_name_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_narg_name_rep(SEXP r_ast, SEXP r_node, SEXP r_name);
// set
void rastr_narg_name_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t name);
SEXP r_rastr_narg_name_set(SEXP r_ast, SEXP r_node, SEXP r_name);


/* op *************************************************************************/
// get
rastr_node_t rastr_narg_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_narg_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_narg_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_narg_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_narg_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_narg_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_narg_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_narg_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_narg_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_narg_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_narg_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_narg_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);




/*******************************************************************************
* parg
*******************************************************************************/
rastr_node_t rastr_parg_new(rastr_ast_t ast, rastr_node_t expr);
SEXP r_rastr_parg_new(SEXP r_ast, SEXP r_expr);
// pred
int rastr_parg_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_parg_type(SEXP r_ast, SEXP r_node);
/* expr ***********************************************************************/
// get
rastr_node_t rastr_parg_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_parg_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_parg_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_parg_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_parg_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_parg_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);




/*******************************************************************************
* cond
*******************************************************************************/
rastr_node_t rastr_cond_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t expr, rastr_node_t rbkt);
SEXP r_rastr_cond_new(SEXP r_ast, SEXP r_lbkt, SEXP r_expr, SEXP r_rbkt);
// pred
int rastr_cond_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cond_type(SEXP r_ast, SEXP r_node);
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_cond_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cond_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_cond_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_cond_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_cond_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_cond_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_cond_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cond_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_cond_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_cond_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_cond_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_cond_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_cond_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_cond_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_cond_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_cond_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_cond_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_cond_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* iter
*******************************************************************************/
rastr_node_t rastr_iter_new(rastr_ast_t ast, rastr_node_t lbkt, rastr_node_t var, rastr_node_t op, rastr_node_t expr, rastr_node_t rbkt);
SEXP r_rastr_iter_new(SEXP r_ast, SEXP r_lbkt, SEXP r_var, SEXP r_op, SEXP r_expr, SEXP r_rbkt);
// pred
int rastr_iter_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_type(SEXP r_ast, SEXP r_node);
/* lbkt ***********************************************************************/
// get
rastr_node_t rastr_iter_lbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_lbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iter_lbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_iter_lbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_lbkt);
// set
void rastr_iter_lbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t lbkt);
SEXP r_rastr_iter_lbkt_set(SEXP r_ast, SEXP r_node, SEXP r_lbkt);


/* var ************************************************************************/
// get
rastr_node_t rastr_iter_var_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_var_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iter_var_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t var);
SEXP r_rastr_iter_var_rep(SEXP r_ast, SEXP r_node, SEXP r_var);
// set
void rastr_iter_var_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t var);
SEXP r_rastr_iter_var_set(SEXP r_ast, SEXP r_node, SEXP r_var);


/* op *************************************************************************/
// get
rastr_node_t rastr_iter_op_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_op_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iter_op_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_iter_op_rep(SEXP r_ast, SEXP r_node, SEXP r_op);
// set
void rastr_iter_op_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t op);
SEXP r_rastr_iter_op_set(SEXP r_ast, SEXP r_node, SEXP r_op);


/* expr ***********************************************************************/
// get
rastr_node_t rastr_iter_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iter_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_iter_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_iter_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_iter_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);


/* rbkt ***********************************************************************/
// get
rastr_node_t rastr_iter_rbkt_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_iter_rbkt_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_iter_rbkt_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_iter_rbkt_rep(SEXP r_ast, SEXP r_node, SEXP r_rbkt);
// set
void rastr_iter_rbkt_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t rbkt);
SEXP r_rastr_iter_rbkt_set(SEXP r_ast, SEXP r_node, SEXP r_rbkt);




/*******************************************************************************
* pgm
*******************************************************************************/
rastr_node_t rastr_pgm_new(rastr_ast_t ast, rastr_node_t beg, rastr_node_t exprs, rastr_node_t end);
SEXP r_rastr_pgm_new(SEXP r_ast, SEXP r_beg, SEXP r_exprs, SEXP r_end);
// pred
int rastr_pgm_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pgm_type(SEXP r_ast, SEXP r_node);
/* beg ************************************************************************/
// get
rastr_node_t rastr_pgm_beg_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pgm_beg_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_pgm_beg_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t beg);
SEXP r_rastr_pgm_beg_rep(SEXP r_ast, SEXP r_node, SEXP r_beg);
// set
void rastr_pgm_beg_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t beg);
SEXP r_rastr_pgm_beg_set(SEXP r_ast, SEXP r_node, SEXP r_beg);


/* exprs **********************************************************************/
// get
rastr_node_t rastr_pgm_exprs_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pgm_exprs_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_pgm_exprs_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs);
SEXP r_rastr_pgm_exprs_rep(SEXP r_ast, SEXP r_node, SEXP r_exprs);
// set
void rastr_pgm_exprs_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t exprs);
SEXP r_rastr_pgm_exprs_set(SEXP r_ast, SEXP r_node, SEXP r_exprs);


/* end ************************************************************************/
// get
rastr_node_t rastr_pgm_end_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_pgm_end_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_pgm_end_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t end);
SEXP r_rastr_pgm_end_rep(SEXP r_ast, SEXP r_node, SEXP r_end);
// set
void rastr_pgm_end_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t end);
SEXP r_rastr_pgm_end_set(SEXP r_ast, SEXP r_node, SEXP r_end);




/*******************************************************************************
* dlmtd
*******************************************************************************/
rastr_node_t rastr_dlmtd_new(rastr_ast_t ast, rastr_node_t expr, rastr_node_t dlmtr);
SEXP r_rastr_dlmtd_new(SEXP r_ast, SEXP r_expr, SEXP r_dlmtr);
// pred
int rastr_dlmtd_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtd_type(SEXP r_ast, SEXP r_node);
/* expr ***********************************************************************/
// get
rastr_node_t rastr_dlmtd_expr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtd_expr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dlmtd_expr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_dlmtd_expr_rep(SEXP r_ast, SEXP r_node, SEXP r_expr);
// set
void rastr_dlmtd_expr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t expr);
SEXP r_rastr_dlmtd_expr_set(SEXP r_ast, SEXP r_node, SEXP r_expr);


/* dlmtr **********************************************************************/
// get
rastr_node_t rastr_dlmtd_dlmtr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_dlmtd_dlmtr_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_dlmtd_dlmtr_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t dlmtr);
SEXP r_rastr_dlmtd_dlmtr_rep(SEXP r_ast, SEXP r_node, SEXP r_dlmtr);
// set
void rastr_dlmtd_dlmtr_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t dlmtr);
SEXP r_rastr_dlmtd_dlmtr_set(SEXP r_ast, SEXP r_node, SEXP r_dlmtr);




/*******************************************************************************
* msng
*******************************************************************************/
rastr_node_t rastr_msng_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_msng_new(SEXP r_ast, SEXP r_gap, SEXP r_loc);
// pred
int rastr_msng_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_msng_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_msng_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_msng_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_msng_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_msng_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_msng_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_msng_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_msng_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_msng_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* beg
*******************************************************************************/
// pred
int rastr_beg_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_beg_type(SEXP r_ast, SEXP r_node);
/* bom ************************************************************************/
// get
const char* rastr_beg_bom_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_beg_bom_get(SEXP r_ast, SEXP r_node);


/* loc ************************************************************************/
// get
rastr_node_t rastr_beg_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_beg_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* end
*******************************************************************************/
rastr_node_t rastr_end_new(rastr_ast_t ast, rastr_node_t gap, rastr_node_t loc);
SEXP r_rastr_end_new(SEXP r_ast, SEXP r_gap, SEXP r_loc);
// pred
int rastr_end_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_end_type(SEXP r_ast, SEXP r_node);
/* gap ************************************************************************/
// get
rastr_node_t rastr_end_gap_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_end_gap_get(SEXP r_ast, SEXP r_node);
// rep
rastr_node_t rastr_end_gap_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_end_gap_rep(SEXP r_ast, SEXP r_node, SEXP r_gap);
// set
void rastr_end_gap_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t gap);
SEXP r_rastr_end_gap_set(SEXP r_ast, SEXP r_node, SEXP r_gap);


/* loc ************************************************************************/
// get
rastr_node_t rastr_end_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_end_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* gap
*******************************************************************************/
// pred
int rastr_gap_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_gap_type(SEXP r_ast, SEXP r_node);
/* val ************************************************************************/
// get
const char* rastr_gap_val_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_gap_val_get(SEXP r_ast, SEXP r_node);


/* loc ************************************************************************/
// get
rastr_node_t rastr_gap_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_gap_loc_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* loc
*******************************************************************************/
// pred
int rastr_loc_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_type(SEXP r_ast, SEXP r_node);
/* lrow ***********************************************************************/
// get
int rastr_loc_lrow_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_lrow_get(SEXP r_ast, SEXP r_node);


/* lcol ***********************************************************************/
// get
int rastr_loc_lcol_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_lcol_get(SEXP r_ast, SEXP r_node);


/* lchr ***********************************************************************/
// get
int rastr_loc_lchr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_lchr_get(SEXP r_ast, SEXP r_node);


/* lbyte **********************************************************************/
// get
int rastr_loc_lbyte_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_lbyte_get(SEXP r_ast, SEXP r_node);


/* rrow ***********************************************************************/
// get
int rastr_loc_rrow_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_rrow_get(SEXP r_ast, SEXP r_node);


/* rcol ***********************************************************************/
// get
int rastr_loc_rcol_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_rcol_get(SEXP r_ast, SEXP r_node);


/* rchr ***********************************************************************/
// get
int rastr_loc_rchr_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_rchr_get(SEXP r_ast, SEXP r_node);


/* rbyte **********************************************************************/
// get
int rastr_loc_rbyte_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_loc_rbyte_get(SEXP r_ast, SEXP r_node);




/*******************************************************************************
* err
*******************************************************************************/
// pred
int rastr_err_type(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_err_type(SEXP r_ast, SEXP r_node);
/* msg ************************************************************************/
// get
const char* rastr_err_msg_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_err_msg_get(SEXP r_ast, SEXP r_node);


/* loc ************************************************************************/
// get
rastr_node_t rastr_err_loc_get(rastr_ast_t ast, rastr_node_t node);
SEXP r_rastr_err_loc_get(SEXP r_ast, SEXP r_node);




