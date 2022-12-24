library(tidyverse)
library(glue)
library(readr)

## for new nodes, loc fields should be NA and not provided via constructor
## for new nodes, gap argument could be string or a gap node (default to " ")
## gap value should be modifiable
## functions common for all nodes:

##- node_id
##- node_pid
##- node_type



NODE_DECL <- list(
    list(type = c("RASTR_OP_SP",
                  "RASTR_OP_PLUS",
                  "RASTR_OP_MINUS",
                  "RASTR_OP_MUL",
                  "RASTR_OP_DIV",
                  "RASTR_OP_POW",
                  "RASTR_OP_POW2",
                  "RASTR_OP_LESS",
                  "RASTR_OP_LESS_EQ",
                  "RASTR_OP_GREAT",
                  "RASTR_OP_GREAT_EQ",
                  "RASTR_OP_EQ",
                  "RASTR_OP_NOT_EQ",
                  "RASTR_OP_NOT",
                  "RASTR_OP_AND",
                  "RASTR_OP_VEC_AND",
                  "RASTR_OP_OR",
                  "RASTR_OP_VEC_OR",
                  "RASTR_OP_EQ_ASGN",
                  "RASTR_OP_LT_ASGN",
                  "RASTR_OP_RT_ASGN",
                  "RASTR_OP_LT_SUP_ASGN",
                  "RASTR_OP_RT_SUP_ASGN",
                  "RASTR_OP_COLON_ASGN",
                  "RASTR_OP_PIPE_FWD",
                  "RASTR_OP_PIPE_BIND",
                  "RASTR_OP_PUB_NS",
                  "RASTR_OP_PVT_NS",
                  "RASTR_OP_RANGE",
                  "RASTR_OP_HELP",
                  "RASTR_OP_SLOT",
                  "RASTR_OP_FORMULA",
                  "RASTR_OP_PART",
                  "RASTR_OP_FN",
                  "RASTR_OP_FN2",
                  "RASTR_OP_WHILE",
                  "RASTR_OP_REPEAT",
                  "RASTR_OP_FOR",
                  "RASTR_OP_IN",
                  "RASTR_OP_IF",
                  "RASTR_OP_ELSE",
                  "RASTR_OP_NEXT",
                  "RASTR_OP_BREAK"),
         node = "op",
         children = list(list(name = "gap", type = "node", mut = FALSE),
                         list(name = "loc", type = "node", mut = FALSE))),


    list(type = c("RASTR_DLMTR_SCOL",
                  "RASTR_DLMTR_COM"),
         node = "dlmtr",
         children = list(list(name = "gap", type = "node", mut = FALSE),
                         list(name = "loc", type = "node", mut = FALSE))),

    list(type = c("RASTR_BKT_LT_RND",
                  "RASTR_BKT_RT_RND",
                  "RASTR_BKT_LT_CURL",
                  "RASTR_BKT_RT_CURL",
                  "RASTR_BKT_LT_SQR",
                  "RASTR_BKT_RT_SQR",
                  "RASTR_BKT_LT_DBL_SQR"),
         node = "bkt",
         children = list(list(name = "gap", type = "node", mut = FALSE),
                         list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_NULL", node = "null", children = list(list(name = "gap", type = "node", mut = FALSE),
                                                             list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_LGL", node = "lgl", children = list(list(name = "val", type = "lgl", mut = FALSE),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_INT", node = "int", children = list(list(name = "syn", type = "chr", mut = FALSE),
                                                           list(name = "val", type = "int", mut = FALSE),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_DBL", node = "dbl", children = list(list(name = "syn", type = "chr"),
                                                           list(name = "val", type = "dbl"),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_CPX", node = "cpx", children = list(list(name = "syn", type = "chr"),
                                                           list(name = "val", type = "cpx"),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_CHR", node = "chr", children = list(list(name = "syn", type = "chr"),
                                                           list(name = "val", type = "chr"),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_SYM", node = "sym", children = list(list(name = "syn", type = "chr"),
                                                           list(name = "val", type = "chr"),
                                                           list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_BLK", node = "blk", children = list(list(name = "lbkt", type = "node", mut = TRUE),
                                                           list(name = "exprs", type = "node", mut = TRUE),
                                                           list(name = "rbkt", type = "node", mut = TRUE))),

    list(type = "RASTR_GRP", node = "grp", children = list(list(name = "lbkt", type = "node", mut = TRUE),
                                                           list(name = "expr", type = "node", mut = TRUE),
                                                           list(name = "rbkt", type = "node", mut = TRUE))),

    list(type = "RASTR_NUOP", node = "nuop", children = list(list(name = "op", type = "node", mut = TRUE))),

    list(type = "RASTR_UNOP", node = "unop", children = list(list(name = "op", type = "node", mut = TRUE),
                                                             list(name = "expr", type = "node", mut = TRUE))),

    list(type = "RASTR_BINOP", node = "binop", children = list(list(name = "lexpr", type = "node", mut = TRUE),
                                                               list(name = "op", type = "node", mut = TRUE),
                                                               list(name = "rexpr", type = "node", mut = TRUE))),

    list(type = "RASTR_RLP", node = "rlp", children = list(list(name = "op", type = "node", mut = TRUE),
                                                           list(name = "body", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_WLP", node = "wlp", children = list(list(name = "op", type = "node", mut = TRUE),
                                                           list(name = "cond", type = "node", mut = TRUE),
                                                           list(name = "body", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_FLP", node = "flp", children = list(list(name = "op", type = "node", mut = TRUE),
                                                           list(name = "iter", type = "node", mut = TRUE),
                                                           list(name = "body", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_ICOND", node = "icond", children = list(list(name = "iop", type = "node", mut = TRUE),
                                                               list(name = "cond", type = "node", mut = TRUE),
                                                               list(name = "ibody", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_IECOND", node = "iecond", children = list(list(name = "iop", type = "node", mut = TRUE),
                                                                 list(name = "cond", type = "node", mut = TRUE),
                                                                 list(name = "ibody", type = "node", mut = TRUE),
                                                                 list(name = "eop", type = "node", mut = TRUE),
                                                                 list(name = "ebody", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_FNDEFN", node = "fndefn", children = list(list(name = "op", type = "node", mut = TRUE),
                                                                 list(name = "lbkt", type = "node", mut = TRUE),
                                                                 list(name = "pars", type = "node", mut = TRUE),
                                                                 list(name = "rbkt", type = "node", mut = TRUE),
                                                                 list(name = "body", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_FNCALL", node = "fncall", children = list(list(name = "fn", type = "node", mut = TRUE),
                                                                 list(name = "lbkt", type = "node", mut = TRUE),
                                                                 list(name = "args", type = "node", mut = TRUE),
                                                                 list(name = "rbkt", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_SUB", node = "sub", children = list(list(name = "obj", type = "node", mut = TRUE),
                                                           list(name = "lbkt", type = "node", mut = TRUE),
                                                           list(name = "args", type = "node", mut = TRUE),
                                                           list(name = "rbkt", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_IDX", node = "idx", children = list(list(name = "obj", type = "node", mut = TRUE),
                                                           list(name = "lbkt", type = "node", mut = TRUE),
                                                           list(name = "args", type = "node", mut = TRUE),
                                                           list(name = "rbkt1", type = "node", mut = TRUE),
                                                           list(name = "rbkt2", type = "node", mut = TRUE))), #changed

    list(type = "RASTR_AEXPR", node = "aexpr", children = list(list(name = "ann", type = "node", mut = FALSE),
                                                               list(name = "expr", type = "node", mut = FALSE))),

    list(type = "RASTR_EXPRS", node = "exprs", children = list(list(name = "len", type = "int"),
                                                               list(name = "seq", type = "seq"))),

    list(type = "RASTR_PARS", node = "pars", children = list(list(name = "len", type = "int"),
                                                             list(name = "seq", type = "seq"))),

    list(type = "RASTR_DPAR", node = "dpar", children = list(list(name = "name", type = "node", mut = TRUE),
                                                             list(name = "op", type = "node", mut = TRUE),
                                                             list(name = "expr", type = "node", mut = TRUE))),

    list(type = "RASTR_NDPAR", node = "ndpar", children = list(list(name = "name", type = "node", mut = TRUE))),

    list(type = "RASTR_ARGS", node = "args", children = list(list(name = "len", type = "int"),
                                                             list(name = "seq", type = "seq"))),

    list(type = "RASTR_NARG", node = "narg", children = list(list(name = "name", type = "node", mut = TRUE),
                                                             list(name = "op", type = "node", mut = TRUE),
                                                             list(name = "expr", type = "node", mut = TRUE))),

    list(type = "RASTR_PARG", node = "parg", children = list(list(name = "expr", type = "node", mut = TRUE))),

    list(type = "RASTR_COND", node = "cond", children = list(list(name = "lbkt", type = "node", mut = TRUE),
                                                             list(name = "expr", type = "node", mut = TRUE),
                                                             list(name = "rbkt", type = "node", mut = TRUE))),

    list(type = "RASTR_ITER", node = "iter", children = list(list(name = "lbkt", type = "node", mut = TRUE),
                                                             list(name = "var", type = "node", mut = TRUE),
                                                             list(name = "op", type = "node", mut = TRUE),
                                                             list(name = "expr", type = "node", mut = TRUE),
                                                             list(name = "rbkt", type = "node", mut = TRUE))),

    list(type = "RASTR_PGM", node = "pgm", children = list(list(name = "beg", type = "node", mut = TRUE),
                                                           list(name = "exprs", type = "node", mut = TRUE),
                                                           list(name = "end", type = "node", mut = TRUE))),

    list(type = "RASTR_DLMTD", node = "dlmtd", children = list(list(name = "expr", type = "node", mut = TRUE),
                                                               list(name = "dlmtr", type = "node", mut = TRUE))),

    list(type = "RASTR_MSNG", node = "msng", children = list(list(name = "gap", type = "node", mut = FALSE),
                                                             list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_BEG", node = "beg", children = list(list(name = "bom", type = "chr", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_END", node = "end", children = list(list(name = "gap", type = "node", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_GAP", node = "gap", children = list(list(name = "val", type = "chr", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))),

    list(type = "RASTR_LOC", node = "loc", children = list(list(name = "lrow", type = "int", mut = FALSE),
                                                           list(name = "lcol", type = "int", mut = FALSE),
                                                           list(name = "lchr", type = "int", mut = FALSE),
                                                           list(name = "lbyte", type = "int", mut = FALSE),
                                                           list(name = "rrow", type = "int", mut = FALSE),
                                                           list(name = "rcol", type = "int", mut = FALSE),
                                                           list(name = "rchr", type = "int", mut = FALSE),
                                                           list(name = "rbyte", type = "int", mut = FALSE))),

    list(type = "RASTR_ERR", node = "err", children = list(list(name = "msg", type = "chr", mut = FALSE),
                                                           list(name = "loc", type = "node", mut = FALSE))))


gen_api <- function(code,
                    node_header_fun,
                    child_header_fun,
                    node_footer_fun,
                    child_footer_fun,
                    node_fun,
                    child_fun) {

    handler <- function(arg) {
        type <- arg$type
        node <- arg$node
        children <- arg$children

        node_header_fun(code, type, node, children)

        node_fun(code, type, node, children)

        map(children, function(child) {
            child_header_fun(code, type, node, child)
            child_fun(code, type, node, child)
            child_footer_fun(code, type, node, child)
        })

        node_footer_fun(code, type, node, children)

        NULL
    }

    map(NODE_DECL, handler)
}

make_buffer <- function() {
    buffer <- character(0)

    read <- function() {
        buffer
    }

    push <- function(content) {
        buffer <<- append(buffer, content)
    }

    write <- function(file) {
        write_lines(buffer, file)
    }

    list(read = read, push = push, write = write)
}

make_code <- function() {

    cpp_impl <- make_buffer()
    cpp_ifc <- make_buffer()
    cpp_unsafe_ifc <- make_buffer()
    cpp_init <- make_buffer()
    r_impl <- make_buffer()

    list(cpp_impl = cpp_impl,
         cpp_ifc = cpp_ifc,
         cpp_unsafe_ifc = cpp_unsafe_ifc,
         cpp_init = cpp_init,
         r_impl = r_impl)
}

as_c_type <- function(type) {
    child_type <- switch(type,
                         "node" = "rastr_node_t",
                         "seq" = "const rastr_node_t*",
                         "int" = "int",
                         "dbl" = "double",
                         "chr" = "const char*",
                         "lgl" = "int",
                         "cpx" = "Rcomplex")
}

gen_get_node <- function(code, type, node, child) {

    child_type <- as_c_type(child$type)

    retcode <- switch(child$type,
                      "node" = "    return rastr_node_wrap(result);",
                      "seq" = "    return rastr_node_seq_wrap(result, rastr_{NODE}_len(ast, node));",
                      "int" = "    return int_vec1(result);",
                      "dbl" = "    return dbl_vec1(result);",
                      "chr" = "    return chr_vec1(result);",
                      "lgl" = "    return lgl_vec1(result);",
                      "cpx" = "    return cpx_vec1(result);")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_{CHILD}_get, 2),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child$name)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// get",
                    "{CHILD_TYPE} rastr_{NODE}_{CHILD}_get(rastr_ast_t ast, rastr_node_t node);",
                    "SEXP r_rastr_{NODE}_{CHILD}_get(SEXP r_ast, SEXP r_node);",
                    .sep = "\n",
                    NODE = node,
                    CHILD = child$name,
                    CHILD_TYPE = child_type)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// get",
                     "{CHILD_TYPE} rastr_{NODE}_{CHILD}_get(rastr_ast_t ast, rastr_node_t node) {{",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                     "    return ptr->node.{NODE}_node.{CHILD};",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_{CHILD}_get(SEXP r_ast, SEXP r_node) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "    {CHILD_TYPE} result = rastr_{NODE}_{CHILD}_get(ast, node);",
                     retcode,
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node,
                     CHILD = child$name,
                     CHILD_TYPE = child_type,
                     WRAPPER = wrapper)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_{CHILD}_get <- function(ast, node) {{",
                   "    .Call(C_rastr_{NODE}_{CHILD}_get, ast, node)",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   CHILD = child$name)

    code$r_impl$push(r_impl)

}

gen_get_seq <- function(code, type, node, child) {

    stopifnot(child$type == "seq")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_get, 3),",
                     "DECLARE_BINDING(rastr_{NODE}_seq_get, 2),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child$name)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// get",
                    "const rastr_node_t* rastr_{NODE}_seq_get(rastr_ast_t ast, rastr_node_t node);",
                    "SEXP r_rastr_{NODE}_seq_get(SEXP r_ast, SEXP r_node);",
                    "rastr_node_t rastr_{NODE}_get(rastr_ast_t ast, rastr_node_t node, int index);",
                    "SEXP r_rastr_{NODE}_get(SEXP r_ast, SEXP r_node, SEXP r_index);",
                    .sep = "\n",
                    NODE = node)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// get",
                     "const rastr_node_t* rastr_{NODE}_seq_get(rastr_ast_t ast, rastr_node_t node) {{",
                     "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "    return ptr->node.{NODE}_node.seq;",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_seq_get(SEXP r_ast, SEXP r_node) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    int len = rastr_{NODE}_len_get(ast, node);",
                     "    const rastr_node_t* seq = rastr_{NODE}_seq_get(ast, node);",
                     "",
                     "    SEXP r_result = PROTECT(Rf_allocVector(VECSXP, len));",
                     "",
                     "    for(int i = 0; i < len; ++i) {{",
                     "        SET_VECTOR_ELT(r_result, i, rastr_node_wrap(seq[i]));",
                     "    }}",
                     "",
                     "    UNPROTECT(1);",
                     "    return r_result;",
                     "}}",
                     "",
                     "rastr_node_t rastr_{NODE}_get(rastr_ast_t ast, rastr_node_t node, int index) {{",
                     "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "    return ptr->node.{NODE}_node.seq[index];",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_get(SEXP r_ast, SEXP r_node, SEXP r_index) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    ensure_numeric_sexp(r_index, 1);",
                     "    int index = (int) num_get(r_index, 0);",
                     "",
                     "    rastr_node_t result = rastr_{NODE}_get(ast, node, index);",
                     "    return rastr_node_wrap(result);",
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_seq_get <- function(ast, node) {{",
                   "    .Call(C_rastr_{NODE}_seq_get, ast, node)",
                   "}}",
                   "",
                   "#' @export",
                   "{NODE}_get <- function(ast, node, index) {{",
                   "    .Call(C_rastr_{NODE}_get, ast, node, index)",
                   "}}",
                   .sep = "\n",
                   NODE = node)

    code$r_impl$push(r_impl)

}


gen_rep_node <- function(code, type, node, child) {

    stopifnot(child$type == "node")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_{CHILD}_rep, 3),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child$name)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// rep",
                    "rastr_node_t rastr_{NODE}_{CHILD}_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t {CHILD});",
                    "SEXP r_rastr_{NODE}_{CHILD}_rep(SEXP r_ast, SEXP r_node, SEXP r_{CHILD});",
                    .sep = "\n",
                    NODE = node,
                    CHILD = child$name)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// rep",
                     "rastr_node_t rastr_{NODE}_{CHILD}_rep(rastr_ast_t ast, rastr_node_t node, rastr_node_t {CHILD}) {{",
                     "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                     "",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "",
                     "    rastr_node_t result = ptr->node.{NODE}_node.{CHILD};",
                     "    rastr_node_pid_unset(ast, result);",
                     "",
                     "    int id = ptr->id;",
                     "    ASSIGN_CHILD({NODE}, {CHILD}, id)",
                     "",
                     "    return result;",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_{CHILD}_rep(SEXP r_ast, SEXP r_node, SEXP r_{CHILD}) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    ensure_node_class(r_{CHILD});",
                     "    rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                     "",
                     "    rastr_node_t result = rastr_{NODE}_{CHILD}_rep(ast, node, {CHILD});",
                     "    return rastr_node_wrap(result);",
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node,
                     CHILD = child$name)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_{CHILD}_rep <- function(ast, node, {CHILD}) {{",
                   "    .Call(C_rastr_{NODE}_{CHILD}_rep, ast, node, {CHILD})",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   CHILD = child$name)

    code$r_impl$push(r_impl)

}

gen_rep_seq <- function(code, type, node, child) {

    stopifnot(child$type == "seq")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_rep, 4),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child$name)

    code$cpp_init$push(cpp_init)

    # converts exprs to expr, args to arg, pars to par
    child_name <- str_sub(node, end = -2)

    cpp_ifc <- glue("// rep",
                    "rastr_node_t rastr_{NODE}_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t {CHILD});",
                    "SEXP r_rastr_{NODE}_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_{CHILD});",
                    .sep = "\n",
                    NODE = node,
                    CHILD = child_name)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// rep",
                     "rastr_node_t rastr_{NODE}_rep(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t {CHILD}) {{",
                     "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                     "",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "    int id = ptr->id;",
                     "",
                     "    rastr_node_t result = ptr->node.{NODE}_node.seq[index];",
                     "    rastr_node_pid_unset(ast, result);",
                     "",
                     "    ASSIGN_SEQ_CHILD({NODE}, index, {CHILD}, id)",
                     "",
                     "    return result;",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_rep(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_{CHILD}) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    ensure_numeric_sexp(r_index, 1);",
                     "    int index = (int) num_get(r_index, 0);",
                     "",
                     "    ensure_node_class(r_{CHILD});",
                     "    rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                     "",
                     "    rastr_node_t result = rastr_{NODE}_rep(ast, node, index, {CHILD});",
                     "    return rastr_node_wrap(result);",
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node,
                     CHILD = child_name)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_rep <- function(ast, node, index, {CHILD}) {{",
                   "    .Call(C_rastr_{NODE}_rep, ast, node, index, {CHILD})",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   CHILD = child_name)

    code$r_impl$push(r_impl)

}

gen_set_node <- function(code, type, node, child) {

    stopifnot(child$type == "node")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_{CHILD}_set, 3),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child$name)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// set",
                    "void rastr_{NODE}_{CHILD}_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t {CHILD});",
                    "SEXP r_rastr_{NODE}_{CHILD}_set(SEXP r_ast, SEXP r_node, SEXP r_{CHILD});",
                    .sep = "\n",
                    NODE = node,
                    CHILD = child$name)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// set",
                     "void rastr_{NODE}_{CHILD}_set(rastr_ast_t ast, rastr_node_t node, rastr_node_t {CHILD}) {{",
                     "    rastr_node_t result = rastr_{NODE}_{CHILD}_rep(ast, node, {CHILD});",
                     "    rastr_node_destroy(ast, result);",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_{CHILD}_set(SEXP r_ast, SEXP r_node, SEXP r_{CHILD}) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    ensure_node_class(r_{CHILD});",
                     "    rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                     "",
                     "    rastr_{NODE}_{CHILD}_set(ast, node, {CHILD});",
                     "    return R_NilValue;",
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node,
                     CHILD = child$name)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_{CHILD}_set <- function(ast, node, {CHILD}) {{",
                   "    invisible(.Call(C_rastr_{NODE}_{CHILD}_set, ast, node, {CHILD}))",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   CHILD = child$name)

    code$r_impl$push(r_impl)

}

gen_set_seq <- function(code, type, node, child) {

    stopifnot(child$type == "seq")

    ## converts exprs to expr, args to arg, pars to par
    child_name <- str_sub(node, end = -2)

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_set, 4),",
                     .sep = "\n",
                     NODE = node,
                     CHILD = child_name)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// set",
                    "void rastr_{NODE}_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t {CHILD});",
                    "SEXP r_rastr_{NODE}_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_{CHILD});",
                    .sep = "\n",
                    NODE = node,
                    CHILD = child_name)

    code$cpp_ifc$push(cpp_ifc)

    cpp_impl <- glue("// set",
                     "void rastr_{NODE}_set(rastr_ast_t ast, rastr_node_t node, int index, rastr_node_t {CHILD}) {{",
                     "    rastr_node_t result = rastr_{NODE}_rep(ast, node, index, {CHILD});",
                     "    rastr_node_destroy(ast, result);",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_set(SEXP r_ast, SEXP r_node, SEXP r_index, SEXP r_{CHILD}) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "",
                     "    ensure_node_class(r_{CHILD});",
                     "    rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                     "",
                     "    ensure_numeric_sexp(r_index, 1);",
                     "    int index = (int) num_get(r_index, 0);",
                     "",
                     "    rastr_{NODE}_set(ast, node, index, {CHILD});",
                     "    return R_NilValue;",
                     "}}",
                     .sep = "\n",
                     TYPE = type,
                     NODE = node,
                     CHILD = child_name)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_{CHILD}_set <- function(ast, node, index, {CHILD}) {{",
                   "    invisible(.Call(C_rastr_{NODE}_set, ast, node, index, {CHILD}))",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   CHILD = child_name)

    code$r_impl$push(r_impl)

}


