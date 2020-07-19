#include "IndexingExpressionRNode.hpp"

namespace rastr {
namespace ast {

SEXP IndexingExpressionRNode::class_ = NULL;

void IndexingExpressionRNode::initialize() {
    class_ = rastr::create_class({"rastr_node_r_expression_indexing",
                                  "rastr_node_r_expression",
                                  "rastr_node_r",
                                  "rastr_node"});
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
