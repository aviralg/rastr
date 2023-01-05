#' @export
_NODE__rep <- function(ast, node, index, _CHILD_) {
    .Call(C_rastr__NODE__rep, ast, node, index, _CHILD_)
}
