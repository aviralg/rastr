#' @rdname doc__NODE_
#' @export
_NODE__ins <- function(ast, node, index, seq) {
    invisible(.Call(C_rastr__NODE__ins, ast, node, index, seq))
}
