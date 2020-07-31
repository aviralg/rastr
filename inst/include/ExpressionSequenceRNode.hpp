#ifndef RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP
#define RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP

#include "IBounded.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ExpressionSequenceRNode: public RNode {
  public:
    explicit ExpressionSequenceRNode(): RNode(Type::ExpressionSequenceRNode) {
    }

    ExpressionRNodeSPtr get_element(int index) const {
        return elements_[index];
    }

    void set_element(int index, ExpressionRNodeSPtr element) {
        elements_[index] = element;
    }

    void push_back(ExpressionRNodeSPtr element) {
        elements_.push_back(element);
    }

    int get_size() const {
        return elements_.size();
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::vector<ExpressionRNodeSPtr> elements_;

    static SEXP class_;
}; // namespace ast

using ExpressionSequenceRNodeSPtr = std::shared_ptr<ExpressionSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP */
