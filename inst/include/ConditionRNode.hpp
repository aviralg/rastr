#ifndef RASTR_AST_CONDITION_RNODE_HPP
#define RASTR_AST_CONDITION_RNODE_HPP

#include "RNode.hpp"
#include "IBounded.hpp"

namespace rastr {
namespace ast {

class ConditionRNode
    : public RNode
    , public IBounded {
  public:
    explicit ConditionRNode(Type type,
                            DelimiterRNodeSPtr opening_delimiter,
                            DelimiterRNodeSPtr closing_delimiter)
        : RNode(type), IBounded(opening_delimiter, closing_delimiter) {
    }
};

using ConditionRNodeSPtr = std::shared_ptr<ConditionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_CONDITION_RNODE_HPP */
