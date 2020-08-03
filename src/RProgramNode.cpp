#include "RProgramNode.hpp"

namespace rastr {
namespace ast {

SEXP RProgramNode::class_ = NULL;

void RProgramNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_program_r", "rastr_ast_node"});
    R_PreserveObject(class_);
}

void RProgramNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RProgramNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