## generates constructor for node
gen_cons <- function(code, type, node, children) {

    c_pars <-
        children %>%
        map_chr(function(child) paste(as_c_type(child$type), child$name, sep = " ")) %>%
        paste(collapse = ", ")

    sexp_pars <-
        children %>%
        map_chr(function(child) glue("SEXP r_{CHILD}", CHILD = child$name)) %>%
        paste(collapse = ", ")

    par_names <-
        children %>%
        map_chr(function(child) child$name) %>%
        paste(collapse = ", ")

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_new, {N}),",
                     .sep = "\n",
                     N = length(children) + 1,
                     NODE = node)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("rastr_node_t rastr_{NODE}_new(rastr_ast_t ast, {C_PARS});",
                    "SEXP r_rastr_{NODE}_new(SEXP r_ast, {SEXP_PARS});",
                    .trim = FALSE,
                    .sep = "\n",
                    NODE = node,
                    C_PARS = c_pars,
                    SEXP_PARS = sexp_pars)

    code$cpp_ifc$push(cpp_ifc)

    cpp_assigns <-
        children %>%
        map_chr(function(child) {
            glue("    ASSIGN_CHILD({NODE}, {CHILD}, id)",
                 .sep = "\n",
                 .trim = FALSE,
                 NODE = node,
                 CHILD = child$name)
        }) %>%
        paste(collapse = "\n")

    r_assigns <-
        children %>%
        map_chr(function(child) {
            glue("    ensure_node_class(r_{CHILD});",
                 "    rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                 .sep = "\n",
                 .trim = FALSE,
                 CHILD = child$name)
        }) %>%
        paste(collapse = "\n")

    cpp_impl <- glue("rastr_node_t rastr_{NODE}_new(rastr_ast_t ast, {C_PARS}) {{",
                     "    rastr_node_pair_t pair = rastr_node_create(ast, {TYPE});",
                     "    rastr_node_ptr_t ptr = pair.ptr;",
                     "    int id = ptr->id;",
                     "",
                     cpp_assigns,
                     "",
                     "    return pair.node;",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_new(SEXP r_ast, {SEXP_PARS}) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "",
                     r_assigns,
                     "",
                     "    rastr_node_t result = rastr_{NODE}_new(ast, {PAR_NAMES});",
                     "    return rastr_node_wrap(result);",
                     "}}",
                     "",
                     .trim = FALSE,
                     .sep = "\n",
                     NODE = node,
                     C_PARS = c_pars,
                     SEXP_PARS = sexp_pars,
                     PAR_NAMES = par_names,
                     TYPE = type)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_new <- function(ast, {PAR_NAMES}) {{",
                   "    .Call(C_rastr_{NODE}_new, ast, {PAR_NAMES})",
                   "}}",
                   .sep = "\n",
                   NODE = node,
                   PAR_NAMES = par_names)

    code$r_impl$push(r_impl)
}


