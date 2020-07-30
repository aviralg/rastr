#ifndef RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP
#define RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

class TerminatedExpressionRNode: public ExpressionRNode {
  public:
    explicit TerminatedExpressionRNode(ExpressionRNodeSPtr expression,
                                       DelimiterRNodeSPtr delimiter)
        : ExpressionRNode(), expression_(expression), delimiter_(delimiter) {
    }

    ExpressionRNodeSPtr get_expression() const {
        return expression_;
    }

    void set_expression(ExpressionRNodeSPtr expression) {
        expression_ = expression;
    }

    DelimiterRNodeSPtr get_delimiter() const {
        return delimiter_;
    }

    void set_delimiter(DelimiterRNodeSPtr delimiter) {
        delimiter_ = delimiter;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr expression_;
    DelimiterRNodeSPtr delimiter_;

    static SEXP class_;
};

using TerminatedExpressionRNodeSPtr =
    std::shared_ptr<TerminatedExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP */
