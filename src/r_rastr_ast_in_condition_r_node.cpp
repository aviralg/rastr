#include "r_rastr_ast_in_condition_r_node.h"
#include "InConditionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::InConditionRNode;
using rastr::ast::InConditionRNodeSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;
using rastr::ast::SymbolExpressionRNode;
using rastr::ast::SymbolExpressionRNodeSPtr;

SEXP r_rastr_ast_in_condition_r_node_create(SEXP r_opening_delimiter,
                                            SEXP r_symbol,
                                            SEXP r_keyword,
                                            SEXP r_expression,
                                            SEXP r_closing_delimiter) {
    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    SymbolExpressionRNodeSPtr symbol =
        from_sexp<SymbolExpressionRNode>(r_symbol);

    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    ExpressionRNodeSPtr expression = from_sexp<ExpressionRNode>(r_expression);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    InConditionRNodeSPtr node = std::make_shared<InConditionRNode>(
        opening_delimiter, symbol, keyword, expression, closing_delimiter);

    return to_sexp<InConditionRNode>(node);
}
