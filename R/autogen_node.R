################################################################################
# op
################################################################################
#' Create and query `op` nodes
#'
#' @param ast AST object
#' @param node `op` node
#'
#' @description
#' * `op_new()` instantiates a new `op` node.
#' * `op_type()` checks if the node is a `op` node.
#' * `op_<child>_get()` returns the `<child>` node of `op`.
#' * `op_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `op_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_op
#' @rdname doc_op
#' @export
op_type <- function(ast, node) {
    .Call(C_rastr_op_type, ast, node)
}
## gap
#' @rdname doc_op
#' @export
op_gap_get <- function(ast, node) {
    .Call(C_rastr_op_gap_get, ast, node)
}
#' @rdname doc_op
#' @export
op_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_op_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_op
#' @export
op_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_op_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_op
#' @export
op_loc_get <- function(ast, node) {
    .Call(C_rastr_op_loc_get, ast, node)
}




################################################################################
# dlmtr
################################################################################
#' Create and query `dlmtr` nodes
#'
#' @param ast AST object
#' @param node `dlmtr` node
#'
#' @description
#' * `dlmtr_new()` instantiates a new `dlmtr` node.
#' * `dlmtr_type()` checks if the node is a `dlmtr` node.
#' * `dlmtr_<child>_get()` returns the `<child>` node of `dlmtr`.
#' * `dlmtr_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `dlmtr_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_dlmtr
#' @rdname doc_dlmtr
#' @export
dlmtr_type <- function(ast, node) {
    .Call(C_rastr_dlmtr_type, ast, node)
}
## gap
#' @rdname doc_dlmtr
#' @export
dlmtr_gap_get <- function(ast, node) {
    .Call(C_rastr_dlmtr_gap_get, ast, node)
}
#' @rdname doc_dlmtr
#' @export
dlmtr_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_dlmtr_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_dlmtr
#' @export
dlmtr_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_dlmtr_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_dlmtr
#' @export
dlmtr_loc_get <- function(ast, node) {
    .Call(C_rastr_dlmtr_loc_get, ast, node)
}




################################################################################
# bkt
################################################################################
#' Create and query `bkt` nodes
#'
#' @param ast AST object
#' @param node `bkt` node
#'
#' @description
#' * `bkt_new()` instantiates a new `bkt` node.
#' * `bkt_type()` checks if the node is a `bkt` node.
#' * `bkt_<child>_get()` returns the `<child>` node of `bkt`.
#' * `bkt_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `bkt_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_bkt
#' @rdname doc_bkt
#' @export
bkt_type <- function(ast, node) {
    .Call(C_rastr_bkt_type, ast, node)
}
## gap
#' @rdname doc_bkt
#' @export
bkt_gap_get <- function(ast, node) {
    .Call(C_rastr_bkt_gap_get, ast, node)
}
#' @rdname doc_bkt
#' @export
bkt_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_bkt_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_bkt
#' @export
bkt_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_bkt_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_bkt
#' @export
bkt_loc_get <- function(ast, node) {
    .Call(C_rastr_bkt_loc_get, ast, node)
}




################################################################################
# null
################################################################################
#' Create and query `null` nodes
#'
#' @param ast AST object
#' @param node `null` node
#'
#' @description
#' * `null_new()` instantiates a new `null` node.
#' * `null_type()` checks if the node is a `null` node.
#' * `null_<child>_get()` returns the `<child>` node of `null`.
#' * `null_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `null_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_null
#' @rdname doc_null
#' @export
null_new <- function(ast, gap, loc) {
    .Call(C_rastr_null_new, ast, gap, loc)
}
#' @rdname doc_null
#' @export
null_type <- function(ast, node) {
    .Call(C_rastr_null_type, ast, node)
}
## gap
#' @rdname doc_null
#' @export
null_gap_get <- function(ast, node) {
    .Call(C_rastr_null_gap_get, ast, node)
}
#' @rdname doc_null
#' @export
null_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_null_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_null
#' @export
null_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_null_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_null
#' @export
null_loc_get <- function(ast, node) {
    .Call(C_rastr_null_loc_get, ast, node)
}




################################################################################
# lgl
################################################################################
#' Create and query `lgl` nodes
#'
#' @param ast AST object
#' @param node `lgl` node
#'
#' @description
#' * `lgl_new()` instantiates a new `lgl` node.
#' * `lgl_type()` checks if the node is a `lgl` node.
#' * `lgl_<child>_get()` returns the `<child>` node of `lgl`.
#' * `lgl_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `lgl_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_lgl
#' @rdname doc_lgl
#' @export
lgl_type <- function(ast, node) {
    .Call(C_rastr_lgl_type, ast, node)
}
## val
#' @rdname doc_lgl
#' @export
lgl_val_get <- function(ast, node) {
    .Call(C_rastr_lgl_val_get, ast, node)
}


## gap
#' @rdname doc_lgl
#' @export
lgl_gap_get <- function(ast, node) {
    .Call(C_rastr_lgl_gap_get, ast, node)
}
#' @rdname doc_lgl
#' @export
lgl_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_lgl_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_lgl
#' @export
lgl_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_lgl_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_lgl
#' @export
lgl_loc_get <- function(ast, node) {
    .Call(C_rastr_lgl_loc_get, ast, node)
}




################################################################################
# int
################################################################################
#' Create and query `int` nodes
#'
#' @param ast AST object
#' @param node `int` node
#'
#' @description
#' * `int_new()` instantiates a new `int` node.
#' * `int_type()` checks if the node is a `int` node.
#' * `int_<child>_get()` returns the `<child>` node of `int`.
#' * `int_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `int_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_int
#' @rdname doc_int
#' @export
int_type <- function(ast, node) {
    .Call(C_rastr_int_type, ast, node)
}
## syn
#' @rdname doc_int
#' @export
int_syn_get <- function(ast, node) {
    .Call(C_rastr_int_syn_get, ast, node)
}


## val
#' @rdname doc_int
#' @export
int_val_get <- function(ast, node) {
    .Call(C_rastr_int_val_get, ast, node)
}


## gap
#' @rdname doc_int
#' @export
int_gap_get <- function(ast, node) {
    .Call(C_rastr_int_gap_get, ast, node)
}
#' @rdname doc_int
#' @export
int_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_int_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_int
#' @export
int_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_int_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_int
#' @export
int_loc_get <- function(ast, node) {
    .Call(C_rastr_int_loc_get, ast, node)
}




################################################################################
# dbl
################################################################################
#' Create and query `dbl` nodes
#'
#' @param ast AST object
#' @param node `dbl` node
#'
#' @description
#' * `dbl_new()` instantiates a new `dbl` node.
#' * `dbl_type()` checks if the node is a `dbl` node.
#' * `dbl_<child>_get()` returns the `<child>` node of `dbl`.
#' * `dbl_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `dbl_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_dbl
#' @rdname doc_dbl
#' @export
dbl_type <- function(ast, node) {
    .Call(C_rastr_dbl_type, ast, node)
}
## syn
#' @rdname doc_dbl
#' @export
dbl_syn_get <- function(ast, node) {
    .Call(C_rastr_dbl_syn_get, ast, node)
}


## val
#' @rdname doc_dbl
#' @export
dbl_val_get <- function(ast, node) {
    .Call(C_rastr_dbl_val_get, ast, node)
}


## gap
#' @rdname doc_dbl
#' @export
dbl_gap_get <- function(ast, node) {
    .Call(C_rastr_dbl_gap_get, ast, node)
}
#' @rdname doc_dbl
#' @export
dbl_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_dbl_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_dbl
#' @export
dbl_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_dbl_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_dbl
#' @export
dbl_loc_get <- function(ast, node) {
    .Call(C_rastr_dbl_loc_get, ast, node)
}




################################################################################
# cpx
################################################################################
#' Create and query `cpx` nodes
#'
#' @param ast AST object
#' @param node `cpx` node
#'
#' @description
#' * `cpx_new()` instantiates a new `cpx` node.
#' * `cpx_type()` checks if the node is a `cpx` node.
#' * `cpx_<child>_get()` returns the `<child>` node of `cpx`.
#' * `cpx_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `cpx_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_cpx
#' @rdname doc_cpx
#' @export
cpx_type <- function(ast, node) {
    .Call(C_rastr_cpx_type, ast, node)
}
## syn
#' @rdname doc_cpx
#' @export
cpx_syn_get <- function(ast, node) {
    .Call(C_rastr_cpx_syn_get, ast, node)
}


## val
#' @rdname doc_cpx
#' @export
cpx_val_get <- function(ast, node) {
    .Call(C_rastr_cpx_val_get, ast, node)
}


## gap
#' @rdname doc_cpx
#' @export
cpx_gap_get <- function(ast, node) {
    .Call(C_rastr_cpx_gap_get, ast, node)
}
#' @rdname doc_cpx
#' @export
cpx_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_cpx_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_cpx
#' @export
cpx_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_cpx_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_cpx
#' @export
cpx_loc_get <- function(ast, node) {
    .Call(C_rastr_cpx_loc_get, ast, node)
}




