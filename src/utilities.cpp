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

void* memclone_or_fail(const void* ptr, std::size_t size) {
    if (ptr == nullptr || size == 0) {
        return nullptr;
    }
    void* new_ptr = malloc_or_fail(size);
    std::memcpy(new_ptr, ptr, size);
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

char* str_dup(const char* str) {
    if (str == nullptr)
        return nullptr;

    int len = std::strlen(str);
    return str_dup(str, len);
}

char* str_dup(const char* str, int len) {
    if (str == nullptr)
        return nullptr;

    int bytes = sizeof(char) * (len + 1);

    char* result = (char*) malloc(bytes);

    std::memcpy(result, str, sizeof(char) * len);

    result[len] = '\0';

    return result;
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

/* https://stackoverflow.com/a/4643526 */
void string_replace(std::string& source,
                    const std::string& pattern,
                    const std::string& replacement) {
    size_t index = 0;
    size_t pat_len = pattern.size();
    size_t rep_len = replacement.size();

    while (true) {
        /* Locate the substring to replace. */
        index = source.find(pattern, index);
        if (index == std::string::npos)
            break;

        /* Make the replacement. */
        source.replace(index, pat_len, replacement);

        /* Advance index forward so the next iteration doesn't pick it up as
         * well. */
        index += rep_len;
    }
}
