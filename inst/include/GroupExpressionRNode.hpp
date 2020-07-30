#ifndef RASTR_AST_GROUP_EXPRESSION_RNODE_HPP
#define RASTR_AST_GROUP_EXPRESSION_RNODE_HPP

#include "IBounded.hpp"
#include "IBody.hpp"

namespace rastr {
namespace ast {

class GroupExpressionRNode
    : public ExpressionRNode
    , public IBounded
    , public IBody {
  public:
    explicit GroupExpressionRNode(DelimiterRNodeSPtr opening_delimiter,
                                  ExpressionRNodeSPtr body,
                                  DelimiterRNodeSPtr closing_delimiter)
        : ExpressionRNode()
        , IBounded(opening_delimiter, closing_delimiter)
        , IBody(body) {
        set_type(Type::GroupExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using GroupExpressionRNodeSPtr = std::shared_ptr<GroupExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_GROUP_EXPRESSION_RNODE_HPP */
