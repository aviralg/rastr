#ifndef RASTR_AST_SPACING_HPP
#define RASTR_AST_SPACING_HPP

#include <vector>
#include <string>
#include <memory>

namespace rastr {
namespace parser {

class Spacing {
  public:
    Spacing() {
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

  private:
    std::vector<std::string> spacing_;
};

using SpacingSPtr = std::shared_ptr<Spacing>;

} // namespace parser
} // namespace rastr

#endif /* RASTR_AST_SPACING_HPP */
