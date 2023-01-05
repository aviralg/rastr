#' @export
_NODE__new <- function(ast, seq) {
    .Call(C_rastr__NODE__new, ast, seq)
}
