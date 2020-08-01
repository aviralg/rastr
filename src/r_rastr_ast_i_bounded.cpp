#include "r_rastr_ast_i_bounded.h"
#include "IBounded.hpp"
#include "r_cast.hpp"

using rastr::ast::DelimiterRNode;
using rastr::ast::DelimiterRNodeSPtr;
using rastr::ast::IBounded;
using rastr::ast::IBoundedSPtr;

SEXP r_rastr_ast_i_bounded_get_opening_delimiter(SEXP r_i_bounded) {
    IBoundedSPtr i_bounded = from_sexp<IBounded>(r_i_bounded);

    DelimiterRNodeSPtr opening_delimiter = i_bounded->get_opening_delimiter();

    return to_sexp<DelimiterRNode>(opening_delimiter);
}

SEXP r_rastr_ast_i_bounded_set_opening_delimiter(SEXP r_i_bounded,
                                                 SEXP r_opening_delimiter) {
    IBoundedSPtr i_bounded = from_sexp<IBounded>(r_i_bounded);

    DelimiterRNodeSPtr opening_delimiter =
        from_sexp<DelimiterRNode>(r_opening_delimiter);

    i_bounded->set_opening_delimiter(opening_delimiter);

    return r_i_bounded;
}

SEXP r_rastr_ast_i_bounded_get_closing_delimiter(SEXP r_i_bounded) {
    IBoundedSPtr i_bounded = from_sexp<IBounded>(r_i_bounded);

    DelimiterRNodeSPtr closing_delimiter = i_bounded->get_closing_delimiter();

    return to_sexp<DelimiterRNode>(closing_delimiter);
}

SEXP r_rastr_ast_i_bounded_set_closing_delimiter(SEXP r_i_bounded,
                                                 SEXP r_closing_delimiter) {
    IBoundedSPtr i_bounded = from_sexp<IBounded>(r_i_bounded);

    DelimiterRNodeSPtr closing_delimiter =
        from_sexp<DelimiterRNode>(r_closing_delimiter);

    i_bounded->set_closing_delimiter(closing_delimiter);

    return r_i_bounded;
}
