
#' @export
CharacterLiteralExpressionRNode <- function(representation) { ## nolint
    stopifnot(is_scalar_character(representation))

    .Call(C_character_literal_expression_r_node_create, representation)
}
