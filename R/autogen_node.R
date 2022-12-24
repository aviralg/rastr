################################################################################
# op
################################################################################
#' @export
op_type <- function(ast, node) {
    .Call(C_rastr_op_type, ast, node)
}
# gap ##########################################################################
#' @export
op_gap_get <- function(ast, node) {
    .Call(C_rastr_op_gap_get, ast, node)
}
#' @export
op_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_op_gap_rep, ast, node, gap)
}
#' @export
op_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_op_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
op_loc_get <- function(ast, node) {
    .Call(C_rastr_op_loc_get, ast, node)
}




################################################################################
# dlmtr
################################################################################
#' @export
dlmtr_type <- function(ast, node) {
    .Call(C_rastr_dlmtr_type, ast, node)
}
# gap ##########################################################################
#' @export
dlmtr_gap_get <- function(ast, node) {
    .Call(C_rastr_dlmtr_gap_get, ast, node)
}
#' @export
dlmtr_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_dlmtr_gap_rep, ast, node, gap)
}
#' @export
dlmtr_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_dlmtr_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
dlmtr_loc_get <- function(ast, node) {
    .Call(C_rastr_dlmtr_loc_get, ast, node)
}




################################################################################
# bkt
################################################################################
#' @export
bkt_type <- function(ast, node) {
    .Call(C_rastr_bkt_type, ast, node)
}
# gap ##########################################################################
#' @export
bkt_gap_get <- function(ast, node) {
    .Call(C_rastr_bkt_gap_get, ast, node)
}
#' @export
bkt_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_bkt_gap_rep, ast, node, gap)
}
#' @export
bkt_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_bkt_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
bkt_loc_get <- function(ast, node) {
    .Call(C_rastr_bkt_loc_get, ast, node)
}




################################################################################
# null
################################################################################
#' @export
null_new <- function(ast, gap, loc) {
    .Call(C_rastr_null_new, ast, gap, loc)
}
#' @export
null_type <- function(ast, node) {
    .Call(C_rastr_null_type, ast, node)
}
# gap ##########################################################################
#' @export
null_gap_get <- function(ast, node) {
    .Call(C_rastr_null_gap_get, ast, node)
}
#' @export
null_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_null_gap_rep, ast, node, gap)
}
#' @export
null_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_null_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
null_loc_get <- function(ast, node) {
    .Call(C_rastr_null_loc_get, ast, node)
}




################################################################################
# lgl
################################################################################
#' @export
lgl_type <- function(ast, node) {
    .Call(C_rastr_lgl_type, ast, node)
}
# val ##########################################################################
#' @export
lgl_val_get <- function(ast, node) {
    .Call(C_rastr_lgl_val_get, ast, node)
}


# gap ##########################################################################
#' @export
lgl_gap_get <- function(ast, node) {
    .Call(C_rastr_lgl_gap_get, ast, node)
}
#' @export
lgl_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_lgl_gap_rep, ast, node, gap)
}
#' @export
lgl_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_lgl_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
lgl_loc_get <- function(ast, node) {
    .Call(C_rastr_lgl_loc_get, ast, node)
}




################################################################################
# int
################################################################################
#' @export
int_type <- function(ast, node) {
    .Call(C_rastr_int_type, ast, node)
}
# syn ##########################################################################
#' @export
int_syn_get <- function(ast, node) {
    .Call(C_rastr_int_syn_get, ast, node)
}


# val ##########################################################################
#' @export
int_val_get <- function(ast, node) {
    .Call(C_rastr_int_val_get, ast, node)
}


# gap ##########################################################################
#' @export
int_gap_get <- function(ast, node) {
    .Call(C_rastr_int_gap_get, ast, node)
}
#' @export
int_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_int_gap_rep, ast, node, gap)
}
#' @export
int_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_int_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
int_loc_get <- function(ast, node) {
    .Call(C_rastr_int_loc_get, ast, node)
}




################################################################################
# dbl
################################################################################
#' @export
dbl_type <- function(ast, node) {
    .Call(C_rastr_dbl_type, ast, node)
}
# syn ##########################################################################
#' @export
dbl_syn_get <- function(ast, node) {
    .Call(C_rastr_dbl_syn_get, ast, node)
}


# val ##########################################################################
#' @export
dbl_val_get <- function(ast, node) {
    .Call(C_rastr_dbl_val_get, ast, node)
}


# gap ##########################################################################
#' @export
dbl_gap_get <- function(ast, node) {
    .Call(C_rastr_dbl_gap_get, ast, node)
}
#' @export
dbl_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_dbl_gap_rep, ast, node, gap)
}
#' @export
dbl_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_dbl_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
dbl_loc_get <- function(ast, node) {
    .Call(C_rastr_dbl_loc_get, ast, node)
}




################################################################################
# cpx
################################################################################
#' @export
cpx_type <- function(ast, node) {
    .Call(C_rastr_cpx_type, ast, node)
}
# syn ##########################################################################
#' @export
cpx_syn_get <- function(ast, node) {
    .Call(C_rastr_cpx_syn_get, ast, node)
}


# val ##########################################################################
#' @export
cpx_val_get <- function(ast, node) {
    .Call(C_rastr_cpx_val_get, ast, node)
}


# gap ##########################################################################
#' @export
cpx_gap_get <- function(ast, node) {
    .Call(C_rastr_cpx_gap_get, ast, node)
}
#' @export
cpx_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_cpx_gap_rep, ast, node, gap)
}
#' @export
cpx_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_cpx_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
cpx_loc_get <- function(ast, node) {
    .Call(C_rastr_cpx_loc_get, ast, node)
}




################################################################################
# chr
################################################################################
#' @export
chr_type <- function(ast, node) {
    .Call(C_rastr_chr_type, ast, node)
}
# syn ##########################################################################
#' @export
chr_syn_get <- function(ast, node) {
    .Call(C_rastr_chr_syn_get, ast, node)
}


