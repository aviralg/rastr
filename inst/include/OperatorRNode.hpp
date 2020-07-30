#ifndef RASTR_AST_OPERATOR_RNODE_HPP
#define RASTR_AST_OPERATOR_RNODE_HPP

#include "RNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class OperatorRNode
    : public RNode
    , public IRepresentation {
  public:
    explicit OperatorRNode(const std::string& representation)
        : RNode(), IRepresentation(representation) {
        set_type(Type::OperatorRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using OperatorRNodeSPtr = std::shared_ptr<OperatorRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_OPERATOR_RNODE_HPP */
