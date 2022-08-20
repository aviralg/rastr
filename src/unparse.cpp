#include <rastr/api.h>
#include "r_api.h"
#include "interop.h"
#include <iostream>
#include <sstream>
#include "utilities.h"
#include "r_api.h"

class AstSerializer: public AstWalker {
  public:
    AstSerializer(std::iostream* stream): AstWalker(), stream_(stream) {
    }

    virtual void post_op(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_op_syn(ast, node);
    }

    virtual void post_dlmtr(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_delimiter_syntax(ast, node);
    }

    virtual void post_term(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_terminator_syntax(ast, node);
    }

    virtual void post_null(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_null_syntax(ast, node);
    }

    virtual void post_logical(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_logical_syntax(ast, node);
    }

    virtual void post_integer(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_integer_syntax(ast, node);
    }

    virtual void post_real(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_real_syntax(ast, node);
    }

    virtual void post_complex(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_complex_syntax(ast, node);
    }

    virtual void post_string(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_string_syntax(ast, node);
    }

    virtual void post_symbol(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_node_symbol_syntax(ast, node);
    }

    virtual void ws(rastr_ast_t ast, rastr_node_t node) {
        char chr = rastr_ws_chr(ast, node);
        int count = rastr_ws_count(ast, node);
        for (int i = 0; i < count; ++i) {
            stream_->put(chr);
        }
    }

    virtual void cmnt(rastr_ast_t ast, rastr_node_t node) {
        (*stream_) << rastr_cmnt_value(ast, node);
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

    int len = (int) ser_data->stream->tellp() + 1;
    buffer = (char*) malloc_or_fail(sizeof(char) * len);
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
    return rastr_node_unparse_str(ast, rastr_ast_root(ast));
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
