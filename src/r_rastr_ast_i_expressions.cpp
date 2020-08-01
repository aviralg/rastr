#include "r_rastr_ast_i_expressions.h"
#include "IExpressions.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::IExpressions;
using rastr::ast::IExpressionsSPtr;

SEXP r_rastr_ast_i_expressions_get_expressions(SEXP r_i_expressions) {
    IExpressionsSPtr i_expressions = from_sexp<IExpressions>(r_i_expressions);

    ExpressionSequenceRNodeSPtr expressions = i_expressions->get_expressions();

    return to_sexp<ExpressionSequenceRNode>(expressions);
}

SEXP r_rastr_ast_i_expressions_set_expressions(SEXP r_i_expressions,
                                               SEXP r_expressions) {
    IExpressionsSPtr i_expressions = from_sexp<IExpressions>(r_i_expressions);

    ExpressionSequenceRNodeSPtr expressions =
        from_sexp<ExpressionSequenceRNode>(r_expressions);

    i_expressions->set_expressions(expressions);

    return r_i_expressions;
}
