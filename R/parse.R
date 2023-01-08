#' Parse and Unparse AST
#'
#' @description
#' * `parse_str()` parses AST from an R string
#' * `parse_file()` parses AST from a file
#' * `unparse_str()` unparses AST to an R string
#' * `unparse_file()` unparses AST to a file
#'
#' @param str A scalar string to be parsed
#' @param file File to be parsed
#' @param ast AST object
#' @param node Node to be unparsed; defaults to AST root node
#' @name parse

#' @export
#' @rdname parse
parse_str <- function(str) {
    .Call(C_rastr_parse_str, str)
}

#' @export
#' @rdname parse
parse_file <- function(file) {
    .Call(C_rastr_parse_file, file)
}

#' @export
#' @rdname parse
unparse_str <- function(ast, node = ast_root_get(ast)) {
    .Call(C_rastr_unparse_str, ast, node)
}

#' @export
#' @rdname parse
unparse_file <- function(ast, node = ast_root_get(ast), file) {
    .Call(C_rastr_unparse_file, ast, node, file)
}
