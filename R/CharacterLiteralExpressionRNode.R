
#' @export
CharacterLiteralExpressionRNode <- function(value) {
    stopifnot(is_scalar_character(value))

    .Call(C_character_literal_expression_r_node_create, value)
}
