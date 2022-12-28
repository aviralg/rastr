
#' @export
unparse_str <- function(ast, node = NULL) {
    if(is.null(node)) {
        .Call(C_rastr_ast_unparse_str, ast)
    }
    else {
        .Call(C_rastr_node_unparse_str, ast, node)
    }
}

#' @export
as_sexp <- function(ast, node = NULL) {
    if(is.null(node)) {
        .Call(C_rastr_ast_as_sexp, ast)
    }
    else {
        .Call(C_rastr_node_as_sexp, ast, node)
    }
}

#' @export
as_df <- function(ast, node = NULL) {
    if(is.null(node)) {
        .Call(C_rastr_ast_as_df, ast)
    }
    else {
        .Call(C_rastr_node_as_df, ast, node)
    }
}

#' @export
desugar <- function(ast, node = NULL, strictness = TRUE) {
    if(is.null(node)) {
        .Call(C_rastr_ast_desugar, ast, strictness)
    }
    else {
        .Call(C_rastr_node_desugar, ast, node, strictness)
    }
}
