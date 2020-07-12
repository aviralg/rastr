#ifndef RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP
#define RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP

#include "DelimitedRNode.hpp"
#include "ExpressionRNode.hpp"
#include "SeparatorRNode.hpp"

namespace rastr {
namespace ast {

class ExpressionSequenceRNode: public DelimitedRNode {
  public:
    explicit ExpressionSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                     DelimiterRNodeSPtr closing_delimiter)
        : DelimitedRNode(opening_delimiter, closing_delimiter) {
    }

    ExpressionRNodeSPtr get_expression(int index) const {
        return expressions_[index];
    }

    SeparatorRNodeSPtr get_separator(int index) const {
        return separators_[index];
    }

    void set_expression(int index, ExpressionRNodeSPtr expression) {
        expressions_[index] = expression;
    }

    void set_separator(int index, SeparatorRNodeSPtr separator) {
        separators_[index] = separator;
    }

    void append(SeparatorRNodeSPtr separator, ExpressionRNodeSPtr expression) {
        separators_.push_back(separator);
        expressions_.push_back(expression);
    }

    int get_size() const {
        return expressions_.size();
    }

  private:
    std::vector<ExpressionRNodeSPtr> expressions_;
    std::vector<SeparatorRNodeSPtr> separators_;
}; // namespace ast

using ExpressionSequenceRNodeSPtr = std::shared_ptr<ExpressionSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP */
