#ifndef RASTR_AST_LITERAL_RNODE_HPP
#define RASTR_AST_LITERAL_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class LiteralRNode: public virtual RNode {
  public:
    LiteralRNode(): RNode() {
    }
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LITERAL_RNODE_HPP */
