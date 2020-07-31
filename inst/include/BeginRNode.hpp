#ifndef RASTR_AST_BEGIN_RNODE_HPP
#define RASTR_AST_BEGIN_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class BeginRNode: public RNode {
  public:
    explicit BeginRNode(): RNode(Type::BeginRNode) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using BeginRNodeSPtr = std::shared_ptr<BeginRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BEGIN_RNODE_HPP */
