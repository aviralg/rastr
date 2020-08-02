#include "r_rastr_ast_i_condition.h"
#include "ICondition.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionConditionRNode;
using rastr::ast::ExpressionConditionRNodeSPtr;
using rastr::ast::ICondition;
using rastr::ast::IConditionSPtr;

SEXP r_rastr_ast_i_condition_get_condition(SEXP r_i_condition) {
    IConditionSPtr i_condition = from_sexp<ICondition>(r_i_condition);

    ExpressionConditionRNodeSPtr condition = i_condition->get_condition();

    return to_sexp<ExpressionConditionRNode>(condition);
}

SEXP r_rastr_ast_i_condition_set_condition(SEXP r_i_condition,
                                           SEXP r_condition) {
    IConditionSPtr i_condition = from_sexp<ICondition>(r_i_condition);

    ExpressionConditionRNodeSPtr condition =
        from_sexp<ExpressionConditionRNode>(r_condition);

    i_condition->set_condition(condition);

    return r_i_condition;
}