################################################################################
# chr
################################################################################
#' Create and query `chr` nodes
#'
#' @param ast AST object
#' @param node `chr` node
#'
#' @description
#' * `chr_new()` instantiates a new `chr` node.
#' * `chr_type()` checks if the node is a `chr` node.
#' * `chr_<child>_get()` returns the `<child>` node of `chr`.
#' * `chr_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `chr_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_chr
#' @rdname doc_chr
#' @export
chr_type <- function(ast, node) {
    .Call(C_rastr_chr_type, ast, node)
}
## syn
#' @rdname doc_chr
#' @export
chr_syn_get <- function(ast, node) {
    .Call(C_rastr_chr_syn_get, ast, node)
}


## val
#' @rdname doc_chr
#' @export
chr_val_get <- function(ast, node) {
    .Call(C_rastr_chr_val_get, ast, node)
}


## gap
#' @rdname doc_chr
#' @export
chr_gap_get <- function(ast, node) {
    .Call(C_rastr_chr_gap_get, ast, node)
}
#' @rdname doc_chr
#' @export
chr_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_chr_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_chr
#' @export
chr_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_chr_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_chr
#' @export
chr_loc_get <- function(ast, node) {
    .Call(C_rastr_chr_loc_get, ast, node)
}




################################################################################
# sym
################################################################################
#' Create and query `sym` nodes
#'
#' @param ast AST object
#' @param node `sym` node
#'
#' @description
#' * `sym_new()` instantiates a new `sym` node.
#' * `sym_type()` checks if the node is a `sym` node.
#' * `sym_<child>_get()` returns the `<child>` node of `sym`.
#' * `sym_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `sym_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_sym
#' @rdname doc_sym
#' @export
sym_type <- function(ast, node) {
    .Call(C_rastr_sym_type, ast, node)
}
## syn
#' @rdname doc_sym
#' @export
sym_syn_get <- function(ast, node) {
    .Call(C_rastr_sym_syn_get, ast, node)
}


## val
#' @rdname doc_sym
#' @export
sym_val_get <- function(ast, node) {
    .Call(C_rastr_sym_val_get, ast, node)
}


## gap
#' @rdname doc_sym
#' @export
sym_gap_get <- function(ast, node) {
    .Call(C_rastr_sym_gap_get, ast, node)
}
#' @rdname doc_sym
#' @export
sym_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_sym_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_sym
#' @export
sym_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_sym_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_sym
#' @export
sym_loc_get <- function(ast, node) {
    .Call(C_rastr_sym_loc_get, ast, node)
}




################################################################################
# blk
################################################################################
#' Create and query `blk` nodes
#'
#' @param ast AST object
#' @param node `blk` node
#'
#' @description
#' * `blk_new()` instantiates a new `blk` node.
#' * `blk_type()` checks if the node is a `blk` node.
#' * `blk_<child>_get()` returns the `<child>` node of `blk`.
#' * `blk_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `blk_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_blk
#' @rdname doc_blk
#' @export
blk_new <- function(ast, lbkt, exprs, rbkt) {
    .Call(C_rastr_blk_new, ast, lbkt, exprs, rbkt)
}
#' @rdname doc_blk
#' @export
blk_type <- function(ast, node) {
    .Call(C_rastr_blk_type, ast, node)
}
## lbkt
#' @rdname doc_blk
#' @export
blk_lbkt_get <- function(ast, node) {
    .Call(C_rastr_blk_lbkt_get, ast, node)
}
#' @rdname doc_blk
#' @export
blk_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_blk_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_blk
#' @export
blk_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_blk_lbkt_set, ast, node, lbkt))
}


## exprs
#' @rdname doc_blk
#' @export
blk_exprs_get <- function(ast, node) {
    .Call(C_rastr_blk_exprs_get, ast, node)
}
#' @rdname doc_blk
#' @export
blk_exprs_rep <- function(ast, node, exprs) {
    .Call(C_rastr_blk_exprs_rep, ast, node, exprs)
}
#' @param exprs `exprs` node
#' @rdname doc_blk
#' @export
blk_exprs_set <- function(ast, node, exprs) {
    invisible(.Call(C_rastr_blk_exprs_set, ast, node, exprs))
}


## rbkt
#' @rdname doc_blk
#' @export
blk_rbkt_get <- function(ast, node) {
    .Call(C_rastr_blk_rbkt_get, ast, node)
}
#' @rdname doc_blk
#' @export
blk_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_blk_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_blk
#' @export
blk_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_blk_rbkt_set, ast, node, rbkt))
}




################################################################################
# grp
################################################################################
#' Create and query `grp` nodes
#'
#' @param ast AST object
#' @param node `grp` node
#'
#' @description
#' * `grp_new()` instantiates a new `grp` node.
#' * `grp_type()` checks if the node is a `grp` node.
#' * `grp_<child>_get()` returns the `<child>` node of `grp`.
#' * `grp_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `grp_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_grp
#' @rdname doc_grp
#' @export
grp_new <- function(ast, lbkt, expr, rbkt) {
    .Call(C_rastr_grp_new, ast, lbkt, expr, rbkt)
}
#' @rdname doc_grp
#' @export
grp_type <- function(ast, node) {
    .Call(C_rastr_grp_type, ast, node)
}
## lbkt
#' @rdname doc_grp
#' @export
grp_lbkt_get <- function(ast, node) {
    .Call(C_rastr_grp_lbkt_get, ast, node)
}
#' @rdname doc_grp
#' @export
grp_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_grp_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_grp
#' @export
grp_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_grp_lbkt_set, ast, node, lbkt))
}


## expr
#' @rdname doc_grp
#' @export
grp_expr_get <- function(ast, node) {
    .Call(C_rastr_grp_expr_get, ast, node)
}
#' @rdname doc_grp
#' @export
grp_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_grp_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_grp
#' @export
grp_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_grp_expr_set, ast, node, expr))
}


## rbkt
#' @rdname doc_grp
#' @export
grp_rbkt_get <- function(ast, node) {
    .Call(C_rastr_grp_rbkt_get, ast, node)
}
#' @rdname doc_grp
#' @export
grp_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_grp_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_grp
#' @export
grp_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_grp_rbkt_set, ast, node, rbkt))
}




################################################################################
# nuop
################################################################################
#' Create and query `nuop` nodes
#'
#' @param ast AST object
#' @param node `nuop` node
#'
#' @description
#' * `nuop_new()` instantiates a new `nuop` node.
#' * `nuop_type()` checks if the node is a `nuop` node.
#' * `nuop_<child>_get()` returns the `<child>` node of `nuop`.
#' * `nuop_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `nuop_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_nuop
#' @rdname doc_nuop
#' @export
nuop_new <- function(ast, op) {
    .Call(C_rastr_nuop_new, ast, op)
}
#' @rdname doc_nuop
#' @export
nuop_type <- function(ast, node) {
    .Call(C_rastr_nuop_type, ast, node)
}
## op
#' @rdname doc_nuop
#' @export
nuop_op_get <- function(ast, node) {
    .Call(C_rastr_nuop_op_get, ast, node)
}
#' @rdname doc_nuop
#' @export
nuop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_nuop_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_nuop
#' @export
nuop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_nuop_op_set, ast, node, op))
}




################################################################################
# unop
################################################################################
#' Create and query `unop` nodes
#'
#' @param ast AST object
#' @param node `unop` node
#'
#' @description
#' * `unop_new()` instantiates a new `unop` node.
#' * `unop_type()` checks if the node is a `unop` node.
#' * `unop_<child>_get()` returns the `<child>` node of `unop`.
#' * `unop_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `unop_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_unop
#' @rdname doc_unop
#' @export
unop_new <- function(ast, op, expr) {
    .Call(C_rastr_unop_new, ast, op, expr)
}
#' @rdname doc_unop
#' @export
unop_type <- function(ast, node) {
    .Call(C_rastr_unop_type, ast, node)
}
## op
#' @rdname doc_unop
#' @export
unop_op_get <- function(ast, node) {
    .Call(C_rastr_unop_op_get, ast, node)
}
#' @rdname doc_unop
#' @export
unop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_unop_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_unop
#' @export
unop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_unop_op_set, ast, node, op))
}


## expr
#' @rdname doc_unop
#' @export
unop_expr_get <- function(ast, node) {
    .Call(C_rastr_unop_expr_get, ast, node)
}
#' @rdname doc_unop
#' @export
unop_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_unop_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_unop
#' @export
unop_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_unop_expr_set, ast, node, expr))
}




################################################################################
# binop
################################################################################
#' Create and query `binop` nodes
#'
#' @param ast AST object
#' @param node `binop` node
#'
#' @description
#' * `binop_new()` instantiates a new `binop` node.
#' * `binop_type()` checks if the node is a `binop` node.
#' * `binop_<child>_get()` returns the `<child>` node of `binop`.
#' * `binop_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `binop_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_binop
#' @rdname doc_binop
#' @export
binop_new <- function(ast, lexpr, op, rexpr) {
    .Call(C_rastr_binop_new, ast, lexpr, op, rexpr)
}
#' @rdname doc_binop
#' @export
binop_type <- function(ast, node) {
    .Call(C_rastr_binop_type, ast, node)
}
## lexpr
#' @rdname doc_binop
#' @export
binop_lexpr_get <- function(ast, node) {
    .Call(C_rastr_binop_lexpr_get, ast, node)
}
#' @rdname doc_binop
#' @export
binop_lexpr_rep <- function(ast, node, lexpr) {
    .Call(C_rastr_binop_lexpr_rep, ast, node, lexpr)
}
#' @param lexpr `lexpr` node
#' @rdname doc_binop
#' @export
binop_lexpr_set <- function(ast, node, lexpr) {
    invisible(.Call(C_rastr_binop_lexpr_set, ast, node, lexpr))
}


