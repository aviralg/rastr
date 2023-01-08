library(tidyverse)
library(glue)
library(readr)
library(fs)
library(yaml)

################################################################################
## DATA STRUCTURES
################################################################################

make_interpolator <- function(dir) {

    interpolate <- function(api, node, file, pat) {
        p <- path(dir, api, node, file)

        if (!file_exists(p)) {
            stop(sprintf("template %s does not exist", p))
        }

        text <- read_lines(p)

        str_replace_all(text, pat)
    }

    interpolate
}

make_store <- function(dir) {
    buffers <-
        list("impl.cpp" = character(0),
             "ifc.cpp" = character(0),
             "init.cpp" = character(0),
             "impl.R" = character(0))

    push <- function(file, content) {
        buffers[[file]] <<- append(buffers[[file]], content)
    }

    push_all <- function(content) {
        for(file in names(buffers)) {
            push(file, content)
        }
    }

    save <- function() {
        for(file in names(buffers)) {
            dest <- path(dir, file)
            write_lines(buffers[[file]], dest)
        }
    }

    list(push = push, push_all = push_all, save = save)
}

make_interpolator <- function(dir) {

    interpolate <- function(api, node, file, pat) {
        p <- path(dir, api, node, file)

        if (!file_exists(p)) {
            stop(sprintf("template %s does not exist", p))
        }

        text <- read_lines(p)

        str_replace_all(text, pat)
    }

    interpolate
}

