#ifndef RASTR_AST_DEFAULT_VALUE_PARAMETER_RNODE_HPP
#define RASTR_AST_DEFAULT_VALUE_PARAMETER_RNODE_HPP

#include "ParameterRNode.hpp"
#include "ExpressionRNode.hpp"
#include "IValue.hpp"
#include "IName.hpp"
#include "IOperator.hpp"

namespace rastr {
namespace ast {

class DefaultValueParameterRNode
    : public ParameterRNode
    , public IOperator
    , public IValue
    , public IName {
  public:
    DefaultValueParameterRNode(OperatorRNodeSPtr op,
                               SymbolRNodeSPtr name,
                               ExpressionRNodeSPtr value)
        : ParameterRNode(Type::DefaultValueParameterRNode)
        , IOperator(op)
        , IValue(value)
        , IName(name) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using DefaultValueParameterRNodeSPtr =
    std::shared_ptr<DefaultValueParameterRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_DEFAULT_VALUE_PARAMETER_RNODE_HPP */