## op
#' @rdname doc_binop
#' @export
binop_op_get <- function(ast, node) {
    .Call(C_rastr_binop_op_get, ast, node)
}
#' @rdname doc_binop
#' @export
binop_op_rep <- function(ast, node, op) {
    .Call(C_rastr_binop_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_binop
#' @export
binop_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_binop_op_set, ast, node, op))
}


## rexpr
#' @rdname doc_binop
#' @export
binop_rexpr_get <- function(ast, node) {
    .Call(C_rastr_binop_rexpr_get, ast, node)
}
#' @rdname doc_binop
#' @export
binop_rexpr_rep <- function(ast, node, rexpr) {
    .Call(C_rastr_binop_rexpr_rep, ast, node, rexpr)
}
#' @param rexpr `rexpr` node
#' @rdname doc_binop
#' @export
binop_rexpr_set <- function(ast, node, rexpr) {
    invisible(.Call(C_rastr_binop_rexpr_set, ast, node, rexpr))
}




################################################################################
# rlp
################################################################################
#' Create and query `rlp` nodes
#'
#' @param ast AST object
#' @param node `rlp` node
#'
#' @description
#' * `rlp_new()` instantiates a new `rlp` node.
#' * `rlp_type()` checks if the node is a `rlp` node.
#' * `rlp_<child>_get()` returns the `<child>` node of `rlp`.
#' * `rlp_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `rlp_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_rlp
#' @rdname doc_rlp
#' @export
rlp_new <- function(ast, op, body) {
    .Call(C_rastr_rlp_new, ast, op, body)
}
#' @rdname doc_rlp
#' @export
rlp_type <- function(ast, node) {
    .Call(C_rastr_rlp_type, ast, node)
}
## op
#' @rdname doc_rlp
#' @export
rlp_op_get <- function(ast, node) {
    .Call(C_rastr_rlp_op_get, ast, node)
}
#' @rdname doc_rlp
#' @export
rlp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_rlp_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_rlp
#' @export
rlp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_rlp_op_set, ast, node, op))
}


## body
#' @rdname doc_rlp
#' @export
rlp_body_get <- function(ast, node) {
    .Call(C_rastr_rlp_body_get, ast, node)
}
#' @rdname doc_rlp
#' @export
rlp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_rlp_body_rep, ast, node, body)
}
#' @param body `body` node
#' @rdname doc_rlp
#' @export
rlp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_rlp_body_set, ast, node, body))
}




################################################################################
# wlp
################################################################################
#' Create and query `wlp` nodes
#'
#' @param ast AST object
#' @param node `wlp` node
#'
#' @description
#' * `wlp_new()` instantiates a new `wlp` node.
#' * `wlp_type()` checks if the node is a `wlp` node.
#' * `wlp_<child>_get()` returns the `<child>` node of `wlp`.
#' * `wlp_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `wlp_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_wlp
#' @rdname doc_wlp
#' @export
wlp_new <- function(ast, op, cond, body) {
    .Call(C_rastr_wlp_new, ast, op, cond, body)
}
#' @rdname doc_wlp
#' @export
wlp_type <- function(ast, node) {
    .Call(C_rastr_wlp_type, ast, node)
}
## op
#' @rdname doc_wlp
#' @export
wlp_op_get <- function(ast, node) {
    .Call(C_rastr_wlp_op_get, ast, node)
}
#' @rdname doc_wlp
#' @export
wlp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_wlp_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_wlp
#' @export
wlp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_wlp_op_set, ast, node, op))
}


## cond
#' @rdname doc_wlp
#' @export
wlp_cond_get <- function(ast, node) {
    .Call(C_rastr_wlp_cond_get, ast, node)
}
#' @rdname doc_wlp
#' @export
wlp_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_wlp_cond_rep, ast, node, cond)
}
#' @param cond `cond` node
#' @rdname doc_wlp
#' @export
wlp_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_wlp_cond_set, ast, node, cond))
}


## body
#' @rdname doc_wlp
#' @export
wlp_body_get <- function(ast, node) {
    .Call(C_rastr_wlp_body_get, ast, node)
}
#' @rdname doc_wlp
#' @export
wlp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_wlp_body_rep, ast, node, body)
}
#' @param body `body` node
#' @rdname doc_wlp
#' @export
wlp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_wlp_body_set, ast, node, body))
}




################################################################################
# flp
################################################################################
#' Create and query `flp` nodes
#'
#' @param ast AST object
#' @param node `flp` node
#'
#' @description
#' * `flp_new()` instantiates a new `flp` node.
#' * `flp_type()` checks if the node is a `flp` node.
#' * `flp_<child>_get()` returns the `<child>` node of `flp`.
#' * `flp_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `flp_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_flp
#' @rdname doc_flp
#' @export
flp_new <- function(ast, op, iter, body) {
    .Call(C_rastr_flp_new, ast, op, iter, body)
}
#' @rdname doc_flp
#' @export
flp_type <- function(ast, node) {
    .Call(C_rastr_flp_type, ast, node)
}
## op
#' @rdname doc_flp
#' @export
flp_op_get <- function(ast, node) {
    .Call(C_rastr_flp_op_get, ast, node)
}
#' @rdname doc_flp
#' @export
flp_op_rep <- function(ast, node, op) {
    .Call(C_rastr_flp_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_flp
#' @export
flp_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_flp_op_set, ast, node, op))
}


## iter
#' @rdname doc_flp
#' @export
flp_iter_get <- function(ast, node) {
    .Call(C_rastr_flp_iter_get, ast, node)
}
#' @rdname doc_flp
#' @export
flp_iter_rep <- function(ast, node, iter) {
    .Call(C_rastr_flp_iter_rep, ast, node, iter)
}
#' @param iter `iter` node
#' @rdname doc_flp
#' @export
flp_iter_set <- function(ast, node, iter) {
    invisible(.Call(C_rastr_flp_iter_set, ast, node, iter))
}


## body
#' @rdname doc_flp
#' @export
flp_body_get <- function(ast, node) {
    .Call(C_rastr_flp_body_get, ast, node)
}
#' @rdname doc_flp
#' @export
flp_body_rep <- function(ast, node, body) {
    .Call(C_rastr_flp_body_rep, ast, node, body)
}
#' @param body `body` node
#' @rdname doc_flp
#' @export
flp_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_flp_body_set, ast, node, body))
}




################################################################################
# icond
################################################################################
#' Create and query `icond` nodes
#'
#' @param ast AST object
#' @param node `icond` node
#'
#' @description
#' * `icond_new()` instantiates a new `icond` node.
#' * `icond_type()` checks if the node is a `icond` node.
#' * `icond_<child>_get()` returns the `<child>` node of `icond`.
#' * `icond_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `icond_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_icond
#' @rdname doc_icond
#' @export
icond_new <- function(ast, iop, cond, ibody) {
    .Call(C_rastr_icond_new, ast, iop, cond, ibody)
}
#' @rdname doc_icond
#' @export
icond_type <- function(ast, node) {
    .Call(C_rastr_icond_type, ast, node)
}
## iop
#' @rdname doc_icond
#' @export
icond_iop_get <- function(ast, node) {
    .Call(C_rastr_icond_iop_get, ast, node)
}
#' @rdname doc_icond
#' @export
icond_iop_rep <- function(ast, node, iop) {
    .Call(C_rastr_icond_iop_rep, ast, node, iop)
}
#' @param iop `iop` node
#' @rdname doc_icond
#' @export
icond_iop_set <- function(ast, node, iop) {
    invisible(.Call(C_rastr_icond_iop_set, ast, node, iop))
}


## cond
#' @rdname doc_icond
#' @export
icond_cond_get <- function(ast, node) {
    .Call(C_rastr_icond_cond_get, ast, node)
}
#' @rdname doc_icond
#' @export
icond_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_icond_cond_rep, ast, node, cond)
}
#' @param cond `cond` node
#' @rdname doc_icond
#' @export
icond_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_icond_cond_set, ast, node, cond))
}


## ibody
#' @rdname doc_icond
#' @export
icond_ibody_get <- function(ast, node) {
    .Call(C_rastr_icond_ibody_get, ast, node)
}
#' @rdname doc_icond
#' @export
icond_ibody_rep <- function(ast, node, ibody) {
    .Call(C_rastr_icond_ibody_rep, ast, node, ibody)
}
#' @param ibody `ibody` node
#' @rdname doc_icond
#' @export
icond_ibody_set <- function(ast, node, ibody) {
    invisible(.Call(C_rastr_icond_ibody_set, ast, node, ibody))
}