# val ##########################################################################
#' @export
chr_val_get <- function(ast, node) {
    .Call(C_rastr_chr_val_get, ast, node)
}


# gap ##########################################################################
#' @export
chr_gap_get <- function(ast, node) {
    .Call(C_rastr_chr_gap_get, ast, node)
}
#' @export
chr_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_chr_gap_rep, ast, node, gap)
}
#' @export
chr_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_chr_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
chr_loc_get <- function(ast, node) {
    .Call(C_rastr_chr_loc_get, ast, node)
}




################################################################################
# sym
################################################################################
#' @export
sym_type <- function(ast, node) {
    .Call(C_rastr_sym_type, ast, node)
}
# syn ##########################################################################
#' @export
sym_syn_get <- function(ast, node) {
    .Call(C_rastr_sym_syn_get, ast, node)
}


# val ##########################################################################
#' @export
sym_val_get <- function(ast, node) {
    .Call(C_rastr_sym_val_get, ast, node)
}


# gap ##########################################################################
#' @export
sym_gap_get <- function(ast, node) {
    .Call(C_rastr_sym_gap_get, ast, node)
}
#' @export
sym_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_sym_gap_rep, ast, node, gap)
}
#' @export
sym_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_sym_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
sym_loc_get <- function(ast, node) {
    .Call(C_rastr_sym_loc_get, ast, node)
}




################################################################################
# blk
################################################################################
#' @export
blk_new <- function(ast, lbkt, exprs, rbkt) {
    .Call(C_rastr_blk_new, ast, lbkt, exprs, rbkt)
}
#' @export
blk_type <- function(ast, node) {
    .Call(C_rastr_blk_type, ast, node)
}
# lbkt #########################################################################
#' @export
blk_lbkt_get <- function(ast, node) {
    .Call(C_rastr_blk_lbkt_get, ast, node)
}
#' @export
blk_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_blk_lbkt_rep, ast, node, lbkt)
}
#' @export
blk_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_blk_lbkt_set, ast, node, lbkt))
}


# exprs ########################################################################
#' @export
blk_exprs_get <- function(ast, node) {
    .Call(C_rastr_blk_exprs_get, ast, node)
}
#' @export
blk_exprs_rep <- function(ast, node, exprs) {
    .Call(C_rastr_blk_exprs_rep, ast, node, exprs)
}
#' @export
blk_exprs_set <- function(ast, node, exprs) {
    invisible(.Call(C_rastr_blk_exprs_set, ast, node, exprs))
}


# rbkt #########################################################################
#' @export
blk_rbkt_get <- function(ast, node) {
    .Call(C_rastr_blk_rbkt_get, ast, node)
}
#' @export
blk_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_blk_rbkt_rep, ast, node, rbkt)
}
#' @export
blk_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_blk_rbkt_set, ast, node, rbkt))
}




################################################################################
# grp
################################################################################
#' @export
grp_new <- function(ast, lbkt, expr, rbkt) {
    .Call(C_rastr_grp_new, ast, lbkt, expr, rbkt)
}
#' @export
grp_type <- function(ast, node) {
    .Call(C_rastr_grp_type, ast, node)
}
# lbkt #########################################################################
#' @export
grp_lbkt_get <- function(ast, node) {
    .Call(C_rastr_grp_lbkt_get, ast, node)
}
#' @export
grp_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_grp_lbkt_rep, ast, node, lbkt)
}
#' @export
grp_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_grp_lbkt_set, ast, node, lbkt))
}


# expr #########################################################################
#' @export
grp_expr_get <- function(ast, node) {
    .Call(C_rastr_grp_expr_get, ast, node)
}
#' @export
grp_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_grp_expr_rep, ast, node, expr)
}
#' @export
grp_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_grp_expr_set, ast, node, expr))
}


# rbkt #########################################################################
#' @export
grp_rbkt_get <- function(ast, node) {
    .Call(C_rastr_grp_rbkt_get, ast, node)
}
#' @export
grp_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_grp_rbkt_rep, ast, node, rbkt)
}
#' @export
grp_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_grp_rbkt_set, ast, node, rbkt))
}




################################################################################
# nuop
################################################################################
#' @export
nuop_new <- function(ast, op) {
    .Call(C_rastr_nuop_new, ast, op)
}
#' @export
nuop_type <- function(ast, node) {
    .Call(C_rastr_nuop_type, ast, node)
}
# op ###########################################################################
#' @export
nuop_op_get <- function(ast, node) {
    .Call(C_rastr_nuop_op_get, ast, node)
}
#' @export
nuop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_nuop_op_rep, ast, node, op)
}
#' @export
nuop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_nuop_op_set, ast, node, op))
}




################################################################################
# unop
################################################################################
#' @export
unop_new <- function(ast, op, expr) {
    .Call(C_rastr_unop_new, ast, op, expr)
}
#' @export
unop_type <- function(ast, node) {
    .Call(C_rastr_unop_type, ast, node)
}
# op ###########################################################################
#' @export
unop_op_get <- function(ast, node) {
    .Call(C_rastr_unop_op_get, ast, node)
}
#' @export
unop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_unop_op_rep, ast, node, op)
}
#' @export
unop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_unop_op_set, ast, node, op))
}


# expr #########################################################################
#' @export
unop_expr_get <- function(ast, node) {
    .Call(C_rastr_unop_expr_get, ast, node)
}
#' @export
unop_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_unop_expr_rep, ast, node, expr)
}
#' @export
unop_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_unop_expr_set, ast, node, expr))
}