## generates constructor for seq node
gen_cons_seq <- function(code, type, node, children) {

    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_new, 2),",
                     .sep = "\n",
                     NODE = node)

    code$cpp_init$push(cpp_init)

    cons_ifc <- glue("rastr_node_t rastr_{NODE}_new(rastr_ast_t ast, int len, const rastr_node_t* seq);",
                     "SEXP r_rastr_{NODE}_new(SEXP r_ast, SEXP r_seq);",
                     .trim = FALSE,
                     .sep = "\n",
                     NODE = node)

    code$cpp_ifc$push(cons_ifc)

    cpp_impl <- glue("rastr_node_t rastr_{NODE}_new(rastr_ast_t ast, int len, const rastr_node_t* seq) {{",
                      "    rastr_node_pair_t pair = rastr_node_create(ast, {TYPE});",
                      "    rastr_node_ptr_t ptr = pair.ptr;",
                      "    int id = ptr->id;",
                      "",
                      "    ptr->node.{NODE}_node.len = len;",
                      "    ptr->node.{NODE}_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);",
                      "",
                      "    for (int i = 0; i < len; ++i) {{",
                      "        rastr_node_t child = seq[i];",
                      "        ASSIGN_SEQ_CHILD({NODE}, i, child, id)",
                      "    }}",
                      "",
                      "    return pair.node;",
                      "}}",
                      "",
                      "SEXP r_rastr_{NODE}_new(SEXP r_ast, SEXP r_seq) {{",
                      "    ensure_ast_class(r_ast);",
                      "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                      "",
                      "    rastr_node_pair_t pair = rastr_node_create(ast, {TYPE});",
                      "    rastr_node_ptr_t ptr = pair.ptr;",
                      "    int id = ptr->id;",
                      "",
                      "    int len = Rf_length(r_seq);",
                      "    ptr->node.{NODE}_node.len = len;",
                      "    ptr->node.{NODE}_node.seq = (rastr_node_t*) malloc_or_fail(sizeof(rastr_node_t) * len);",
                      "",
                      "    for (int i = 0; i < len; ++i) {{",
                      "        rastr_node_t child = rastr_node_unwrap(VECTOR_ELT(r_seq, i));",
                      "        ASSIGN_SEQ_CHILD({NODE}, i, child, id)",
                      "    }}",
                      "",
                      "    return rastr_node_wrap(pair.node);",
                      "}}",
                      .trim = FALSE,
                      .sep = "\n",
                      NODE = node,
                      TYPE = type)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_new <- function(ast, seq) {{",
                   "    .Call(C_rastr_{NODE}_new, ast, seq)",
                   "}}",
                   .sep = "\n",
                   NODE = node)

    code$r_impl$push(r_impl)
}

