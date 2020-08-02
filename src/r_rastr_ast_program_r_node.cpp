#include "r_rastr_ast_program_r_node.h"
#include "ProgramRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BeginRNode;
using rastr::ast::BeginRNodeSPtr;
using rastr::ast::EndRNode;
using rastr::ast::EndRNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::ProgramRNode;
using rastr::ast::ProgramRNodeSPtr;
using rastr::parser::SyntaxError;
using rastr::parser::SyntaxErrorSPtr;

SEXP r_rastr_ast_program_r_node_create(SEXP r_begin,
                                       SEXP r_expressions,
                                       SEXP r_end) {
    BeginRNodeSPtr begin = from_sexp<BeginRNode>(r_begin);

    ExpressionSequenceRNodeSPtr expressions =
        from_sexp<ExpressionSequenceRNode>(r_expressions);

    EndRNodeSPtr end = from_sexp<EndRNode>(r_end);

    ProgramRNodeSPtr node =
        std::make_shared<ProgramRNode>(begin, expressions, end);

    return to_sexp<ProgramRNode>(node);
}

SEXP r_rastr_ast_program_r_node_is_well_formed(SEXP r_node) {
    ProgramRNodeSPtr node = from_sexp<ProgramRNode>(r_node);

    bool well_formed = node->is_well_formed();

    return ScalarLogical(well_formed);
}

SEXP r_rastr_ast_program_r_node_get_syntax_error(SEXP r_node) {
    ProgramRNodeSPtr node = from_sexp<ProgramRNode>(r_node);

    SyntaxErrorSPtr syntax_error = node->get_syntax_error();

    return to_sexp<SyntaxError>(syntax_error);
}

SEXP r_rastr_ast_program_r_node_set_syntax_error(SEXP r_node,
                                                 SEXP r_syntax_error) {
    ProgramRNodeSPtr node = from_sexp<ProgramRNode>(r_node);

    SyntaxErrorSPtr syntax_error = from_sexp<SyntaxError>(r_syntax_error);

    node->set_syntax_error(syntax_error);

    return r_node;
}
