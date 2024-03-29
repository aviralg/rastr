% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_unop}
\alias{doc_unop}
\alias{unop_new}
\alias{unop_type}
\alias{unop_op_get}
\alias{unop_op_rep}
\alias{unop_op_set}
\alias{unop_expr_get}
\alias{unop_expr_rep}
\alias{unop_expr_set}
\title{Create and query \code{unop} nodes}
\usage{
unop_new(ast, op, expr)

unop_type(ast, node)

unop_op_get(ast, node)

unop_op_rep(ast, node, op)

unop_op_set(ast, node, op)

unop_expr_get(ast, node)

unop_expr_rep(ast, node, expr)

unop_expr_set(ast, node, expr)
}
\arguments{
\item{ast}{AST object}

\item{op}{\code{op} node}

\item{expr}{\code{expr} node}

\item{node}{\code{unop} node}
}
\description{
\itemize{
\item \code{unop_new()} instantiates a new \code{unop} node.
\item \code{unop_type()} checks if the node is a \code{unop} node.
\item \verb{unop_<child>_get()} returns the \verb{<child>} node of \code{unop}.
\item \verb{unop_<child>_set()} sets the new \verb{<child>} and deletes the old \verb{<child>}.
\item \verb{unop_<child>_rep()} sets the new \verb{<child>} and returns the old \verb{<child>}.
}
}
