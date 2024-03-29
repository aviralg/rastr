% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/autogen_node.R
\name{doc_pars}
\alias{doc_pars}
\alias{pars_new}
\alias{pars_type}
\alias{pars_len_get}
\alias{pars_seq_get}
\alias{pars_get}
\alias{pars_rep}
\alias{pars_par_set}
\alias{pars_ins}
\title{Create and query \code{pars} nodes}
\usage{
pars_new(ast, seq)

pars_type(ast, node)

pars_len_get(ast, node)

pars_seq_get(ast, node)

pars_get(ast, node, index)

pars_rep(ast, node, index, par)

pars_par_set(ast, node, index, par)

pars_ins(ast, node, index, seq)
}
\arguments{
\item{ast}{AST object}

\item{seq}{list of child nodes}

\item{node}{\code{pars} node}

\item{index}{one-based index into the \code{pars} node}

\item{par}{\code{par} node}
}
\description{
\itemize{
\item \code{pars_new()} instantiates a new \code{pars} node.
\item \code{pars_type()} checks if the node is a \code{pars} node.
\item \code{pars_seq_get()} returns all the child nodes as a list.
\item \code{pars_get()} returns node at position \code{index}.
\item \code{pars_set()} sets the new node at position \code{index} and deletes the old node.
\item \code{pars_rep()} sets the new node at position \code{index} and returns the old node.
\item \code{pars_ins()} inserts nodes starting from position \code{index}.
}
}
