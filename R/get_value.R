
#' @export
get_value <- function(object, ...) {
    UseMethod("get_value")
}

#' @export
get_value.r_character_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_character_literal_expression_r_node_get_value, object)
}

#' @export
get_value.r_complex_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_complex_literal_expression_r_node_get_value, object)
}

#' @export
get_value.r_double_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_double_literal_expression_r_node_get_value, object)
}

#' @export
get_value.r_integer_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_integer_literal_expression_r_node_get_value, object)
}

#' @export
get_value.r_logical_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_logical_literal_expression_r_node_get_value, object)
}

#' @export
get_value.r_raw_literal_expression_r_node <- function(object, ...) { ## nolint
    .Call(C_raw_literal_expression_r_node_get_value, object)
}
