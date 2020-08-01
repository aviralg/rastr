#include "r_rastr_ast_subsetting_expression_r_node.h"
#include "SubsettingExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::SubsettingExpressionRNode;
using rastr::ast::SubsettingExpressionRNodeSPtr;

SEXP r_rastr_ast_subsetting_expression_r_node_create(SEXP r_object,
                                                     SEXP r_opening_delimiter,
                                                     SEXP r_indices,
                                                     SEXP r_closing_delimiter) {
    ExpressionRNodeSPtr object = from_sexp<ExpressionRNode>(r_object);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    ExpressionSequenceRNodeSPtr indices =
        from_sexp<ExpressionSequenceRNode>(r_indices);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    SubsettingExpressionRNodeSPtr node =
        std::make_shared<SubsettingExpressionRNode>(
            object, opening_delimiter, indices, closing_delimiter);

    return to_sexp<SubsettingExpressionRNode>(node);
}
