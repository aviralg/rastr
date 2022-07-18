#ifndef RASTR_STRING_VIEW
#define RASTR_STRING_VIEW

#include <cstring>

class StringView {
  public:
    StringView(const char* str, const std::size_t length)
        : StringView(str, 0, length) {
    }

    StringView(const char* str): StringView(str, std::strlen(str)) {
    }

    StringView(const char* str,
               const std::size_t left_index,
               const std::size_t right_index)
        : length_(right_index - left_index) {
        str_ = str == nullptr ? nullptr : str + left_index;
    }

    char* materialize(bool null_terminate = true) const {
        if (str_ == nullptr)
            return nullptr;

        /* allocate extra space for terminating null character */
        char* copy = (char*) malloc(sizeof(char) * (length_ + null_terminate));
        /* copy length characters, don't assume str_ is null terminated */
        std::memcpy(copy, str_, sizeof(char) * length_);
        /* explicitly add the terminating null byte */
        if (null_terminate) {
            copy[length_] = '\0';
        }

        return copy;
    }

    static char* duplicate(const char* str) {
        return StringView(str).materialize();
    }

  private:
    const char* str_;
    const std::size_t length_;
};

#endif /* RASTR_STRING_VIEW */
