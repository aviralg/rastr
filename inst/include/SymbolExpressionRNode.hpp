#ifndef RASTR_AST_SYMBOL_EXPRESSION_RNODE_HPP
#define RASTR_AST_SYMBOL_EXPRESSION_RNODE_HPP

#include "ExpressionRNode.hpp"

namespace rastr {
namespace ast {

class SymbolExpressionRNode: public ExpressionRNode {
  public:
    explicit SymbolExpressionRNode(const std::string& representation = "",
                                   bool quoted = false)
        : ExpressionRNode(), representation_(representation), quoted_(quoted) {
        set_type(Type::SymbolExpressionRNode);
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

using SymbolExpressionRNodeSPtr = std::shared_ptr<SymbolExpressionRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_SYMBOL_EXPRESSION_RNODE_HPP */
