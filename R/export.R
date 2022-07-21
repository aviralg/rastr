
#' @export
#' @rdname export
export_to_dot <- function(ast, filepath) {
    .Call(C_rastr_export_to_dot, ast, filepath)
}
