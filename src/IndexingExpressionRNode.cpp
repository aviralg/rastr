#include "IndexingExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IndexingExpressionRNode::class_ = NULL;

void IndexingExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_ast_node_r_expression_indexing",
                                  "rastr_ast_node_r_expression",
                                  "rastr_ast_node_r",
                                  "rastr_ast_node",
                                  "rastr_ast_object_i",
                                  "rastr_ast_indices_i"});
    R_PreserveObject(class_);
}

void IndexingExpressionRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP IndexingExpressionRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
