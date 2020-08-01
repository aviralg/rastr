#ifndef RASTR_I_CONDITION_RNODE_HPP
#define RASTR_I_CONDITION_RNODE_HPP

#include "ConditionRNode.hpp"

namespace rastr {
namespace ast {

class ICondition {
  public:
    explicit ICondition(ConditionRNodeSPtr condition): condition_(condition) {
    }

    virtual ~ICondition() = default;

    ConditionRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(ConditionRNodeSPtr condition) {
        condition_ = condition;
    }

  private:
    ConditionRNodeSPtr condition_;
};

using IConditionSPtr = std::shared_ptr<ICondition>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_CONDITION_RNODE_HPP */
