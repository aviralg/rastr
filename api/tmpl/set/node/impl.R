#' @param _CHILD_ `_CHILD_` node
#' @rdname doc__NODE_
#' @export
_NODE___CHILD__set <- function(ast, node, _CHILD_) {
    invisible(.Call(C_rastr__NODE___CHILD__set, ast, node, _CHILD_))
}
