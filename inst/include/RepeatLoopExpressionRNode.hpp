#ifndef RASTR_AST_REPEAT_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_REPEAT_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "DelimitedRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class RepeatLoopExpressionRNode: public virtual LoopExpressionRNode {
  public:
    explicit RepeatLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                       ExpressionRNodeSPtr body)
        : LoopExpressionRNode(keyword, body) {
        set_type(Type::RepeatLoopExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

    static std::shared_ptr<RepeatLoopExpressionRNode> from_sexp(SEXP r_node);

    static SEXP to_sexp(std::shared_ptr<RepeatLoopExpressionRNode> node);

    static void destroy_sexp(SEXP r_node);

  private:
    static SEXP class_;
}; // namespace ast

using RepeatLoopExpressionRNodeSPtr =
    std::shared_ptr<RepeatLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_REPEAT_LOOP_EXPRESSION_RNODE_HPP */
