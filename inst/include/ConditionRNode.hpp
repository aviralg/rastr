#ifndef RASTR_AST_CONDITION_RNODE_HPP
#define RASTR_AST_CONDITION_RNODE_HPP

#include "BoundedRNode.hpp"

namespace rastr {
namespace ast {

class ConditionRNode: public BoundedRNode {
  public:
    explicit ConditionRNode(DelimiterRNodeSPtr opening_delimiter,
                            RNodeSPtr condition,
                            DelimiterRNodeSPtr closing_delimiter)
        : BoundedRNode(opening_delimiter, closing_delimiter)
        , condition_(condition) {
    }

    RNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(RNodeSPtr condition) {
        condition_ = condition;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    RNodeSPtr condition_;

    static SEXP class_;
};

using ConditionRNodeSPtr = std::shared_ptr<ConditionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONDITION_RNODE_HPP */