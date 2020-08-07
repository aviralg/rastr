#ifndef RASTR_AST_SYMBOL_RNODE_HPP
#define RASTR_AST_SYMBOL_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class SymbolRNode: public RNode {
  public:
    explicit SymbolRNode(const std::string& representation, bool quoted)
        : RNode(Type::SymbolRNode)
        , representation_(representation)
        , quoted_(quoted) {
    }

    const std::string& get_representation() const {
        return representation_;
    }

    void set_representation(const std::string& representation) {
        representation_ = representation;
    }

    bool is_quoted() const {
        return quoted_;
    }

    void set_quoted(bool quoted) {
        quoted_ = quoted;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::string representation_;
    bool quoted_;

    static SEXP class_;
};

using SymbolRNodeSPtr = std::shared_ptr<SymbolRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_SYMBOL_RNODE_HPP */