################################################################################
# binop
################################################################################
#' @export
binop_new <- function(ast, lexpr, op, rexpr) {
    .Call(C_rastr_binop_new, ast, lexpr, op, rexpr)
}
#' @export
binop_type <- function(ast, node) {
    .Call(C_rastr_binop_type, ast, node)
}
# lexpr ########################################################################
#' @export
binop_lexpr_get <- function(ast, node) {
    .Call(C_rastr_binop_lexpr_get, ast, node)
}
#' @export
binop_lexpr_rep <- function(ast, node, lexpr) {
    .Call(C_rastr_binop_lexpr_rep, ast, node, lexpr)
}
#' @export
binop_lexpr_set <- function(ast, node, lexpr) {
    invisible(.Call(C_rastr_binop_lexpr_set, ast, node, lexpr))
}


# op ###########################################################################
#' @export
binop_op_get <- function(ast, node) {
    .Call(C_rastr_binop_op_get, ast, node)
}
#' @export
binop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_binop_op_rep, ast, node, op)
}
#' @export
binop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_binop_op_set, ast, node, op))
}


# rexpr ########################################################################
#' @export
binop_rexpr_get <- function(ast, node) {
    .Call(C_rastr_binop_rexpr_get, ast, node)
}
#' @export
binop_rexpr_rep <- function(ast, node, rexpr) {
    .Call(C_rastr_binop_rexpr_rep, ast, node, rexpr)
}
#' @export
binop_rexpr_set <- function(ast, node, rexpr) {
    invisible(.Call(C_rastr_binop_rexpr_set, ast, node, rexpr))
}




################################################################################
# rlp
################################################################################
#' @export
rlp_new <- function(ast, op, body) {
    .Call(C_rastr_rlp_new, ast, op, body)
}
#' @export
rlp_type <- function(ast, node) {
    .Call(C_rastr_rlp_type, ast, node)
}
# op ###########################################################################
#' @export
rlp_op_get <- function(ast, node) {
    .Call(C_rastr_rlp_op_get, ast, node)
}
#' @export
rlp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_rlp_op_rep, ast, node, op)
}
#' @export
rlp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_rlp_op_set, ast, node, op))
}


# body #########################################################################
#' @export
rlp_body_get <- function(ast, node) {
    .Call(C_rastr_rlp_body_get, ast, node)
}
#' @export
rlp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_rlp_body_rep, ast, node, body)
}
#' @export
rlp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_rlp_body_set, ast, node, body))
}




################################################################################
# wlp
################################################################################
#' @export
wlp_new <- function(ast, op, cond, body) {
    .Call(C_rastr_wlp_new, ast, op, cond, body)
}
#' @export
wlp_type <- function(ast, node) {
    .Call(C_rastr_wlp_type, ast, node)
}
# op ###########################################################################
#' @export
wlp_op_get <- function(ast, node) {
    .Call(C_rastr_wlp_op_get, ast, node)
}
#' @export
wlp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_wlp_op_rep, ast, node, op)
}
#' @export
wlp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_wlp_op_set, ast, node, op))
}


# cond #########################################################################
#' @export
wlp_cond_get <- function(ast, node) {
    .Call(C_rastr_wlp_cond_get, ast, node)
}
#' @export
wlp_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_wlp_cond_rep, ast, node, cond)
}
#' @export
wlp_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_wlp_cond_set, ast, node, cond))
}


# body #########################################################################
#' @export
wlp_body_get <- function(ast, node) {
    .Call(C_rastr_wlp_body_get, ast, node)
}
#' @export
wlp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_wlp_body_rep, ast, node, body)
}
#' @export
wlp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_wlp_body_set, ast, node, body))
}




################################################################################
# flp
################################################################################
#' @export
flp_new <- function(ast, op, iter, body) {
    .Call(C_rastr_flp_new, ast, op, iter, body)
}
#' @export
flp_type <- function(ast, node) {
    .Call(C_rastr_flp_type, ast, node)
}
# op ###########################################################################
#' @export
flp_op_get <- function(ast, node) {
    .Call(C_rastr_flp_op_get, ast, node)
}
#' @export
flp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_flp_op_rep, ast, node, op)
}
#' @export
flp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_flp_op_set, ast, node, op))
}


# iter #########################################################################
#' @export
flp_iter_get <- function(ast, node) {
    .Call(C_rastr_flp_iter_get, ast, node)
}
#' @export
flp_iter_rep <- function(ast, node, iter) {
    .Call(C_rastr_flp_iter_rep, ast, node, iter)
}
#' @export
flp_iter_set <- function(ast, node, iter) {
    invisible(.Call(C_rastr_flp_iter_set, ast, node, iter))
}


# body #########################################################################
#' @export
flp_body_get <- function(ast, node) {
    .Call(C_rastr_flp_body_get, ast, node)
}
#' @export
flp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_flp_body_rep, ast, node, body)
}
#' @export
flp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_flp_body_set, ast, node, body))
}




################################################################################
# icond
################################################################################
#' @export
icond_new <- function(ast, iop, cond, ibody) {
    .Call(C_rastr_icond_new, ast, iop, cond, ibody)
}
#' @export
icond_type <- function(ast, node) {
    .Call(C_rastr_icond_type, ast, node)
}
# iop ##########################################################################
#' @export
icond_iop_get <- function(ast, node) {
    .Call(C_rastr_icond_iop_get, ast, node)
}
#' @export
icond_iop_rep <- function(ast, node, iop) {
    .Call(C_rastr_icond_iop_rep, ast, node, iop)
}
#' @export
icond_iop_set <- function(ast, node, iop) {
    invisible(.Call(C_rastr_icond_iop_set, ast, node, iop))
}


# cond #########################################################################
#' @export
icond_cond_get <- function(ast, node) {
    .Call(C_rastr_icond_cond_get, ast, node)
}
#' @export
icond_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_icond_cond_rep, ast, node, cond)
}
#' @export
icond_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_icond_cond_set, ast, node, cond))
}


# ibody ########################################################################
#' @export
icond_ibody_get <- function(ast, node) {
    .Call(C_rastr_icond_ibody_get, ast, node)
}
#' @export
icond_ibody_rep <- function(ast, node, ibody) {
    .Call(C_rastr_icond_ibody_rep, ast, node, ibody)
}
#' @export
icond_ibody_set <- function(ast, node, ibody) {
    invisible(.Call(C_rastr_icond_ibody_set, ast, node, ibody))
}




