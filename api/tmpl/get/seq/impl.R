
#' @rdname doc__NODE_
#' @export
_NODE__seq_get <- function(ast, node) {
    .Call(C_rastr__NODE__seq_get, ast, node)
}

#' @rdname doc__NODE_
#' @export
_NODE__get <- function(ast, node, index) {
    .Call(C_rastr__NODE__get, ast, node, index)
}
