#ifndef RASTR_I_REPRESENTATION_RNODE_HPP
#define RASTR_I_REPRESENTATION_RNODE_HPP

#include <string>
#include "RNode.hpp"

namespace rastr {
namespace ast {

class IRepresentation {
  public:
    explicit IRepresentation(const std::string& representation)
        : representation_(representation) {
    }

    virtual ~IRepresentation() = default;

    const std::string& get_representation() const {
        return representation_;
    }

  private:
    std::string representation_;
};

using IRepresentationSPtr = std::shared_ptr<IRepresentation>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_REPRESENTATION_RNODE_HPP */
