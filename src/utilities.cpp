#include "utilities.h"
#include <cstring>
#include <fstream>
#include <cstdio>
#include "logger.h"

void* malloc_or_fail(std::size_t size) {
    void* ptr = std::malloc(size);

    if (ptr == nullptr) {
        fail_with("failed to allocate %zu bytes", size);
    }
    return ptr;
}

void* realloc_or_fail(void* ptr, std::size_t size) {
    void* new_ptr = std::realloc(ptr, size);

    if (new_ptr == nullptr) {
        fail_with("failed to reallocate to %zu bytes", size);
    }
    return new_ptr;
}

bool file_exists(const char* filepath) {
    std::ifstream file(filepath);
    return file.good();
}

std::string read_file(const char* filepath) {
    /* open file in binary mode so seekg is meaningful */
    std::ifstream file(filepath, std::ios::in | std::ios::binary);

    /* if opening file fails, exit with error */
    if (!file) {
        fail_with("received error '%s' while opening file '%s'",
                  std::strerror(errno),
                  filepath)
    }

    std::string contents;

    /* allocate space for reading file contents */
    file.seekg(0, std::ios::end);
    contents.resize(file.tellg());
    file.seekg(0, std::ios::beg);

    /* read file contents */
    file.read(&contents[0], contents.size());

    /* close file */
    file.close();

    return contents;
}

const std::size_t STR_BUFFER_SIZE = 10000;
char str_buffer[STR_BUFFER_SIZE];

const char* bufprintf(const char* fmt, ...) {
    std::va_list args;

    va_start(args, fmt);
    vbufprintf(fmt, args);
    va_end(args);

    return str_buffer;
}

const char* vbufprintf(const char* fmt, std::va_list args) {
    vsnprintf(str_buffer, STR_BUFFER_SIZE, fmt, args);
    return str_buffer;
}

const char* int_to_string(int value) {
    snprintf(str_buffer, STR_BUFFER_SIZE, "%d", value);
    return str_buffer;
}
