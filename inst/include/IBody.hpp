#ifndef RASTR_I_BODY_RNODE_HPP
#define RASTR_I_BODY_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class IBody {
  public:
    explicit IBody(ExpressionRNodeSPtr body): body_(body) {
    }

    virtual ~IBody() = default;

    ExpressionRNodeSPtr get_body() const {
        return body_;
    }

    void set_body(ExpressionRNodeSPtr body) {
        body_ = body;
    }

  private:
    ExpressionRNodeSPtr body_;
};

using IBodySPtr = std::shared_ptr<IBody>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_BODY_RNODE_HPP */
