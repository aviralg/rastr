#ifndef RASTR_AST_SPACING_RNODE_HPP
#define RASTR_AST_SPACING_RNODE_HPP

#include "RNode.hpp"

namespace rastr {
namespace ast {

class SpacingRNode: public RNode {
  public:
    explicit SpacingRNode(): RNode(Type::SpacingRNode) {
    }

    int get_size() const {
        return spacing_.size();
    }

    const std::string& get_spaces(int index) const {
        return spacing_[index];
    }

    std::string& get_spaces(int index) {
        return spacing_[index];
    }

    void set_spaces(int index, const std::string& spaces) {
        spacing_[index] = spaces;
    }

    void push_back(const std::string& spaces) {
        spacing_.push_back(spaces);
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::vector<std::string> spacing_;

    static SEXP class_;
};

using SpacingRNodeSPtr = std::shared_ptr<SpacingRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_SPACING_RNODE_HPP */
