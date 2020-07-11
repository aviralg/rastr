
#' @export
ComplexLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_complex(representation))

    .Call(C_complex_literal_expression_r_node_create, representation)
}
