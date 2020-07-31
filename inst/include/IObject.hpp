#ifndef RASTR_I_OBJECT_RNODE_HPP
#define RASTR_I_OBJECT_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IObject {
  public:
    explicit IObject(ExpressionRNodeSPtr object): object_(object) {
    }

    virtual ~IObject() = default;

    ExpressionRNodeSPtr get_object() const {
        return object_;
    }

    void set_object(ExpressionRNodeSPtr object) {
        object_ = object;
    }

  private:
    ExpressionRNodeSPtr object_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_OBJECT_RNODE_HPP */
