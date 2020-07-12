#ifndef RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP
#define RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP

#include "ArgumentSequenceRNode.hpp"
#include "KeywordRNode.hpp"
#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class FunctionCallExpressionRNode: public virtual ExpressionRNode {
  public:
    explicit FunctionCallExpressionRNode(ArgumentSequenceRNodeSPtr arguments,
                                         ExpressionRNodeSPtr function)
        : ExpressionRNode(), arguments_(arguments), function_(function) {
        set_type(Type::FunctionCallExpressionRNode);
    }

    ArgumentSequenceRNodeSPtr get_arguments() const {
        return arguments_;
    }

    void set_arguments(ArgumentSequenceRNodeSPtr arguments) {
        arguments_ = arguments;
    }

    ExpressionRNodeSPtr get_function() const {
        return function_;
    }

    void set_function(ExpressionRNodeSPtr function) {
        function_ = function;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ArgumentSequenceRNodeSPtr arguments_;
    ExpressionRNodeSPtr function_;

    static SEXP class_;
}; // namespace ast

using FunctionCallExpressionRNodeSPtr =
    std::shared_ptr<FunctionCallExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FUNCTION_CALL_EXPRESSION_RNODE_HPP */
