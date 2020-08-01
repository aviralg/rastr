#include "r_rastr_ast_i_indices.h"
#include "IIndices.hpp"
#include "r_cast.hpp"

using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::IIndices;
using rastr::ast::IIndicesSPtr;

SEXP r_rastr_ast_i_indices_get_indices(SEXP r_i_indices) {
    IIndicesSPtr i_indices = from_sexp<IIndices>(r_i_indices);

    ExpressionSequenceRNodeSPtr indices = i_indices->get_indices();

    return to_sexp<ExpressionSequenceRNode>(indices);
}

SEXP r_rastr_ast_i_indices_set_indices(SEXP r_i_indices, SEXP r_indices) {
    IIndicesSPtr i_indices = from_sexp<IIndices>(r_i_indices);

    ExpressionSequenceRNodeSPtr indices =
        from_sexp<ExpressionSequenceRNode>(r_indices);

    i_indices->set_indices(indices);

    return r_i_indices;
}