make_generator <- function(interpolate, store) {

    generator <- function(api, node, file, pat) {
        code <- interpolate(api, node, file, pat)
        store$push(file, code)
    }

    generator
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

gen_get_node <- function(gen, type, node, child) {

    child_type <- as_c_type(child$type)

    retcode <- switch(child$type,
                      "node" = "return rastr_node_wrap(result);",
                      "seq" = "return rastr_node_seq_wrap(result, rastr_{NODE}_len(ast, node));",
                      "int" = "return int_vec1(result);",
                      "dbl" = "return dbl_vec1(result);",
                      "chr" = "return chr_vec1(result);",
                      "lgl" = "return lgl_vec1(result);",
                      "cpx" = "return cpx_vec1(result);")

    gen("get", "node", "init.cpp", c("_NODE_" = node,
                                     "_CHILD_" = child$name))

    gen("get", "node", "ifc.cpp", c("_CHILD_TYPE_" = child_type,
                                    "_NODE_" = node,
                                    "_CHILD_" = child$name))


    gen("get", "node", "impl.cpp", c("_CHILD_TYPE_" = child_type,
                                     "_TYPE_" = type,
                                     "_NODE_" = node,
                                     "_CHILD_" = child$name,
                                     "_RETCODE_" = retcode))

    gen("get", "node", "impl.R", c("_NODE_" = node, "_CHILD_" = child$name))
}

gen_get_seq <- function(gen, type, node, child) {

    stopifnot(child$type == "seq")

    gen("get", "seq", "init.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

    gen("get", "seq", "ifc.cpp", c("_NODE_" = node))

    gen("get", "seq", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node))

    gen("get", "seq", "impl.R", c("_NODE_" = node))
}


gen_rep_node <- function(gen, type, node, child) {

    stopifnot(child$type == "node")

    gen("rep", "node", "init.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

    gen("rep", "node", "ifc.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

    gen("rep", "node", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node, "_CHILD_" = child$name))

    gen("rep", "node", "impl.R", c("_NODE_" = node, "_CHILD_" = child$name))
}

gen_rep_seq <- function(gen, type, node, child) {

    stopifnot(child$type == "seq")

    gen("rep", "seq", "init.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

                                        # converts exprs to expr, args to arg, pars to par
    child_name <- str_sub(node, end = -2)

    gen("rep", "seq", "ifc.cpp", c("_NODE_" = node, "_CHILD_" = child_name))

    gen("rep", "seq", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node, "_CHILD_" = child_name))

    gen("rep", "seq", "impl.R", c("_NODE_" = node, "_CHILD_" = child_name))
}

gen_set_node <- function(gen, type, node, child) {

    stopifnot(child$type == "node")

    gen("set", "node", "init.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

    gen("set", "node", "ifc.cpp", c("_NODE_" = node, "_CHILD_" = child$name))

    gen("set", "node", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node, "_CHILD_" = child$name))

    gen("set", "node", "impl.R", c("_NODE_" = node, "_CHILD_" = child$name))
}

gen_set_seq <- function(gen, type, node, child) {

    stopifnot(child$type == "seq")

    ## converts exprs to expr, args to arg, pars to par
    child_name <- str_sub(node, end = -2)

    gen("set", "seq", "init.cpp", c("_NODE_" = node, "_CHILD_" = child_name))

    gen("set", "seq", "ifc.cpp", c("_NODE_" = node, "_CHILD_" = child_name))

    gen("set", "seq", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node, "_CHILD_" = child_name))

    gen("set", "seq", "impl.R", c("_NODE_" = node, "_CHILD_" = child_name))
}

gen_ins_seq <- function(gen, type, node, child) {

    stopifnot(child$type == "seq")

    gen("ins", "seq", "init.cpp", c("_NODE_" = node))

    gen("ins", "seq", "ifc.cpp", c("_NODE_" = node))

    gen("ins", "seq", "impl.cpp", c("_TYPE_" = type, "_NODE_" = node))

    gen("ins", "seq", "impl.R", c("_NODE_" = node))
}

## generates constructor for node
gen_cons <- function(gen, type, node, children) {

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

    gen("new", "node", "init.cpp",
        c("_N_" = toString(length(children) + 1),
          "_NODE_" = node))

    gen("new", "node", "ifc.cpp",
        c("_NODE_" = node,
          "_C_PARS_" = c_pars,
          "_SEXP_PARS_" = sexp_pars))

    cpp_assigns <-
        children %>%
        map_chr(function(child) {
            glue("ASSIGN_CHILD({NODE}, {CHILD}, id)",
                 .sep = "\n",
                 .trim = FALSE,
                 NODE = node,
                 CHILD = child$name)
        }) %>%
        paste(collapse = "\n")

    r_assigns <-
        children %>%
        map_chr(function(child) {
            glue("ensure_node_class(r_{CHILD});",
                 "rastr_node_t {CHILD} = rastr_node_unwrap(r_{CHILD});",
                 .sep = "\n",
                 .trim = FALSE,
                 CHILD = child$name)
        }) %>%
        paste(collapse = "\n")

    gen("new", "node", "impl.cpp",
        c("_NODE_" = node,
          "_C_PARS_" = c_pars,
          "_SEXP_PARS_" = sexp_pars,
          "_PAR_NAMES_" = par_names,
          "_TYPE_" = type,
          "_CPP_ASSIGNS_" = cpp_assigns,
          "_R_ASSIGNS_" = r_assigns))

    gen("new", "node", "impl.R", c("_NODE_" = node, "_PAR_NAMES_" = par_names))

}

## generates constructor for seq node
gen_cons_seq <- function(gen, type, node, children) {

    gen("new", "seq", "init.cpp", c("_NODE_" = node))

    gen("new", "seq", "ifc.cpp", c("_NODE_" = node))

    gen("new", "seq", "impl.cpp", c("_NODE_" = node, "_TYPE_" = type))

    gen("new", "seq", "impl.R", c("_NODE_" = node))
}

gen_pred <- function(gen, type, node, children) {

    gen("pred", "any", "init.cpp", c("_NODE_" = node))

    gen("pred", "any", "ifc.cpp", c("_NODE_" = node))

    checks <- paste("type ==", type, collapse = " || ")

    gen("pred", "any", "impl.cpp", c("_NODE_" = node, "_CHECKS_" = checks))

    gen("pred", "any", "impl.R", c("_NODE_" = node))
}

gen_doc <- function(gen, type, node, children) {
    if (any(map_lgl(children, function(child) child$name == "seq"))) {
        gen("doc", "seq", "impl.R", c("_NODE_" = node))
    }
    else {
        gen("doc", "node", "impl.R", c("_NODE_" = node))
    }
}

gen_node <- function(gen, type, node, children) {
    gen_doc(gen, type, node, children)

    if (length(type) == 1) {
        if(any(map_lgl(children, function(child) child$name == "seq"))) {
            gen_cons_seq(gen, type, node, children)
        }
        else if(!(node %in% c("lgl", "int", "dbl", "cpx", "chr", "sym", "gap", "beg", "err", "loc"))) {
            gen_cons(gen, type, node, children)
        }
    }

    gen_pred(gen, type, node, children)
}

gen_child <- function(gen, type, node, child) {

    if(child$type != "seq") {
        gen_get_node(gen, type, node, child)
    }

    ## no replacement or setting of loc nodes
    if(child$type == "node" && child$name != "loc") {
        gen_rep_node(gen, type, node, child)
        gen_set_node(gen, type, node, child)
    }

    if(child$type == "seq") {
        gen_get_seq(gen, type, node, child)
        gen_rep_seq(gen, type, node, child)
        gen_set_seq(gen, type, node, child)
        gen_ins_seq(gen, type, node, child)
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


gen_node_header <- function(store, type, node, children) {

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

    store$push("impl.cpp", cpp_header)
    store$push("ifc.cpp", cpp_header)
    store$push("init.cpp", cpp_header)
    store$push("impl.R", r_header)
}

gen_child_header <- function(store, type, node, child) {

    len <- nchar(child$name)

    r_header <- glue("## {CHILD}\n",
                     .sep = "\n",
                     CHILD = child$name)

    cpp_header <- glue("// {CHILD}\n",
                       .sep = "\n",
                       CHILD = child$name)

    store$push("impl.cpp", cpp_header)
    store$push("ifc.cpp", cpp_header)
    store$push("init.cpp", cpp_header)
    store$push("impl.R", r_header)
}

gen_node_footer <- function(store, type, node, children) {
    store$push_all("\n")
}

gen_child_footer <- function(store, type, node, child) {
    store$push_all("\n")
}

gen_api <- function(node_decl, interpolate, store) {


    gen <- function(api, node, file, pat) {
        code <- interpolate(api, node, file, pat)
        store$push(file, code)
    }

    handler <- function(arg) {
        type <- arg$type
        node <- arg$node
        children <- arg$children

        gen_node_header(store, type, node, children)

        gen_node(gen, type, node, children)

        map(children,
            function(child) {
                gen_child_header(store, type, node, child)
                gen_child(gen, type, node, child)
                gen_child_footer(store, type, node, child)
            })

        gen_node_footer(store, type, node, children)

        NULL
    }

    map(node_decl, handler)
}

main <- function() {
    args <- commandArgs(trailingOnly=TRUE)

    if (length(args) != 3) {
        stop("required three directory arguments")
    }

    node_decl_file <- args[1]
    tmpl_dir <- args[2]
    store_dir <- args[3]

    node_decl <- read_yaml(node_decl_file)
    dir_create(store_dir, recurse=TRUE)

    interpolate <- make_interpolator(tmpl_dir)
    store <- make_store(store_dir)

    gen_api(node_decl, interpolate, store)

    store$save()
}

main()
