#ifndef RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP
#define RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP

#include "LoopExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "DelimitedRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class ForLoopExpressionRNode: public virtual LoopExpressionRNode {
  public:
    explicit ForLoopExpressionRNode(KeywordRNodeSPtr keyword,
                                    DelimitedRNodeSPtr condition,
                                    ExpressionRNodeSPtr body)
        : LoopExpressionRNode(keyword, body) {
        set_type(Type::ForLoopExpressionRNode);
    }

    DelimitedRNodeSPtr get_condition() const {
        return condition_;
    }

    void set_condition(DelimitedRNodeSPtr condition) {
        condition_ = condition;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    DelimitedRNodeSPtr condition_;

    static SEXP class_;
}; // namespace ast

using ForLoopExpressionRNodeSPtr = std::shared_ptr<ForLoopExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FOR_LOOP_EXPRESSION_RNODE_HPP */
