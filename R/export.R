
#' @export
#' @rdname export
export_to_dot <- function(ast, filepath, depth) {
    .Call(C_rastr_export_to_dot, ast, filepath, depth)
}
