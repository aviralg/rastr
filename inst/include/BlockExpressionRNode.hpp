#ifndef RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP
#define RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP

#include "IBounded.hpp"
#include "IExpressions.hpp"

namespace rastr {
namespace ast {

class BlockExpressionRNode
    : public ExpressionRNode
    , public IBounded
    , public IExpressions {
  public:
    BlockExpressionRNode(DelimiterRNodeSPtr opening_delimiter,
                         ExpressionSequenceRNodeSPtr expressions,
                         DelimiterRNodeSPtr closing_delimiter)
        : ExpressionRNode(Type::BlockExpressionRNode)
        , IBounded(opening_delimiter, closing_delimiter)
        , IExpressions(expressions) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using BlockExpressionRNodeSPtr = std::shared_ptr<BlockExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP */
