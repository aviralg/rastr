#include "ProgramRNode.hpp"

namespace rastr {
namespace ast {

SEXP ProgramRNode::class_ = NULL;

void ProgramRNode::initialize() {
    class_ = rastr::create_class(
        {"rastr_node_r_program", "rastr_node_r", "rastr_node"});
    R_PreserveObject(class_);
}

void ProgramRNode::finalize() {
    R_ReleaseObject(class_);
    class_ = NULL;
}

SEXP ProgramRNode::get_class() {
    return class_;
}

} // namespace ast
} // namespace rastr
