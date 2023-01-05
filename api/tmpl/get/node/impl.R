
#' @description
#' * `_NODE___CHILD__get()` returns the `_CHILD_` node of `_NODE_`
#'
#' @rdname doc__NODE_
#' @export
_NODE___CHILD__get <- function(ast, node) {
    .Call(C_rastr__NODE___CHILD__get, ast, node)
}
