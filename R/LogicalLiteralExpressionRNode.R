
#' @export
LogicalLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_logical(value))

    .Call(C_logical_literal_expression_r_node_create, value)
}