gen_pred <- function(code, type, node, children) {


    cpp_init <- glue("DECLARE_BINDING(rastr_{NODE}_type, 2),",
                     .sep = "\n",
                     NODE = node)

    code$cpp_init$push(cpp_init)

    cpp_ifc <- glue("// pred",
                    "int rastr_{NODE}_type(rastr_ast_t ast, rastr_node_t node);",
                    "SEXP r_rastr_{NODE}_type(SEXP r_ast, SEXP r_node);",
                    .sep = "\n",
                    NODE = node)

    code$cpp_ifc$push(cpp_ifc)

    checks <- paste("type ==", type, collapse = " || ")

    cpp_impl <- glue("// pred",
                     "int rastr_{NODE}_type(rastr_ast_t ast, rastr_node_t node) {{",
                     "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                     "    rastr_node_type_t type = ptr -> type;",
                     "    return ({CHECKS});",
                     "}}",
                     "",
                     "SEXP r_rastr_{NODE}_type(SEXP r_ast, SEXP r_node) {{",
                     "    ensure_ast_class(r_ast);",
                     "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                     "    ensure_node_class(r_node);",
                     "    rastr_node_t node = rastr_node_unwrap(r_node);",
                     "    int result = rastr_{NODE}_type(ast, node);",
                     "    return lgl_vec1(result);",
                     "}}",
                     .sep = "\n",
                     NODE = node,
                     CHECKS = checks)

    code$cpp_impl$push(cpp_impl)

    r_impl <- glue("#' @export",
                   "{NODE}_type <- function(ast, node) {{",
                   "    .Call(C_rastr_{NODE}_type, ast, node)",
                   "}}",
                   .sep = "\n",
                   NODE = node)

    code$r_impl$push(r_impl)

}


