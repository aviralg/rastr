% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_op}
\alias{doc_op}
\alias{op_type}
\alias{op_gap_get}
\alias{op_gap_rep}
\alias{op_gap_set}
\alias{op_loc_get}
\title{Create and query \code{op} nodes}
\usage{
op_type(ast, node)

op_gap_get(ast, node)

op_gap_rep(ast, node, gap)

op_gap_set(ast, node, gap)

op_loc_get(ast, node)
}
\arguments{
\item{ast}{AST object}

\item{node}{\code{op} node}

\item{gap}{\code{gap} node}
}
\description{
\itemize{
\item \code{op_new()} instantiates a new \code{op} node.
\item \code{op_type()} checks if the node is a \code{op} node.
\item \verb{op_<child>_get()} returns the \verb{<child>} node of \code{op}.
\item \verb{op_<child>_set()} sets the new \verb{<child>} and deletes the old \verb{<child>}.
\item \verb{op_<child>_rep()} sets the new \verb{<child>} and returns the old \verb{<child>}.
}
}
