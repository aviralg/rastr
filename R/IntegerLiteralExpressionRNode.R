
#' @export
IntegerLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_integer(representation))

    .Call(C_integer_literal_expression_r_node_create, representation)
}
