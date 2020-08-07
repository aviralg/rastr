#include "SymbolRNode.hpp"

namespace rastr {
namespace ast {

SEXP SymbolRNode::class_ = NULL;

void SymbolRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_symbol", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void SymbolRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP SymbolRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
