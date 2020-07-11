
#' @export
RawLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_raw(representation))

    .Call(C_raw_literal_expression_r_node_create, representation)
}
