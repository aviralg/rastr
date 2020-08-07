#ifndef RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP
#define RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP

#include "IBounded.hpp"
#include "ParameterRNode.hpp"

namespace rastr {
namespace ast {

class ParameterSequenceRNode: public RNode {
  public:
    explicit ParameterSequenceRNode(): RNode(Type::ParameterSequenceRNode) {
    }

    int get_size() const {
        return elements_.size();
    }

    ParameterRNodeSPtr get_element(int index) const {
        return elements_[index];
    }

    void set_element(int index, ParameterRNodeSPtr element) {
        elements_[index] = element;
    }

    void push_back(ParameterRNodeSPtr element) {
        elements_.push_back(element);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::vector<ParameterRNodeSPtr> elements_;

    static SEXP class_;
}; // namespace ast

using ParameterSequenceRNodeSPtr = std::shared_ptr<ParameterSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP */
