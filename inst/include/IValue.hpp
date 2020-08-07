#ifndef RASTR_I_VALUE_RNODE_HPP
#define RASTR_I_VALUE_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IValue {
  public:
    explicit IValue(ExpressionRNodeSPtr value): value_(value) {
    }

    virtual ~IValue() = default;

    ExpressionRNodeSPtr get_value() const {
        return value_;
    }

    void set_value(ExpressionRNodeSPtr value) {
        value_ = value;
    }

  private:
    ExpressionRNodeSPtr value_;
};

using IValueSPtr = std::shared_ptr<IValue>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_VALUE_RNODE_HPP */
