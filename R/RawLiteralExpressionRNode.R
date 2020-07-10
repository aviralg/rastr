
#' @export
RawLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_raw(value))

    .Call(C_raw_literal_expression_r_node_create, value)
}
