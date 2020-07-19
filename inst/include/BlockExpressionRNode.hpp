#ifndef RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP
#define RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class BlockExpressionRNode
    : public ExpressionSequenceRNode
    , public ExpressionRNode {
  public:
    explicit BlockExpressionRNode(DelimiterRNodeSPtr opening_delimiter,
                                  DelimiterRNodeSPtr closing_delimiter)
        : ExpressionSequenceRNode(opening_delimiter, closing_delimiter)
        , ExpressionRNode() {
        set_type(Type::BlockExpressionRNode);
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
