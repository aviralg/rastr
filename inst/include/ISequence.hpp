#ifndef RASTR_AST_I_SEQUENCE_HPP
#define RASTR_AST_I_SEQUENCE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ISequence {
  public:
    explicit ISequence() {
    }

    virtual ~ISequence() = default;

    ExpressionRNodeSPtr get_expression(int index) const {
        return expressions_[index];
    }

    void set_expression(int index, ExpressionRNodeSPtr expression) {
        expressions_[index] = expression;
    }

    void push_back(ExpressionRNodeSPtr expression) {
        expressions_.push_back(expression);
    }

    int get_size() const {
        return expressions_.size();
    }

  private:
    std::vector<ExpressionRNodeSPtr> expressions_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_I_SEQUENCE_HPP */