################################################################################
# iecond
################################################################################
#' @export
iecond_new <- function(ast, iop, cond, ibody, eop, ebody) {
    .Call(C_rastr_iecond_new, ast, iop, cond, ibody, eop, ebody)
}
#' @export
iecond_type <- function(ast, node) {
    .Call(C_rastr_iecond_type, ast, node)
}
# iop ##########################################################################
#' @export
iecond_iop_get <- function(ast, node) {
    .Call(C_rastr_iecond_iop_get, ast, node)
}
#' @export
iecond_iop_rep <- function(ast, node, iop) {
    .Call(C_rastr_iecond_iop_rep, ast, node, iop)
}
#' @export
iecond_iop_set <- function(ast, node, iop) {
    invisible(.Call(C_rastr_iecond_iop_set, ast, node, iop))
}


# cond #########################################################################
#' @export
iecond_cond_get <- function(ast, node) {
    .Call(C_rastr_iecond_cond_get, ast, node)
}
#' @export
iecond_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_iecond_cond_rep, ast, node, cond)
}
#' @export
iecond_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_iecond_cond_set, ast, node, cond))
}


# ibody ########################################################################
#' @export
iecond_ibody_get <- function(ast, node) {
    .Call(C_rastr_iecond_ibody_get, ast, node)
}
#' @export
iecond_ibody_rep <- function(ast, node, ibody) {
    .Call(C_rastr_iecond_ibody_rep, ast, node, ibody)
}
#' @export
iecond_ibody_set <- function(ast, node, ibody) {
    invisible(.Call(C_rastr_iecond_ibody_set, ast, node, ibody))
}


# eop ##########################################################################
#' @export
iecond_eop_get <- function(ast, node) {
    .Call(C_rastr_iecond_eop_get, ast, node)
}
#' @export
iecond_eop_rep <- function(ast, node, eop) {
    .Call(C_rastr_iecond_eop_rep, ast, node, eop)
}
#' @export
iecond_eop_set <- function(ast, node, eop) {
    invisible(.Call(C_rastr_iecond_eop_set, ast, node, eop))
}


# ebody ########################################################################
#' @export
iecond_ebody_get <- function(ast, node) {
    .Call(C_rastr_iecond_ebody_get, ast, node)
}
#' @export
iecond_ebody_rep <- function(ast, node, ebody) {
    .Call(C_rastr_iecond_ebody_rep, ast, node, ebody)
}
#' @export
iecond_ebody_set <- function(ast, node, ebody) {
    invisible(.Call(C_rastr_iecond_ebody_set, ast, node, ebody))
}




################################################################################
# fndefn
################################################################################
#' @export
fndefn_new <- function(ast, op, lbkt, pars, rbkt, body) {
    .Call(C_rastr_fndefn_new, ast, op, lbkt, pars, rbkt, body)
}
#' @export
fndefn_type <- function(ast, node) {
    .Call(C_rastr_fndefn_type, ast, node)
}
# op ###########################################################################
#' @export
fndefn_op_get <- function(ast, node) {
    .Call(C_rastr_fndefn_op_get, ast, node)
}
#' @export
fndefn_op_rep <- function(ast, node, op) {
    .Call(C_rastr_fndefn_op_rep, ast, node, op)
}
#' @export
fndefn_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_fndefn_op_set, ast, node, op))
}


# lbkt #########################################################################
#' @export
fndefn_lbkt_get <- function(ast, node) {
    .Call(C_rastr_fndefn_lbkt_get, ast, node)
}
#' @export
fndefn_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_fndefn_lbkt_rep, ast, node, lbkt)
}
#' @export
fndefn_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_fndefn_lbkt_set, ast, node, lbkt))
}


# pars #########################################################################
#' @export
fndefn_pars_get <- function(ast, node) {
    .Call(C_rastr_fndefn_pars_get, ast, node)
}
#' @export
fndefn_pars_rep <- function(ast, node, pars) {
    .Call(C_rastr_fndefn_pars_rep, ast, node, pars)
}
#' @export
fndefn_pars_set <- function(ast, node, pars) {
    invisible(.Call(C_rastr_fndefn_pars_set, ast, node, pars))
}


# rbkt #########################################################################
#' @export
fndefn_rbkt_get <- function(ast, node) {
    .Call(C_rastr_fndefn_rbkt_get, ast, node)
}
#' @export
fndefn_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_fndefn_rbkt_rep, ast, node, rbkt)
}
#' @export
fndefn_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_fndefn_rbkt_set, ast, node, rbkt))
}


# body #########################################################################
#' @export
fndefn_body_get <- function(ast, node) {
    .Call(C_rastr_fndefn_body_get, ast, node)
}
#' @export
fndefn_body_rep <- function(ast, node, body) {
    .Call(C_rastr_fndefn_body_rep, ast, node, body)
}
#' @export
fndefn_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_fndefn_body_set, ast, node, body))
}




################################################################################
# fncall
################################################################################
#' @export
fncall_new <- function(ast, fn, lbkt, args, rbkt) {
    .Call(C_rastr_fncall_new, ast, fn, lbkt, args, rbkt)
}
#' @export
fncall_type <- function(ast, node) {
    .Call(C_rastr_fncall_type, ast, node)
}
# fn ###########################################################################
#' @export
fncall_fn_get <- function(ast, node) {
    .Call(C_rastr_fncall_fn_get, ast, node)
}
#' @export
fncall_fn_rep <- function(ast, node, fn) {
    .Call(C_rastr_fncall_fn_rep, ast, node, fn)
}
#' @export
fncall_fn_set <- function(ast, node, fn) {
    invisible(.Call(C_rastr_fncall_fn_set, ast, node, fn))
}