gen_seq_getter <- function(code, type, node, child) {

    getter_impl <- glue("// {CHILD}",
                        "rastr_node_t rastr_{NODE}_get(rastr_ast_t ast, rastr_ast_t node, int index) {{",
                        "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                        "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                        "    SEQ_OUT_OF_BOUNDS_ERROR(ptr->node.{NODE}_node.len, index, rastr_{NODE}_get)",
                        "    return ptr->node.{NODE}_node.seq[index];",
                        "}}",
                        "",
                        "rastr_node_t rastr_{NODE}_set(rastr_ast_t ast, rastr_ast_t node, rastr_ast_t child, int index) {{",
                        "    rastr_node_ptr_t ptr = rastr_ast_get_impl(ast, node);",
                        "    ENSURE_NODE_TYPE(rastr_{NODE}_type, node);",
                        "    SEQ_OUT_OF_BOUNDS_ERROR(ptr->node.{NODE}_node.len, index, rastr_{NODE}_get)",
                        "    return ptr->node.{NODE}_node.seq[index];",
                        "}}",
                        "",
                        "SEXP r_rastr_{NODE}_get(SEXP r_ast, SEXP r_node, SEXP r_index) {{",
                        "    ensure_ast_class(r_ast);",
                        "    rastr_ast_t ast = rastr_ast_unwrap(r_ast);",
                        "    ensure_node_class(r_node);",
                        "    rastr_node_t node = rastr_node_unwrap(r_node);",
                        "    INT_TYPECHECK(r_index, r_rastr_{NODE}_get)",
                        "    int index = int_get(r_index, 0) - 1;",
                        "    {CHILD_TYPE} result = rastr_{NODE}_get(ast, node, index);",
                        retcode,
                        "}}",
                        .sep = "\n",
                        TYPE = type,
                        NODE = node,
                        CHILD = child$name,
                        CHILD_TYPE = child_type,
                        WRAPPER = wrapper)

    glue("#' @export",
         "{NODE}_get <- function(ast, node, index) {{",
         "    .Call(C_rastr_{NODE}_get, ast, node, index)",
         "}}",
         .sep = "\n",
         NODE = node)

    glue("DECLARE_BINDING(rastr_{NODE}_get, 3),",
         .sep = "\n",
         NODE = node)


    glue("// {CHILD}",
         "rastr_node_t rastr_{NODE}_get(rastr_ast_t ast, rastr_ast_t node, int index);",
         "SEXP r_rastr_{NODE}_get(SEXP r_ast, SEXP r_node, SEXP r_index);",
         .sep = "\n",
         NODE = node,
         CHILD = child$name)
}

