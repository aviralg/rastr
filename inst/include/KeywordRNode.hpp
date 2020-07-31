#ifndef RASTR_AST_KEYWORD_RNODE_HPP
#define RASTR_AST_KEYWORD_RNODE_HPP

#include "RNode.hpp"
#include "IRepresentation.hpp"

namespace rastr {
namespace ast {

class KeywordRNode
    : public RNode
    , public IRepresentation {
  public:
    explicit KeywordRNode(const std::string& representation)
        : RNode(Type::KeywordRNode), IRepresentation(representation) {
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    static SEXP class_;
};

using KeywordRNodeSPtr = std::shared_ptr<KeywordRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_KEYWORD_RNODE_HPP */