################################################################################
# iecond
################################################################################
#' Create and query `iecond` nodes
#'
#' @param ast AST object
#' @param node `iecond` node
#'
#' @description
#' * `iecond_new()` instantiates a new `iecond` node.
#' * `iecond_type()` checks if the node is a `iecond` node.
#' * `iecond_<child>_get()` returns the `<child>` node of `iecond`.
#' * `iecond_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `iecond_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_iecond
#' @rdname doc_iecond
#' @export
iecond_new <- function(ast, iop, cond, ibody, eop, ebody) {
    .Call(C_rastr_iecond_new, ast, iop, cond, ibody, eop, ebody)
}
#' @rdname doc_iecond
#' @export
iecond_type <- function(ast, node) {
    .Call(C_rastr_iecond_type, ast, node)
}
## iop
#' @rdname doc_iecond
#' @export
iecond_iop_get <- function(ast, node) {
    .Call(C_rastr_iecond_iop_get, ast, node)
}
#' @rdname doc_iecond
#' @export
iecond_iop_rep <- function(ast, node, iop) {
    .Call(C_rastr_iecond_iop_rep, ast, node, iop)
}
#' @param iop `iop` node
#' @rdname doc_iecond
#' @export
iecond_iop_set <- function(ast, node, iop) {
    invisible(.Call(C_rastr_iecond_iop_set, ast, node, iop))
}


## cond
#' @rdname doc_iecond
#' @export
iecond_cond_get <- function(ast, node) {
    .Call(C_rastr_iecond_cond_get, ast, node)
}
#' @rdname doc_iecond
#' @export
iecond_cond_rep <- function(ast, node, cond) {
    .Call(C_rastr_iecond_cond_rep, ast, node, cond)
}
#' @param cond `cond` node
#' @rdname doc_iecond
#' @export
iecond_cond_set <- function(ast, node, cond) {
    invisible(.Call(C_rastr_iecond_cond_set, ast, node, cond))
}


## ibody
#' @rdname doc_iecond
#' @export
iecond_ibody_get <- function(ast, node) {
    .Call(C_rastr_iecond_ibody_get, ast, node)
}
#' @rdname doc_iecond
#' @export
iecond_ibody_rep <- function(ast, node, ibody) {
    .Call(C_rastr_iecond_ibody_rep, ast, node, ibody)
}
#' @param ibody `ibody` node
#' @rdname doc_iecond
#' @export
iecond_ibody_set <- function(ast, node, ibody) {
    invisible(.Call(C_rastr_iecond_ibody_set, ast, node, ibody))
}


## eop
#' @rdname doc_iecond
#' @export
iecond_eop_get <- function(ast, node) {
    .Call(C_rastr_iecond_eop_get, ast, node)
}
#' @rdname doc_iecond
#' @export
iecond_eop_rep <- function(ast, node, eop) {
    .Call(C_rastr_iecond_eop_rep, ast, node, eop)
}
#' @param eop `eop` node
#' @rdname doc_iecond
#' @export
iecond_eop_set <- function(ast, node, eop) {
    invisible(.Call(C_rastr_iecond_eop_set, ast, node, eop))
}


## ebody
#' @rdname doc_iecond
#' @export
iecond_ebody_get <- function(ast, node) {
    .Call(C_rastr_iecond_ebody_get, ast, node)
}
#' @rdname doc_iecond
#' @export
iecond_ebody_rep <- function(ast, node, ebody) {
    .Call(C_rastr_iecond_ebody_rep, ast, node, ebody)
}
#' @param ebody `ebody` node
#' @rdname doc_iecond
#' @export
iecond_ebody_set <- function(ast, node, ebody) {
    invisible(.Call(C_rastr_iecond_ebody_set, ast, node, ebody))
}




################################################################################
# fndefn
################################################################################
#' Create and query `fndefn` nodes
#'
#' @param ast AST object
#' @param node `fndefn` node
#'
#' @description
#' * `fndefn_new()` instantiates a new `fndefn` node.
#' * `fndefn_type()` checks if the node is a `fndefn` node.
#' * `fndefn_<child>_get()` returns the `<child>` node of `fndefn`.
#' * `fndefn_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `fndefn_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_fndefn
#' @rdname doc_fndefn
#' @export
fndefn_new <- function(ast, op, lbkt, pars, rbkt, body) {
    .Call(C_rastr_fndefn_new, ast, op, lbkt, pars, rbkt, body)
}
#' @rdname doc_fndefn
#' @export
fndefn_type <- function(ast, node) {
    .Call(C_rastr_fndefn_type, ast, node)
}
## op
#' @rdname doc_fndefn
#' @export
fndefn_op_get <- function(ast, node) {
    .Call(C_rastr_fndefn_op_get, ast, node)
}
#' @rdname doc_fndefn
#' @export
fndefn_op_rep <- function(ast, node, op) {
    .Call(C_rastr_fndefn_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_fndefn
#' @export
fndefn_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_fndefn_op_set, ast, node, op))
}


## lbkt
#' @rdname doc_fndefn
#' @export
fndefn_lbkt_get <- function(ast, node) {
    .Call(C_rastr_fndefn_lbkt_get, ast, node)
}
#' @rdname doc_fndefn
#' @export
fndefn_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_fndefn_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_fndefn
#' @export
fndefn_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_fndefn_lbkt_set, ast, node, lbkt))
}


## pars
#' @rdname doc_fndefn
#' @export
fndefn_pars_get <- function(ast, node) {
    .Call(C_rastr_fndefn_pars_get, ast, node)
}
#' @rdname doc_fndefn
#' @export
fndefn_pars_rep <- function(ast, node, pars) {
    .Call(C_rastr_fndefn_pars_rep, ast, node, pars)
}
#' @param pars `pars` node
#' @rdname doc_fndefn
#' @export
fndefn_pars_set <- function(ast, node, pars) {
    invisible(.Call(C_rastr_fndefn_pars_set, ast, node, pars))
}


## rbkt
#' @rdname doc_fndefn
#' @export
fndefn_rbkt_get <- function(ast, node) {
    .Call(C_rastr_fndefn_rbkt_get, ast, node)
}
#' @rdname doc_fndefn
#' @export
fndefn_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_fndefn_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_fndefn
#' @export
fndefn_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_fndefn_rbkt_set, ast, node, rbkt))
}


## body
#' @rdname doc_fndefn
#' @export
fndefn_body_get <- function(ast, node) {
    .Call(C_rastr_fndefn_body_get, ast, node)
}
#' @rdname doc_fndefn
#' @export
fndefn_body_rep <- function(ast, node, body) {
    .Call(C_rastr_fndefn_body_rep, ast, node, body)
}
#' @param body `body` node
#' @rdname doc_fndefn
#' @export
fndefn_body_set <- function(ast, node, body) {
    invisible(.Call(C_rastr_fndefn_body_set, ast, node, body))
}




################################################################################
# fncall
################################################################################
#' Create and query `fncall` nodes
#'
#' @param ast AST object
#' @param node `fncall` node
#'
#' @description
#' * `fncall_new()` instantiates a new `fncall` node.
#' * `fncall_type()` checks if the node is a `fncall` node.
#' * `fncall_<child>_get()` returns the `<child>` node of `fncall`.
#' * `fncall_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `fncall_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_fncall
#' @rdname doc_fncall
#' @export
fncall_new <- function(ast, fn, lbkt, args, rbkt) {
    .Call(C_rastr_fncall_new, ast, fn, lbkt, args, rbkt)
}
#' @rdname doc_fncall
#' @export
fncall_type <- function(ast, node) {
    .Call(C_rastr_fncall_type, ast, node)
}
## fn
#' @rdname doc_fncall
#' @export
fncall_fn_get <- function(ast, node) {
    .Call(C_rastr_fncall_fn_get, ast, node)
}
#' @rdname doc_fncall
#' @export
fncall_fn_rep <- function(ast, node, fn) {
    .Call(C_rastr_fncall_fn_rep, ast, node, fn)
}
#' @param fn `fn` node
#' @rdname doc_fncall
#' @export
fncall_fn_set <- function(ast, node, fn) {
    invisible(.Call(C_rastr_fncall_fn_set, ast, node, fn))
}


## lbkt
#' @rdname doc_fncall
#' @export
fncall_lbkt_get <- function(ast, node) {
    .Call(C_rastr_fncall_lbkt_get, ast, node)
}
#' @rdname doc_fncall
#' @export
fncall_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_fncall_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_fncall
#' @export
fncall_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_fncall_lbkt_set, ast, node, lbkt))
}


## args
#' @rdname doc_fncall
#' @export
fncall_args_get <- function(ast, node) {
    .Call(C_rastr_fncall_args_get, ast, node)
}
#' @rdname doc_fncall
#' @export
fncall_args_rep <- function(ast, node, args) {
    .Call(C_rastr_fncall_args_rep, ast, node, args)
}
#' @param args `args` node
#' @rdname doc_fncall
#' @export
fncall_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_fncall_args_set, ast, node, args))
}


