
#' @export
set_representation <- function(object, representation, ...) {
    UseMethod("set_representation")
}

#' @export
set_representation.rastr_node_r_expression_literal_character <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_character(representation))

    .Call(C_character_literal_expression_r_node_set_representation, object, representation)
}

#' @export
set_representation.rastr_node_r_expression_literal_complex <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_complex(representation))

    .Call(C_complex_literal_expression_r_node_set_representation, object, representation)
}

#' @export
set_representation.rastr_node_r_expression_literal_double <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_double(representation))

    .Call(C_double_literal_expression_r_node_set_representation, object, representation)
}

#' @export
set_representation.rastr_node_r_expression_literal_integer <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_integer(representation))

    .Call(C_integer_literal_expression_r_node_set_representation, object, representation)
}

#' @export
set_representation.rastr_node_r_expression_literal_logical <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_logical(representation))

    .Call(C_logical_literal_expression_r_node_set_representation, object, representation)
}

#' @export
set_representation.rastr_node_r_expression_literal_raw <- function(object, representation, ...) { ## nolint
    stopifnot(is_scalar_raw(representation))

    .Call(C_raw_literal_expression_r_node_set_representation, object, representation)
}
