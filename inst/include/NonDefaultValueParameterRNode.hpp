#ifndef RASTR_AST_NON_DEFAULT_VALUE_PARAMETER_RNODE_HPP
#define RASTR_AST_NON_DEFAULT_VALUE_PARAMETER_RNODE_HPP

#include "ParameterRNode.hpp"
#include "IName.hpp"

namespace rastr {
namespace ast {

class NonDefaultValueParameterRNode
    : public ParameterRNode
    , public IName {
  public:
    explicit NonDefaultValueParameterRNode(SymbolRNodeSPtr name)
        : ParameterRNode(Type::NonDefaultValueParameterRNode), IName(name) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using NonDefaultValueParameterRNodeSPtr =
    std::shared_ptr<NonDefaultValueParameterRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_NON_DEFAULT_VALUE_PARAMETER_RNODE_HPP */