## rbkt
#' @rdname doc_fncall
#' @export
fncall_rbkt_get <- function(ast, node) {
    .Call(C_rastr_fncall_rbkt_get, ast, node)
}
#' @rdname doc_fncall
#' @export
fncall_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_fncall_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_fncall
#' @export
fncall_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_fncall_rbkt_set, ast, node, rbkt))
}




################################################################################
# sub
################################################################################
#' Create and query `sub` nodes
#'
#' @param ast AST object
#' @param node `sub` node
#'
#' @description
#' * `sub_new()` instantiates a new `sub` node.
#' * `sub_type()` checks if the node is a `sub` node.
#' * `sub_<child>_get()` returns the `<child>` node of `sub`.
#' * `sub_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `sub_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_sub
#' @rdname doc_sub
#' @export
sub_new <- function(ast, obj, lbkt, args, rbkt) {
    .Call(C_rastr_sub_new, ast, obj, lbkt, args, rbkt)
}
#' @rdname doc_sub
#' @export
sub_type <- function(ast, node) {
    .Call(C_rastr_sub_type, ast, node)
}
## obj
#' @rdname doc_sub
#' @export
sub_obj_get <- function(ast, node) {
    .Call(C_rastr_sub_obj_get, ast, node)
}
#' @rdname doc_sub
#' @export
sub_obj_rep <- function(ast, node, obj) {
    .Call(C_rastr_sub_obj_rep, ast, node, obj)
}
#' @param obj `obj` node
#' @rdname doc_sub
#' @export
sub_obj_set <- function(ast, node, obj) {
    invisible(.Call(C_rastr_sub_obj_set, ast, node, obj))
}


## lbkt
#' @rdname doc_sub
#' @export
sub_lbkt_get <- function(ast, node) {
    .Call(C_rastr_sub_lbkt_get, ast, node)
}
#' @rdname doc_sub
#' @export
sub_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_sub_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_sub
#' @export
sub_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_sub_lbkt_set, ast, node, lbkt))
}


## args
#' @rdname doc_sub
#' @export
sub_args_get <- function(ast, node) {
    .Call(C_rastr_sub_args_get, ast, node)
}
#' @rdname doc_sub
#' @export
sub_args_rep <- function(ast, node, args) {
    .Call(C_rastr_sub_args_rep, ast, node, args)
}
#' @param args `args` node
#' @rdname doc_sub
#' @export
sub_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_sub_args_set, ast, node, args))
}


## rbkt
#' @rdname doc_sub
#' @export
sub_rbkt_get <- function(ast, node) {
    .Call(C_rastr_sub_rbkt_get, ast, node)
}
#' @rdname doc_sub
#' @export
sub_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_sub_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_sub
#' @export
sub_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_sub_rbkt_set, ast, node, rbkt))
}




################################################################################
# idx
################################################################################
#' Create and query `idx` nodes
#'
#' @param ast AST object
#' @param node `idx` node
#'
#' @description
#' * `idx_new()` instantiates a new `idx` node.
#' * `idx_type()` checks if the node is a `idx` node.
#' * `idx_<child>_get()` returns the `<child>` node of `idx`.
#' * `idx_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `idx_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_idx
#' @rdname doc_idx
#' @export
idx_new <- function(ast, obj, lbkt, args, rbkt1, rbkt2) {
    .Call(C_rastr_idx_new, ast, obj, lbkt, args, rbkt1, rbkt2)
}
#' @rdname doc_idx
#' @export
idx_type <- function(ast, node) {
    .Call(C_rastr_idx_type, ast, node)
}
## obj
#' @rdname doc_idx
#' @export
idx_obj_get <- function(ast, node) {
    .Call(C_rastr_idx_obj_get, ast, node)
}
#' @rdname doc_idx
#' @export
idx_obj_rep <- function(ast, node, obj) {
    .Call(C_rastr_idx_obj_rep, ast, node, obj)
}
#' @param obj `obj` node
#' @rdname doc_idx
#' @export
idx_obj_set <- function(ast, node, obj) {
    invisible(.Call(C_rastr_idx_obj_set, ast, node, obj))
}


## lbkt
#' @rdname doc_idx
#' @export
idx_lbkt_get <- function(ast, node) {
    .Call(C_rastr_idx_lbkt_get, ast, node)
}
#' @rdname doc_idx
#' @export
idx_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_idx_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_idx
#' @export
idx_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_idx_lbkt_set, ast, node, lbkt))
}


## args
#' @rdname doc_idx
#' @export
idx_args_get <- function(ast, node) {
    .Call(C_rastr_idx_args_get, ast, node)
}
#' @rdname doc_idx
#' @export
idx_args_rep <- function(ast, node, args) {
    .Call(C_rastr_idx_args_rep, ast, node, args)
}
#' @param args `args` node
#' @rdname doc_idx
#' @export
idx_args_set <- function(ast, node, args) {
    invisible(.Call(C_rastr_idx_args_set, ast, node, args))
}


## rbkt1
#' @rdname doc_idx
#' @export
idx_rbkt1_get <- function(ast, node) {
    .Call(C_rastr_idx_rbkt1_get, ast, node)
}
#' @rdname doc_idx
#' @export
idx_rbkt1_rep <- function(ast, node, rbkt1) {
    .Call(C_rastr_idx_rbkt1_rep, ast, node, rbkt1)
}
#' @param rbkt1 `rbkt1` node
#' @rdname doc_idx
#' @export
idx_rbkt1_set <- function(ast, node, rbkt1) {
    invisible(.Call(C_rastr_idx_rbkt1_set, ast, node, rbkt1))
}


## rbkt2
#' @rdname doc_idx
#' @export
idx_rbkt2_get <- function(ast, node) {
    .Call(C_rastr_idx_rbkt2_get, ast, node)
}
#' @rdname doc_idx
#' @export
idx_rbkt2_rep <- function(ast, node, rbkt2) {
    .Call(C_rastr_idx_rbkt2_rep, ast, node, rbkt2)
}
#' @param rbkt2 `rbkt2` node
#' @rdname doc_idx
#' @export
idx_rbkt2_set <- function(ast, node, rbkt2) {
    invisible(.Call(C_rastr_idx_rbkt2_set, ast, node, rbkt2))
}




################################################################################
# aexpr
################################################################################
#' Create and query `aexpr` nodes
#'
#' @param ast AST object
#' @param node `aexpr` node
#'
#' @description
#' * `aexpr_new()` instantiates a new `aexpr` node.
#' * `aexpr_type()` checks if the node is a `aexpr` node.
#' * `aexpr_<child>_get()` returns the `<child>` node of `aexpr`.
#' * `aexpr_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `aexpr_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_aexpr
#' @rdname doc_aexpr
#' @export
aexpr_new <- function(ast, ann, expr) {
    .Call(C_rastr_aexpr_new, ast, ann, expr)
}
#' @rdname doc_aexpr
#' @export
aexpr_type <- function(ast, node) {
    .Call(C_rastr_aexpr_type, ast, node)
}
## ann
#' @rdname doc_aexpr
#' @export
aexpr_ann_get <- function(ast, node) {
    .Call(C_rastr_aexpr_ann_get, ast, node)
}
#' @rdname doc_aexpr
#' @export
aexpr_ann_rep <- function(ast, node, ann) {
    .Call(C_rastr_aexpr_ann_rep, ast, node, ann)
}
#' @param ann `ann` node
#' @rdname doc_aexpr
#' @export
aexpr_ann_set <- function(ast, node, ann) {
    invisible(.Call(C_rastr_aexpr_ann_set, ast, node, ann))
}


## expr
#' @rdname doc_aexpr
#' @export
aexpr_expr_get <- function(ast, node) {
    .Call(C_rastr_aexpr_expr_get, ast, node)
}
#' @rdname doc_aexpr
#' @export
aexpr_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_aexpr_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_aexpr
#' @export
aexpr_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_aexpr_expr_set, ast, node, expr))
}




################################################################################
# exprs
################################################################################
#' Create and query `exprs` nodes
#'
#' @param ast AST object
#' @param node `exprs` node
#' @param index one-based index into the `exprs` node
#' @param seq list of child nodes
#'
#' @description
#' * `exprs_new()` instantiates a new `exprs` node.
#' * `exprs_type()` checks if the node is a `exprs` node.
#' * `exprs_seq_get()` returns all the child nodes as a list.
#' * `exprs_get()` returns node at position `index`.
#' * `exprs_set()` sets the new node at position `index` and deletes the old node.
#' * `exprs_rep()` sets the new node at position `index` and returns the old node.
#' * `exprs_ins()` inserts nodes starting from position `index`.
#'
#' @name doc_exprs
#' @rdname doc_exprs
#' @export
exprs_new <- function(ast, seq) {
    .Call(C_rastr_exprs_new, ast, seq)
}
#' @rdname doc_exprs
#' @export
exprs_type <- function(ast, node) {
    .Call(C_rastr_exprs_type, ast, node)
}
## len
#' @rdname doc_exprs
#' @export
exprs_len_get <- function(ast, node) {
    .Call(C_rastr_exprs_len_get, ast, node)
}


## seq

