#include <rastr/api.h>
#include "r_api.h"
#include "interop.h"
#include <iostream>
#include <sstream>
#include "utilities.h"

class AstSerializer: public AstWalker {
  public:
    AstSerializer(std::iostream* stream): AstWalker(), stream_(stream) {
    }

    void post_op(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_op_syn_get(ast, node);
    }

    void post_bkt(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_bkt_syn_get(ast, node);
    }

    void post_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_dlmtr_syn_get(ast, node);
    }

    void post_null(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_null_syn_get(ast, node);
    }

    void post_lgl(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_lgl_syn_get(ast, node);
    }

    void post_int(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_int_syn_get(ast, node);
    }

    void post_dbl(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_dbl_syn_get(ast, node);
    }

    void post_cpx(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_cpx_syn_get(ast, node);
    }

    void post_chr(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_chr_syn_get(ast, node);
    }

    void post_sym(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_sym_syn_get(ast, node);
    }

    void post_gap(rastr_ast_t ast, rastr_node_t node) override {
        (*stream_) << rastr_gap_val_get(ast, node);
    }

  private:
    std::iostream* stream_;
};

struct ser_data_t {
    std::iostream* stream;
    AstSerializer* serializer;
    rastr_ast_t ast;
    rastr_node_t node;
};

SEXP serialize_str(void* data) {
    char* buffer = nullptr;
    ser_data_t* ser_data = (ser_data_t*) data;

    ser_data->serializer->walk(ser_data->ast, ser_data->node);

    int len = (int) ser_data->stream->tellp();
    buffer = (char*) malloc_or_fail(sizeof(char) * (len + 1));
    ser_data->stream->read(buffer, len);
    buffer[len] = '\0';

    /* is this valid? */
    return (SEXP) buffer;
}

void cleanup_str(void* data) {
    ser_data_t* ser_data = (ser_data_t*) data;
    delete ser_data->serializer;
    delete ser_data->stream;
}

char* rastr_node_unparse_str(rastr_ast_t ast, rastr_node_t node) {
    std::stringstream* stream = new std::stringstream();
    AstSerializer* serializer = new AstSerializer(stream);
    ser_data_t data{stream, serializer, ast, node};
    char* result =
        (char*) R_ExecWithCleanup(serialize_str, &data, cleanup_str, &data);
    return result;
}

char* rastr_ast_unparse_str(rastr_ast_t ast) {
    return rastr_node_unparse_str(ast, rastr_ast_root_get(ast));
}

// void rastr_node_unparse_file(rastr_ast_t ast,
//                              rastr_node_t node,
//                              const char* filepath) {
//     std::stringstream* stream = new std::fstream(filepath);
//     AstSerializer* serializer = new AstSerializer(stream);
//     ser_data_t data{stream, serializer, ast, node};
//     R_ExecWithCleanup(serialize_str, &data, cleanup_str, &data);
// }
//
SEXP r_rastr_ast_unparse_str(SEXP r_ast) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    char* str = rastr_ast_unparse_str(ast);
    SEXP r_str = rastr_str_wrap(str);
    free(str);
    return r_str;
}

SEXP r_rastr_node_unparse_str(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    char* str = rastr_node_unparse_str(ast, node);
    SEXP r_str = rastr_str_wrap(str);
    free(str);
    return r_str;
}
