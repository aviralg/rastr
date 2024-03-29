% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_narg}
\alias{doc_narg}
\alias{narg_new}
\alias{narg_type}
\alias{narg_name_get}
\alias{narg_name_rep}
\alias{narg_name_set}
\alias{narg_op_get}
\alias{narg_op_rep}
\alias{narg_op_set}
\alias{narg_expr_get}
\alias{narg_expr_rep}
\alias{narg_expr_set}
\title{Create and query \code{narg} nodes}
\usage{
narg_new(ast, name, op, expr)

narg_type(ast, node)

narg_name_get(ast, node)

narg_name_rep(ast, node, name)

narg_name_set(ast, node, name)

narg_op_get(ast, node)

narg_op_rep(ast, node, op)

narg_op_set(ast, node, op)

narg_expr_get(ast, node)

narg_expr_rep(ast, node, expr)

narg_expr_set(ast, node, expr)
}
\arguments{
\item{ast}{AST object}

\item{name}{\code{name} node}

\item{op}{\code{op} node}

\item{expr}{\code{expr} node}

\item{node}{\code{narg} node}
}
\description{
\itemize{
\item \code{narg_new()} instantiates a new \code{narg} node.
\item \code{narg_type()} checks if the node is a \code{narg} node.
\item \verb{narg_<child>_get()} returns the \verb{<child>} node of \code{narg}.
\item \verb{narg_<child>_set()} sets the new \verb{<child>} and deletes the old \verb{<child>}.
\item \verb{narg_<child>_rep()} sets the new \verb{<child>} and returns the old \verb{<child>}.
}
}
