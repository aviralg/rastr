#include "RFileNode.hpp"

namespace rastr {
namespace ast {

SEXP RFileNode::class_ = NULL;

void RFileNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_file_r", "rastr_ast_node"});
    R_PreserveObject(class_);
}

void RFileNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP RFileNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
