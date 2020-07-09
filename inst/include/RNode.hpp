#ifndef RASTR_AST_RNODE_HPP
#define RASTR_AST_RNODE_HPP

#include "Node.hpp"

namespace rastr {
namespace ast {

class RNode: public virtual Node {
  public:
    RNode(): Node() {
    }

    virtual ~RNode() {
    }

    rastr::ast::Language get_language() const override {
        return Language::R;
    }
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_RNODE_HPP */
