#ifndef RASTR_AST_BOUNDED_HPP
#define RASTR_AST_BOUNDED_HPP

#include "DelimiterRNode.hpp"

namespace rastr {
namespace ast {

class IBounded {
  public:
    IBounded(DelimiterRNodeSPtr opening_delimiter,
             DelimiterRNodeSPtr closing_delimiter)
        : opening_delimiter_(opening_delimiter)
        , closing_delimiter_(closing_delimiter) {
    }

    virtual ~IBounded() = default;

    DelimiterRNodeSPtr get_opening_delimiter() const {
        return opening_delimiter_;
    }

    void set_opening_delimiter(DelimiterRNodeSPtr opening_delimiter) {
        opening_delimiter_ = opening_delimiter;
    }

    DelimiterRNodeSPtr get_closing_delimiter() const {
        return closing_delimiter_;
    }

    void set_closing_delimiter(DelimiterRNodeSPtr closing_delimiter) {
        closing_delimiter_ = closing_delimiter;
    }

    void set_delimiters(DelimiterRNodeSPtr opening_delimiter,
                        DelimiterRNodeSPtr closing_delimiter) {
        set_opening_delimiter(opening_delimiter);
        set_closing_delimiter(closing_delimiter);
    }

  private:
    DelimiterRNodeSPtr opening_delimiter_;
    DelimiterRNodeSPtr closing_delimiter_;
};

using IBoundedSPtr = std::shared_ptr<IBounded>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_BOUNDED_HPP */