# lbkt #########################################################################
#' @export
fncall_lbkt_get <- function(ast, node) {
    .Call(C_rastr_fncall_lbkt_get, ast, node)
}
#' @export
fncall_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_fncall_lbkt_rep, ast, node, lbkt)
}
#' @export
fncall_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_fncall_lbkt_set, ast, node, lbkt))
}


# args #########################################################################
#' @export
fncall_args_get <- function(ast, node) {
    .Call(C_rastr_fncall_args_get, ast, node)
}
#' @export
fncall_args_rep <- function(ast, node, args) {
    .Call(C_rastr_fncall_args_rep, ast, node, args)
}
#' @export
fncall_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_fncall_args_set, ast, node, args))
}


# rbkt #########################################################################
#' @export
fncall_rbkt_get <- function(ast, node) {
    .Call(C_rastr_fncall_rbkt_get, ast, node)
}
#' @export
fncall_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_fncall_rbkt_rep, ast, node, rbkt)
}
#' @export
fncall_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_fncall_rbkt_set, ast, node, rbkt))
}




################################################################################
# sub
################################################################################
#' @export
sub_new <- function(ast, obj, lbkt, args, rbkt) {
    .Call(C_rastr_sub_new, ast, obj, lbkt, args, rbkt)
}
#' @export
sub_type <- function(ast, node) {
    .Call(C_rastr_sub_type, ast, node)
}
# obj ##########################################################################
#' @export
sub_obj_get <- function(ast, node) {
    .Call(C_rastr_sub_obj_get, ast, node)
}
#' @export
sub_obj_rep <- function(ast, node, obj) {
    .Call(C_rastr_sub_obj_rep, ast, node, obj)
}
#' @export
sub_obj_set <- function(ast, node, obj) {
    invisible(.Call(C_rastr_sub_obj_set, ast, node, obj))
}


# lbkt #########################################################################
#' @export
sub_lbkt_get <- function(ast, node) {
    .Call(C_rastr_sub_lbkt_get, ast, node)
}
#' @export
sub_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_sub_lbkt_rep, ast, node, lbkt)
}
#' @export
sub_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_sub_lbkt_set, ast, node, lbkt))
}


# args #########################################################################
#' @export
sub_args_get <- function(ast, node) {
    .Call(C_rastr_sub_args_get, ast, node)
}
#' @export
sub_args_rep <- function(ast, node, args) {
    .Call(C_rastr_sub_args_rep, ast, node, args)
}
#' @export
sub_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_sub_args_set, ast, node, args))
}


# rbkt #########################################################################
#' @export
sub_rbkt_get <- function(ast, node) {
    .Call(C_rastr_sub_rbkt_get, ast, node)
}
#' @export
sub_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_sub_rbkt_rep, ast, node, rbkt)
}
#' @export
sub_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_sub_rbkt_set, ast, node, rbkt))
}




################################################################################
# idx
################################################################################
#' @export
idx_new <- function(ast, obj, lbkt, args, rbkt1, rbkt2) {
    .Call(C_rastr_idx_new, ast, obj, lbkt, args, rbkt1, rbkt2)
}
#' @export
idx_type <- function(ast, node) {
    .Call(C_rastr_idx_type, ast, node)
}
# obj ##########################################################################
#' @export
idx_obj_get <- function(ast, node) {
    .Call(C_rastr_idx_obj_get, ast, node)
}
#' @export
idx_obj_rep <- function(ast, node, obj) {
    .Call(C_rastr_idx_obj_rep, ast, node, obj)
}
#' @export
idx_obj_set <- function(ast, node, obj) {
    invisible(.Call(C_rastr_idx_obj_set, ast, node, obj))
}


# lbkt #########################################################################
#' @export
idx_lbkt_get <- function(ast, node) {
    .Call(C_rastr_idx_lbkt_get, ast, node)
}
#' @export
idx_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_idx_lbkt_rep, ast, node, lbkt)
}
#' @export
idx_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_idx_lbkt_set, ast, node, lbkt))
}


# args #########################################################################
#' @export
idx_args_get <- function(ast, node) {
    .Call(C_rastr_idx_args_get, ast, node)
}
#' @export
idx_args_rep <- function(ast, node, args) {
    .Call(C_rastr_idx_args_rep, ast, node, args)
}
#' @export
idx_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_idx_args_set, ast, node, args))
}


# rbkt1 ########################################################################
#' @export
idx_rbkt1_get <- function(ast, node) {
    .Call(C_rastr_idx_rbkt1_get, ast, node)
}
#' @export
idx_rbkt1_rep <- function(ast, node, rbkt1) {
    .Call(C_rastr_idx_rbkt1_rep, ast, node, rbkt1)
}
#' @export
idx_rbkt1_set <- function(ast, node, rbkt1) {
    invisible(.Call(C_rastr_idx_rbkt1_set, ast, node, rbkt1))
}


# rbkt2 ########################################################################
#' @export
idx_rbkt2_get <- function(ast, node) {
    .Call(C_rastr_idx_rbkt2_get, ast, node)
}
#' @export
idx_rbkt2_rep <- function(ast, node, rbkt2) {
    .Call(C_rastr_idx_rbkt2_rep, ast, node, rbkt2)
}
#' @export
idx_rbkt2_set <- function(ast, node, rbkt2) {
    invisible(.Call(C_rastr_idx_rbkt2_set, ast, node, rbkt2))
}




################################################################################
# aexpr
################################################################################
#' @export
aexpr_new <- function(ast, ann, expr) {
    .Call(C_rastr_aexpr_new, ast, ann, expr)
}
#' @export
aexpr_type <- function(ast, node) {
    .Call(C_rastr_aexpr_type, ast, node)
}
# ann ##########################################################################
#' @export
aexpr_ann_get <- function(ast, node) {
    .Call(C_rastr_aexpr_ann_get, ast, node)
}
#' @export
aexpr_ann_rep <- function(ast, node, ann) {
    .Call(C_rastr_aexpr_ann_rep, ast, node, ann)
}
#' @export
aexpr_ann_set <- function(ast, node, ann) {
    invisible(.Call(C_rastr_aexpr_ann_set, ast, node, ann))
}