#' @rdname doc_exprs
#' @export
exprs_seq_get <- function(ast, node) {
    .Call(C_rastr_exprs_seq_get, ast, node)
}

#' @rdname doc_exprs
#' @export
exprs_get <- function(ast, node, index) {
    .Call(C_rastr_exprs_get, ast, node, index)
}
#' @rdname doc_exprs
#' @export
exprs_rep <- function(ast, node, index, expr) {
    .Call(C_rastr_exprs_rep, ast, node, index, expr)
}
#' @param expr `expr` node
#' @rdname doc_exprs
#' @export
exprs_expr_set <- function(ast, node, index, expr) {
    invisible(.Call(C_rastr_exprs_set, ast, node, index, expr))
}
#' @rdname doc_exprs
#' @export
exprs_ins <- function(ast, node, index, seq) {
    invisible(.Call(C_rastr_exprs_ins, ast, node, index, seq))
}




################################################################################
# pars
################################################################################
#' Create and query `pars` nodes
#'
#' @param ast AST object
#' @param node `pars` node
#' @param index one-based index into the `pars` node
#' @param seq list of child nodes
#'
#' @description
#' * `pars_new()` instantiates a new `pars` node.
#' * `pars_type()` checks if the node is a `pars` node.
#' * `pars_seq_get()` returns all the child nodes as a list.
#' * `pars_get()` returns node at position `index`.
#' * `pars_set()` sets the new node at position `index` and deletes the old node.
#' * `pars_rep()` sets the new node at position `index` and returns the old node.
#' * `pars_ins()` inserts nodes starting from position `index`.
#'
#' @name doc_pars
#' @rdname doc_pars
#' @export
pars_new <- function(ast, seq) {
    .Call(C_rastr_pars_new, ast, seq)
}
#' @rdname doc_pars
#' @export
pars_type <- function(ast, node) {
    .Call(C_rastr_pars_type, ast, node)
}
## len
#' @rdname doc_pars
#' @export
pars_len_get <- function(ast, node) {
    .Call(C_rastr_pars_len_get, ast, node)
}


## seq

#' @rdname doc_pars
#' @export
pars_seq_get <- function(ast, node) {
    .Call(C_rastr_pars_seq_get, ast, node)
}

#' @rdname doc_pars
#' @export
pars_get <- function(ast, node, index) {
    .Call(C_rastr_pars_get, ast, node, index)
}
#' @rdname doc_pars
#' @export
pars_rep <- function(ast, node, index, par) {
    .Call(C_rastr_pars_rep, ast, node, index, par)
}
#' @param par `par` node
#' @rdname doc_pars
#' @export
pars_par_set <- function(ast, node, index, par) {
    invisible(.Call(C_rastr_pars_set, ast, node, index, par))
}
#' @rdname doc_pars
#' @export
pars_ins <- function(ast, node, index, seq) {
    invisible(.Call(C_rastr_pars_ins, ast, node, index, seq))
}




################################################################################
# dpar
################################################################################
#' Create and query `dpar` nodes
#'
#' @param ast AST object
#' @param node `dpar` node
#'
#' @description
#' * `dpar_new()` instantiates a new `dpar` node.
#' * `dpar_type()` checks if the node is a `dpar` node.
#' * `dpar_<child>_get()` returns the `<child>` node of `dpar`.
#' * `dpar_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `dpar_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_dpar
#' @rdname doc_dpar
#' @export
dpar_new <- function(ast, name, op, expr) {
    .Call(C_rastr_dpar_new, ast, name, op, expr)
}
#' @rdname doc_dpar
#' @export
dpar_type <- function(ast, node) {
    .Call(C_rastr_dpar_type, ast, node)
}
## name
#' @rdname doc_dpar
#' @export
dpar_name_get <- function(ast, node) {
    .Call(C_rastr_dpar_name_get, ast, node)
}
#' @rdname doc_dpar
#' @export
dpar_name_rep <- function(ast, node, name) {
    .Call(C_rastr_dpar_name_rep, ast, node, name)
}
#' @param name `name` node
#' @rdname doc_dpar
#' @export
dpar_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_dpar_name_set, ast, node, name))
}


## op
#' @rdname doc_dpar
#' @export
dpar_op_get <- function(ast, node) {
    .Call(C_rastr_dpar_op_get, ast, node)
}
#' @rdname doc_dpar
#' @export
dpar_op_rep <- function(ast, node, op) {
    .Call(C_rastr_dpar_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_dpar
#' @export
dpar_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_dpar_op_set, ast, node, op))
}


## expr
#' @rdname doc_dpar
#' @export
dpar_expr_get <- function(ast, node) {
    .Call(C_rastr_dpar_expr_get, ast, node)
}
#' @rdname doc_dpar
#' @export
dpar_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_dpar_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_dpar
#' @export
dpar_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_dpar_expr_set, ast, node, expr))
}




################################################################################
# ndpar
################################################################################
#' Create and query `ndpar` nodes
#'
#' @param ast AST object
#' @param node `ndpar` node
#'
#' @description
#' * `ndpar_new()` instantiates a new `ndpar` node.
#' * `ndpar_type()` checks if the node is a `ndpar` node.
#' * `ndpar_<child>_get()` returns the `<child>` node of `ndpar`.
#' * `ndpar_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `ndpar_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_ndpar
#' @rdname doc_ndpar
#' @export
ndpar_new <- function(ast, name) {
    .Call(C_rastr_ndpar_new, ast, name)
}
#' @rdname doc_ndpar
#' @export
ndpar_type <- function(ast, node) {
    .Call(C_rastr_ndpar_type, ast, node)
}
## name
#' @rdname doc_ndpar
#' @export
ndpar_name_get <- function(ast, node) {
    .Call(C_rastr_ndpar_name_get, ast, node)
}
#' @rdname doc_ndpar
#' @export
ndpar_name_rep <- function(ast, node, name) {
    .Call(C_rastr_ndpar_name_rep, ast, node, name)
}
#' @param name `name` node
#' @rdname doc_ndpar
#' @export
ndpar_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_ndpar_name_set, ast, node, name))
}




################################################################################
# args
################################################################################
#' Create and query `args` nodes
#'
#' @param ast AST object
#' @param node `args` node
#' @param index one-based index into the `args` node
#' @param seq list of child nodes
#'
#' @description
#' * `args_new()` instantiates a new `args` node.
#' * `args_type()` checks if the node is a `args` node.
#' * `args_seq_get()` returns all the child nodes as a list.
#' * `args_get()` returns node at position `index`.
#' * `args_set()` sets the new node at position `index` and deletes the old node.
#' * `args_rep()` sets the new node at position `index` and returns the old node.
#' * `args_ins()` inserts nodes starting from position `index`.
#'
#' @name doc_args
#' @rdname doc_args
#' @export
args_new <- function(ast, seq) {
    .Call(C_rastr_args_new, ast, seq)
}
#' @rdname doc_args
#' @export
args_type <- function(ast, node) {
    .Call(C_rastr_args_type, ast, node)
}
## len
#' @rdname doc_args
#' @export
args_len_get <- function(ast, node) {
    .Call(C_rastr_args_len_get, ast, node)
}


## seq

#' @rdname doc_args
#' @export
args_seq_get <- function(ast, node) {
    .Call(C_rastr_args_seq_get, ast, node)
}

#' @rdname doc_args
#' @export
args_get <- function(ast, node, index) {
    .Call(C_rastr_args_get, ast, node, index)
}
#' @rdname doc_args
#' @export
args_rep <- function(ast, node, index, arg) {
    .Call(C_rastr_args_rep, ast, node, index, arg)
}
#' @param arg `arg` node
#' @rdname doc_args
#' @export
args_arg_set <- function(ast, node, index, arg) {
    invisible(.Call(C_rastr_args_set, ast, node, index, arg))
}
#' @rdname doc_args
#' @export
args_ins <- function(ast, node, index, seq) {
    invisible(.Call(C_rastr_args_ins, ast, node, index, seq))
}




################################################################################
# narg
################################################################################
#' Create and query `narg` nodes
#'
#' @param ast AST object
#' @param node `narg` node
#'
#' @description
#' * `narg_new()` instantiates a new `narg` node.
#' * `narg_type()` checks if the node is a `narg` node.
#' * `narg_<child>_get()` returns the `<child>` node of `narg`.
#' * `narg_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `narg_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_narg
#' @rdname doc_narg
#' @export
narg_new <- function(ast, name, op, expr) {
    .Call(C_rastr_narg_new, ast, name, op, expr)
}
#' @rdname doc_narg
#' @export
narg_type <- function(ast, node) {
    .Call(C_rastr_narg_type, ast, node)
}
## name
#' @rdname doc_narg
#' @export
narg_name_get <- function(ast, node) {
    .Call(C_rastr_narg_name_get, ast, node)
}
#' @rdname doc_narg
#' @export
narg_name_rep <- function(ast, node, name) {
    .Call(C_rastr_narg_name_rep, ast, node, name)
}
#' @param name `name` node
#' @rdname doc_narg
#' @export
narg_name_set <- function(ast, node, name) {
    invisible(.Call(C_rastr_narg_name_set, ast, node, name))
}


