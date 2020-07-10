
#' @export
IntegerLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_integer(value))

    .Call(C_integer_literal_expression_r_node_create, value)
}
