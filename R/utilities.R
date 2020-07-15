is_scalar_character <- function(vector) {
    is.character(vector) && (length(vector) == 1) && (nchar(vector) != 0)
}

is_vector_character <- function(vector) {
    is.character(vector)
}

is_scalar_logical <- function(vector) {
    is.logical(vector) && (length(vector) == 1)
}

is_scalar_integer <- function(vector) {
    is.integer(vector) && (length(vector) == 1)
}

is_scalar_double <- function(object) {
    is.double(object) && (length(object) == 1)
}

is_scalar_complex <- function(object) {
    is.complex(object) && (length(object) == 1)
}

is_scalar_raw <- function(object) {
    is.raw(object) && (length(object) == 1)
}

is_environment <- function(env) {
    is.environment(env)
}

is_function <- function(fun) {
    is.function(fun)
}

is_null <- function(obj) {
    is.null(obj)
}

is_symbol <- function(obj) {
    is.symbol(obj)
}

is_closure <- function(obj) {
    typeof(obj) == "closure"
}

is_language <- function(obj) {
    is.language(obj)
}
