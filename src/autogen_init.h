/*******************************************************************************
 * op
 *******************************************************************************/
DECLARE_BINDING(rastr_op_type, 2),
    // gap
    DECLARE_BINDING(rastr_op_gap_get, 2), DECLARE_BINDING(rastr_op_gap_rep, 3),

    DECLARE_BINDING(rastr_op_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_op_loc_get, 2),

    /*******************************************************************************
     * dlmtr
     *******************************************************************************/
    DECLARE_BINDING(rastr_dlmtr_type, 2),
    // gap
    DECLARE_BINDING(rastr_dlmtr_gap_get, 2),
    DECLARE_BINDING(rastr_dlmtr_gap_rep, 3),

    DECLARE_BINDING(rastr_dlmtr_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_dlmtr_loc_get, 2),

    /*******************************************************************************
     * bkt
     *******************************************************************************/
    DECLARE_BINDING(rastr_bkt_type, 2),
    // gap
    DECLARE_BINDING(rastr_bkt_gap_get, 2),
    DECLARE_BINDING(rastr_bkt_gap_rep, 3),

    DECLARE_BINDING(rastr_bkt_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_bkt_loc_get, 2),

    /*******************************************************************************
     * null
     *******************************************************************************/
    DECLARE_BINDING(rastr_null_new, 3),

    DECLARE_BINDING(rastr_null_type, 2),
    // gap
    DECLARE_BINDING(rastr_null_gap_get, 2),
    DECLARE_BINDING(rastr_null_gap_rep, 3),

    DECLARE_BINDING(rastr_null_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_null_loc_get, 2),

    /*******************************************************************************
     * lgl
     *******************************************************************************/
    DECLARE_BINDING(rastr_lgl_type, 2),
    // val
    DECLARE_BINDING(rastr_lgl_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_lgl_gap_get, 2),
    DECLARE_BINDING(rastr_lgl_gap_rep, 3),

    DECLARE_BINDING(rastr_lgl_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_lgl_loc_get, 2),

    /*******************************************************************************
     * int
     *******************************************************************************/
    DECLARE_BINDING(rastr_int_type, 2),
    // syn
    DECLARE_BINDING(rastr_int_syn_get, 2),

    // val
    DECLARE_BINDING(rastr_int_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_int_gap_get, 2),
    DECLARE_BINDING(rastr_int_gap_rep, 3),

    DECLARE_BINDING(rastr_int_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_int_loc_get, 2),

    /*******************************************************************************
     * dbl
     *******************************************************************************/
    DECLARE_BINDING(rastr_dbl_type, 2),
    // syn
    DECLARE_BINDING(rastr_dbl_syn_get, 2),

    // val
    DECLARE_BINDING(rastr_dbl_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_dbl_gap_get, 2),
    DECLARE_BINDING(rastr_dbl_gap_rep, 3),

    DECLARE_BINDING(rastr_dbl_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_dbl_loc_get, 2),

    /*******************************************************************************
     * cpx
     *******************************************************************************/
    DECLARE_BINDING(rastr_cpx_type, 2),
    // syn
    DECLARE_BINDING(rastr_cpx_syn_get, 2),

    // val
    DECLARE_BINDING(rastr_cpx_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_cpx_gap_get, 2),
    DECLARE_BINDING(rastr_cpx_gap_rep, 3),

    DECLARE_BINDING(rastr_cpx_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_cpx_loc_get, 2),

    /*******************************************************************************
     * chr
     *******************************************************************************/
    DECLARE_BINDING(rastr_chr_type, 2),
    // syn
    DECLARE_BINDING(rastr_chr_syn_get, 2),

    // val
    DECLARE_BINDING(rastr_chr_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_chr_gap_get, 2),
    DECLARE_BINDING(rastr_chr_gap_rep, 3),

    DECLARE_BINDING(rastr_chr_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_chr_loc_get, 2),

    /*******************************************************************************
     * sym
     *******************************************************************************/
    DECLARE_BINDING(rastr_sym_type, 2),
    // syn
    DECLARE_BINDING(rastr_sym_syn_get, 2),

    // val
    DECLARE_BINDING(rastr_sym_val_get, 2),

    // gap
    DECLARE_BINDING(rastr_sym_gap_get, 2),
    DECLARE_BINDING(rastr_sym_gap_rep, 3),

    DECLARE_BINDING(rastr_sym_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_sym_loc_get, 2),

    /*******************************************************************************
     * blk
     *******************************************************************************/
    DECLARE_BINDING(rastr_blk_new, 4),

    DECLARE_BINDING(rastr_blk_type, 2),
    // lbkt
    DECLARE_BINDING(rastr_blk_lbkt_get, 2),
    DECLARE_BINDING(rastr_blk_lbkt_rep, 3),

    DECLARE_BINDING(rastr_blk_lbkt_set, 3),

    // exprs
    DECLARE_BINDING(rastr_blk_exprs_get, 2),
    DECLARE_BINDING(rastr_blk_exprs_rep, 3),

    DECLARE_BINDING(rastr_blk_exprs_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_blk_rbkt_get, 2),
    DECLARE_BINDING(rastr_blk_rbkt_rep, 3),

    DECLARE_BINDING(rastr_blk_rbkt_set, 3),

    /*******************************************************************************
     * grp
     *******************************************************************************/
    DECLARE_BINDING(rastr_grp_new, 4),

    DECLARE_BINDING(rastr_grp_type, 2),
    // lbkt
    DECLARE_BINDING(rastr_grp_lbkt_get, 2),
    DECLARE_BINDING(rastr_grp_lbkt_rep, 3),

    DECLARE_BINDING(rastr_grp_lbkt_set, 3),

    // expr
    DECLARE_BINDING(rastr_grp_expr_get, 2),
    DECLARE_BINDING(rastr_grp_expr_rep, 3),

    DECLARE_BINDING(rastr_grp_expr_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_grp_rbkt_get, 2),
    DECLARE_BINDING(rastr_grp_rbkt_rep, 3),

    DECLARE_BINDING(rastr_grp_rbkt_set, 3),

    /*******************************************************************************
     * nuop
     *******************************************************************************/
    DECLARE_BINDING(rastr_nuop_new, 2),

    DECLARE_BINDING(rastr_nuop_type, 2),
    // op
    DECLARE_BINDING(rastr_nuop_op_get, 2),
    DECLARE_BINDING(rastr_nuop_op_rep, 3),

    DECLARE_BINDING(rastr_nuop_op_set, 3),

    /*******************************************************************************
     * unop
     *******************************************************************************/
    DECLARE_BINDING(rastr_unop_new, 3),

    DECLARE_BINDING(rastr_unop_type, 2),
    // op
    DECLARE_BINDING(rastr_unop_op_get, 2),
    DECLARE_BINDING(rastr_unop_op_rep, 3),

    DECLARE_BINDING(rastr_unop_op_set, 3),

    // expr
    DECLARE_BINDING(rastr_unop_expr_get, 2),
    DECLARE_BINDING(rastr_unop_expr_rep, 3),

    DECLARE_BINDING(rastr_unop_expr_set, 3),

    /*******************************************************************************
     * binop
     *******************************************************************************/
    DECLARE_BINDING(rastr_binop_new, 4),

    DECLARE_BINDING(rastr_binop_type, 2),
    // lexpr
    DECLARE_BINDING(rastr_binop_lexpr_get, 2),
    DECLARE_BINDING(rastr_binop_lexpr_rep, 3),

    DECLARE_BINDING(rastr_binop_lexpr_set, 3),

    // op
    DECLARE_BINDING(rastr_binop_op_get, 2),
    DECLARE_BINDING(rastr_binop_op_rep, 3),

    DECLARE_BINDING(rastr_binop_op_set, 3),

    // rexpr
    DECLARE_BINDING(rastr_binop_rexpr_get, 2),
    DECLARE_BINDING(rastr_binop_rexpr_rep, 3),

    DECLARE_BINDING(rastr_binop_rexpr_set, 3),

    /*******************************************************************************
     * rlp
     *******************************************************************************/
    DECLARE_BINDING(rastr_rlp_new, 3),

    DECLARE_BINDING(rastr_rlp_type, 2),
    // op
    DECLARE_BINDING(rastr_rlp_op_get, 2), DECLARE_BINDING(rastr_rlp_op_rep, 3),

    DECLARE_BINDING(rastr_rlp_op_set, 3),

    // body
    DECLARE_BINDING(rastr_rlp_body_get, 2),
    DECLARE_BINDING(rastr_rlp_body_rep, 3),

    DECLARE_BINDING(rastr_rlp_body_set, 3),

    /*******************************************************************************
     * wlp
     *******************************************************************************/
    DECLARE_BINDING(rastr_wlp_new, 4),

    DECLARE_BINDING(rastr_wlp_type, 2),
    // op
    DECLARE_BINDING(rastr_wlp_op_get, 2), DECLARE_BINDING(rastr_wlp_op_rep, 3),

    DECLARE_BINDING(rastr_wlp_op_set, 3),

    // cond
    DECLARE_BINDING(rastr_wlp_cond_get, 2),
    DECLARE_BINDING(rastr_wlp_cond_rep, 3),

    DECLARE_BINDING(rastr_wlp_cond_set, 3),

    // body
    DECLARE_BINDING(rastr_wlp_body_get, 2),
    DECLARE_BINDING(rastr_wlp_body_rep, 3),

    DECLARE_BINDING(rastr_wlp_body_set, 3),

    /*******************************************************************************
     * flp
     *******************************************************************************/
    DECLARE_BINDING(rastr_flp_new, 4),

    DECLARE_BINDING(rastr_flp_type, 2),
    // op
    DECLARE_BINDING(rastr_flp_op_get, 2), DECLARE_BINDING(rastr_flp_op_rep, 3),

    DECLARE_BINDING(rastr_flp_op_set, 3),

    // iter
    DECLARE_BINDING(rastr_flp_iter_get, 2),
    DECLARE_BINDING(rastr_flp_iter_rep, 3),

    DECLARE_BINDING(rastr_flp_iter_set, 3),

    // body
    DECLARE_BINDING(rastr_flp_body_get, 2),
    DECLARE_BINDING(rastr_flp_body_rep, 3),

    DECLARE_BINDING(rastr_flp_body_set, 3),

    /*******************************************************************************
     * icond
     *******************************************************************************/
    DECLARE_BINDING(rastr_icond_new, 4),

    DECLARE_BINDING(rastr_icond_type, 2),
    // iop
    DECLARE_BINDING(rastr_icond_iop_get, 2),
    DECLARE_BINDING(rastr_icond_iop_rep, 3),

    DECLARE_BINDING(rastr_icond_iop_set, 3),

    // cond
    DECLARE_BINDING(rastr_icond_cond_get, 2),
    DECLARE_BINDING(rastr_icond_cond_rep, 3),

    DECLARE_BINDING(rastr_icond_cond_set, 3),

    // ibody
    DECLARE_BINDING(rastr_icond_ibody_get, 2),
    DECLARE_BINDING(rastr_icond_ibody_rep, 3),

    DECLARE_BINDING(rastr_icond_ibody_set, 3),

    /*******************************************************************************
     * iecond
     *******************************************************************************/
    DECLARE_BINDING(rastr_iecond_new, 6),

    DECLARE_BINDING(rastr_iecond_type, 2),
    // iop
    DECLARE_BINDING(rastr_iecond_iop_get, 2),
    DECLARE_BINDING(rastr_iecond_iop_rep, 3),

    DECLARE_BINDING(rastr_iecond_iop_set, 3),

    // cond
    DECLARE_BINDING(rastr_iecond_cond_get, 2),
    DECLARE_BINDING(rastr_iecond_cond_rep, 3),

    DECLARE_BINDING(rastr_iecond_cond_set, 3),

    // ibody
    DECLARE_BINDING(rastr_iecond_ibody_get, 2),
    DECLARE_BINDING(rastr_iecond_ibody_rep, 3),

    DECLARE_BINDING(rastr_iecond_ibody_set, 3),

    // eop
    DECLARE_BINDING(rastr_iecond_eop_get, 2),
    DECLARE_BINDING(rastr_iecond_eop_rep, 3),

    DECLARE_BINDING(rastr_iecond_eop_set, 3),

    // ebody
    DECLARE_BINDING(rastr_iecond_ebody_get, 2),
    DECLARE_BINDING(rastr_iecond_ebody_rep, 3),

    DECLARE_BINDING(rastr_iecond_ebody_set, 3),

    /*******************************************************************************
     * fndefn
     *******************************************************************************/
    DECLARE_BINDING(rastr_fndefn_new, 6),

    DECLARE_BINDING(rastr_fndefn_type, 2),
    // op
    DECLARE_BINDING(rastr_fndefn_op_get, 2),
    DECLARE_BINDING(rastr_fndefn_op_rep, 3),

    DECLARE_BINDING(rastr_fndefn_op_set, 3),

    // lbkt
    DECLARE_BINDING(rastr_fndefn_lbkt_get, 2),
    DECLARE_BINDING(rastr_fndefn_lbkt_rep, 3),

    DECLARE_BINDING(rastr_fndefn_lbkt_set, 3),

    // pars
    DECLARE_BINDING(rastr_fndefn_pars_get, 2),
    DECLARE_BINDING(rastr_fndefn_pars_rep, 3),

    DECLARE_BINDING(rastr_fndefn_pars_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_fndefn_rbkt_get, 2),
    DECLARE_BINDING(rastr_fndefn_rbkt_rep, 3),

    DECLARE_BINDING(rastr_fndefn_rbkt_set, 3),

    // body
    DECLARE_BINDING(rastr_fndefn_body_get, 2),
    DECLARE_BINDING(rastr_fndefn_body_rep, 3),

    DECLARE_BINDING(rastr_fndefn_body_set, 3),

    /*******************************************************************************
     * fncall
     *******************************************************************************/
    DECLARE_BINDING(rastr_fncall_new, 5),

    DECLARE_BINDING(rastr_fncall_type, 2),
    // fn
    DECLARE_BINDING(rastr_fncall_fn_get, 2),
    DECLARE_BINDING(rastr_fncall_fn_rep, 3),

    DECLARE_BINDING(rastr_fncall_fn_set, 3),

    // lbkt
    DECLARE_BINDING(rastr_fncall_lbkt_get, 2),
    DECLARE_BINDING(rastr_fncall_lbkt_rep, 3),

    DECLARE_BINDING(rastr_fncall_lbkt_set, 3),

    // args
    DECLARE_BINDING(rastr_fncall_args_get, 2),
    DECLARE_BINDING(rastr_fncall_args_rep, 3),

    DECLARE_BINDING(rastr_fncall_args_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_fncall_rbkt_get, 2),
    DECLARE_BINDING(rastr_fncall_rbkt_rep, 3),

    DECLARE_BINDING(rastr_fncall_rbkt_set, 3),

    /*******************************************************************************
     * sub
     *******************************************************************************/
    DECLARE_BINDING(rastr_sub_new, 5),

    DECLARE_BINDING(rastr_sub_type, 2),
    // obj
    DECLARE_BINDING(rastr_sub_obj_get, 2),
    DECLARE_BINDING(rastr_sub_obj_rep, 3),

    DECLARE_BINDING(rastr_sub_obj_set, 3),

    // lbkt
    DECLARE_BINDING(rastr_sub_lbkt_get, 2),
    DECLARE_BINDING(rastr_sub_lbkt_rep, 3),

    DECLARE_BINDING(rastr_sub_lbkt_set, 3),

    // args
    DECLARE_BINDING(rastr_sub_args_get, 2),
    DECLARE_BINDING(rastr_sub_args_rep, 3),

    DECLARE_BINDING(rastr_sub_args_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_sub_rbkt_get, 2),
    DECLARE_BINDING(rastr_sub_rbkt_rep, 3),

    DECLARE_BINDING(rastr_sub_rbkt_set, 3),

    /*******************************************************************************
     * idx
     *******************************************************************************/
    DECLARE_BINDING(rastr_idx_new, 6),

    DECLARE_BINDING(rastr_idx_type, 2),
    // obj
    DECLARE_BINDING(rastr_idx_obj_get, 2),
    DECLARE_BINDING(rastr_idx_obj_rep, 3),

    DECLARE_BINDING(rastr_idx_obj_set, 3),

    // lbkt
    DECLARE_BINDING(rastr_idx_lbkt_get, 2),
    DECLARE_BINDING(rastr_idx_lbkt_rep, 3),

    DECLARE_BINDING(rastr_idx_lbkt_set, 3),

    // args
    DECLARE_BINDING(rastr_idx_args_get, 2),
    DECLARE_BINDING(rastr_idx_args_rep, 3),

    DECLARE_BINDING(rastr_idx_args_set, 3),

    // rbkt1
    DECLARE_BINDING(rastr_idx_rbkt1_get, 2),
    DECLARE_BINDING(rastr_idx_rbkt1_rep, 3),

    DECLARE_BINDING(rastr_idx_rbkt1_set, 3),

    // rbkt2
    DECLARE_BINDING(rastr_idx_rbkt2_get, 2),
    DECLARE_BINDING(rastr_idx_rbkt2_rep, 3),

    DECLARE_BINDING(rastr_idx_rbkt2_set, 3),

    /*******************************************************************************
     * aexpr
     *******************************************************************************/
    DECLARE_BINDING(rastr_aexpr_new, 3),

    DECLARE_BINDING(rastr_aexpr_type, 2),
    // ann
    DECLARE_BINDING(rastr_aexpr_ann_get, 2),
    DECLARE_BINDING(rastr_aexpr_ann_rep, 3),

    DECLARE_BINDING(rastr_aexpr_ann_set, 3),

    // expr
    DECLARE_BINDING(rastr_aexpr_expr_get, 2),
    DECLARE_BINDING(rastr_aexpr_expr_rep, 3),

    DECLARE_BINDING(rastr_aexpr_expr_set, 3),

    /*******************************************************************************
     * exprs
     *******************************************************************************/
    DECLARE_BINDING(rastr_exprs_new, 2), DECLARE_BINDING(rastr_exprs_type, 2),
    // len
    DECLARE_BINDING(rastr_exprs_len_get, 2),

    // seq
    DECLARE_BINDING(rastr_exprs_get, 3),
    DECLARE_BINDING(rastr_exprs_seq_get, 2),
    DECLARE_BINDING(rastr_exprs_rep, 4), DECLARE_BINDING(rastr_exprs_set, 4),
    DECLARE_BINDING(rastr_exprs_ins, 5),

    /*******************************************************************************
     * pars
     *******************************************************************************/
    DECLARE_BINDING(rastr_pars_new, 2), DECLARE_BINDING(rastr_pars_type, 2),
    // len
    DECLARE_BINDING(rastr_pars_len_get, 2),

    // seq
    DECLARE_BINDING(rastr_pars_get, 3), DECLARE_BINDING(rastr_pars_seq_get, 2),
    DECLARE_BINDING(rastr_pars_rep, 4), DECLARE_BINDING(rastr_pars_set, 4),
    DECLARE_BINDING(rastr_pars_ins, 5),

    /*******************************************************************************
     * dpar
     *******************************************************************************/
    DECLARE_BINDING(rastr_dpar_new, 4),

    DECLARE_BINDING(rastr_dpar_type, 2),
    // name
    DECLARE_BINDING(rastr_dpar_name_get, 2),
    DECLARE_BINDING(rastr_dpar_name_rep, 3),

    DECLARE_BINDING(rastr_dpar_name_set, 3),

    // op
    DECLARE_BINDING(rastr_dpar_op_get, 2),
    DECLARE_BINDING(rastr_dpar_op_rep, 3),

    DECLARE_BINDING(rastr_dpar_op_set, 3),

    // expr
    DECLARE_BINDING(rastr_dpar_expr_get, 2),
    DECLARE_BINDING(rastr_dpar_expr_rep, 3),

    DECLARE_BINDING(rastr_dpar_expr_set, 3),

    /*******************************************************************************
     * ndpar
     *******************************************************************************/
    DECLARE_BINDING(rastr_ndpar_new, 2),

    DECLARE_BINDING(rastr_ndpar_type, 2),
    // name
    DECLARE_BINDING(rastr_ndpar_name_get, 2),
    DECLARE_BINDING(rastr_ndpar_name_rep, 3),

    DECLARE_BINDING(rastr_ndpar_name_set, 3),

    /*******************************************************************************
     * args
     *******************************************************************************/
    DECLARE_BINDING(rastr_args_new, 2), DECLARE_BINDING(rastr_args_type, 2),
    // len
    DECLARE_BINDING(rastr_args_len_get, 2),

    // seq
    DECLARE_BINDING(rastr_args_get, 3), DECLARE_BINDING(rastr_args_seq_get, 2),
    DECLARE_BINDING(rastr_args_rep, 4), DECLARE_BINDING(rastr_args_set, 4),
    DECLARE_BINDING(rastr_args_ins, 5),

    /*******************************************************************************
     * narg
     *******************************************************************************/
    DECLARE_BINDING(rastr_narg_new, 4),

    DECLARE_BINDING(rastr_narg_type, 2),
    // name
    DECLARE_BINDING(rastr_narg_name_get, 2),
    DECLARE_BINDING(rastr_narg_name_rep, 3),

    DECLARE_BINDING(rastr_narg_name_set, 3),

    // op
    DECLARE_BINDING(rastr_narg_op_get, 2),
    DECLARE_BINDING(rastr_narg_op_rep, 3),

    DECLARE_BINDING(rastr_narg_op_set, 3),

    // expr
    DECLARE_BINDING(rastr_narg_expr_get, 2),
    DECLARE_BINDING(rastr_narg_expr_rep, 3),

    DECLARE_BINDING(rastr_narg_expr_set, 3),

    /*******************************************************************************
     * parg
     *******************************************************************************/
    DECLARE_BINDING(rastr_parg_new, 2),

    DECLARE_BINDING(rastr_parg_type, 2),
    // expr
    DECLARE_BINDING(rastr_parg_expr_get, 2),
    DECLARE_BINDING(rastr_parg_expr_rep, 3),

    DECLARE_BINDING(rastr_parg_expr_set, 3),

    /*******************************************************************************
     * cond
     *******************************************************************************/
    DECLARE_BINDING(rastr_cond_new, 4),

    DECLARE_BINDING(rastr_cond_type, 2),
    // lbkt
    DECLARE_BINDING(rastr_cond_lbkt_get, 2),
    DECLARE_BINDING(rastr_cond_lbkt_rep, 3),

    DECLARE_BINDING(rastr_cond_lbkt_set, 3),

    // expr
    DECLARE_BINDING(rastr_cond_expr_get, 2),
    DECLARE_BINDING(rastr_cond_expr_rep, 3),

    DECLARE_BINDING(rastr_cond_expr_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_cond_rbkt_get, 2),
    DECLARE_BINDING(rastr_cond_rbkt_rep, 3),

    DECLARE_BINDING(rastr_cond_rbkt_set, 3),

    /*******************************************************************************
     * iter
     *******************************************************************************/
    DECLARE_BINDING(rastr_iter_new, 6),

    DECLARE_BINDING(rastr_iter_type, 2),
    // lbkt
    DECLARE_BINDING(rastr_iter_lbkt_get, 2),
    DECLARE_BINDING(rastr_iter_lbkt_rep, 3),

    DECLARE_BINDING(rastr_iter_lbkt_set, 3),

    // var
    DECLARE_BINDING(rastr_iter_var_get, 2),
    DECLARE_BINDING(rastr_iter_var_rep, 3),

    DECLARE_BINDING(rastr_iter_var_set, 3),

    // op
    DECLARE_BINDING(rastr_iter_op_get, 2),
    DECLARE_BINDING(rastr_iter_op_rep, 3),

    DECLARE_BINDING(rastr_iter_op_set, 3),

    // expr
    DECLARE_BINDING(rastr_iter_expr_get, 2),
    DECLARE_BINDING(rastr_iter_expr_rep, 3),

    DECLARE_BINDING(rastr_iter_expr_set, 3),

    // rbkt
    DECLARE_BINDING(rastr_iter_rbkt_get, 2),
    DECLARE_BINDING(rastr_iter_rbkt_rep, 3),

    DECLARE_BINDING(rastr_iter_rbkt_set, 3),

    /*******************************************************************************
     * pgm
     *******************************************************************************/
    DECLARE_BINDING(rastr_pgm_new, 4),

    DECLARE_BINDING(rastr_pgm_type, 2),
    // beg
    DECLARE_BINDING(rastr_pgm_beg_get, 2),
    DECLARE_BINDING(rastr_pgm_beg_rep, 3),

    DECLARE_BINDING(rastr_pgm_beg_set, 3),

    // exprs
    DECLARE_BINDING(rastr_pgm_exprs_get, 2),
    DECLARE_BINDING(rastr_pgm_exprs_rep, 3),

    DECLARE_BINDING(rastr_pgm_exprs_set, 3),

    // end
    DECLARE_BINDING(rastr_pgm_end_get, 2),
    DECLARE_BINDING(rastr_pgm_end_rep, 3),

    DECLARE_BINDING(rastr_pgm_end_set, 3),

    /*******************************************************************************
     * dlmtd
     *******************************************************************************/
    DECLARE_BINDING(rastr_dlmtd_new, 3),

    DECLARE_BINDING(rastr_dlmtd_type, 2),
    // expr
    DECLARE_BINDING(rastr_dlmtd_expr_get, 2),
    DECLARE_BINDING(rastr_dlmtd_expr_rep, 3),

    DECLARE_BINDING(rastr_dlmtd_expr_set, 3),

    // dlmtr
    DECLARE_BINDING(rastr_dlmtd_dlmtr_get, 2),
    DECLARE_BINDING(rastr_dlmtd_dlmtr_rep, 3),

    DECLARE_BINDING(rastr_dlmtd_dlmtr_set, 3),

    /*******************************************************************************
     * msng
     *******************************************************************************/
    DECLARE_BINDING(rastr_msng_new, 3),

    DECLARE_BINDING(rastr_msng_type, 2),
    // gap
    DECLARE_BINDING(rastr_msng_gap_get, 2),
    DECLARE_BINDING(rastr_msng_gap_rep, 3),

    DECLARE_BINDING(rastr_msng_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_msng_loc_get, 2),

    /*******************************************************************************
     * beg
     *******************************************************************************/
    DECLARE_BINDING(rastr_beg_type, 2),
    // bom
    DECLARE_BINDING(rastr_beg_bom_get, 2),

    // loc
    DECLARE_BINDING(rastr_beg_loc_get, 2),

    /*******************************************************************************
     * end
     *******************************************************************************/
    DECLARE_BINDING(rastr_end_new, 3),

    DECLARE_BINDING(rastr_end_type, 2),
    // gap
    DECLARE_BINDING(rastr_end_gap_get, 2),
    DECLARE_BINDING(rastr_end_gap_rep, 3),

    DECLARE_BINDING(rastr_end_gap_set, 3),

    // loc
    DECLARE_BINDING(rastr_end_loc_get, 2),

    /*******************************************************************************
     * gap
     *******************************************************************************/
    DECLARE_BINDING(rastr_gap_type, 2),
    // val
    DECLARE_BINDING(rastr_gap_val_get, 2),

    // loc
    DECLARE_BINDING(rastr_gap_loc_get, 2),

    /*******************************************************************************
     * loc
     *******************************************************************************/
    DECLARE_BINDING(rastr_loc_type, 2),
    // lrow
    DECLARE_BINDING(rastr_loc_lrow_get, 2),

    // lcol
    DECLARE_BINDING(rastr_loc_lcol_get, 2),

    // lchr
    DECLARE_BINDING(rastr_loc_lchr_get, 2),

    // lbyte
    DECLARE_BINDING(rastr_loc_lbyte_get, 2),

    // rrow
    DECLARE_BINDING(rastr_loc_rrow_get, 2),

    // rcol
    DECLARE_BINDING(rastr_loc_rcol_get, 2),

    // rchr
    DECLARE_BINDING(rastr_loc_rchr_get, 2),

    // rbyte
    DECLARE_BINDING(rastr_loc_rbyte_get, 2),

    /*******************************************************************************
     * err
     *******************************************************************************/
    DECLARE_BINDING(rastr_err_type, 2),
    // msg
    DECLARE_BINDING(rastr_err_msg_get, 2),

    // loc
    DECLARE_BINDING(rastr_err_loc_get, 2),
