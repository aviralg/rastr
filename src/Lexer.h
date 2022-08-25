#include "Input.h"
#include <rastr/api.h>
#include "internal_api.h"
#include "logger.h"
#include "interop.h"
#include <vector>

class Lexer {
  public:
    Lexer(Input input, rastr_ast_t ast)
        : input_(input)
        , ast_(ast)
        , context_("")
        , token_saved_(false)
        , eat_lines_(false)
        , beg_(true)
        , lrow_(-1)
        , lcol_(-1)
        , lchr_(-1)
        , lbyte_(-1) {
    }

    rastr_node_t next_token() {
        rastr_node_t token;
        rastr_node_type_t token_type;

    again:
        token = next_token_helper_();
        token_type = rastr_node_type(ast_, token);

        /* Newlines must be handled in a context */
        /* sensitive way.  The following block of */
        /* deals directly with newlines in the */
        /* body of "if" statements. */
        if (token_type == Newline) {
            /* eat newlines while inside a ( or [ context */
            if (should_eat_lines() || peek_context() == '[' ||
                peek_context() == '(') {
                rastr_node_destroy(ast_, token);
                goto again;
            }

            /* The essence of this is that in the body of */
            /* an "if", any newline must be checked to */
            /* see if it is followed by an "else". */
            /* such newlines are discarded. */

            /* this means we are inside if, condition parens have been parsed,
             * and the body is to be parsed next */
            if (peek_context() == 'i') {
                /* Find the next non-newline token */
                /* ignore all newlines until the if body is encountered */
                while (token_type == Newline) {
                    rastr_node_destroy(ast_, token);
                    token = next_token_helper_();
                    token_type = rastr_node_type(ast_, token);
                }

                /* If we encounter "}", ")" or "]" then */
                /* we know that all immediately preceding */
                /* "if" bodies have been terminated. */
                /* The corresponding "i" values are */
                /* popped off the context stack. */

                /* remove all ifs sandwiched between the left delimiter and
                 * right delimiter. the logic stops as soon as a ( or { or [ is
                 * encountered. */
                if (token_type == RightBrace || token_type == RightParen ||
                    token_type == RightBracket) {
                    while (peek_context() == 'i')
                        pop_context_if('i');
                    pop_context();
                    return token;
                }

                /* When a "," is encountered, it terminates */
                /* just the immediately preceding "if" body */
                /* so we pop just a single "i" of the */
                /* context stack. */

                if (token_type == Comma) {
                    pop_context_if('i');
                    return token;
                }

                /* Tricky! If we find an "else" we must */
                /* ignore the preceding newline.  Any other */
                /* token means that we must return the newline */
                /* to terminate the "if" and "push back" that */
                /* token so that we will obtain it on the next */
                /* call to token.  In either case sensitivity */
                /* is lost, so we pop the "i" from the context */
                /* stack. */

                if (token_type == Else) {
                    enable_eat_lines();
                    pop_context_if('i');
                    return token;
                } else {
                    pop_context_if('i');
                    saved_token_ = token;
                    token_saved_ = true;
                    return rastr_node_terminator(
                        ast_, Newline, empty_gap_(), empty_loc_());
                }
            } else {
                return token;
            }
        }

        /* Additional context sensitivities */

        switch (token_type) {
            /* Any newlines immediately following the */
            /* the following tokens are discarded. The */
            /* expressions are clearly incomplete. */

        case Special:

        case Plus:
        case Minus:
        case Multiplication:
        case Division:
        case Power:

        case LessThan:
        case LessThanEqual:
        case GreaterThan:
        case GreaterThanEqual:
        case Equal:
        case NotEqual:

        case Not:
        case And:
        case VecAnd:
        case Or:
        case VecOr:

        case EqualAssign:
        case LeftAssign:
        case RightAssign:
        case LeftSuperAssign:
        case RightSuperAssign:
        case ColonAssign:

        case PipeForward:
        case PipeBind:

        case Range:
        case Formula:
        case Help:

        case SlotExtract:
        case PartExtract:

        case Function:
        case While:
        case Repeat:
        case For:
        case In:
            enable_eat_lines();
            break;

            /* Push any "if" statements found and */
            /* discard any immediately following newlines. */

        case If:
            if (peek_context() == '{' || peek_context() == '[' ||
                peek_context() == '(' || peek_context() == 'i') {
                push_context('i');
            }
            enable_eat_lines();
            break;

            /* Terminate any immediately preceding "if" */
            /* statements and discard any immediately */
            /* following newlines. */

        case Else:
            pop_context_if('i');
            enable_eat_lines();
            break;

            /* These tokens terminate any immediately */
            /* preceding "if" statements. */

        case Semicolon:
        case Comma:
            pop_context_if('i');
            break;

            /* Any newlines following these tokens can */
            /* indicate the end of an expression. */

        case Symbol:
        case String:
        case Integer:
        case Real:
        case Complex:
        case Logical:
        case Null:
        case Next:
        case Break:
            disable_eat_lines();
            break;

            /* Handle brackets, braces and parentheses */
        case DoubleLeftBracket:
            push_context('[');
            push_context('[');
            break;

        case LeftBracket:
            push_context('[');
            break;

        case LeftBrace:
            push_context('{');
            enable_eat_lines();
            break;

        case LeftParen:
            push_context('(');
            break;

        case RightBracket:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            disable_eat_lines();
            break;

        case RightBrace:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            break;

        case RightParen:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            disable_eat_lines();
            break;

        default:
            break;
        }

        return token;
    }

