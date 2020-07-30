#ifndef RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP
#define RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP

#include "IBounded.hpp"
#include "ExpressionRNode.hpp"
#include "ISequence.hpp"

namespace rastr {
namespace ast {

class ExpressionSequenceRNode
    : public RNode
    , public IBounded
    , public ISequence {
  public:
    explicit ExpressionSequenceRNode(): RNode(), IBounded(), ISequence() {
        set_type(Type::ExpressionSequenceRNode);
    }

    explicit ExpressionSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                     DelimiterRNodeSPtr closing_delimiter)
        : ExpressionSequenceRNode() {
        set_delimiters(opening_delimiter, closing_delimiter);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
}; // namespace ast

using ExpressionSequenceRNodeSPtr = std::shared_ptr<ExpressionSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_EXPRESSION_SEQUENCE_RNODE_HPP */
