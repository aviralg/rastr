#ifndef RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP
#define RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"
#include "KeywordRNode.hpp"
#include "IBounded.hpp"

namespace rastr {
namespace ast {

class FunctionCallExpressionRNode
    : public ExpressionRNode
    , public IBounded {
  public:
    explicit FunctionCallExpressionRNode(ExpressionRNodeSPtr function,
                                         DelimiterRNodeSPtr opening_delimiter,
                                         ExpressionSequenceRNodeSPtr arguments,
                                         DelimiterRNodeSPtr closing_delimiter)
        : ExpressionRNode()
        , IBounded(opening_delimiter, closing_delimiter)
        , function_(function)
        , arguments_(arguments) {
        set_type(Type::FunctionCallExpressionRNode);
    }

    ExpressionRNodeSPtr get_function() const {
        return function_;
    }

    void set_function(ExpressionRNodeSPtr function) {
        function_ = function;
    }

    ExpressionSequenceRNodeSPtr get_arguments() const {
        return arguments_;
    }

    void set_arguments(ExpressionSequenceRNodeSPtr arguments) {
        arguments_ = arguments;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ExpressionRNodeSPtr function_;
    ExpressionSequenceRNodeSPtr arguments_;

    static SEXP class_;
}; // namespace ast

using FunctionCallExpressionRNodeSPtr =
    std::shared_ptr<FunctionCallExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP */
