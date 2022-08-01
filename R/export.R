
#' @export
#' @rdname export
export_to_dot <- function(ast, filepath, depth) {
    .Call(C_rastr_export_to_dot, ast, filepath, depth)
}

#' @export
#' @rdname export
to_sexp <- function(ast, node = NULL) {
    if(is.null(node)) {
        .Call(C_rastr_to_sexp, ast)
    }
    else {
        .Call(C_rastr_node_to_sexp, ast, node)
    }
}
