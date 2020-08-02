#include "FileRNode.hpp"

namespace rastr {
namespace ast {

SEXP FileRNode::class_ = NULL;

void FileRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_file", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void FileRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP FileRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
