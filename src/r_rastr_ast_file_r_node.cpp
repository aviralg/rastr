#include "r_rastr_ast_file_r_node.h"
#include "FileRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::FileRNode;
using rastr::ast::FileRNodeSPtr;
using rastr::ast::ProgramRNode;
using rastr::ast::ProgramRNodeSPtr;

SEXP r_rastr_ast_file_r_node_create(SEXP r_filepath, SEXP r_program) {
    const char* filepath = CHAR(asChar(r_filepath));

    ProgramRNodeSPtr program = from_sexp<ProgramRNode>(r_program);

    FileRNodeSPtr node = std::make_shared<FileRNode>(filepath, program);

    return to_sexp<FileRNode>(node);
}

SEXP r_rastr_ast_file_r_node_get_filepath(SEXP r_node) {
    FileRNodeSPtr node = from_sexp<FileRNode>(r_node);

    const std::string& filepath = node->get_filepath();

    return mkString(filepath.c_str());
}

SEXP r_rastr_ast_file_r_node_set_filepath(SEXP r_node, SEXP r_filepath) {
    FileRNodeSPtr node = from_sexp<FileRNode>(r_node);

    const char* filepath = CHAR(asChar(r_filepath));

    node->set_filepath(filepath);

    return r_node;
}

SEXP r_rastr_ast_file_r_node_get_program(SEXP r_node) {
    FileRNodeSPtr node = from_sexp<FileRNode>(r_node);

    ProgramRNodeSPtr program = node->get_program();

    return to_sexp<ProgramRNode>(program);
}

SEXP r_rastr_ast_file_r_node_set_program(SEXP r_node, SEXP r_program) {
    FileRNodeSPtr node = from_sexp<FileRNode>(r_node);

    ProgramRNodeSPtr program = from_sexp<ProgramRNode>(r_program);

    node->set_program(program);

    return r_node;
}