## op
#' @rdname doc_narg
#' @export
narg_op_get <- function(ast, node) {
    .Call(C_rastr_narg_op_get, ast, node)
}
#' @rdname doc_narg
#' @export
narg_op_rep <- function(ast, node, op) {
    .Call(C_rastr_narg_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_narg
#' @export
narg_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_narg_op_set, ast, node, op))
}


## expr
#' @rdname doc_narg
#' @export
narg_expr_get <- function(ast, node) {
    .Call(C_rastr_narg_expr_get, ast, node)
}
#' @rdname doc_narg
#' @export
narg_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_narg_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_narg
#' @export
narg_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_narg_expr_set, ast, node, expr))
}




################################################################################
# parg
################################################################################
#' Create and query `parg` nodes
#'
#' @param ast AST object
#' @param node `parg` node
#'
#' @description
#' * `parg_new()` instantiates a new `parg` node.
#' * `parg_type()` checks if the node is a `parg` node.
#' * `parg_<child>_get()` returns the `<child>` node of `parg`.
#' * `parg_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `parg_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_parg
#' @rdname doc_parg
#' @export
parg_new <- function(ast, expr) {
    .Call(C_rastr_parg_new, ast, expr)
}
#' @rdname doc_parg
#' @export
parg_type <- function(ast, node) {
    .Call(C_rastr_parg_type, ast, node)
}
## expr
#' @rdname doc_parg
#' @export
parg_expr_get <- function(ast, node) {
    .Call(C_rastr_parg_expr_get, ast, node)
}
#' @rdname doc_parg
#' @export
parg_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_parg_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_parg
#' @export
parg_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_parg_expr_set, ast, node, expr))
}




################################################################################
# cond
################################################################################
#' Create and query `cond` nodes
#'
#' @param ast AST object
#' @param node `cond` node
#'
#' @description
#' * `cond_new()` instantiates a new `cond` node.
#' * `cond_type()` checks if the node is a `cond` node.
#' * `cond_<child>_get()` returns the `<child>` node of `cond`.
#' * `cond_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `cond_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_cond
#' @rdname doc_cond
#' @export
cond_new <- function(ast, lbkt, expr, rbkt) {
    .Call(C_rastr_cond_new, ast, lbkt, expr, rbkt)
}
#' @rdname doc_cond
#' @export
cond_type <- function(ast, node) {
    .Call(C_rastr_cond_type, ast, node)
}
## lbkt
#' @rdname doc_cond
#' @export
cond_lbkt_get <- function(ast, node) {
    .Call(C_rastr_cond_lbkt_get, ast, node)
}
#' @rdname doc_cond
#' @export
cond_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_cond_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_cond
#' @export
cond_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_cond_lbkt_set, ast, node, lbkt))
}


## expr
#' @rdname doc_cond
#' @export
cond_expr_get <- function(ast, node) {
    .Call(C_rastr_cond_expr_get, ast, node)
}
#' @rdname doc_cond
#' @export
cond_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_cond_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_cond
#' @export
cond_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_cond_expr_set, ast, node, expr))
}


## rbkt
#' @rdname doc_cond
#' @export
cond_rbkt_get <- function(ast, node) {
    .Call(C_rastr_cond_rbkt_get, ast, node)
}
#' @rdname doc_cond
#' @export
cond_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_cond_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_cond
#' @export
cond_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_cond_rbkt_set, ast, node, rbkt))
}




################################################################################
# iter
################################################################################
#' Create and query `iter` nodes
#'
#' @param ast AST object
#' @param node `iter` node
#'
#' @description
#' * `iter_new()` instantiates a new `iter` node.
#' * `iter_type()` checks if the node is a `iter` node.
#' * `iter_<child>_get()` returns the `<child>` node of `iter`.
#' * `iter_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `iter_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_iter
#' @rdname doc_iter
#' @export
iter_new <- function(ast, lbkt, var, op, expr, rbkt) {
    .Call(C_rastr_iter_new, ast, lbkt, var, op, expr, rbkt)
}
#' @rdname doc_iter
#' @export
iter_type <- function(ast, node) {
    .Call(C_rastr_iter_type, ast, node)
}
## lbkt
#' @rdname doc_iter
#' @export
iter_lbkt_get <- function(ast, node) {
    .Call(C_rastr_iter_lbkt_get, ast, node)
}
#' @rdname doc_iter
#' @export
iter_lbkt_rep <- function(ast, node, lbkt) {
    .Call(C_rastr_iter_lbkt_rep, ast, node, lbkt)
}
#' @param lbkt `lbkt` node
#' @rdname doc_iter
#' @export
iter_lbkt_set <- function(ast, node, lbkt) {
    invisible(.Call(C_rastr_iter_lbkt_set, ast, node, lbkt))
}


## var
#' @rdname doc_iter
#' @export
iter_var_get <- function(ast, node) {
    .Call(C_rastr_iter_var_get, ast, node)
}
#' @rdname doc_iter
#' @export
iter_var_rep <- function(ast, node, var) {
    .Call(C_rastr_iter_var_rep, ast, node, var)
}
#' @param var `var` node
#' @rdname doc_iter
#' @export
iter_var_set <- function(ast, node, var) {
    invisible(.Call(C_rastr_iter_var_set, ast, node, var))
}


## op
#' @rdname doc_iter
#' @export
iter_op_get <- function(ast, node) {
    .Call(C_rastr_iter_op_get, ast, node)
}
#' @rdname doc_iter
#' @export
iter_op_rep <- function(ast, node, op) {
    .Call(C_rastr_iter_op_rep, ast, node, op)
}
#' @param op `op` node
#' @rdname doc_iter
#' @export
iter_op_set <- function(ast, node, op) {
    invisible(.Call(C_rastr_iter_op_set, ast, node, op))
}


## expr
#' @rdname doc_iter
#' @export
iter_expr_get <- function(ast, node) {
    .Call(C_rastr_iter_expr_get, ast, node)
}
#' @rdname doc_iter
#' @export
iter_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_iter_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_iter
#' @export
iter_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_iter_expr_set, ast, node, expr))
}


## rbkt
#' @rdname doc_iter
#' @export
iter_rbkt_get <- function(ast, node) {
    .Call(C_rastr_iter_rbkt_get, ast, node)
}
#' @rdname doc_iter
#' @export
iter_rbkt_rep <- function(ast, node, rbkt) {
    .Call(C_rastr_iter_rbkt_rep, ast, node, rbkt)
}
#' @param rbkt `rbkt` node
#' @rdname doc_iter
#' @export
iter_rbkt_set <- function(ast, node, rbkt) {
    invisible(.Call(C_rastr_iter_rbkt_set, ast, node, rbkt))
}




################################################################################
# pgm
################################################################################
#' Create and query `pgm` nodes
#'
#' @param ast AST object
#' @param node `pgm` node
#'
#' @description
#' * `pgm_new()` instantiates a new `pgm` node.
#' * `pgm_type()` checks if the node is a `pgm` node.
#' * `pgm_<child>_get()` returns the `<child>` node of `pgm`.
#' * `pgm_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `pgm_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_pgm
#' @rdname doc_pgm
#' @export
pgm_new <- function(ast, beg, exprs, end) {
    .Call(C_rastr_pgm_new, ast, beg, exprs, end)
}
#' @rdname doc_pgm
#' @export
pgm_type <- function(ast, node) {
    .Call(C_rastr_pgm_type, ast, node)
}
## beg
#' @rdname doc_pgm
#' @export
pgm_beg_get <- function(ast, node) {
    .Call(C_rastr_pgm_beg_get, ast, node)
}
#' @rdname doc_pgm
#' @export
pgm_beg_rep <- function(ast, node, beg) {
    .Call(C_rastr_pgm_beg_rep, ast, node, beg)
}
#' @param beg `beg` node
#' @rdname doc_pgm
#' @export
pgm_beg_set <- function(ast, node, beg) {
    invisible(.Call(C_rastr_pgm_beg_set, ast, node, beg))
}


## exprs
#' @rdname doc_pgm
#' @export
pgm_exprs_get <- function(ast, node) {
    .Call(C_rastr_pgm_exprs_get, ast, node)
}
#' @rdname doc_pgm
#' @export
pgm_exprs_rep <- function(ast, node, exprs) {
    .Call(C_rastr_pgm_exprs_rep, ast, node, exprs)
}
#' @param exprs `exprs` node
#' @rdname doc_pgm
#' @export
pgm_exprs_set <- function(ast, node, exprs) {
    invisible(.Call(C_rastr_pgm_exprs_set, ast, node, exprs))
}


## end
#' @rdname doc_pgm
#' @export
pgm_end_get <- function(ast, node) {
    .Call(C_rastr_pgm_end_get, ast, node)
}
#' @rdname doc_pgm
#' @export
pgm_end_rep <- function(ast, node, end) {
    .Call(C_rastr_pgm_end_rep, ast, node, end)
}
#' @param end `end` node
#' @rdname doc_pgm
#' @export
pgm_end_set <- function(ast, node, end) {
    invisible(.Call(C_rastr_pgm_end_set, ast, node, end))
}




