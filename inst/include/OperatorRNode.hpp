#ifndef RASTR_AST_OPERATOR_RNODE_HPP
#define RASTR_AST_OPERATOR_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class OperatorRNode: public RNode {
  public:
    explicit OperatorRNode(const std::string& representation = "")
        : RNode(), representation_(representation) {
        set_type(Type::OperatorRNode);
    }

    const std::string& get_representation() const {
        return representation_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::string representation_;

    static SEXP class_;
};

using OperatorRNodeSPtr = std::shared_ptr<OperatorRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_OPERATOR_RNODE_HPP */
