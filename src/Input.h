#ifndef RASTR_INPUT_H
#define RASTR_INPUT_H

#include <cstring>
#include <string>
#include "StringView.h"

/* treats a string as a sequence of characters followed by infinitely many EOFs
 */
class Input {
  public:
    int Eof = INT_MAX;

    /* input is a non-owning pointer to a character sequence */
    Input(const char* input, std::size_t length)
        : input_(input), length_(length), index_(0) {
    }

    /* start reading characters from the beginning */
    void reset() {
        index_ = 0;
    }

    /* true if all characters have been read */
    bool end() const {
        return index_ >= length_;
    }

    /* length of the input */
    std::size_t get_length() const {
        return length_;
    }

    /* 0 based index of the next character to be read from the input */
    std::size_t get_index() const {
        return index_;
    }

    /* number of characters read so far */
    std::size_t get_traversed_length() const {
        return index_;
    }

    /* remaining number of characters that can be read */
    std::size_t get_remaining_length() const {
        return length_ - get_traversed_length();
    }

    /* true if the next character in the input is a digit */
    bool is_digit() const {
        return isdigit(peek_char_next_());
    }

    /* true if the next character in the input is an alphabet */
    bool is_alphabet() const {
        return isalpha(peek_char_next_());
    }

    /* true if the next character in the input is a digit or an alphabet */
    bool is_alpha_numeric() const {
        return is_digit() || is_alphabet();
    }

    bool is_hex_digit() const {
        int c = peek_char_next_();
        return isdigit(c) || ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F');
    }

    /* true if c is the next character to be read from the input */
    bool peek_char(char c) const {
        return peek_char_next_() == c;
    }

    /* true if next character is c1 or c2 */
    bool peek_char_any(char c1, char c2) const {
        int c = peek_char_next_();
        return c == c1 || c == c2;
    }

    /* true if next character is c1 or c2 or c3 */
    bool peek_char_any(char c1, char c2, char c3) const {
        int c = peek_char_next_();
        return c == c1 || c == c2 || c == c3;
    }

    /* true if next to next character is c */
    bool peek_next_char(char c) const {
        return peek_char_at_(index_ + 1) == c;
    }

    /* true if next to next character is c1 or c2 */
    bool peek_next_char_any(char c1, char c2) const {
        int c = peek_char_at_(index_ + 1);
        return c == c1 || c == c2;
    }

    /* reads next character from the input */
    int read_char() {
        if (index_ >= length_) {
            return Eof;
        }

        char c = input_[index_];
        ++index_;
        return c;
    }

    /* true if input has 'ch' as the next character */
    bool read_char_if(int ch) {
        if (ch == peek_char_next_()) {
            if (ch != Eof)
                ++index_;
            return true;
        }
        return false;
    }

    bool read_char_if_any(char c1, char c2, char c3) {
        int c = peek_char_next_();

        if (c == c1 || c == c2 || c == c3) {
            if (c != Eof)
                ++index_;
            return true;
        }

        return false;
    }

    /* true if input does not have 'ch' as the next character */
    bool read_char_if_not(int ch) {
        int c = peek_char_next_();

        if (c != ch) {
            if (c != Eof)
                ++index_;
            return true;
        }

        return false;
    }

    /* read consecutive occurrences of ch */
    std::size_t read_char_while(char ch) {
        std::size_t count = 0;

        while (!end() && input_[index_] == ch) {
            ++index_;
            ++count;
        }

        return count;
    }

    /* stop reading when ch is found */
    std::size_t read_char_while_not(int ch) {
        std::size_t count = 0;

        while (!end() && input_[index_] != ch) {
            ++index_;
            ++count;
        }

        return count;
    }

    /* compare length characters of 'str' with the input starting at 'index',
       undefined behavior on reading past input */
    int equal(const char* str, std::size_t index, std::size_t length) const {
        if (index + length <= length_) {
            return strncmp(input_ + index, str, length) == 0;
        }

        else {
            return 0;
        }
    }

    // /* substring of input of size 'length' starting at index,
    //    undefined behavior on reading past input */
    // std::string slice(std::size_t index, std::size_t length) const {
    //     return std::string(input_ + index, length);
    // }

    StringView get_view(std::size_t left_index, std::size_t right_index) const {
        return StringView(input_, left_index, right_index);
    }

    StringView get_view(std::size_t length) const {
        return StringView(input_, length);
    }

  private:
    const char* input_;
    const std::size_t length_;
    std::size_t index_;

    int peek_char_at_(std::size_t index) const {
        if (index >= length_) {
            return Eof;
        }

        return input_[index];
    }

    int peek_char_next_() const {
        return peek_char_at_(index_);
    }
};

#endif /* RASTR_INPUT_H */
