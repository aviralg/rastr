#ifndef RASTR_I_OPERATOR_RNODE_HPP
#define RASTR_I_OPERATOR_RNODE_HPP

#include "OperatorRNode.hpp"

namespace rastr {
namespace ast {

class IOperator {
  public:
    IOperator(OperatorRNodeSPtr op): op_(op) {
    }

    virtual ~IOperator() = default;

    OperatorRNodeSPtr get_operator() const {
        return op_;
    }

    void set_operator(OperatorRNodeSPtr op) {
        op_ = op;
    }

  private:
    OperatorRNodeSPtr op_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_OPERATOR_RNODE_HPP */
