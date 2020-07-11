#ifndef RASTR_AST_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_LOOP_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "KeywordRNode.hpp"

namespace rastr {
namespace ast {

class LoopExpressionRNode: public virtual ExpressionRNode {
  public:
    LoopExpressionRNode(KeywordRNodeSPtr keyword, ExpressionRNodeSPtr body)
        : ExpressionRNode(), keyword_(keyword), body_(body) {
    }

    virtual ~LoopExpressionRNode() {
    }

    bool is_loop_expression_node() const override {
        return true;
    }

    KeywordRNodeSPtr get_keyword() const {
        return keyword_;
    }

    void set_keyword(KeywordRNodeSPtr keyword) {
        keyword_ = keyword;
    }

    ExpressionRNodeSPtr get_body() const {
        return body_;
    }

    void set_body(ExpressionRNodeSPtr body) {
        body_ = body;
    }

  private:
    KeywordRNodeSPtr keyword_;
    ExpressionRNodeSPtr body_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_LOOP_EXPRESSION_RNODE_HPP */
