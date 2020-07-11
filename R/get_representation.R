
#' @export
get_representation <- function(object, ...) {
    UseMethod("get_representation")
}

#' @export
get_representation.rastr_node_r_expression_literal_character <- function(object, ...) { ## nolint
    .Call(C_character_literal_expression_r_node_get_representation, object)
}

#' @export
get_representation.rastr_node_r_expression_literal_complex <- function(object, ...) { ## nolint
    .Call(C_complex_literal_expression_r_node_get_representation, object)
}

#' @export
get_representation.rastr_node_r_expression_literal_double <- function(object, ...) { ## nolint
    .Call(C_double_literal_expression_r_node_get_representation, object)
}

#' @export
get_representation.rastr_node_r_expression_literal_integer <- function(object, ...) { ## nolint
    .Call(C_integer_literal_expression_r_node_get_representation, object)
}

#' @export
get_representation.rastr_node_r_expression_literal_logical <- function(object, ...) { ## nolint
    .Call(C_logical_literal_expression_r_node_get_representation, object)
}

#' @export
get_representation.rastr_node_r_expression_literal_raw <- function(object, ...) { ## nolint
    .Call(C_raw_literal_expression_r_node_get_representation, object)
}
