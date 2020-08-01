#include "r_rastr_ast_i_body.h"
#include "IBody.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::IBody;
using rastr::ast::IBodySPtr;

SEXP r_rastr_ast_i_body_get_body(SEXP r_i_body) {
    IBodySPtr i_body = from_sexp<IBody>(r_i_body);

    ExpressionRNodeSPtr body = i_body->get_body();

    return to_sexp<ExpressionRNode>(body);
}

SEXP r_rastr_ast_i_body_set_body(SEXP r_i_body, SEXP r_body) {
    IBodySPtr i_body = from_sexp<IBody>(r_i_body);

    ExpressionRNodeSPtr body = from_sexp<ExpressionRNode>(r_body);

    i_body->set_body(body);

    return r_i_body;
}
