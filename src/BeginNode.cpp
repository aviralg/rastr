#include "BeginNode.hpp"

namespace rastr {
namespace ast {

SEXP BeginNode::class_ = NULL;

void BeginNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_begin", "rastr_ast_node"});
    R_PreserveObject(class_);
}

void BeginNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP BeginNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