    void enable_eat_lines() {
        eat_lines_ = true;
    }

    void disable_eat_lines() {
        eat_lines_ = false;
    }

  private:
    Input input_;
    rastr_ast_t ast_;
    std::string context_;
    rastr_node_t saved_token_;
    bool token_saved_;
    bool eat_lines_;
    bool beg_;
    int lrow_;
    int lcol_;
    int lchr_;
    int lbyte_;
    rastr_node_t gap_;

    bool should_eat_lines() {
        return eat_lines_;
    }

    void push_context(char c) {
        context_.push_back(c);
    }

    char pop_context() {
        char c = context_.back();
        context_.pop_back();
        return c;
    }

    char peek_context() {
        return context_.back();
    }

    void pop_context_if(char c) {
        if (peek_context() == c)
            pop_context();
    }

    rastr_node_t next_token_helper_() {
        if (token_saved_) {
            token_saved_ = false;
            return saved_token_;
        } else {
            return parse_token_();
        }
    }

    /* this function is implemented as a long if-else ladder. At each step
       of the ladder, the next character in the input stream is checked to
       parse the appropriate token. */
    rastr_node_t parse_token_() {
        /* if token is cached, return it and clear the cache. */
        if (token_saved_) {
            token_saved_ = false;
            return saved_token_;
        }

        save_lloc_();

        if (beg_) {
            beg_ = false;
            return rastr_beg_node(ast_, empty_loc_());
        }

        bool nl = parse_gap_();

        if (nl) {
            return rastr_node_terminator(
                ast_, Newline, empty_gap_(), empty_loc_());
        } else {
            save_lloc_();
        }

        /* return end token if end of input is reached */
        if (input_.end()) {
            return rastr_node_end(ast_, get_gap_(), get_loc_());
        }

        /* since the previous check failed there is at least one character
           in the input stream from this point onwards. */

        /* Either digits or symbols can start with a "." */
        /* so we need to decide which it is and jump to  */
        /* the correct spot. */
        else if (input_.read_char_if('.')) {
            if (input_.is_digit()) {
                return parse_number_('.');
            } else {
                /* this cannot be an operator since it starts with a . so this
                   function bypasses operator checks if the symbol starts
                   with a
                   . */
                input_.rewind();
                return parse_sym_or_op_(true);
            }
        }

        else if (input_.read_char_if('_')) {
            char* temp = StringView("_").materialize();
            return rastr_node_symbol(ast_, temp, temp, get_gap_(), get_loc_());
        }

        /* raw string literal */
        else if (input_.is_digit()) {
            return parse_number_(input_.read_char());
        }

        /* raw string literal */
        else if (input_.peek_char_any('r', 'R') &&
                 input_.peek_next_char_any('"', '\'')) {
            char r = input_.read_char();
            char quote = input_.read_char();

            return parse_raw_string_(r, quote);
        }

        /* literal strings */
        else if (input_.peek_char_any('"', '\'')) {
            return parse_string_(input_.read_char());
        }

        /* special functions */
        else if (input_.read_char_if('%')) {
            return parse_special_('%');
        }

        /* quoted symbols */
        else if (input_.read_char_if('`')) {
            return parse_quoted_symbol_('`');
        }

        /* symbols and operators */
        else if (input_.is_walpha()) {
            return parse_sym_or_op_(false);
        }

        /* operators */

        else if (input_.read_char_if('<')) {
            if (input_.read_char_if('=')) {
                return rastr_op_node(
                    ast_, LessThanEqual, get_gap_(), get_loc_());
            }

            else if (input_.read_char_if('-')) {
                return rastr_op_node(ast_, LeftAssign, get_gap_(), get_loc_());
            }

            else if (input_.read_char_if('<')) {
                if (input_.read_char_if('-')) {
                    return rastr_op_node(
                        ast_, LeftSuperAssign, get_gap_(), get_loc_());
                }
                return rastr_node_error(
                    ast_, "invalid character sequence: <<", get_gap_());
            }
            return rastr_op_node(ast_, LessThan, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('-')) {
            if (input_.read_char_if('>')) {
                if (input_.read_char_if('>')) {
                    return rastr_op_node(
                        ast_, RightSuperAssign, get_gap_(), get_loc_());
                }
                return rastr_op_node(ast_, RightAssign, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, Minus, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('>')) {
            if (input_.read_char_if('=')) {
                return rastr_op_node(
                    ast_, GreaterThanEqual, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, GreaterThan, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('!')) {
            if (input_.read_char_if('=')) {
                return rastr_op_node(ast_, NotEqual, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, Not, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('=')) {
            if (input_.read_char_if('=')) {
                return rastr_op_node(ast_, Equal, get_gap_(), get_loc_());
            }

            else if (input_.read_char_if('>')) {
                return rastr_op_node(ast_, PipeBind, get_gap_(), get_loc_());
            }

            return rastr_op_node(ast_, EqualAssign, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if(':')) {
            if (input_.read_char_if(':')) {
                if (input_.read_char_if(':')) {
                    return rastr_op_node(
                        ast_, PrivateNamespace, get_gap_(), get_loc_());
                }
                return rastr_op_node(
                    ast_, PublicNamespace, get_gap_(), get_loc_());
            }

            else if (input_.read_char_if('=')) {
                return rastr_op_node(ast_, ColonAssign, get_gap_(), get_loc_());
            }

            return rastr_op_node(ast_, Range, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('&')) {
            if (input_.read_char_if('&')) {
                return rastr_op_node(ast_, And, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, VecAnd, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('|')) {
            if (input_.read_char_if('|')) {
                return rastr_op_node(ast_, Or, get_gap_(), get_loc_());
            } else if (input_.read_char_if('>')) {
                return rastr_op_node(ast_, PipeForward, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, VecOr, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('{')) {
            return rastr_node_delimiter(
                ast_, LeftBrace, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('}')) {
            return rastr_node_delimiter(
                ast_, RightBrace, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('(')) {
            return rastr_node_delimiter(
                ast_, LeftParen, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if(')')) {
            return rastr_node_delimiter(
                ast_, RightParen, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('[')) {
            if (input_.read_char_if('[')) {
                return rastr_node_delimiter(
                    ast_, DoubleLeftBracket, get_gap_(), get_loc_());
            }
            return rastr_node_delimiter(
                ast_, LeftBracket, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if(']')) {
            return rastr_node_delimiter(
                ast_, RightBracket, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('?')) {
            return rastr_op_node(ast_, Help, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('*')) {
            if (input_.read_char_if('*')) {
                return rastr_op_node(ast_, Power2, get_gap_(), get_loc_());
            }
            return rastr_op_node(ast_, Multiplication, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('+')) {
            return rastr_op_node(ast_, Plus, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('/')) {
            return rastr_op_node(ast_, Division, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('^')) {
            return rastr_op_node(ast_, Power, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('~')) {
            return rastr_op_node(ast_, Formula, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('$')) {
            return rastr_op_node(ast_, PartExtract, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('@')) {
            return rastr_op_node(ast_, SlotExtract, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if(',')) {
            return rastr_node_terminator(ast_, Comma, get_gap_(), get_loc_());
        }

        // else if (input_.peek_char('\n')) {
        //     //   /* increment counter if consecutive newline characters
        //     //   encountered
        //     //    */
        //     //   if (gap_nl_last_) {
        //     //       rastr_ws_inc(ast_, gaps_.back());
        //     //       rastr_pos_inc(ast_,
        //     //       rastr_loc_end(rastr_ws_loc(gaps_.back())));
        //     //   }
        //     //   /* if not, create a new ws node*/
        //     //   else {
        //     //       gaps_.push_back(rastr_ws_node(ast_, '\n', 1,
        //     get_loc_()));
        //     //       save_lloc_();
        //     //       gap_nl_last_ = true;
        //     //   }
        //
        //     int count = parse_ws_inner_('\n');
        //
        //     input_.next_line(count);
        //
        //     return rastr_node_terminator(
        //         ast_, Newline, empty_gap_(), empty_loc_());
        // }

        else if (input_.read_char_if(';')) {
            return rastr_node_terminator(
                ast_, Semicolon, get_gap_(), get_loc_());
        }

        else if (input_.read_char_if('\\')) {
            return rastr_op_node(ast_, Function2, get_gap_(), get_loc_());
        }

        else {
            fail_with("Unhandled character encountered '%d'",
                      input_.read_char());
            // return rastr_op_node(ast_, input_.read_char(), get_gap_());
        }
    }

    bool parse_gap_() {
        int a = 0;
        int b = 0;
        int c = 0;
        int d = 0;
        int e = 0;
        bool nl = false;
        bool process = true;

        while (process) {
            /* whitespace */
            a = input_.read_char_while(' ');
            b = input_.read_char_while('\t');
            c = input_.read_char_while('\f');

            /* newline */
            d = input_.read_char_while('\n');

            if (d) {
                nl = true;
                input_.next_line(d);
            }

            /* comment */
            e = 0;
            if (input_.read_char_if('#')) {
                e = 1 + input_.read_char_while_not('\n');
            }

            process = a || b || c || d || e;
        }

        gap_ = rastr_gap_node_owner(
            ast_, input_.view_at(lbyte_).materialize(), get_loc_());

        return nl;
    }

    // int parse_ws_inner_(char chr) {
    //     int count = input_.read_char_while(chr);
    //
    //     if (count != 0) {
    //         gaps_.push_back(rastr_ws_node(ast_, chr, count, get_loc_()));
    //         save_lloc_();
    //     }
    //
    //     return count;
    // }
    //
    // void parse_ws_() {
    //     while (parse_ws_inner_(' ') || parse_ws_inner_('\t') ||
    //            parse_ws_inner_('\f'))
    //         ;
    //     gap_nl_last_ = false;
    // }
    //
    // void parse_cmnt_(char initial) {
    //     int left_index = input_.get_index() - 1;
    //     int size = input_.read_char_while_not('\n');
    //     gaps_.push_back(rastr_cmnt_node_from_view(
    //         ast_,
    //         input_.get_view(left_index, left_index + size + 1),
    //         get_loc_()));
    //     save_lloc_();
    //     gap_nl_last_ = false;
    // }

    rastr_node_t parse_sym_or_op_(bool dot) {
        std::size_t left_index = input_.get_index();

        /* keep reading until the end is reached or a non symbol character
         * is encountered */
        input_.read_identifier();

        std::size_t right_index = input_.get_index();
        std::size_t length = right_index - left_index;

        /* if it starts with a . it cannot be an operator. This check is an
           optimization to avoid the long if-else ladder below if the symbol
           starts with a . */
        if (dot) {
            char* temp = input_.get_view(left_index, right_index).materialize();
            return rastr_node_symbol_unsafe(
                ast_, temp, temp, get_gap_(), get_loc_());
        }

        else if (length == 4 && input_.equal("NULL", left_index, length)) {
            return rastr_node_null(ast_, get_gap_(), get_loc_());
        }

        else if (length == 2 && input_.equal("NA", left_index, length)) {
            return rastr_node_logical(
                ast_, "NA", NA_LOGICAL, get_gap_(), get_loc_());
        }

        else if (length == 4 && input_.equal("TRUE", left_index, length)) {
            return rastr_node_logical(
                ast_, "TRUE", TRUE, get_gap_(), get_loc_());
        }

        else if (length == 5 && input_.equal("FALSE", left_index, length)) {
            return rastr_node_logical(
                ast_, "FALSE", FALSE, get_gap_(), get_loc_());
        }

        else if (length == 3 && input_.equal("Inf", left_index, length)) {
            return rastr_node_real(
                ast_, "Inf", R_PosInf, get_gap_(), get_loc_());
        }

        else if (length == 3 && input_.equal("NaN", left_index, length)) {
            return rastr_node_real(ast_, "NaN", R_NaN, get_gap_(), get_loc_());
        }

        else if (length == 11 &&
                 input_.equal("NA_integer_", left_index, length)) {
            return rastr_node_integer(
                ast_, "NA_integer_", NA_INTEGER, get_gap_(), get_loc_());
        }

        else if (length == 8 && input_.equal("NA_real_", left_index, length)) {
            return rastr_node_integer(
                ast_, "NA_real_", NA_REAL, get_gap_(), get_loc_());
        }

        else if (length == 13 &&
                 input_.equal("NA_character_", left_index, length)) {
            return rastr_node_string(
                ast_, "NA_character_", nullptr, get_gap_(), get_loc_());
        }

        else if (length == 11 &&
                 input_.equal("NA_complex_", left_index, length)) {
            return rastr_node_complex(ast_,
                                      "NA_complex_",
                                      Rcomplex{NA_REAL, NA_REAL},
                                      get_gap_(),
                                      get_loc_());
        }

        else if (length == 8 && input_.equal("function", left_index, length)) {
            return rastr_op_node(ast_, Function, get_gap_(), get_loc_());
        }

        else if (length == 5 && input_.equal("while", left_index, length)) {
            return rastr_op_node(ast_, While, get_gap_(), get_loc_());
        }

        else if (length == 6 && input_.equal("repeat", left_index, length)) {
            return rastr_op_node(ast_, Repeat, get_gap_(), get_loc_());
        }

        else if (length == 3 && input_.equal("for", left_index, length)) {
            return rastr_op_node(ast_, For, get_gap_(), get_loc_());
        }

        else if (length == 2 && input_.equal("if", left_index, length)) {
            return rastr_op_node(ast_, If, get_gap_(), get_loc_());
        }

        else if (length == 2 && input_.equal("in", left_index, length)) {
            return rastr_op_node(ast_, In, get_gap_(), get_loc_());
        }

        else if (length == 4 && input_.equal("else", left_index, length)) {
            return rastr_op_node(ast_, Else, get_gap_(), get_loc_());
        }

        else if (length == 4 && input_.equal("next", left_index, length)) {
            return rastr_op_node(ast_, Next, get_gap_(), get_loc_());
        }

        else if (length == 5 && input_.equal("break", left_index, length)) {
            return rastr_op_node(ast_, Break, get_gap_(), get_loc_());
        }

        else {
            char* temp = input_.get_view(left_index, right_index).materialize();
            return rastr_node_symbol_unsafe(
                ast_, temp, temp, get_gap_(), get_loc_());
        }
    }

    rastr_node_t parse_raw_string_(std::uint32_t r, std::uint32_t quote) {
        std::size_t left_quote_index = input_.get_index() - 2;
        std::size_t left_string_index = 0;
        std::size_t right_string_index = 0;
        std::size_t right_quote_index = 0;

        std::size_t opening_dash_count = 0;
        std::size_t closing_dash_count = 0;

        std::uint32_t close = '\0';

        /* read a possibly empty, consecutive sequence of -'s */
        opening_dash_count = input_.read_char_while('-');

        /* compute closing quote based on opening quote */
        if (input_.read_char_if('(')) {
            close = ')';
        } else if (input_.read_char_if('[')) {
            close = ']';
        } else if (input_.read_char_if('{')) {
            close = '}';
        } else if (input_.read_char_if('|')) {
            close = '|';
        } else {
            /* TODO: add location */
            return rastr_node_error(ast_, "malformed raw string literal");
        }

        /* the actual string content starts at this index */
        left_string_index = input_.get_index();

        std::uint32_t chr;
        int bytes = 0;

        while (!input_.end()) {

            chr = input_.read_utf8_char(&bytes);

            if (chr == '\n') {
                input_.next_line();
            }

            input_.inc_loc(bytes);

            /* if we reach a closing quote, the string might be ending
             */
            if (chr == close) {
                /* the actual string content
                   might end at this index-2 becase (index - 1)
                   contains the close delimiter */
                right_string_index = input_.get_index() - 1;

                /* count the number of closing - */
                closing_dash_count = input_.read_char_while('-');

                /* if the number of opening and closing dashes, and the
                 * opening and closing quote characters match, then the
                 * string ends and we return the token  */
                if (closing_dash_count == opening_dash_count &&
                    input_.read_char_if(quote)) {
                    /* the right quote portion ends at this index-1 */
                    right_quote_index = input_.get_index();

                    return rastr_node_string_from_view(
                        ast_,
                        input_.get_view(left_quote_index, right_quote_index),
                        input_.get_view(left_string_index, right_string_index),
                        get_gap_(),
                        get_loc_());
                }
            }
        }

        /* if we reach here, it means the raw string was not terminated */
        return rastr_node_error(ast_, "unterminated raw string");
    }

    void parse_string_helper_(std::uint32_t delimiter,
                              std::size_t& left_index,
                              std::size_t& right_index) {
        std::uint32_t previous = delimiter;
        char current;
        left_index = input_.get_index() - 1;
        bool escaped = false;

        std::uint32_t chr;
        int bytes;

        while (!input_.end()) {
            chr = input_.read_utf8_char(&bytes);

            /* quoted symbols can span multiple lines! since this function is
               called from parse_quoted_symbol_, we need to check for
               occurrences of \n and increment row.*/
            if (chr == '\n') {
                input_.next_line();
            }

            input_.inc_loc(bytes);

            /* if current char is escaped by a previous \, then toggle
               escaped. an even number of \ cancel out the escaping
               behavior. this logic ensures that escape is only true for odd
               number of consecutive
               \ */
            escaped = (previous == '\\') ? !escaped : false;

            // if delimiter encountered and not escaped, then parsing is
            // complete
            if (chr == delimiter && !escaped) {
                // left_index is inclusive and right_index is exclusive
                right_index = input_.get_index();
                return;
            }

            previous = chr;
        }

        // return rastr_node_error(ast_, "unterminated special value");
        // TODO: return error node instead of failing with error message;
        fail_with("unterminated special value");
    }

    rastr_node_t parse_string_(char delimiter) {
        std::size_t left_index = 0;
        std::size_t right_index = 0;
        parse_string_helper_(delimiter, left_index, right_index);
        /* right_index points next to the delimiter, so right_index-1 points
         * to the delimiter */
        return rastr_node_string_from_view(
            ast_,
            input_.get_view(left_index, right_index),
            input_.get_view(left_index + 1, right_index - 1),
            get_gap_(),
            get_loc_());
    }

    rastr_node_t parse_quoted_symbol_(char delimiter) {
        std::size_t left_index = 0;
        std::size_t right_index = 0;
        parse_string_helper_(delimiter, left_index, right_index);

        return rastr_node_symbol_unsafe(
            ast_,
            input_.get_view(left_index, right_index).materialize(),
            input_.get_view(left_index + 1, right_index - 1).materialize(),
            get_gap_(),
            get_loc_());
    }

    rastr_node_t parse_special_(char delimiter) {
        std::size_t left_index = input_.get_index() - 1;

        input_.read_char_while_not(delimiter);
        if (input_.end()) {
            return rastr_node_error(
                ast_, "eof encountered while parsing special operator");
        }

        /* read the trailing % */
        input_.read_char();

        std::size_t right_index = input_.get_index();

        return rastr_special_op_node(ast_,
                                     input_.get_view(left_index, right_index),
                                     get_gap_(),
                                     get_loc_());
    }

    rastr_node_t parse_number_(int c) {
        int seendot = (c == '.');
        int seenexp = 0;
        int last = c;
        int nd = 0;
        int asNumeric = 0;
        int count = 1; /* The number of characters seen */

        int left_index = input_.get_index() - 1;

        /* We don't care about other than ASCII digits */
        while (isdigit(c = input_.read_char()) || c == '.' || c == 'e' ||
               c == 'E' || c == 'x' || c == 'X' || c == 'L') {
            count++;

            /* must be at the end.  Won't allow 1Le3 (at present). */
            if (c == 'L') {
                break;
            }

            /* hexadecimal numbers */
            if (c == 'x' || c == 'X') {
                if (count > 2 || last != '0') {
                    break; /* 0x must be first */
                }

                while (isdigit(c = input_.read_char()) ||
                       ('a' <= c && c <= 'f') || ('A' <= c && c <= 'F') ||
                       c == '.') {
                    if (c == '.') {
                        if (seendot) {
                            return rastr_node_error(
                                ast_,
                                "two decimal points in hexadecimal number");
                        }
                        seendot = 1;
                    }
                    nd++;
                }

                if (nd == 0) {
                    return rastr_node_error(ast_,
                                            "no hexadecimal digits follow 0x");
                }

                if (c == 'p' || c == 'P') {
                    seenexp = 1;

                    c = input_.read_char();

                    if (!isdigit(c) && c != '+' && c != '-') {
                        return rastr_node_error(ast_,
                                                "expected a digit, +, or - to "
                                                "follow the exponent sign of "
                                                "hexadecimal number");
                    }

                    if (c == '+' || c == '-') {
                        c = input_.read_char();
                    }

                    for (nd = 0; isdigit(c); c = input_.read_char(), nd++)
                        ;

                    if (nd == 0) {
                        return rastr_node_error(
                            ast_,
                            "no digits present in the exponent of "
                            "hexadecimal number");
                    }
                }

                if (seendot && !seenexp) {
                    return rastr_node_error(ast_,
                                            "missing exponent in hexadecimal "
                                            "number with a decimal point");
                }

                /* for getParseData */
                if (c == 'L') {
                    // seenexp will be checked later
                    break;
                }

                break;
            }

            if (c == 'E' || c == 'e') {
                if (seenexp) {
                    break;
                }

                seenexp = 1;
                seendot = seendot == 1 ? seendot : 2;
                c = input_.read_char();

                if (!isdigit(c) && c != '+' && c != '-') {
                    return rastr_node_error(
                        ast_, "expected digit, +, or - after exponent");
                }

                if (c == '+' || c == '-') {
                    c = input_.read_char();

                    if (!isdigit(c)) {
                        return rastr_node_error(
                            ast_, "expected digit after +/- sign in exponent");
                    }
                }
            }

            if (c == '.') {
                if (seendot) {
                    break;
                }

                seendot = 1;
            }

            last = c;
        }

        /* Make certain that things are okay. */
        if (c == 'L') {
            const char* syntax = input_.view_at(left_index).materialize();

            double a = R_atof(syntax);
            int b = (int) a;
            /* We are asked to create an integer via the L, so we check that the
               double and int values are the same. If not, this is a problem and
               we will not lose information and so use the numeric value.
            */
            if (a != (double) b) {
                if (seendot == 1 && seenexp == 0) {
                    rastr_log_warning(
                        "integer literal %s contains decimal; using "
                        "numeric value",
                        syntax);
                } else {
                    /* hide the L for the warning message */
                    rastr_log_warning("non-integer value %s qualified with L; "
                                      "using numeric value",
                                      syntax);
                }

                asNumeric = 1;
                seenexp = 1;
            }

            free((void*) syntax);
        }

        if (c == 'i') {
            return rastr_node_complex_from_view(
                ast_, input_.view_at(left_index), get_gap_(), get_loc_());
        }

        else if (c == 'L' && asNumeric == 0) {
            if (seendot == 1 && seenexp == 0) {
                const char* syntax = input_.view_at(left_index).materialize();
                rastr_log_warning(
                    "integer literal %s contains unnecessary decimal point",
                    syntax);
                free((void*) syntax);
            }

            return rastr_node_integer_from_view(
                ast_, input_.view_at(left_index), get_gap_(), get_loc_());

        } else {
            if (c != 'L') {
                input_.rewind();
            }

            return rastr_node_double_from_view(
                ast_, input_.view_at(left_index), get_gap_(), get_loc_());
        }

        return rastr_node_error(ast_, "should not reach here!");
    }

    rastr_node_t get_gap_() {
        return gap_;
    }

    rastr_node_t get_loc_() {
        int rrow;
        int rcol;
        int rchr;
        int rbyte;

        input_.get_pos(&rrow, &rcol, &rchr, &rbyte);

        rastr_node_t loc = rastr_loc_node(
            ast_, lrow_, lcol_, lchr_, lbyte_, rrow, rcol, rchr, rbyte);

        return loc;
    }

    void save_lloc_() {
        input_.get_pos(&lrow_, &lcol_, &lchr_, &lbyte_);
    }

    /* TODO: delete */
    rastr_node_t empty_loc_() {
        return rastr_loc_node(ast_, 0, 0, 0, 0, 0, 0, 0, 0);
    }

    /* TODO: delete */
    rastr_node_t empty_gap_() {
        return rastr_gap_node_owner(ast_, nullptr, empty_loc_());
    }
};
