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
    LoopExpressionRNode(Type type,
                        KeywordRNodeSPtr keyword,
                        ExpressionRNodeSPtr body)
        : ExpressionRNode(type), IKeyword(keyword), IBody(body) {
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
