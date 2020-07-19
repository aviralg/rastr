#ifndef RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP
#define RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"
#include "IndexSequenceRNode.hpp"

namespace rastr {
namespace ast {

class IndexingExpressionRNode: public ExpressionRNode {
  public:
    IndexingExpressionRNode(ExpressionRNodeSPtr body,
                            IndexSequenceRNodeSPtr indices)
        : ExpressionRNode(), body_(body), indices_(indices) {
        set_type(Type::IndexingExpressionRNode);
    }

    ExpressionRNodeSPtr get_body() const {
        return body_;
    }

    void set_body(ExpressionRNodeSPtr body) {
        body_ = body;
    }

    IndexSequenceRNodeSPtr get_index_expressions() const {
        return indices_;
    }

    void set_indices(IndexSequenceRNodeSPtr indices) {
        indices_ = indices;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr body_;
    IndexSequenceRNodeSPtr indices_;

    static SEXP class_;
};

using IndexingExpressionRNodeSPtr = std::shared_ptr<IndexingExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_INDEXING_EXPRESSION_RNODE_HPP */