# expr #########################################################################
#' @export
aexpr_expr_get <- function(ast, node) {
    .Call(C_rastr_aexpr_expr_get, ast, node)
}
#' @export
aexpr_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_aexpr_expr_rep, ast, node, expr)
}
#' @export
aexpr_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_aexpr_expr_set, ast, node, expr))
}




################################################################################
# exprs
################################################################################
#' @export
exprs_new <- function(ast, seq) {
    .Call(C_rastr_exprs_new, ast, seq)
}
#' @export
exprs_type <- function(ast, node) {
    .Call(C_rastr_exprs_type, ast, node)
}
# len ##########################################################################
#' @export
exprs_len_get <- function(ast, node) {
    .Call(C_rastr_exprs_len_get, ast, node)
}


# seq ##########################################################################
#' @export
exprs_seq_get <- function(ast, node) {
    .Call(C_rastr_exprs_seq_get, ast, node)
}

#' @export
exprs_get <- function(ast, node, index) {
    .Call(C_rastr_exprs_get, ast, node, index)
}
#' @export
exprs_rep <- function(ast, node, index, expr) {
    .Call(C_rastr_exprs_rep, ast, node, index, expr)
}
#' @export
exprs_expr_set <- function(ast, node, index, expr) {
    invisible(.Call(C_rastr_exprs_set, ast, node, index, expr))
}




################################################################################
# pars
################################################################################
#' @export
pars_new <- function(ast, seq) {
    .Call(C_rastr_pars_new, ast, seq)
}
#' @export
pars_type <- function(ast, node) {
    .Call(C_rastr_pars_type, ast, node)
}
# len ##########################################################################
#' @export
pars_len_get <- function(ast, node) {
    .Call(C_rastr_pars_len_get, ast, node)
}


# seq ##########################################################################
#' @export
pars_seq_get <- function(ast, node) {
    .Call(C_rastr_pars_seq_get, ast, node)
}

#' @export
pars_get <- function(ast, node, index) {
    .Call(C_rastr_pars_get, ast, node, index)
}
#' @export
pars_rep <- function(ast, node, index, par) {
    .Call(C_rastr_pars_rep, ast, node, index, par)
}
#' @export
pars_par_set <- function(ast, node, index, par) {
    invisible(.Call(C_rastr_pars_set, ast, node, index, par))
}




################################################################################
# dpar
################################################################################
#' @export
dpar_new <- function(ast, name, op, expr) {
    .Call(C_rastr_dpar_new, ast, name, op, expr)
}
#' @export
dpar_type <- function(ast, node) {
    .Call(C_rastr_dpar_type, ast, node)
}
# name #########################################################################
#' @export
dpar_name_get <- function(ast, node) {
    .Call(C_rastr_dpar_name_get, ast, node)
}
#' @export
dpar_name_rep <- function(ast, node, name) {
    .Call(C_rastr_dpar_name_rep, ast, node, name)
}
#' @export
dpar_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_dpar_name_set, ast, node, name))
}


# op ###########################################################################
#' @export
dpar_op_get <- function(ast, node) {
    .Call(C_rastr_dpar_op_get, ast, node)
}
#' @export
dpar_op_rep <- function(ast, node, op) {
    .Call(C_rastr_dpar_op_rep, ast, node, op)
}
#' @export
dpar_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_dpar_op_set, ast, node, op))
}


# expr #########################################################################
#' @export
dpar_expr_get <- function(ast, node) {
    .Call(C_rastr_dpar_expr_get, ast, node)
}
#' @export
dpar_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_dpar_expr_rep, ast, node, expr)
}
#' @export
dpar_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_dpar_expr_set, ast, node, expr))
}




################################################################################
# ndpar
################################################################################
#' @export
ndpar_new <- function(ast, name) {
    .Call(C_rastr_ndpar_new, ast, name)
}
#' @export
ndpar_type <- function(ast, node) {
    .Call(C_rastr_ndpar_type, ast, node)
}
# name #########################################################################
#' @export
ndpar_name_get <- function(ast, node) {
    .Call(C_rastr_ndpar_name_get, ast, node)
}
#' @export
ndpar_name_rep <- function(ast, node, name) {
    .Call(C_rastr_ndpar_name_rep, ast, node, name)
}
#' @export
ndpar_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_ndpar_name_set, ast, node, name))
}




################################################################################
# args
################################################################################
#' @export
args_new <- function(ast, seq) {
    .Call(C_rastr_args_new, ast, seq)
}
#' @export
args_type <- function(ast, node) {
    .Call(C_rastr_args_type, ast, node)
}
# len ##########################################################################
#' @export
args_len_get <- function(ast, node) {
    .Call(C_rastr_args_len_get, ast, node)
}


# seq ##########################################################################
#' @export
args_seq_get <- function(ast, node) {
    .Call(C_rastr_args_seq_get, ast, node)
}

#' @export
args_get <- function(ast, node, index) {
    .Call(C_rastr_args_get, ast, node, index)
}
#' @export
args_rep <- function(ast, node, index, arg) {
    .Call(C_rastr_args_rep, ast, node, index, arg)
}
#' @export
args_arg_set <- function(ast, node, index, arg) {
    invisible(.Call(C_rastr_args_set, ast, node, index, arg))
}




################################################################################
# narg
################################################################################
#' @export
narg_new <- function(ast, name, op, expr) {
    .Call(C_rastr_narg_new, ast, name, op, expr)
}
#' @export
narg_type <- function(ast, node) {
    .Call(C_rastr_narg_type, ast, node)
}
# name #########################################################################
#' @export
narg_name_get <- function(ast, node) {
    .Call(C_rastr_narg_name_get, ast, node)
}
#' @export
narg_name_rep <- function(ast, node, name) {
    .Call(C_rastr_narg_name_rep, ast, node, name)
}
#' @export
narg_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_narg_name_set, ast, node, name))
}