cdefn_api <- function(file) {

    nodefun <- function(type, node, children) {
        pars <-
            children %>%
            map_chr(function(child) paste(get_c_type(child$type), child$name, sep = " ")) %>%
            paste(collapse = ", ")

        assignments <-
            children %>%
            map_chr(function(child) {
                glue("    pair.ptr->node.{NODE}_node.{CHILD} = {CHILD};", NODE = node, CHILD = child$name)
            }) %>%
            paste(collapse = "\n")

        has_str <- any(map_lgl(children, function(child) child$type == "chr"))

        glue("// constructor",
             "rastr_node_t rastr_{NODE}_node{SUFFIX}({PARS}) {{",
             "    rastr_node_pair_t pair = rastr_node_create(ast, {TYPE});",
             assignments,
             "}}",
             .sep = "\n",
             NODE = node,
             PARS = pars,
             TYPE = type,
             SUFFIX = if(has_str) "_unsafe" else "")
    }

    childfun <- function(type, node, child) {


    }

    gen_api(file, c_header, childfun, nodefun)
}

gen_node <- function(code, type, node, children) {
    if(length(type) == 1) {
        if(any(map_lgl(children, function(child) child$name == "seq"))) {
            gen_cons_seq(code, type, node, children)
        }
        else if(!(node %in% c("lgl", "int", "dbl", "cpx", "chr", "sym", "gap", "beg", "err", "loc"))) {
            gen_cons(code, type, node, children)
        }
    }

    gen_pred(code, type, node, children)
}

