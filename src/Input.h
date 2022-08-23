#ifndef RASTR_INPUT_H
#define RASTR_INPUT_H

#include <cstring>
#include <string>
#include <cstdint>
#include <cwctype>
#include "StringView.h"

// Copyright (c) 2008-2009 Bjoern Hoehrmann <bjoern@hoehrmann.de>
// See http://bjoern.hoehrmann.de/utf-8/decoder/dfa/ for details.

#define UTF8_ACCEPT 0
#define UTF8_REJECT 1

static const std::uint8_t utf8d[] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 00..1f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 20..3f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 40..5f
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, // 60..7f
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9, // 80..9f
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7, // a0..bf
  8,8,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, // c0..df
  0xa,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x3,0x4,0x3,0x3, // e0..ef
  0xb,0x6,0x6,0x6,0x5,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8, // f0..ff
  0x0,0x1,0x2,0x3,0x5,0x8,0x7,0x1,0x1,0x1,0x4,0x6,0x1,0x1,0x1,0x1, // s0..s0
  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,1, // s1..s2
  1,2,1,1,1,1,1,2,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1, // s3..s4
  1,2,1,1,1,1,1,1,1,2,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,3,1,1,1,1,1,1, // s5..s6
  1,3,1,1,1,1,1,3,1,3,1,1,1,1,1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,1,1,1, // s7..s8
};

/*
UTF-8 is a variable length character encoding. To decode a character one or more
bytes have to be read from a string. The decode function implements a single
step in this process. It takes two parameters maintaining state and a byte, and
returns the state achieved after processing the byte. Specifically, it returns
the value UTF8_ACCEPT (0) if enough bytes have been read for a character,
UTF8_REJECT (12) if the byte is not allowed to occur at its position, and some
other positive value if more bytes have to be read.

When decoding the first byte of a string, the caller must set the state variable
to UTF8_ACCEPT. If, after decoding one or more bytes the state UTF8_ACCEPT is
reached again, then the decoded Unicode character value is available through the
codep parameter. If the state UTF8_REJECT is entered, that state will never be
exited unless the caller intervenes. See the examples below for more information
on usage and error handling, and the section on implementation details for how
the decoder is constructed.
*/

std::uint32_t inline
decode(std::uint32_t* state, std::uint32_t* codep, std::uint32_t byte) {
    std::uint32_t type = utf8d[byte];

  *codep = (*state != UTF8_ACCEPT) ?
    (byte & 0x3fu) | (*codep << 6) :
    (0xff >> type) & (byte);

  *state = utf8d[256 + *state*16 + type];
  return *state;
}

/* treats a string as a sequence of characters followed by infinitely many EOFs
 */
class Input {
  public:
    int Eof = INT_MAX;

    /* input is a non-owning pointer to a character sequence */
    Input(const std::uint8_t* input, std::size_t length)
        : input_(input)
        , length_(length)
        , index_(0)
        , row_(0)
        , col_(0)
        , chr_(0)
        , byte_(0) {
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
        inc_index_();
        return c;
    }

    /* true if input has 'ch' as the next character */
    bool read_char_if(int ch) {
        if (ch == peek_char_next_()) {
            if (ch != Eof)
                inc_index_();
            return true;
        }
        return false;
    }

    bool read_char_if_any(char c1, char c2, char c3) {
        int c = peek_char_next_();

        if (c == c1 || c == c2 || c == c3) {
            if (c != Eof)
                inc_index_();
            return true;
        }

        return false;
    }

    /* Read consecutive occurrences of ch. No need to deal with utf8 here since
       we are only checking for consecutive occurrences of ascii ch. */
    std::size_t read_char_while(char ch) {
        std::size_t count = 0;

        while (!end() && input_[index_] == ch) {
            inc_index_();
            ++count;
        }

        return count;
    }

    /* stop reading when ch is found, check for utf8 characters */
    std::size_t read_identifier() {
        std::size_t count = 0;
        std::uint32_t codepoint;
        int bytes;

        while (!end()) {
            codepoint = read_utf8_char(&bytes);

            if (codepoint != '.' && codepoint != '_' &&
                !std::iswalnum((std::wint_t) codepoint)) {
                index_ -= bytes;
                break;
            }

            /* each utf8 char contributes one col_, one chr_, and bytes worth of
             * byte_ */
            ++col_;
            ++chr_;
            byte_ += bytes;
            ++count;
        }
        return count;
    }

    bool is_walpha() {
        int bytes;
        std::uint32_t codepoint = read_utf8_char(&bytes);
        index_ -= bytes;
        return std::iswalpha((std::wint_t) codepoint);
    }

    std::uint32_t read_utf8_char(int* bytes) {
        uint32_t codepoint = 0;
        uint32_t state = UTF8_ACCEPT;

        *bytes = index_;

        while (true) {
            decode(&state, &codepoint, input_[index_]);
            index_++;

            switch (state) {
            case UTF8_ACCEPT:
                *bytes = index_ - *bytes;
                return codepoint;
                break;

            case UTF8_REJECT:
                /* TODO: improve error message */
                Rf_error("invalid UTF-8 character encountered");
                break;

            default:
                continue;
                break;
            }
        }
    }

    void inc_loc(int bytes) {
        ++col_;
        ++chr_;
        byte_ += bytes;
    }

    /* stop reading when ch is found, check for utf8 characters */
    std::size_t read_char_while_not(char ch) {
        std::size_t count = 0;
        int bytes;
        std::uint32_t chr = (std::uint32_t) ch;

        while (!end()) {
            if (read_utf8_char(&bytes) == chr) {
                /* unread ch which is 1 byte by design and exit loop */
                index_ -= 1;
                break;
            }
            /* each utf8 char contributes one col_, one chr_, and bytes worth of
             * byte_ */
            ++col_;
            ++chr_;
            byte_ += bytes;
            ++count;
        }

        return count;
    }

    /* compare length characters of 'str' with the input starting at 'index',
       undefined behavior on reading past input */
    int equal(const char* str, std::size_t index, std::size_t length) const {
        if (index + length <= length_) {
            return strncmp((const char*)input_ + index, str, length) == 0;
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
        return StringView((const char*)input_, left_index, right_index);
    }

    StringView get_view(std::size_t length) const {
        return StringView((const char*)input_, length);
    }

    StringView view_at(std::size_t left_index) const {
        return StringView((const char*)input_, left_index, index_);
    }

    void rewind() {
        if (index_ > 0) {
            dec_index_();
        }
    }

    void next_line(int count = 1) {
        row_ += count;
        col_ = 0;
    }

    void get_pos(int* row, int* col, int* chr, int* byte) {
        *row = row_;
        *col = col_;
        *chr = chr_;
        *byte = byte_;
    }

  private:
    const std::uint8_t* input_;
    const std::size_t length_;
    std::size_t index_;

    int row_;
    int col_;
    int chr_;
    int byte_;
    /* size in bytes of the last char read from the input stream, used by
       rewind */
    int last_chr_size_;

    int peek_char_at_(std::size_t index) const {
        if (index >= length_) {
            return Eof;
        }

        return input_[index];
    }

    int peek_char_next_() const {
        return peek_char_at_(index_);
    }

    void inc_index_() {
        ++col_;
        ++chr_;
        ++byte_;
        ++index_;
    }

    void dec_index_() {
        --col_;
        --chr_;
        --byte_;
        --index_;
    }
};

#endif /* RASTR_INPUT_H */
