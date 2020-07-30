#ifndef RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP
#define RASTR_AST_BLOCK_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IBounded.hpp"
#include "ExpressionSequence.hpp"

namespace rastr {
namespace ast {

class BlockExpressionRNode
    : public ExpressionRNode
    , public IBounded
    , public ExpressionSequence {
  public:
    explicit BlockExpressionRNode()
        : ExpressionRNode(), IBounded(), ExpressionSequence() {
    }
    explicit BlockExpressionRNode(DelimiterRNodeSPtr opening_delimiter,
                                  DelimiterRNodeSPtr closing_delimiter)
        : BlockExpressionRNode() {
        set_type(Type::BlockExpressionRNode);
        set_delimiters(opening_delimiter, closing_delimiter);
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
