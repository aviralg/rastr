#include "r_rastr_ast_i_object.h"
#include "IObject.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionRNode;
using rastr::ast::ExpressionRNodeSPtr;
using rastr::ast::IObject;
using rastr::ast::IObjectSPtr;

SEXP r_rastr_ast_i_object_get_object(SEXP r_i_object) {
    IObjectSPtr i_object = from_sexp<IObject>(r_i_object);

    ExpressionRNodeSPtr object = i_object->get_object();

    return to_sexp<ExpressionRNode>(object);
}

SEXP r_rastr_ast_i_object_set_object(SEXP r_i_object, SEXP r_object) {
    IObjectSPtr i_object = from_sexp<IObject>(r_i_object);

    ExpressionRNodeSPtr object = from_sexp<ExpressionRNode>(r_object);

    i_object->set_object(object);

    return r_i_object;
}