gen_child <- function(code, type, node, child) {

    if(child$type != "seq") {
        gen_get_node(code, type, node, child)
    }

    ## no replacement or setting of loc nodes
    if(child$type == "node" && child$name != "loc") {
        gen_rep_node(code, type, node, child)
        gen_set_node(code, type, node, child)
    }

    if(child$type == "seq") {
        gen_get_seq(code, type, node, child)
        gen_rep_seq(code, type, node, child)
        gen_set_seq(code, type, node, child)
    }
    ##child_type <- as_c_type(child$type)
    ##
    ##retcode <- switch(child$type,
    ##                  "rastr_node_t" = "    return rastr_node_wrap(result);",
    ##                  "rastr_node_seq_t" = "    return rastr_node_seq_wrap(result, rastr_{NODE}_len(ast, node));",
    ##                  "int" = "    return int_vec1(result);",
    ##                  "dbl" = "    return dbl_vec1(result);",
    ##                  "chr" = "    return chr_vec1(result);",
    ##                  "lgl" = "    return lgl_vec1(result);",
    ##                  "cpx" = "    return cpx_vec1(result);")
}


gen_node_header <- function(code, type, node, children) {

    r_header <-
        glue("################################################################################",
             "# {NODE}",
             "################################################################################",
             .sep = "\n",
             NODE = node)

    cpp_header <-
        glue("/*******************************************************************************",
             "* {NODE}",
             "*******************************************************************************/",
             .sep = "\n",
             NODE = node)

    code$cpp_impl$push(cpp_header)
    code$cpp_ifc$push(cpp_header)
    code$cpp_unsafe_ifc$push(cpp_header)
    code$cpp_init$push(cpp_header)
    code$r_impl$push(r_header)
}

