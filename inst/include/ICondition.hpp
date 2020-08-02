#ifndef RASTR_I_CONDITION_RNODE_HPP
#define RASTR_I_CONDITION_RNODE_HPP

#include "ExpressionConditionRNode.hpp"

namespace rastr {
namespace ast {

class ICondition {
  public:
    explicit ICondition(ExpressionConditionRNodeSPtr condition)
        : condition_(condition) {
    }

    virtual ~ICondition() = default;

    ExpressionConditionRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(ExpressionConditionRNodeSPtr condition) {
        condition_ = condition;
    }

  private:
    ExpressionConditionRNodeSPtr condition_;
};

using IConditionSPtr = std::shared_ptr<ICondition>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_CONDITION_RNODE_HPP */
