#ifndef RASTR_UTILITIES_H
#define RASTR_UTILITIES_H

#include <string>
#include <cstdarg>

void* malloc_or_fail(std::size_t size);

void* realloc_or_fail(void* ptr, std::size_t size);

bool file_exists(const char* filepath);

std::string read_file(const char* filepath);

const char* bufprintf(const char* fmt, ...);

const char* vbufprintf(const char* fmt, std::va_list args);

const char* int_to_string(int value);

void string_replace(std::string& source,
                    const std::string& pattern,
                    const std::string& replacement);

#endif /* RASTR_UTILITIES_H */
