
#' @export
set_value <- function(object, value, ...) {
    UseMethod("set_value")
}

#' @export
set_value.r_character_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_character(value))

    .Call(C_character_literal_expression_r_node_set_value, object, value)
}

#' @export
set_value.r_complex_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_complex(value))

    .Call(C_complex_literal_expression_r_node_set_value, object, value)
}

#' @export
set_value.r_double_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_double(value))

    .Call(C_double_literal_expression_r_node_set_value, object, value)
}

#' @export
set_value.r_integer_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_integer(value))

    .Call(C_integer_literal_expression_r_node_set_value, object, value)
}

#' @export
set_value.r_logical_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_logical(value))

    .Call(C_logical_literal_expression_r_node_set_value, object, value)
}

#' @export
set_value.r_raw_literal_expression_r_node <- function(object, value, ...) { ## nolint
    stopifnot(is_scalar_raw(value))

    .Call(C_raw_literal_expression_r_node_set_value, object, value)
}
