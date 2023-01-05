
#' @description
#' * `_NODE__seq_get()` returns the child nodes as a list
#'
#' @rdname doc__NODE_
#' @export
_NODE__seq_get <- function(ast, node) {
    .Call(C_rastr__NODE__seq_get, ast, node)
}

#' @description
#' * `_NODE__get()` returns the child node at position `index`
#'
#' @param `index` is one-based index of the child node
#'
#' @rdname doc__NODE_
#' @export
_NODE__get <- function(ast, node, index) {
    .Call(C_rastr__NODE__get, ast, node, index)
}
