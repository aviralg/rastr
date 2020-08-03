#ifndef RASTR_AST_BEGIN_NODE_HPP
#define RASTR_AST_BEGIN_NODE_HPP

#include "Node.hpp"

namespace rastr {
namespace ast {

class BeginNode: public Node {
  public:
    explicit BeginNode(): Node(Type::BeginNode) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using BeginNodeSPtr = std::shared_ptr<BeginNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BEGIN_NODE_HPP */
