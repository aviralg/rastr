#' @rdname doc__NODE_
#' @export
_NODE__new <- function(ast, _PAR_NAMES_) {
    .Call(C_rastr__NODE__new, ast, _PAR_NAMES_)
}
