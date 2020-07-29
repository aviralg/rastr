#ifndef RASTR_AST_END_RNODE_HPP
#define RASTR_AST_END_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class EndRNode: public RNode {
  public:
    explicit EndRNode(): RNode() {
        set_type(Type::EndRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using EndRNodeSPtr = std::shared_ptr<EndRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_END_RNODE_HPP */
