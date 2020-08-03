#include "r_rastr_ast_r_file_node.h"
#include "RFileNode.hpp"
#include "r_cast.hpp"

using rastr::ast::RFileNode;
using rastr::ast::RFileNodeSPtr;
using rastr::ast::RProgramNode;
using rastr::ast::RProgramNodeSPtr;

SEXP r_rastr_ast_r_file_node_create(SEXP r_filepath, SEXP r_program) {
    const char* filepath = CHAR(asChar(r_filepath));

    RProgramNodeSPtr program = from_sexp<RProgramNode>(r_program);

    RFileNodeSPtr node = std::make_shared<RFileNode>(filepath, program);

    return to_sexp<RFileNode>(node);
}

SEXP r_rastr_ast_r_file_node_get_filepath(SEXP r_node) {
    RFileNodeSPtr node = from_sexp<RFileNode>(r_node);

    const std::string& filepath = node->get_filepath();

    return mkString(filepath.c_str());
}

SEXP r_rastr_ast_r_file_node_set_filepath(SEXP r_node, SEXP r_filepath) {
    RFileNodeSPtr node = from_sexp<RFileNode>(r_node);

    const char* filepath = CHAR(asChar(r_filepath));

    node->set_filepath(filepath);

    return r_node;
}

SEXP r_rastr_ast_r_file_node_get_program(SEXP r_node) {
    RFileNodeSPtr node = from_sexp<RFileNode>(r_node);

    RProgramNodeSPtr program = node->get_program();

    return to_sexp<RProgramNode>(program);
}

SEXP r_rastr_ast_r_file_node_set_program(SEXP r_node, SEXP r_program) {
    RFileNodeSPtr node = from_sexp<RFileNode>(r_node);

    RProgramNodeSPtr program = from_sexp<RProgramNode>(r_program);

    node->set_program(program);

    return r_node;
}
