% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_null}
\alias{doc_null}
\alias{null_new}
\alias{null_type}
\alias{null_gap_get}
\alias{null_gap_rep}
\alias{null_gap_set}
\alias{null_loc_get}
\title{Create and query \code{null} nodes}
\usage{
null_new(ast, gap, loc)

null_type(ast, node)

null_gap_get(ast, node)

null_gap_rep(ast, node, gap)

null_gap_set(ast, node, gap)

null_loc_get(ast, node)
}
\arguments{
\item{ast}{AST object}

\item{gap}{\code{gap} node}

\item{node}{\code{null} node}
}
\description{
\itemize{
\item \code{null_new()} instantiates a new \code{null} node.
\item \code{null_type()} checks if the node is a \code{null} node.
\item \verb{null_<child>_get()} returns the \verb{<child>} node of \code{null}.
\item \verb{null_<child>_set()} sets the new \verb{<child>} and deletes the old \verb{<child>}.
\item \verb{null_<child>_rep()} sets the new \verb{<child>} and returns the old \verb{<child>}.
}
}
