#' Create and query `_NODE_` nodes
#'
#' @param ast AST object
#' @param node `_NODE_` node
#' @param index one-based index into the `_NODE_` node
#' @param seq list of child nodes
#'
#' @description
#' * `_NODE__new()` instantiates a new `_NODE_` node.
#' * `_NODE__type()` checks if the node is a `_NODE_` node.
#' * `_NODE__seq_get()` returns all the child nodes as a list.
#' * `_NODE__get()` returns node at position `index`.
#' * `_NODE__set()` sets the new node at position `index` and deletes the old node.
#' * `_NODE__rep()` sets the new node at position `index` and returns the old node.
#' * `_NODE__ins()` inserts nodes starting from position `index`.
#'
#' @name doc__NODE_
