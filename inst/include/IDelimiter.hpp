#ifndef RASTR_AST_I_DELIMITER_HPP
#define RASTR_AST_I_DELIMITER_HPP

#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

class IDelimiter {
  public:
    IDelimiter(DelimiterRNodeSPtr delimiter): delimiter_(delimiter) {
    }

    virtual ~IDelimiter() = default;

    DelimiterRNodeSPtr get_delimiter() const {
        return delimiter_;
    }

    void set_delimiter(DelimiterRNodeSPtr delimiter) {
        delimiter_ = delimiter;
    }

  private:
    DelimiterRNodeSPtr delimiter_;
};

using IDelimiterSPtr = std::shared_ptr<IDelimiter>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_I_DELIMITER_HPP */
