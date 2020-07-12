#ifndef RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP
#define RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class ParameterSequenceRNode: public ExpressionSequenceRNode {
  public:
    explicit ParameterSequenceRNode(DelimiterRNodeSPtr opening_delimiter,
                                    DelimiterRNodeSPtr closing_delimiter)
        : ExpressionSequenceRNode(opening_delimiter, closing_delimiter) {
        set_type(Type::ParameterSequenceRNode);
    }

    ExpressionRNodeSPtr get_parameter(int index) const {
        return get_expression(index);
    }

    void set_parameter(int index, ExpressionRNodeSPtr parameter) {
        set_expression(index, parameter);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
}; // namespace ast

using ParameterSequenceRNodeSPtr = std::shared_ptr<ParameterSequenceRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_PARAMETER_SEQUENCE_RNODE_HPP */
