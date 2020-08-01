#include "KeywordRNode.hpp"

namespace rastr {
namespace ast {

SEXP KeywordRNode::class_ = NULL;

void KeywordRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_keyword",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_representation_i"});
    R_PreserveObject(class_);
}

void KeywordRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP KeywordRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
