% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_dpar}
\alias{doc_dpar}
\alias{dpar_new}
\alias{dpar_type}
\alias{dpar_name_get}
\alias{dpar_name_rep}
\alias{dpar_name_set}
\alias{dpar_op_get}
\alias{dpar_op_rep}
\alias{dpar_op_set}
\alias{dpar_expr_get}
\alias{dpar_expr_rep}
\alias{dpar_expr_set}
\title{Create and query \code{dpar} nodes}
\usage{
dpar_new(ast, name, op, expr)

dpar_type(ast, node)

dpar_name_get(ast, node)

dpar_name_rep(ast, node, name)

dpar_name_set(ast, node, name)

dpar_op_get(ast, node)

dpar_op_rep(ast, node, op)

dpar_op_set(ast, node, op)

dpar_expr_get(ast, node)

dpar_expr_rep(ast, node, expr)

dpar_expr_set(ast, node, expr)
}
\arguments{
\item{ast}{AST object}

\item{name}{\code{name} node}

\item{op}{\code{op} node}

\item{expr}{\code{expr} node}

\item{node}{\code{dpar} node}
}
\description{
\itemize{
\item \code{dpar_new()} instantiates a new \code{dpar} node.
\item \code{dpar_type()} checks if the node is a \code{dpar} node.
\item \verb{dpar_<child>_get()} returns the \verb{<child>} node of \code{dpar}.
\item \verb{dpar_<child>_set()} sets the new \verb{<child>} and deletes the old \verb{<child>}.
\item \verb{dpar_<child>_rep()} sets the new \verb{<child>} and returns the old \verb{<child>}.
}
}
