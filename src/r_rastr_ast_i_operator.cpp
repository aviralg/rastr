#include "r_rastr_ast_i_operator.h"
#include "IOperator.hpp"
#include "r_cast.hpp"

using rastr::ast::IOperator;
using rastr::ast::IOperatorSPtr;
using rastr::ast::OperatorRNode;
using rastr::ast::OperatorRNodeSPtr;

SEXP r_rastr_ast_i_operator_get_operator(SEXP r_i_operator) {
    IOperatorSPtr i_operator = from_sexp<IOperator>(r_i_operator);

    OperatorRNodeSPtr op = i_operator->get_operator();

    return to_sexp<OperatorRNode>(op);
}

SEXP r_rastr_ast_i_operator_set_operator(SEXP r_i_operator, SEXP r_operator) {
    IOperatorSPtr i_operator = from_sexp<IOperator>(r_i_operator);

    OperatorRNodeSPtr op = from_sexp<OperatorRNode>(r_operator);

    i_operator->set_operator(op);

    return r_i_operator;
}
