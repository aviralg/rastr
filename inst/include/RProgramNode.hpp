#ifndef RASTR_AST_R_PROGRAM_NODE_HPP
#define RASTR_AST_R_PROGRAM_NODE_HPP

#include "Node.hpp"
#include "BeginNode.hpp"
#include "IExpressions.hpp"
#include "EndNode.hpp"
#include "SyntaxError.hpp"

namespace rastr {
namespace ast {

class RProgramNode
    : public Node
    , public IExpressions {
  public:
    RProgramNode(BeginNodeSPtr begin,
                 ExpressionSequenceRNodeSPtr expressions,
                 EndNodeSPtr end)
        : Node(Type::RProgramNode)
        , IExpressions(expressions)
        , begin_(begin)
        , end_(end) {
    }

    ~RProgramNode() = default;

    bool is_well_formed() const {
        return syntax_error_->is_valid();
    }

    rastr::parser::SyntaxErrorSPtr get_syntax_error() const {
        return syntax_error_;
    }

    void set_syntax_error(const rastr::parser::SyntaxErrorSPtr& syntax_error) {
        syntax_error_ = syntax_error;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    BeginNodeSPtr begin_;
    EndNodeSPtr end_;

    rastr::parser::SyntaxErrorSPtr syntax_error_;

    static SEXP class_;
};

using RProgramNodeSPtr = std::shared_ptr<RProgramNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_PROGRAM_RNODE_HPP */
