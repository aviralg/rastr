#ifndef RASTR_AST_FILE_RNODE_HPP
#define RASTR_AST_FILE_RNODE_HPP

#include "RNode.hpp"
#include "ProgramRNode.hpp"

namespace rastr {
namespace ast {

class FileRNode: public RNode {
  public:
    FileRNode(const std::string& filepath, ProgramRNodeSPtr program)
        : RNode(Type::FileRNode), filepath_(filepath), program_(program) {
    }

    ~FileRNode() = default;

    const std::string& get_filepath() const {
        return filepath_;
    }

    void set_filepath(const std::string& filepath) {
        filepath_ = filepath;
    }

    void set_program(ProgramRNodeSPtr program) {
        program_ = program;
    }

    ProgramRNodeSPtr get_program() const {
        return program_;
    }

    static void initialize();

    static void finalize();

    static SEXP get_class();

  private:
    std::string filepath_;
    ProgramRNodeSPtr program_;

    static SEXP class_;
};

using FileRNodeSPtr = std::shared_ptr<FileRNode>;

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_FILE_RNODE_HPP */
