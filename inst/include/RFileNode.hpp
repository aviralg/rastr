#ifndef RASTR_AST_R_FILE_NODE_HPP
#define RASTR_AST_R_FILE_NODE_HPP

#include "Node.hpp"
#include "RProgramNode.hpp"

namespace rastr {
namespace ast {

class RFileNode: public Node {
  public:
    RFileNode(const std::string& filepath, RProgramNodeSPtr program)
        : Node(Type::RFileNode), filepath_(filepath), program_(program) {
    }

    ~RFileNode() = default;

    const std::string& get_filepath() const {
        return filepath_;
    }

    void set_filepath(const std::string& filepath) {
        filepath_ = filepath;
    }

    void set_program(RProgramNodeSPtr program) {
        program_ = program;
    }

    RProgramNodeSPtr get_program() const {
        return program_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::string filepath_;
    RProgramNodeSPtr program_;

    static SEXP class_;
};

using RFileNodeSPtr = std::shared_ptr<RFileNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_R_FILE_NODE_HPP */
