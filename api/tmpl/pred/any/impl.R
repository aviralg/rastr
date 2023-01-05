#' @export
_NODE__type <- function(ast, node) {
    .Call(C_rastr__NODE__type, ast, node)
}
