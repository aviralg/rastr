#ifndef RASTR_AST_LITERAL_RNODE_HPP
#define RASTR_AST_LITERAL_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class LiteralRNode: public virtual RNode {
  public:
    LiteralRNode(): RNode() {
    }

    virtual ~LiteralRNode() {
    }

    bool is_literal_node() const override {
        return true;
    }
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LITERAL_RNODE_HPP */
