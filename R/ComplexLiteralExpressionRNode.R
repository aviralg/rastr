
#' @export
ComplexLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_complex(value))

    .Call(C_complex_literal_expression_r_node_create, value)
}
