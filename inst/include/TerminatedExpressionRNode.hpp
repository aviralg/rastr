#ifndef RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP
#define RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP

#include "IBody.hpp"
#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

class TerminatedExpressionRNode
    : public ExpressionRNode
    , public IBody {
  public:
    explicit TerminatedExpressionRNode(ExpressionRNodeSPtr body,
                                       DelimiterRNodeSPtr delimiter)
        : ExpressionRNode(Type::TerminatedExpressionRNode)
        , IBody(body)
        , delimiter_(delimiter) {
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
    DelimiterRNodeSPtr delimiter_;

    static SEXP class_;
};

using TerminatedExpressionRNodeSPtr =
    std::shared_ptr<TerminatedExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_TERMINATED_EXPRESSION_RNODE_HPP */
