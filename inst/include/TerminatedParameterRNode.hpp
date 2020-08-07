#ifndef RASTR_AST_TERMINATED_PARAMETER_RNODE_HPP
#define RASTR_AST_TERMINATED_PARAMETER_RNODE_HPP

#include "IDelimiter.hpp"
#include "ParameterRNode.hpp"

namespace rastr {
namespace ast {

class TerminatedParameterRNode
    : public ParameterRNode
    , public IDelimiter {
  public:
    explicit TerminatedParameterRNode(ParameterRNodeSPtr parameter,
                                      DelimiterRNodeSPtr delimiter)
        : ParameterRNode(Type::TerminatedParameterRNode)
        , IDelimiter(delimiter) {
    }

    ParameterRNodeSPtr get_parameter() const {
        return parameter_;
    }

    void set_parameter(ParameterRNodeSPtr parameter) {
        parameter_ = parameter;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    ParameterRNodeSPtr parameter_;

    static SEXP class_;
};

using TerminatedParameterRNodeSPtr = std::shared_ptr<TerminatedParameterRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_TERMINATED_PARAMETER_RNODE_HPP */
