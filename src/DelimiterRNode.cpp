#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

SEXP DelimiterRNode::class_ = NULL;

void DelimiterRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_delimiter",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_representation_i"});
    R_PreserveObject(class_);
}

void DelimiterRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP DelimiterRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
