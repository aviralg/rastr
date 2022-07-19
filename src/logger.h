#ifndef RASTR_LOGGER_H
#define RASTR_LOGGER_H

#include <cstdlib>
#include <cstdio>

#define log_msg(fmt, ...) \
    log_raw(stderr, "MESSAGE", __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_warn(fmt, ...) \
    log_raw(stderr, "WARNING", __FILE__, __LINE__, fmt, ##__VA_ARGS__)

#define log_err(fmt, ...) \
    log_raw(stderr, "ERROR", __FILE__, __LINE__, fmt, ##__VA_ARGS__);

#define fail_with(fmt, ...)                                           \
    log_raw(stderr, "ERROR", __FILE__, __LINE__, fmt, ##__VA_ARGS__); \
    std::exit(1);

void log_raw(FILE* fp,
             const char* prefix,
             const char* filename,
             int line,
             const char* fmt,
             ...);

#endif /* RASTR_LOGGER_H */
