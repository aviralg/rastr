#include "r_rastr_ast_i_expression.h"
#include "IExpression.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::IExpression;
using rastr::ast::IExpressionSPtr;

SEXP r_rastr_ast_i_expression_get_expression(SEXP r_i_expression) {
    IExpressionSPtr i_expression = from_sexp<IExpression>(r_i_expression);

    ExpressionRNodeSPtr expression = i_expression->get_expression();

    return to_sexp<ExpressionRNode>(expression);
}

SEXP r_rastr_ast_i_expression_set_expression(SEXP r_i_expression,
                                             SEXP r_expression) {
    IExpressionSPtr i_expression = from_sexp<IExpression>(r_i_expression);

    ExpressionRNodeSPtr expression = from_sexp<ExpressionRNode>(r_expression);

    i_expression->set_expression(expression);

    return r_i_expression;
}
