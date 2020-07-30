#ifndef RASTR_AST_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOOP_EXPRESSION_RNODE_HPP

#include "IBody.hpp"
#include "IKeyword.hpp"

namespace rastr {
namespace ast {

class LoopExpressionRNode
    : public ExpressionRNode
    , public IKeyword
    , public IBody {
  public:
    LoopExpressionRNode(KeywordRNodeSPtr keyword, ExpressionRNodeSPtr body)
        : ExpressionRNode(), IKeyword(keyword), IBody(body) {
    }

    virtual ~LoopExpressionRNode() = default;

    bool is_loop_expression_node() const override {
        return true;
    }
};

using LoopExpressionRNodeSPtr = std::shared_ptr<LoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOOP_EXPRESSION_RNODE_HPP */