# op ###########################################################################
#' @export
narg_op_get <- function(ast, node) {
    .Call(C_rastr_narg_op_get, ast, node)
}
#' @export
narg_op_rep <- function(ast, node, op) {
    .Call(C_rastr_narg_op_rep, ast, node, op)
}
#' @export
narg_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_narg_op_set, ast, node, op))
}


# expr #########################################################################
#' @export
narg_expr_get <- function(ast, node) {
    .Call(C_rastr_narg_expr_get, ast, node)
}
#' @export
narg_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_narg_expr_rep, ast, node, expr)
}
#' @export
narg_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_narg_expr_set, ast, node, expr))
}




################################################################################
# parg
################################################################################
#' @export
parg_new <- function(ast, expr) {
    .Call(C_rastr_parg_new, ast, expr)
}
#' @export
parg_type <- function(ast, node) {
    .Call(C_rastr_parg_type, ast, node)
}
# expr #########################################################################
#' @export
parg_expr_get <- function(ast, node) {
    .Call(C_rastr_parg_expr_get, ast, node)
}
#' @export
parg_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_parg_expr_rep, ast, node, expr)
}
#' @export
parg_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_parg_expr_set, ast, node, expr))
}




################################################################################
# cond
################################################################################
#' @export
cond_new <- function(ast, lbkt, expr, rbkt) {
    .Call(C_rastr_cond_new, ast, lbkt, expr, rbkt)
}
#' @export
cond_type <- function(ast, node) {
    .Call(C_rastr_cond_type, ast, node)
}
# lbkt #########################################################################
#' @export
cond_lbkt_get <- function(ast, node) {
    .Call(C_rastr_cond_lbkt_get, ast, node)
}
#' @export
cond_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_cond_lbkt_rep, ast, node, lbkt)
}
#' @export
cond_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_cond_lbkt_set, ast, node, lbkt))
}


# expr #########################################################################
#' @export
cond_expr_get <- function(ast, node) {
    .Call(C_rastr_cond_expr_get, ast, node)
}
#' @export
cond_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_cond_expr_rep, ast, node, expr)
}
#' @export
cond_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_cond_expr_set, ast, node, expr))
}


# rbkt #########################################################################
#' @export
cond_rbkt_get <- function(ast, node) {
    .Call(C_rastr_cond_rbkt_get, ast, node)
}
#' @export
cond_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_cond_rbkt_rep, ast, node, rbkt)
}
#' @export
cond_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_cond_rbkt_set, ast, node, rbkt))
}




################################################################################
# iter
################################################################################
#' @export
iter_new <- function(ast, lbkt, var, op, expr, rbkt) {
    .Call(C_rastr_iter_new, ast, lbkt, var, op, expr, rbkt)
}
#' @export
iter_type <- function(ast, node) {
    .Call(C_rastr_iter_type, ast, node)
}
# lbkt #########################################################################
#' @export
iter_lbkt_get <- function(ast, node) {
    .Call(C_rastr_iter_lbkt_get, ast, node)
}
#' @export
iter_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_iter_lbkt_rep, ast, node, lbkt)
}
#' @export
iter_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_iter_lbkt_set, ast, node, lbkt))
}


# var ##########################################################################
#' @export
iter_var_get <- function(ast, node) {
    .Call(C_rastr_iter_var_get, ast, node)
}
#' @export
iter_var_rep <- function(ast, node, var) {
    .Call(C_rastr_iter_var_rep, ast, node, var)
}
#' @export
iter_var_set <- function(ast, node, var) {
    invisible(.Call(C_rastr_iter_var_set, ast, node, var))
}


# op ###########################################################################
#' @export
iter_op_get <- function(ast, node) {
    .Call(C_rastr_iter_op_get, ast, node)
}
#' @export
iter_op_rep <- function(ast, node, op) {
    .Call(C_rastr_iter_op_rep, ast, node, op)
}
#' @export
iter_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_iter_op_set, ast, node, op))
}


# expr #########################################################################
#' @export
iter_expr_get <- function(ast, node) {
    .Call(C_rastr_iter_expr_get, ast, node)
}
#' @export
iter_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_iter_expr_rep, ast, node, expr)
}
#' @export
iter_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_iter_expr_set, ast, node, expr))
}


# rbkt #########################################################################
#' @export
iter_rbkt_get <- function(ast, node) {
    .Call(C_rastr_iter_rbkt_get, ast, node)
}
#' @export
iter_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_iter_rbkt_rep, ast, node, rbkt)
}
#' @export
iter_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_iter_rbkt_set, ast, node, rbkt))
}




################################################################################
# pgm
################################################################################
#' @export
pgm_new <- function(ast, beg, exprs, end) {
    .Call(C_rastr_pgm_new, ast, beg, exprs, end)
}
#' @export
pgm_type <- function(ast, node) {
    .Call(C_rastr_pgm_type, ast, node)
}
# beg ##########################################################################
#' @export
pgm_beg_get <- function(ast, node) {
    .Call(C_rastr_pgm_beg_get, ast, node)
}
#' @export
pgm_beg_rep <- function(ast, node, beg) {
    .Call(C_rastr_pgm_beg_rep, ast, node, beg)
}
#' @export
pgm_beg_set <- function(ast, node, beg) {
    invisible(.Call(C_rastr_pgm_beg_set, ast, node, beg))
}


# exprs ########################################################################
#' @export
pgm_exprs_get <- function(ast, node) {
    .Call(C_rastr_pgm_exprs_get, ast, node)
}
#' @export
pgm_exprs_rep <- function(ast, node, exprs) {
    .Call(C_rastr_pgm_exprs_rep, ast, node, exprs)
}
#' @export
pgm_exprs_set <- function(ast, node, exprs) {
    invisible(.Call(C_rastr_pgm_exprs_set, ast, node, exprs))
}


