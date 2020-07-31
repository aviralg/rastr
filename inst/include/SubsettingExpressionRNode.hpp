#ifndef RASTR_AST_SUBSETTING_EXPRESSION_RNODE_HPP
#define RASTR_AST_SUBSETTING_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IBounded.hpp"
#include "IObject.hpp"
#include "IIndices.hpp"
#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class SubsettingExpressionRNode
    : public ExpressionRNode
    , public IObject
    , public IBounded
    , public IIndices {
  public:
    SubsettingExpressionRNode(ExpressionRNodeSPtr object,
                              DelimiterRNodeSPtr opening_delimiter,
                              ExpressionSequenceRNodeSPtr indices,
                              DelimiterRNodeSPtr closing_delimiter)
        : ExpressionRNode()
        , IObject(object)
        , IBounded(opening_delimiter, closing_delimiter)
        , IIndices(indices) {
        set_type(Type::SubsettingExpressionRNode);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using SubsettingExpressionRNodeSPtr =
    std::shared_ptr<SubsettingExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_SUBSETTING_EXPRESSION_RNODE_HPP */
