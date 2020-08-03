#include "r_rastr_ast_r_program_node.h"
#include "RProgramNode.hpp"
#include "r_cast.hpp"

using rastr::ast::BeginNode;
using rastr::ast::BeginNodeSPtr;
using rastr::ast::EndNode;
using rastr::ast::EndNodeSPtr;
using rastr::ast::ExpressionSequenceRNode;
using rastr::ast::ExpressionSequenceRNodeSPtr;
using rastr::ast::RProgramNode;
using rastr::ast::RProgramNodeSPtr;
using rastr::parser::SyntaxError;
using rastr::parser::SyntaxErrorSPtr;

SEXP r_rastr_ast_r_program_node_create(SEXP r_begin,
                                       SEXP r_expressions,
                                       SEXP r_end) {
    BeginNodeSPtr begin = from_sexp<BeginNode>(r_begin);

    ExpressionSequenceRNodeSPtr expressions =
        from_sexp<ExpressionSequenceRNode>(r_expressions);

    EndNodeSPtr end = from_sexp<EndNode>(r_end);

    RProgramNodeSPtr node =
        std::make_shared<RProgramNode>(begin, expressions, end);

    return to_sexp<RProgramNode>(node);
}

SEXP r_rastr_ast_r_program_node_is_well_formed(SEXP r_node) {
    RProgramNodeSPtr node = from_sexp<RProgramNode>(r_node);

    bool well_formed = node->is_well_formed();

    return ScalarLogical(well_formed);
}

SEXP r_rastr_ast_r_program_node_get_syntax_error(SEXP r_node) {
    RProgramNodeSPtr node = from_sexp<RProgramNode>(r_node);

    SyntaxErrorSPtr syntax_error = node->get_syntax_error();

    return to_sexp<SyntaxError>(syntax_error);
}

SEXP r_rastr_ast_r_program_node_set_syntax_error(SEXP r_node,
                                                 SEXP r_syntax_error) {
    RProgramNodeSPtr node = from_sexp<RProgramNode>(r_node);

    SyntaxErrorSPtr syntax_error = from_sexp<SyntaxError>(r_syntax_error);

    node->set_syntax_error(syntax_error);

    return r_node;
}
