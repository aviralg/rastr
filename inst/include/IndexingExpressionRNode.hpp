#ifndef RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP
#define RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"
#include "IObject.hpp"
#include "IIndices.hpp"

namespace rastr {
namespace ast {

class IndexingExpressionRNode
    : public ExpressionRNode
    , public IObject
    , public IIndices {
  public:
    IndexingExpressionRNode(ExpressionRNodeSPtr object,
                            DelimiterRNodeSPtr opening_delimiter,
                            ExpressionSequenceRNodeSPtr indices,
                            DelimiterRNodeSPtr first_closing_delimiter,
                            DelimiterRNodeSPtr second_closing_delimiter)
        : ExpressionRNode(Type::IndexingExpressionRNode)
        , IObject(object)
        , IIndices(indices)
        , opening_delimiter_(opening_delimiter)
        , first_closing_delimiter_(first_closing_delimiter)
        , second_closing_delimiter_(second_closing_delimiter) {
    }

    DelimiterRNodeSPtr get_opening_delimiter() const {
        return opening_delimiter_;
    }

    void set_opening_delimiter(DelimiterRNodeSPtr opening_delimiter) {
        opening_delimiter_ = opening_delimiter;
    }

    DelimiterRNodeSPtr get_first_closing_delimiter() const {
        return first_closing_delimiter_;
    }

    void
    set_first_closing_delimiter(DelimiterRNodeSPtr first_closing_delimiter) {
        first_closing_delimiter_ = first_closing_delimiter;
    }

    DelimiterRNodeSPtr get_second_closing_delimiter() const {
        return second_closing_delimiter_;
    }

    void
    set_second_closing_delimiter(DelimiterRNodeSPtr second_closing_delimiter) {
        second_closing_delimiter_ = second_closing_delimiter;
    }

    void set_delimiters(DelimiterRNodeSPtr opening_delimiter,
                        DelimiterRNodeSPtr first_closing_delimiter,
                        DelimiterRNodeSPtr second_closing_delimiter) {
        set_opening_delimiter(opening_delimiter);
        set_first_closing_delimiter(first_closing_delimiter);
        set_second_closing_delimiter(second_closing_delimiter);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    DelimiterRNodeSPtr opening_delimiter_;
    DelimiterRNodeSPtr first_closing_delimiter_;
    DelimiterRNodeSPtr second_closing_delimiter_;

    static SEXP class_;
};

using IndexingExpressionRNodeSPtr = std::shared_ptr<IndexingExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP */
