################################################################################
## Parsing
################################################################################

#' @export
#' @rdname parsing
parse_file <- function(filepath) {
    .Call(C_rastr_parse_file, filepath)
}

#' @export
#' @rdname parsing
parse_str <- function(str) {
    .Call(C_rastr_parse_str, str)
}
