#' Convert AST to SEXP, data frame, list and Graphviz Dot format
#'
#' @description
#' * `to_sexp()` turns the AST to R's AST representation.
#' * `to_df()` turns the AST to a data frame.
#' * `to_list()` turns the AST to an R list.
#' * `to_dot()` turns the AST to [Graphviz's](https://graphviz.org/) [dot](https://graphviz.org/doc/info/lang.html) format.
#'
#' @param ast AST object
#' @param node Node to be exported; defaults to AST root node
#' @name convert

#' @export
#' @rdname convert
to_sexp <- function(ast, node = ast_root_get(ast)) {
    .Call(C_rastr_to_sexp, ast, node)
}

#' @export
#' @rdname convert
to_df <- function(ast, node = ast_root_get(ast)) {
    .Call(C_rastr_to_df, ast, node)
}

#' @export
#' @rdname convert
to_list <- function(ast, node = ast_root_get(ast)) {
    .Call(C_rastr_to_list, ast, node)
}

#' @export
#' @rdname convert
to_dot <- function(ast, node = ast_root_get(ast)) {
    .Call(C_rastr_to_dot, ast, node)
}
