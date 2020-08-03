#ifndef RASTR_AST_END_NODE_HPP
#define RASTR_AST_END_NODE_HPP

#include "Node.hpp"

namespace rastr {
namespace ast {

class EndNode: public Node {
  public:
    explicit EndNode(): Node(Type::EndNode) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using EndNodeSPtr = std::shared_ptr<EndNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_END_NODE_HPP */
