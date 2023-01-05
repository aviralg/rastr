#' @export
_NODE__ins <- function(ast, node, index, len, seq) {
    invisible(.Call(C_rastr__NODE__ins, ast, node, index, len, seq))
}
