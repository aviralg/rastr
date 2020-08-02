#include "r_rastr_ast_block_expression_r_node.h"
#include "BlockExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BlockExpressionRNode;
using rastr::ast::BlockExpressionRNodeSPtr;
using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;

SEXP r_rastr_ast_block_expression_r_node_create(SEXP r_opening_delimiter,
                                                SEXP r_expressions,
                                                SEXP r_closing_delimiter) {
    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionSequenceRNodeSPtr expressions =
        from_sexp<ExpressionSequenceRNode>(r_expressions);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    BlockExpressionRNodeSPtr node = std::make_shared<BlockExpressionRNode>(
        opening_delimiter, expressions, closing_delimiter);

    return to_sexp<BlockExpressionRNode>(node);
}
