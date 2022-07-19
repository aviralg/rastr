#include "logger.h"
#include "utilities.h"
#include <cstdarg>
#include <cstdio>

void log_raw(FILE* fp,
             const char* prefix,
             const char* filename,
             int line,
             const char* fmt,
             ...) {
    std::va_list args;
    va_start(args, fmt);
    const char* buf = vbufprintf(fmt, args);
    va_end(args);

    fprintf(fp, "[%s]-[%s:%d] - %s\n", prefix, filename, line, buf);
}
