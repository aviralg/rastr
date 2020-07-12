#ifndef RASTR_AST_ARGUMENT_SEQUENCE_RNODE_HPP
#define RASTR_AST_ARGUMENT_SEQUENCE_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class ArgumentSequenceRNode: public ExpressionSequenceRNode {
  public:
    explicit ArgumentSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                   DelimiterRNodeSPtr closing_delimiter)
        : ExpressionSequenceRNode(opening_delimiter, closing_delimiter) {
        set_type(Type::ArgumentSequenceRNode);
    }

    ExpressionRNodeSPtr get_argument(int index) const {
        return get_expression(index);
    }

    void set_argument(int index, ExpressionRNodeSPtr argument) {
        set_expression(index, argument);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
}; // namespace ast

using ArgumentSequenceRNodeSPtr = std::shared_ptr<ArgumentSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_ARGUMENT_SEQUENCE_RNODE_HPP */