# end ##########################################################################
#' @export
pgm_end_get <- function(ast, node) {
    .Call(C_rastr_pgm_end_get, ast, node)
}
#' @export
pgm_end_rep <- function(ast, node, end) {
    .Call(C_rastr_pgm_end_rep, ast, node, end)
}
#' @export
pgm_end_set <- function(ast, node, end) {
    invisible(.Call(C_rastr_pgm_end_set, ast, node, end))
}




################################################################################
# dlmtd
################################################################################
#' @export
dlmtd_new <- function(ast, expr, dlmtr) {
    .Call(C_rastr_dlmtd_new, ast, expr, dlmtr)
}
#' @export
dlmtd_type <- function(ast, node) {
    .Call(C_rastr_dlmtd_type, ast, node)
}
# expr #########################################################################
#' @export
dlmtd_expr_get <- function(ast, node) {
    .Call(C_rastr_dlmtd_expr_get, ast, node)
}
#' @export
dlmtd_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_dlmtd_expr_rep, ast, node, expr)
}
#' @export
dlmtd_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_dlmtd_expr_set, ast, node, expr))
}


# dlmtr ########################################################################
#' @export
dlmtd_dlmtr_get <- function(ast, node) {
    .Call(C_rastr_dlmtd_dlmtr_get, ast, node)
}
#' @export
dlmtd_dlmtr_rep <- function(ast, node, dlmtr) {
    .Call(C_rastr_dlmtd_dlmtr_rep, ast, node, dlmtr)
}
#' @export
dlmtd_dlmtr_set <- function(ast, node, dlmtr) {
    invisible(.Call(C_rastr_dlmtd_dlmtr_set, ast, node, dlmtr))
}




################################################################################
# msng
################################################################################
#' @export
msng_new <- function(ast, gap, loc) {
    .Call(C_rastr_msng_new, ast, gap, loc)
}
#' @export
msng_type <- function(ast, node) {
    .Call(C_rastr_msng_type, ast, node)
}
# gap ##########################################################################
#' @export
msng_gap_get <- function(ast, node) {
    .Call(C_rastr_msng_gap_get, ast, node)
}
#' @export
msng_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_msng_gap_rep, ast, node, gap)
}
#' @export
msng_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_msng_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
msng_loc_get <- function(ast, node) {
    .Call(C_rastr_msng_loc_get, ast, node)
}




################################################################################
# beg
################################################################################
#' @export
beg_type <- function(ast, node) {
    .Call(C_rastr_beg_type, ast, node)
}
# bom ##########################################################################
#' @export
beg_bom_get <- function(ast, node) {
    .Call(C_rastr_beg_bom_get, ast, node)
}


# loc ##########################################################################
#' @export
beg_loc_get <- function(ast, node) {
    .Call(C_rastr_beg_loc_get, ast, node)
}




################################################################################
# end
################################################################################
#' @export
end_new <- function(ast, gap, loc) {
    .Call(C_rastr_end_new, ast, gap, loc)
}
#' @export
end_type <- function(ast, node) {
    .Call(C_rastr_end_type, ast, node)
}
# gap ##########################################################################
#' @export
end_gap_get <- function(ast, node) {
    .Call(C_rastr_end_gap_get, ast, node)
}
#' @export
end_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_end_gap_rep, ast, node, gap)
}
#' @export
end_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_end_gap_set, ast, node, gap))
}


# loc ##########################################################################
#' @export
end_loc_get <- function(ast, node) {
    .Call(C_rastr_end_loc_get, ast, node)
}




################################################################################
# gap
################################################################################
#' @export
gap_type <- function(ast, node) {
    .Call(C_rastr_gap_type, ast, node)
}
# val ##########################################################################
#' @export
gap_val_get <- function(ast, node) {
    .Call(C_rastr_gap_val_get, ast, node)
}


# loc ##########################################################################
#' @export
gap_loc_get <- function(ast, node) {
    .Call(C_rastr_gap_loc_get, ast, node)
}




################################################################################
# loc
################################################################################
#' @export
loc_type <- function(ast, node) {
    .Call(C_rastr_loc_type, ast, node)
}
# lrow #########################################################################
#' @export
loc_lrow_get <- function(ast, node) {
    .Call(C_rastr_loc_lrow_get, ast, node)
}


# lcol #########################################################################
#' @export
loc_lcol_get <- function(ast, node) {
    .Call(C_rastr_loc_lcol_get, ast, node)
}


# lchr #########################################################################
#' @export
loc_lchr_get <- function(ast, node) {
    .Call(C_rastr_loc_lchr_get, ast, node)
}


# lbyte ########################################################################
#' @export
loc_lbyte_get <- function(ast, node) {
    .Call(C_rastr_loc_lbyte_get, ast, node)
}


# rrow #########################################################################
#' @export
loc_rrow_get <- function(ast, node) {
    .Call(C_rastr_loc_rrow_get, ast, node)
}


# rcol #########################################################################
#' @export
loc_rcol_get <- function(ast, node) {
    .Call(C_rastr_loc_rcol_get, ast, node)
}


# rchr #########################################################################
#' @export
loc_rchr_get <- function(ast, node) {
    .Call(C_rastr_loc_rchr_get, ast, node)
}


# rbyte ########################################################################
#' @export
loc_rbyte_get <- function(ast, node) {
    .Call(C_rastr_loc_rbyte_get, ast, node)
}




################################################################################
# err
################################################################################
#' @export
err_type <- function(ast, node) {
    .Call(C_rastr_err_type, ast, node)
}
# msg ##########################################################################
#' @export
err_msg_get <- function(ast, node) {
    .Call(C_rastr_err_msg_get, ast, node)
}


# loc ##########################################################################
#' @export
err_loc_get <- function(ast, node) {
    .Call(C_rastr_err_loc_get, ast, node)
}




