#ifndef RASTR_AST_SEPARATOR_RNODE_HPP
#define RASTR_AST_SEPARATOR_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class SeparatorRNode: public RNode {
  public:
    explicit SeparatorRNode(const std::string& representation = "")
        : RNode(), representation_(representation) {
        set_type(Type::SeparatorRNode);
    }

    const std::string& get_representation() const {
        return representation_;
    }

    void set_representation(const std::string& representation) {
        representation_ = representation;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::string representation_;

    static SEXP class_;
};

using SeparatorRNodeSPtr = std::shared_ptr<SeparatorRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_SEPARATOR_RNODE_HPP */
