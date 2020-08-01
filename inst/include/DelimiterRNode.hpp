#ifndef RASTR_AST_DELIMITER_RNODE_HPP
#define RASTR_AST_DELIMITER_RNODE_HPP

#include "RNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class DelimiterRNode
    : public RNode
    , public IRepresentation {
  public:
    explicit DelimiterRNode(const std::string& representation)
        : RNode(Type::DelimiterRNode), IRepresentation(representation) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using DelimiterRNodeSPtr = std::shared_ptr<DelimiterRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_DELIMITER_RNODE_HPP */
