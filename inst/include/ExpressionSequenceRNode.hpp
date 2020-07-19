#ifndef RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP
#define RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP

#include "BoundedRNode.hpp"
#include "ExpressionRNode.hpp"
#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

class ExpressionSequenceRNode: public BoundedRNode {
  public:
    explicit ExpressionSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                     DelimiterRNodeSPtr closing_delimiter)
        : BoundedRNode(opening_delimiter, closing_delimiter) {
    }

    ExpressionRNodeSPtr get_expression(int index) const {
        return expressions_[index];
    }

    DelimiterRNodeSPtr get_delimiter(int index) const {
        return delimiters_[index];
    }

    void set_expression(int index, ExpressionRNodeSPtr expression) {
        expressions_[index] = expression;
    }

    void set_delimiter(int index, DelimiterRNodeSPtr delimiter) {
        delimiters_[index] = delimiter;
    }

    void append(DelimiterRNodeSPtr delimiter, ExpressionRNodeSPtr expression) {
        delimiters_.push_back(delimiter);
        expressions_.push_back(expression);
    }

    int get_size() const {
        return expressions_.size();
    }

  private:
    std::vector<ExpressionRNodeSPtr> expressions_;
    std::vector<DelimiterRNodeSPtr> delimiters_;
}; // namespace ast

using ExpressionSequenceRNodeSPtr = std::shared_ptr<ExpressionSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP */
