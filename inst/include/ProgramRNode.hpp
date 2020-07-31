#ifndef RASTR_AST_PROGRAM_RNODE_HPP
#define RASTR_AST_PROGRAM_RNODE_HPP

#include "RNode.hpp"
#include "BeginRNode.hpp"
#include "IExpressions.hpp"
#include "EndRNode.hpp"
#include "SyntaxError.hpp"

namespace rastr {
namespace ast {

class ProgramRNode
    : public RNode
    , public IExpressions {
  public:
    ProgramRNode(BeginRNodeSPtr begin,
                 ExpressionSequenceRNodeSPtr expressions,
                 EndRNodeSPtr end)
        : RNode(Type::ProgramRNode)
        , IExpressions(expressions)
        , begin_(begin)
        , end_(end) {
    }

    ~ProgramRNode() = default;

    bool is_program_node() const override {
        return true;
    }

    bool is_well_formed() const {
        return syntax_error_.is_valid();
    }

    rastr::r::parser::SyntaxError get_syntax_error() const {
        return syntax_error_;
    }

    void set_syntax_error(const rastr::r::parser::SyntaxError& syntax_error) {
        syntax_error_ = syntax_error;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    BeginRNodeSPtr begin_;
    EndRNodeSPtr end_;

    rastr::r::parser::SyntaxError syntax_error_;

    static SEXP class_;
};

using ProgramRNodeSPtr = std::shared_ptr<ProgramRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_PROGRAM_RNODE_HPP */
