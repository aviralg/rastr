#ifndef RASTR_AST_PARAMETER_RNODE_HPP
#define RASTR_AST_PARAMETER_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class ParameterRNode: public RNode {
  public:
    explicit ParameterRNode(Type type): RNode(type) {
    }

    virtual ~ParameterRNode() = default;
};

using ParameterRNodeSPtr = std::shared_ptr<ParameterRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_PARAMETER_RNODE_HPP */
