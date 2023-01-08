#' AST APIs
#'
#' @description
#' * `ast_new()` instantiates a new AST
#' * `ast_id()` returns the unique id of the AST
#' * `ast_size()` returns the number of nodes in the AST
#' * `ast_root_get()` returns the root node of `_NODE_`.
#' * `ast_root_set()` sets the new root and deletes the old root.
#' * `ast_root_rep()` sets the new root and returns the old root.
#'
#' @param ast AST object
#' @param root Root node
#' @param capacity expected size of AST; size will increase dynamically if more nodes are added
#' @name ast

#' @export
#' @rdname ast
ast_new <- function(capacity = 10000L) {
    .Call(C_rastr_ast_new, capacity)
}

#' @export
#' @rdname ast
ast_id <- function(ast) {
    .Call(C_rastr_ast_id, ast)
}

#' @export
#' @rdname ast
ast_size <- function(ast) {
    .Call(C_rastr_ast_size, ast)
}

#' @export
#' @rdname ast
ast_root_get <- function(ast) {
    .Call(C_rastr_ast_root_get, ast)
}

#' @export
#' @rdname ast
ast_root_rep <- function(ast, root) {
    .Call(C_rastr_ast_root_rep, ast, root)
}

#' @export
#' @rdname ast
ast_root_set <- function(ast, root) {
    .Call(C_rastr_ast_root_set, ast, root)
}

