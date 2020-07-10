
#' @export
DoubleLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_double(value))

    .Call(C_double_literal_expression_r_node_create, value)
}
