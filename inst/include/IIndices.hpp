#ifndef RASTR_I_INDEX_RNODE_HPP
#define RASTR_I_INDEX_RNODE_HPP

#include "ExpressionSequenceRNode.hpp"

namespace rastr {
namespace ast {

class IIndices {
  public:
    explicit IIndices(ExpressionSequenceRNodeSPtr indices): indices_(indices) {
    }

    virtual ~IIndices() = default;

    ExpressionSequenceRNodeSPtr get_indices() const {
        return indices_;
    }

    void set_indices(ExpressionSequenceRNodeSPtr indices) {
        indices_ = indices;
    }

  private:
    ExpressionSequenceRNodeSPtr indices_;
};

} // namespace ast
} // namespace rastr

#endif /* RASTR_I_INDEX_RNODE_HPP */
