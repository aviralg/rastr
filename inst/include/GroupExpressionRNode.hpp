#ifndef RASTR_AST_GROUP_EXPRESSION_RNODE_HPP
#define RASTR_AST_GROUP_EXPRESSION_RNODE_HPP

#include "BoundedRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class GroupExpressionRNode
    : public BoundedRNode
    , public ExpressionRNode {
  public:
    explicit GroupExpressionRNode(DelimiterRNodeSPtr opening_delimiter,
                                  ExpressionRNodeSPtr expression,
                                  DelimiterRNodeSPtr closing_delimiter)
        : BoundedRNode(opening_delimiter, closing_delimiter)
        , ExpressionRNode()
        , expression_(expression) {
        set_type(Type::GroupExpressionRNode);
    }

    ExpressionRNodeSPtr get_expression() const {
        return expression_;
    }

    void set_expression(ExpressionRNodeSPtr expression) {
        expression_ = expression;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr expression_;

    static SEXP class_;
};

using GroupExpressionRNodeSPtr = std::shared_ptr<GroupExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_GROUP_EXPRESSION_RNODE_HPP */
