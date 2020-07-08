#ifndef RASTR_AST_NODE_HPP
#define RASTR_AST_NODE_HPP

#include "Language.hpp"
#include "rastr.hpp"
#include "Type.hpp"

#include <atomic>
#include <memory>
#include <string>
#include <vector>

namespace rastr {
namespace ast {

class Node {
  public:
    Node(): id_(Node::get_next_id_()), r_data_(get_undefined_object()) {
    }

    int get_id() const {
        return id_;
    }

    void set_data(SEXP r_data) {
        r_data_ = r_data;
        R_PreserveObject(r_data_);
    }

    SEXP get_data() {
        return r_data_;
    }

    void remove_data() {
        R_ReleaseObject(r_data_);
        r_data_ = get_undefined_object();
    }

    bool has_data() const {
        return is_defined_object(r_data_);
    }

    virtual rastr::ast::Language get_language() const = 0;

    virtual rastr::ast::Type get_type() const = 0;

  private:
    const int id_;
    SEXP r_data_;

    static int get_next_id_();
    static std::atomic<int> id_counter_;
};

using NodeSPtr = std::shared_ptr<Node>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_NODE_HPP */
