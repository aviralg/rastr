#ifndef RASTR_I_REPRESENTATION_RNODE_HPP
#define RASTR_I_REPRESENTATION_RNODE_HPP

#include <string>

namespace rastr {
namespace ast {

class IRepresentation {
  public:
    IRepresentation(const std::string& representation)
        : representation_(representation) {
    }

    virtual ~IRepresentation() = default;

    const std::string& get_representation() const {
        return representation_;
    }

  private:
    std::string representation_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_REPRESENTATION_RNODE_HPP */
