#ifndef RASTR_I_NAME_RNODE_HPP
#define RASTR_I_NAME_RNODE_HPP

#include "SymbolRNode.hpp"

namespace rastr {
namespace ast {

class IName {
  public:
    explicit IName(SymbolRNodeSPtr name): name_(name) {
    }

    virtual ~IName() = default;

    SymbolRNodeSPtr get_name() const {
        return name_;
    }

    void set_name(SymbolRNodeSPtr name) {
        name_ = name;
    }

  private:
    SymbolRNodeSPtr name_;
};

using INameSPtr = std::shared_ptr<IName>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_NAME_RNODE_HPP */
