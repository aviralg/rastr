#include "EndNode.hpp"

namespace rastr {
namespace ast {

SEXP EndNode::class_ = NULL;

void EndNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_end", "rastr_ast_node"});
    R_PreserveObject(class_);
}

void EndNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP EndNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
