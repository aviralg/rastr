#ifndef RASTR_AST_INDEX_SEQUENCE_RNODE_HPP
#define RASTR_AST_INDEX_SEQUENCE_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class IndexSequenceRNode: public ExpressionSequenceRNode {
  public:
    explicit IndexSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                DelimiterRNodeSPtr closing_delimiter)
        : ExpressionSequenceRNode(opening_delimiter, closing_delimiter) {
        set_type(Type::IndexSequenceRNode);
    }

    ExpressionRNodeSPtr get_index_expression(int index) const {
        return get_expression(index);
    }

    void set_index_expression(int index, ExpressionRNodeSPtr expression) {
        set_expression(index, expression);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
}; // namespace ast

using IndexSequenceRNodeSPtr = std::shared_ptr<IndexSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INDEX_SEQUENCE_RNODE_HPP */
