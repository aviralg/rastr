
#' @export
DoubleLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_double(representation))

    .Call(C_double_literal_expression_r_node_create, representation)
}
