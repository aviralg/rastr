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
    explicit Node(Type type)
        : id_(Node::get_next_id_())
        , r_data_(get_undefined_object())
        , type_(type) {
    }

    virtual ~Node() = default;

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

    Type get_type() const {
        return type_;
    }

    virtual rastr::ast::Language get_language() const {
        return Language::Undefined;
    }

    bool is_r_node() const {
        return get_language() == Language::R;
    }

    bool is_c_node() const {
        return get_language() == Language::C;
    }

    bool is_cpp_node() const {
        return get_language() == Language::CPP;
    }

    virtual bool is_program_node() const {
        return false;
    }

    virtual bool is_expression_node() const {
        return false;
    }

    virtual bool is_literal_expression_node() const {
        return false;
    }

    virtual bool is_loop_expression_node() const {
        return false;
    }

    virtual bool is_arithmetic_node() const {
        return false;
    }

    virtual bool is_unary_operation_node() const {
        return false;
    }

    bool is_character_literal_node() const {
        return get_type() == Type::CharacterLiteralExpressionRNode;
    }

    bool is_integer_literal_node() const {
        return get_type() == Type::IntegerLiteralExpressionRNode;
    }

    bool is_double_literal_node() const {
        return get_type() == Type::DoubleLiteralExpressionRNode;
    }

    bool is_complex_literal_node() const {
        return get_type() == Type::ComplexLiteralExpressionRNode;
    }

    bool is_logical_literal_node() const {
        return get_type() == Type::LogicalLiteralExpressionRNode;
    }

    bool is_file_node() const {
        return get_type() == Type::RFileNode;
    }

  private:
    const int id_;
    SEXP r_data_;
    Type type_;

    static int get_next_id_();
    static std::atomic<int> id_counter_;
};

using NodeSPtr = std::shared_ptr<Node>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_NODE_HPP */