################################################################################
# dlmtd
################################################################################
#' Create and query `dlmtd` nodes
#'
#' @param ast AST object
#' @param node `dlmtd` node
#'
#' @description
#' * `dlmtd_new()` instantiates a new `dlmtd` node.
#' * `dlmtd_type()` checks if the node is a `dlmtd` node.
#' * `dlmtd_<child>_get()` returns the `<child>` node of `dlmtd`.
#' * `dlmtd_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `dlmtd_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_dlmtd
#' @rdname doc_dlmtd
#' @export
dlmtd_new <- function(ast, expr, dlmtr) {
    .Call(C_rastr_dlmtd_new, ast, expr, dlmtr)
}
#' @rdname doc_dlmtd
#' @export
dlmtd_type <- function(ast, node) {
    .Call(C_rastr_dlmtd_type, ast, node)
}
## expr
#' @rdname doc_dlmtd
#' @export
dlmtd_expr_get <- function(ast, node) {
    .Call(C_rastr_dlmtd_expr_get, ast, node)
}
#' @rdname doc_dlmtd
#' @export
dlmtd_expr_rep <- function(ast, node, expr) {
    .Call(C_rastr_dlmtd_expr_rep, ast, node, expr)
}
#' @param expr `expr` node
#' @rdname doc_dlmtd
#' @export
dlmtd_expr_set <- function(ast, node, expr) {
    invisible(.Call(C_rastr_dlmtd_expr_set, ast, node, expr))
}


## dlmtr
#' @rdname doc_dlmtd
#' @export
dlmtd_dlmtr_get <- function(ast, node) {
    .Call(C_rastr_dlmtd_dlmtr_get, ast, node)
}
#' @rdname doc_dlmtd
#' @export
dlmtd_dlmtr_rep <- function(ast, node, dlmtr) {
    .Call(C_rastr_dlmtd_dlmtr_rep, ast, node, dlmtr)
}
#' @param dlmtr `dlmtr` node
#' @rdname doc_dlmtd
#' @export
dlmtd_dlmtr_set <- function(ast, node, dlmtr) {
    invisible(.Call(C_rastr_dlmtd_dlmtr_set, ast, node, dlmtr))
}




################################################################################
# msng
################################################################################
#' Create and query `msng` nodes
#'
#' @param ast AST object
#' @param node `msng` node
#'
#' @description
#' * `msng_new()` instantiates a new `msng` node.
#' * `msng_type()` checks if the node is a `msng` node.
#' * `msng_<child>_get()` returns the `<child>` node of `msng`.
#' * `msng_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `msng_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_msng
#' @rdname doc_msng
#' @export
msng_new <- function(ast, gap, loc) {
    .Call(C_rastr_msng_new, ast, gap, loc)
}
#' @rdname doc_msng
#' @export
msng_type <- function(ast, node) {
    .Call(C_rastr_msng_type, ast, node)
}
## gap
#' @rdname doc_msng
#' @export
msng_gap_get <- function(ast, node) {
    .Call(C_rastr_msng_gap_get, ast, node)
}
#' @rdname doc_msng
#' @export
msng_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_msng_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_msng
#' @export
msng_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_msng_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_msng
#' @export
msng_loc_get <- function(ast, node) {
    .Call(C_rastr_msng_loc_get, ast, node)
}




################################################################################
# beg
################################################################################
#' Create and query `beg` nodes
#'
#' @param ast AST object
#' @param node `beg` node
#'
#' @description
#' * `beg_new()` instantiates a new `beg` node.
#' * `beg_type()` checks if the node is a `beg` node.
#' * `beg_<child>_get()` returns the `<child>` node of `beg`.
#' * `beg_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `beg_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_beg
#' @rdname doc_beg
#' @export
beg_type <- function(ast, node) {
    .Call(C_rastr_beg_type, ast, node)
}
## bom
#' @rdname doc_beg
#' @export
beg_bom_get <- function(ast, node) {
    .Call(C_rastr_beg_bom_get, ast, node)
}


## loc
#' @rdname doc_beg
#' @export
beg_loc_get <- function(ast, node) {
    .Call(C_rastr_beg_loc_get, ast, node)
}




################################################################################
# end
################################################################################
#' Create and query `end` nodes
#'
#' @param ast AST object
#' @param node `end` node
#'
#' @description
#' * `end_new()` instantiates a new `end` node.
#' * `end_type()` checks if the node is a `end` node.
#' * `end_<child>_get()` returns the `<child>` node of `end`.
#' * `end_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `end_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_end
#' @rdname doc_end
#' @export
end_new <- function(ast, gap, loc) {
    .Call(C_rastr_end_new, ast, gap, loc)
}
#' @rdname doc_end
#' @export
end_type <- function(ast, node) {
    .Call(C_rastr_end_type, ast, node)
}
## gap
#' @rdname doc_end
#' @export
end_gap_get <- function(ast, node) {
    .Call(C_rastr_end_gap_get, ast, node)
}
#' @rdname doc_end
#' @export
end_gap_rep <- function(ast, node, gap) {
    .Call(C_rastr_end_gap_rep, ast, node, gap)
}
#' @param gap `gap` node
#' @rdname doc_end
#' @export
end_gap_set <- function(ast, node, gap) {
    invisible(.Call(C_rastr_end_gap_set, ast, node, gap))
}


## loc
#' @rdname doc_end
#' @export
end_loc_get <- function(ast, node) {
    .Call(C_rastr_end_loc_get, ast, node)
}




################################################################################
# gap
################################################################################
#' Create and query `gap` nodes
#'
#' @param ast AST object
#' @param node `gap` node
#'
#' @description
#' * `gap_new()` instantiates a new `gap` node.
#' * `gap_type()` checks if the node is a `gap` node.
#' * `gap_<child>_get()` returns the `<child>` node of `gap`.
#' * `gap_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `gap_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_gap
#' @rdname doc_gap
#' @export
gap_type <- function(ast, node) {
    .Call(C_rastr_gap_type, ast, node)
}
## val
#' @rdname doc_gap
#' @export
gap_val_get <- function(ast, node) {
    .Call(C_rastr_gap_val_get, ast, node)
}


## loc
#' @rdname doc_gap
#' @export
gap_loc_get <- function(ast, node) {
    .Call(C_rastr_gap_loc_get, ast, node)
}




################################################################################
# loc
################################################################################
#' Create and query `loc` nodes
#'
#' @param ast AST object
#' @param node `loc` node
#'
#' @description
#' * `loc_new()` instantiates a new `loc` node.
#' * `loc_type()` checks if the node is a `loc` node.
#' * `loc_<child>_get()` returns the `<child>` node of `loc`.
#' * `loc_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `loc_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_loc
#' @rdname doc_loc
#' @export
loc_type <- function(ast, node) {
    .Call(C_rastr_loc_type, ast, node)
}
## lrow
#' @rdname doc_loc
#' @export
loc_lrow_get <- function(ast, node) {
    .Call(C_rastr_loc_lrow_get, ast, node)
}


## lcol
#' @rdname doc_loc
#' @export
loc_lcol_get <- function(ast, node) {
    .Call(C_rastr_loc_lcol_get, ast, node)
}


## lchr
#' @rdname doc_loc
#' @export
loc_lchr_get <- function(ast, node) {
    .Call(C_rastr_loc_lchr_get, ast, node)
}


## lbyte
#' @rdname doc_loc
#' @export
loc_lbyte_get <- function(ast, node) {
    .Call(C_rastr_loc_lbyte_get, ast, node)
}


## rrow
#' @rdname doc_loc
#' @export
loc_rrow_get <- function(ast, node) {
    .Call(C_rastr_loc_rrow_get, ast, node)
}


## rcol
#' @rdname doc_loc
#' @export
loc_rcol_get <- function(ast, node) {
    .Call(C_rastr_loc_rcol_get, ast, node)
}


## rchr
#' @rdname doc_loc
#' @export
loc_rchr_get <- function(ast, node) {
    .Call(C_rastr_loc_rchr_get, ast, node)
}


## rbyte
#' @rdname doc_loc
#' @export
loc_rbyte_get <- function(ast, node) {
    .Call(C_rastr_loc_rbyte_get, ast, node)
}




################################################################################
# err
################################################################################
#' Create and query `err` nodes
#'
#' @param ast AST object
#' @param node `err` node
#'
#' @description
#' * `err_new()` instantiates a new `err` node.
#' * `err_type()` checks if the node is a `err` node.
#' * `err_<child>_get()` returns the `<child>` node of `err`.
#' * `err_<child>_set()` sets the new `<child>` and deletes the old `<child>`.
#' * `err_<child>_rep()` sets the new `<child>` and returns the old `<child>`.
#'
#' @name doc_err
#' @rdname doc_err
#' @export
err_type <- function(ast, node) {
    .Call(C_rastr_err_type, ast, node)
}
## msg
#' @rdname doc_err
#' @export
err_msg_get <- function(ast, node) {
    .Call(C_rastr_err_msg_get, ast, node)
}


## loc
#' @rdname doc_err
#' @export
err_loc_get <- function(ast, node) {
    .Call(C_rastr_err_loc_get, ast, node)
}