gen_child_header <- function(code, type, node, child) {

    len <- nchar(child$name)

    hashes <- paste0(rep("#", 80 - len - 3), collapse = "")

    r_header <- glue("# {CHILD} {HASHES}\n",
                     .sep = "\n",
                     CHILD = child$name,
                     HASHES = hashes)

    stars <- paste0(rep("*", 80 - len - 6), collapse = "")

    cpp_header <- glue("/* {CHILD} {STARS}*/\n",
                       .sep = "\n",
                       CHILD = child$name,
                       STARS = stars)

    code$cpp_impl$push(cpp_header)
    code$cpp_ifc$push(cpp_header)
    code$cpp_unsafe_ifc$push(cpp_header)
    code$cpp_init$push(cpp_header)
    code$r_impl$push(r_header)
}

gen_node_footer <- function(code, type, node, children) {
    code$cpp_impl$push("\n")
    code$cpp_ifc$push("\n")
    code$cpp_unsafe_ifc$push("\n")
    code$cpp_init$push("\n")
    code$r_impl$push("\n")
}

gen_child_footer <- function(code, type, node, child) {
    code$cpp_impl$push("\n")
    code$cpp_ifc$push("\n")
    code$cpp_unsafe_ifc$push("\n")
    code$cpp_init$push("\n")
    code$r_impl$push("\n")
}

main <- function() {
    code <- make_code()

    gen_api(code,
            gen_node_header,
            gen_child_header,
            gen_node_footer,
            gen_child_footer,
            gen_node,
            gen_child)

    write_lines(code$cpp_impl$read(), "autogen_node_impl.h")
    write_lines(code$cpp_ifc$read(), "autogen_node_ifc.h")
    write_lines(code$cpp_unsafe_ifc$read(), "autogen_unsafe_node_ifc.h")
    write_lines(code$cpp_init$read(), "autogen_init.h")
    write_lines(code$r_impl$read(), "autogen_node.R")
}

main()
