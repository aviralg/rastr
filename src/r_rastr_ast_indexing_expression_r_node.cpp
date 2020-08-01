#include "r_rastr_ast_indexing_expression_r_node.h"
#include "IndexingExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::IndexingExpressionRNode;
using rastr::ast::IndexingExpressionRNodeSPtr;

SEXP r_rastr_ast_indexing_expression_r_node_create(
    SEXP r_object,
    SEXP r_opening_delimiter,
    SEXP r_indices,
    SEXP r_first_closing_delimiter,
    SEXP r_second_closing_delimiter) {
    ExpressionRNodeSPtr object = from_sexp<ExpressionRNode>(r_object);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionSequenceRNodeSPtr indices =
        from_sexp<ExpressionSequenceRNode>(r_indices);

    DelimiterRNodeSPtr first_closing_delimiter =
        from_sexp<DelimiterRNode>(r_first_closing_delimiter);

    DelimiterRNodeSPtr second_closing_delimiter =
        from_sexp<DelimiterRNode>(r_second_closing_delimiter);

    IndexingExpressionRNodeSPtr node =
        std::make_shared<IndexingExpressionRNode>(object,
                                                  opening_delimiter,
                                                  indices,
                                                  first_closing_delimiter,
                                                  second_closing_delimiter);

    return to_sexp<IndexingExpressionRNode>(node);
}

SEXP r_rastr_ast_indexing_expression_r_node_get_opening_delimiter(SEXP r_node) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr opening_delimiter = node->get_opening_delimiter();

    return to_sexp<DelimiterRNode>(opening_delimiter);
}

SEXP r_rastr_ast_indexing_expression_r_node_set_opening_delimiter(
    SEXP r_node,
    SEXP r_opening_delimiter) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    node->set_opening_delimiter(opening_delimiter);

    return r_node;
}

SEXP r_rastr_ast_indexing_expression_r_node_get_first_closing_delimiter(
    SEXP r_node) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr first_closing_delimiter =
        node->get_first_closing_delimiter();

    return to_sexp<DelimiterRNode>(first_closing_delimiter);
}

SEXP r_rastr_ast_indexing_expression_r_node_set_first_closing_delimiter(
    SEXP r_node,
    SEXP r_first_closing_delimiter) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr first_closing_delimiter =
        from_sexp<DelimiterRNode>(r_first_closing_delimiter);

    node->set_first_closing_delimiter(first_closing_delimiter);

    return r_node;
}

SEXP r_rastr_ast_indexing_expression_r_node_get_second_closing_delimiter(
    SEXP r_node) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr second_closing_delimiter =
        node->get_second_closing_delimiter();

    return to_sexp<DelimiterRNode>(second_closing_delimiter);
}

SEXP r_rastr_ast_indexing_expression_r_node_set_second_closing_delimiter(
    SEXP r_node,
    SEXP r_second_closing_delimiter) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr second_closing_delimiter =
        from_sexp<DelimiterRNode>(r_second_closing_delimiter);

    node->set_second_closing_delimiter(second_closing_delimiter);

    return r_node;
}

SEXP r_rastr_ast_indexing_expression_r_node_set_delimiters(
    SEXP r_node,
    SEXP r_opening_delimiter,
    SEXP r_first_closing_delimiter,
    SEXP r_second_closing_delimiter) {
    IndexingExpressionRNodeSPtr node =
        from_sexp<IndexingExpressionRNode>(r_node);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    DelimiterRNodeSPtr first_closing_delimiter =
        from_sexp<DelimiterRNode>(r_first_closing_delimiter);

    DelimiterRNodeSPtr second_closing_delimiter =
        from_sexp<DelimiterRNode>(r_second_closing_delimiter);

    node->set_delimiters(
        opening_delimiter, first_closing_delimiter, second_closing_delimiter);

    return r_node;
}
