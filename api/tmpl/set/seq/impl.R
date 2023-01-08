#' @param _CHILD_ `_CHILD_` node
#' @rdname doc__NODE_
#' @export
_NODE___CHILD__set <- function(ast, node, index, _CHILD_) {
    invisible(.Call(C_rastr__NODE__set, ast, node, index, _CHILD_))
}
