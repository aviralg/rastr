
#' @export
LogicalLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_logical(representation))

    .Call(C_logical_literal_expression_r_node_create, representation)
}
