#ifndef RASTR_I_EXPRESSIONS_RNODE_HPP
#define RASTR_I_EXPRESSIONS_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class IExpressions {
  public:
    explicit IExpressions(ExpressionSequenceRNodeSPtr expressions)
        : expressions_(expressions) {
    }

    virtual ~IExpressions() = default;

    ExpressionSequenceRNodeSPtr get_expressions() const {
        return expressions_;
    }

    void set_expressions(ExpressionSequenceRNodeSPtr expressions) {
        expressions_ = expressions;
    }

  private:
    ExpressionSequenceRNodeSPtr expressions_;
};

using IExpressionsSPtr = std::shared_ptr<IExpressions>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_EXPRESSIONS_RNODE_HPP */
