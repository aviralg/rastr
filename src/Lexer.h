#include "Input.h"
#include <rastr/api.h>
#include "internal_api.h"
#include "logger.h"

class Lexer {
  public:
    Lexer(Input input, rastr_ast_t ast)
        : input_(input)
        , ast_(ast)
        , context_("")
        , token_saved_(false)
        , eat_lines_(false) {
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
                    return rastr_node_terminator(ast_, Newline);
                }
            } else {
                return rastr_node_terminator(ast_, Newline);
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
        case VectorizedAnd:
        case Or:
        case VectorizedOr:

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
        case Placeholder:
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

  private:
    Input input_;
    rastr_ast_t ast_;
    std::string context_;
    rastr_node_t saved_token_;
    bool token_saved_;
    bool eat_lines_;

    void disable_eat_lines() {
        eat_lines_ = false;
    }

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

        /* parse whitespace; newline is excluded because it can be an
           expression terminator or a whitespace depending on the context */
        if (input_.peek_char_any(' ', '\t', '\f')) {
            parse_space_();
        }

        /* parse comment */
        if (input_.read_char_if('#')) {
            parse_comment_('#');
        }

        /* return end token if end of input is reached */
        if (input_.end()) {
            return rastr_node_end(ast_);
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
                /* this cannot be a keyword since it starts with a . so this
                   function bypasses keyword checks if the symbol starts
                   with a
                   . */
                return parse_symbol_or_keyword_('.');
            }
        }

        else if (input_.read_char_if('_')) {
            return rastr_node_placeholder(ast_);
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

        /* symbols and keywords */
        else if (input_.is_alphabet()) {
            return parse_symbol_or_keyword_(input_.read_char());
        }

        /* operators */

        else if (input_.read_char_if('<')) {
            if (input_.read_char_if('=')) {
                return rastr_node_operator(ast_, "<=", LessThanEqual);
            }

            else if (input_.read_char_if('-')) {
                return rastr_node_operator(ast_, "<-", LeftAssign);
            }

            else if (input_.read_char_if('<')) {
                if (input_.read_char_if('-')) {
                    return rastr_node_operator(ast_, "<<-", LeftSuperAssign);
                }
                return rastr_node_error(ast_, "invalid character sequence: <<");
            }
            return rastr_node_operator(ast_, "<", LessThan);
        }

        else if (input_.read_char_if('-')) {
            if (input_.read_char_if('>')) {
                if (input_.read_char_if('>')) {
                    return rastr_node_operator(ast_, "->>", RightSuperAssign);
                }
                return rastr_node_operator(ast_, "->", RightAssign);
            }
            return rastr_node_operator(ast_, "-", Minus);
        }

        else if (input_.read_char_if('>')) {
            if (input_.read_char_if('=')) {
                return rastr_node_operator(ast_, ">=", GreaterThanEqual);
            }
            return rastr_node_operator(ast_, ">", GreaterThan);
        }

        else if (input_.read_char_if('!')) {
            if (input_.read_char_if('=')) {
                return rastr_node_operator(ast_, "!=", NotEqual);
            }
            return rastr_node_operator(ast_, "!", Not);
        }

        else if (input_.read_char_if('=')) {
            if (input_.read_char_if('=')) {
                return rastr_node_operator(ast_, "==", Equal);
            }

            else if (input_.read_char_if('>')) {
                return rastr_node_operator(ast_, "=>", PipeBind);
            }

            return rastr_node_operator(ast_, "=", EqualAssign);
        }

        else if (input_.read_char_if(':')) {
            if (input_.read_char_if(':')) {
                if (input_.read_char_if(':')) {
                    return rastr_node_operator(ast_, ":::", PrivateNamespace);
                }
                return rastr_node_operator(ast_, "::", PublicNamespace);
            }

            else if (input_.read_char_if('=')) {
                return rastr_node_operator(ast_, ":=", ColonAssign);
            }

            return rastr_node_operator(ast_, ":", Range);
        }

        else if (input_.read_char_if('&')) {
            if (input_.read_char_if('&')) {
                return rastr_node_operator(ast_, "&&", And);
            }
            return rastr_node_operator(ast_, "&", VectorizedAnd);
        }

        else if (input_.read_char_if('|')) {
            if (input_.read_char_if('|')) {
                return rastr_node_operator(ast_, "||", Or);
            } else if (input_.read_char_if('>')) {
                return rastr_node_operator(ast_, "|>", PipeForward);
            }
            return rastr_node_operator(ast_, "|", VectorizedOr);
        }

        else if (input_.read_char_if('{')) {
            return rastr_node_delimiter(ast_, LeftBrace);
        }

        else if (input_.read_char_if('}')) {
            return rastr_node_delimiter(ast_, RightBrace);
        }

        else if (input_.read_char_if('(')) {
            return rastr_node_delimiter(ast_, LeftParen);
        }

        else if (input_.read_char_if(')')) {
            return rastr_node_delimiter(ast_, RightParen);
        }

        else if (input_.read_char_if('[')) {
            if (input_.read_char_if('[')) {
                return rastr_node_delimiter(ast_, DoubleLeftBracket);
            }
            return rastr_node_delimiter(ast_, LeftBracket);
        }

        else if (input_.read_char_if(']')) {
            return rastr_node_delimiter(ast_, RightBracket);
        }

        else if (input_.read_char_if('?')) {
            return rastr_node_operator(ast_, "?", Help);
        }

        else if (input_.read_char_if('*')) {
            if (input_.read_char_if('*')) {
                return rastr_node_operator(ast_, "**", Power);
            }
            return rastr_node_operator(ast_, "*", Multiplication);
        }

        else if (input_.read_char_if('+')) {
            return rastr_node_operator(ast_, "+", Plus);
        }

        else if (input_.read_char_if('/')) {
            return rastr_node_operator(ast_, "/", Division);
        }

        else if (input_.read_char_if('^')) {
            return rastr_node_operator(ast_, "^", Power);
        }

        else if (input_.read_char_if('~')) {
            return rastr_node_operator(ast_, "~", Formula);
        }

        else if (input_.read_char_if('$')) {
            return rastr_node_operator(ast_, "$", PartExtract);
        }

        else if (input_.read_char_if('@')) {
            return rastr_node_operator(ast_, "@", SlotExtract);
        }

        else if (input_.read_char_if(',')) {
            return rastr_node_terminator(ast_, Comma);
        }

        else if (input_.read_char_if('\n')) {
            return rastr_node_terminator(ast_, Newline);
        }

        else if (input_.read_char_if(';')) {
            return rastr_node_terminator(ast_, Semicolon);
        }

        else if (input_.read_char_if('\\')) {
            return rastr_node_operator(ast_, "\\", AnonymousFunction);
        }

        else {
            fail_with("Unhandled character encountered '%d'",
                      input_.read_char());
            // return rastr_node_operator(ast_, input_.read_char());
        }
    }

    void parse_space_() {
        while (!input_.end() && input_.read_char_if_any(' ', '\t', '\f'))
            ;
    }

    void parse_comment_(char initial) {
        input_.read_char_while_not('\n');
        if (!input_.end()) {
            input_.read_char();
        }
    }

    rastr_node_t parse_symbol_or_keyword_(char initial) {
        std::size_t left_index = input_.get_index() - 1;

        /* keep reading until the end is reached or a non symbol character
         * is encountered */
        while (!input_.end() &&
               (input_.is_alpha_numeric() || input_.peek_char_any('.', '_'))) {
            input_.read_char();
        }

        std::size_t right_index = input_.get_index();
        std::size_t length = right_index - left_index;

        /* if it starts with a . it cannot be a keyword. This check is an
           optimization to avoid the long if-else ladder below if the symbol
           starts with a . */
        if (initial == '.') {
            return rastr_node_symbol_from_view(
                ast_,
                input_.get_view(left_index, right_index),
                input_.get_view(left_index, right_index));
        }

        else if (length == 4 && input_.equal("NULL", left_index, length)) {
            return rastr_node_null(ast_);
        }

        else if (length == 2 && input_.equal("NA", left_index, length)) {
            return rastr_node_logical(ast_, "NA", 0 /*TODO: NA_LOGICAL */);
        }

        else if (length == 4 && input_.equal("TRUE", left_index, length)) {
            return rastr_node_logical(ast_, "TRUE", TRUE);
        }

        else if (length == 5 && input_.equal("FALSE", left_index, length)) {
            return rastr_node_logical(ast_, "FALSE", FALSE);
        }

        else if (length == 3 && input_.equal("Inf", left_index, length)) {
            return rastr_node_real(ast_, "Inf", 23.0 /* TODO: R_PosInf */);
        }

        else if (length == 3 && input_.equal("NaN", left_index, length)) {
            return rastr_node_real(ast_, "NaN", 23.0 /* TODO: R_NaN */);
        }

        else if (length == 11 &&
                 input_.equal("NA_integer_", left_index, length)) {
            return rastr_node_integer(
                ast_, "NA_integer_", 0 /* TODO: NA_INTEGER */);
        }

        else if (length == 8 && input_.equal("NA_real_", left_index, length)) {
            return rastr_node_integer(
                ast_, "NA_real_", 0.0 /* TODO: NA_REAL */);
        }

        else if (length == 13 &&
                 input_.equal("NA_character_", left_index, length)) {
            return rastr_node_string(ast_, "NA_character_", nullptr);
        }

        else if (length == 11 &&
                 input_.equal("NA_complex_", left_index, length)) {
            return rastr_node_complex(
                ast_,
                "NA_complex_",
                Rcomplex{0 /* TODO: NA_REAL */, 0 /* NA_REAL */});
        }

        else if (length == 8 && input_.equal("function", left_index, length)) {
            return rastr_node_keyword(ast_, "function", Function);
        }

        else if (length == 5 && input_.equal("while", left_index, length)) {
            return rastr_node_keyword(ast_, "while", While);
        }

        else if (length == 6 && input_.equal("repeat", left_index, length)) {
            return rastr_node_keyword(ast_, "repeat", Repeat);
        }

        else if (length == 3 && input_.equal("for", left_index, length)) {
            return rastr_node_keyword(ast_, "for", For);
        }

        else if (length == 2 && input_.equal("if", left_index, length)) {
            return rastr_node_keyword(ast_, "if", If);
        }

        else if (length == 2 && input_.equal("in", left_index, length)) {
            return rastr_node_keyword(ast_, "in", In);
        }

        else if (length == 4 && input_.equal("else", left_index, length)) {
            return rastr_node_keyword(ast_, "else", Else);
        }

        else if (length == 4 && input_.equal("next", left_index, length)) {
            return rastr_node_keyword(ast_, "next", Next);
        }

        else if (length == 5 && input_.equal("break", left_index, length)) {
            return rastr_node_keyword(ast_, "break", Break);
        }

        else {
            return rastr_node_symbol_from_view(
                ast_,
                input_.get_view(left_index, right_index),
                input_.get_view(left_index, right_index));
        }
    }

    rastr_node_t parse_raw_string_(char r, char quote) {
        std::size_t left_quote_index = input_.get_index() - 2;
        std::size_t left_string_index = 0;
        std::size_t right_string_index = 0;
        std::size_t right_quote_index = 0;

        std::size_t opening_dash_count = 0;
        std::size_t closing_dash_count = 0;

        char close = '\0';

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
            return rastr_node_error(ast_, "malformed raw string literal");
        }

        /* the actual string content starts at this index */
        left_string_index = input_.get_index();

        while (!input_.end()) {
            char chr = input_.read_char();

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
                        input_.get_view(left_string_index, right_string_index));
                }
            }
        }

        /* if we reach here, it means the raw string was not terminated */
        return rastr_node_error(ast_, "unterminated raw string");
    }

    void parse_string_helper_(char delimiter,
                              std::size_t& left_index,
                              std::size_t& right_index) {
        char previous = delimiter;
        char current;
        left_index = input_.get_index() - 1;
        bool escaped = false;

        while (!input_.end()) {
            char current = input_.read_char();

            /* if current char is escaped by a previous \, then toggle
               escaped. an even number of \ cancel out the escaping
               behavior. this logic ensures that escape is only true for odd
               number of consecutive
               \ */
            escaped = (previous == '\\') ? !escaped : false;

            // if delimiter encountered and not escaped, then parsing is
            // complete
            if (current == delimiter && !escaped) {
                // left_index is inclusive and right_index is exclusive
                right_index = input_.get_index();
                return;
            }

            previous = current;
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
            input_.get_view(left_index + 1, right_index - 1));
    }

    rastr_node_t parse_quoted_symbol_(char delimiter) {
        std::size_t left_index = 0;
        std::size_t right_index = 0;
        parse_string_helper_(delimiter, left_index, right_index);

        return rastr_node_symbol_from_view(
            ast_,
            input_.get_view(left_index, right_index),
            input_.get_view(left_index + 1, right_index - 1));
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

        return rastr_node_operator_from_view(
            ast_, input_.get_view(left_index, right_index), Special);
    }

    rastr_node_t parse_number_(char c) {
        return rastr_node_error(ast_, "TODO: handle numbers");
    }

    //     rastr_node_t parse_number_(char c) {
    //         int seendot = (c == '.');
    //         int seenexp = 0;
    //         int last = c;
    //         int nd = 0;
    //         int asNumeric = 0;
    //         int count = 1; /* The number of characters seen */
    //
    //         int left_index = input_.get_index() - 1;
    //
    //         /* We don't care about other than ASCII digits */
    //         while (!input_.end() &&
    //                (input_.is_digit() || input_.peek_char_any('e', 'E')
    //                ||
    //                 input_.peek_char_any('x', 'X') ||
    //                 input_.peek_char_any('.', 'L'))) {
    //             c = input_.next_char();
    //             count++;
    //
    //             if (c ==
    //                 'L') /* must be at the end.  Won't allow 1Le3 (at
    //                 present). */
    //             {
    //                 break;
    //             }
    //
    //             if (c == 'x' || c == 'X') {
    //                 if (count > 2 || last != '0') {
    //                     /* "push back" 'x' or 'X' into the input as this
    //                     marks the
    //                        end of the number. */
    //                     input_.rewind(1);
    //                     break; /* 0x must be first */
    //                 }
    //
    //                 while (!input_.end() &&
    //                        (input_.is_hex_digit() ||
    //                        input_.peek_char('.')))
    //                        {
    //                     c = input_.next_char();
    //                     if (c == '.') {
    //                         if (seendot)
    //                             return rastr_node_error(
    //                                 "encountered two decimal points in a
    //                                 number");
    //                         seendot = 1;
    //                     }
    //                     nd++;
    //                 }
    //                 if (nd == 0)
    //                     return ERROR;
    //                 if (c == 'p' || c == 'P') {
    //                     seenexp = 1;
    //                     if (input_.peek_char_any('+', '-')) {
    //                         input_.read_char();
    //                         c = input_.read_char();
    //                     }
    //                     /* if neither digit, nor + and - follow p, it is
    //                     an error */ else if (!input_.is_digit()) {
    //                         return rastr_node_error(
    //                             "encountered invalid character after p");
    //                     }
    //
    //                     /* read consecutive sequence of digits */
    //                     for (nd = 0; !input_.end() && input_.is_digit();
    //                          c = input_.read_char(), nd++)
    //                         ;
    //
    //                     if (nd == 0) {
    //                         return rastr_node_error(
    //                             "invalid number: no digits after p");
    //                     }
    //                 }
    //                 if (seendot && !seenexp)
    //                     return rastr_node_error("invalid hex number: has
    //                     decimal "
    //                                             "point but no exponent
    //                                             provided");
    //
    //                 if (c == 'L') /* for getParseData */
    //                 {
    //                     // seenexp will be checked later
    //                     break;
    //                 }
    //                 break;
    //             }
    //             if (c == 'E' || c == 'e') {
    //                 if (seenexp)
    //                     break;
    //                 seenexp = 1;
    //                 seendot = seendot == 1 ? seendot : 2;
    //                 YYTEXT_PUSH(c, yyp);
    //                 c = xxgetc();
    //                 if (!isdigit(c) && c != '+' && c != '-')
    //                     return ERROR;
    //                 if (c == '+' || c == '-') {
    //                     YYTEXT_PUSH(c, yyp);
    //                     c = xxgetc();
    //                     if (!isdigit(c))
    //                         return ERROR;
    //                 }
    //             }
    //             if (c == '.') {
    //                 if (seendot)
    //                     break;
    //                 seendot = 1;
    //             }
    //             YYTEXT_PUSH(c, yyp);
    //             last = c;
    //         }
    //
    //         if (c == 'i')
    //             YYTEXT_PUSH(c, yyp); /* for getParseData */
    //
    //         YYTEXT_PUSH('\0', yyp);
    //         /* Make certain that things are okay. */
    //         if (c == 'L') {
    //             double a = R_atof(yytext);
    //             int b = (int) a;
    //             /* We are asked to create an integer via the L, so we
    //             check that the
    //                double and int values are the same. If not, this is a
    //                problem and we will not lose information and so use
    //                the numeric value.
    //             */
    //             if (a != (double) b) {
    //                 if (GenerateCode) {
    //                     if (seendot == 1 && seenexp == 0)
    //                         warning(_("integer literal %s contains
    //                         decimal; using "
    //                                   "numeric value"),
    //                                 yytext);
    //                     else {
    //                         /* hide the L for the warning message */
    //                         warning(_("non-integer value %s qualified
    //                         with L;
    //                         "
    //                                   "using numeric value"),
    //                                 yytext);
    //                     }
    //                 }
    //                 asNumeric = 1;
    //                 seenexp = 1;
    //             }
    //         }
    //
    //         if (c == 'i') {
    //             yylval = GenerateCode ? mkComplex(yytext) : R_NilValue;
    //         } else if (c == 'L' && asNumeric == 0) {
    //             if (GenerateCode && seendot == 1 && seenexp == 0)
    //                 warning(
    //                     _("integer literal %s contains unnecessary
    //                     decimal point"), yytext);
    //             yylval = GenerateCode ? mkInt(yytext) : R_NilValue;
    // #if 0 /* do this to make 123 integer not double */
    //     } else if(!(seendot || seenexp)) {
    // 	if(c != 'L') xxungetc(c);
    // 	if (GenerateCode) {
    // 	    double a = R_atof(yytext);
    // 	    int b = (int) a;
    // 	    yylval = (a != (double) b) ? mkFloat(yytext) :
    // mkInt(yytext); 	} else yylval = R_NilValue; #endif
    //         } else {
    //             if (c != 'L')
    //                 xxungetc(c);
    //             yylval = GenerateCode ? mkFloat(yytext) : R_NilValue;
    //         }
    //
    //         PRESERVE_SV(yylval);
    //         return NUM_CONST;
    //     }
    //
    //     rastr_node_t parse_number_(char initial) {
    //         char c = initial;
    //
    //         int seendot = (c == '.');
    //         int seenexp = 0;
    //         int last = c;
    //         int nd = 0;
    //         int asNumeric = 0;
    //         int count = 1; /* The number of characters seen */
    //
    //         push_token_buffer(c);
    //         /* We don't care about other than ASCII digits */
    //         while (isdigit(c = yyinput()) ||           //
    //                c == '.' || c == 'e' || c == 'E' || //
    //                c == 'x' || c == 'X' || c == 'L') {
    //             count++;
    //
    //             /* must be at the end.  Won't allow 1Le3 (at present). */
    //             if (c == 'L') {
    //                 push_token_buffer(c);
    //                 break;
    //             }
    //
    //             if (c == 'x' || c == 'X') {
    //                 if (count > 2 || last != '0')
    //                     break; /* 0x must be first */
    //                 push_token_buffer(c);
    //                 while (isdigit(c = yyinput()) || ('a' <= c && c <=
    //                 'f')
    //                 ||
    //                        ('A' <= c && c <= 'F') || c == '.') {
    //                     if (c == '.') {
    //                         if (seendot)
    //                             HANDLE_ERROR();
    //                         seendot = 1;
    //                     }
    //                     push_token_buffer(c);
    //                     nd++;
    //                 }
    //                 if (nd == 0)
    //                     HANDLE_ERROR();
    //                 if (c == 'p' || c == 'P') {
    //                     seenexp = 1;
    //                     push_token_buffer(c);
    //                     c = yyinput();
    //                     if (!isdigit(c) && c != '+' && c != '-')
    //                         HANDLE_ERROR();
    //                     if (c == '+' || c == '-') {
    //                         push_token_buffer(c);
    //                         c = yyinput();
    //                     }
    //                     for (nd = 0; isdigit(c); c = yyinput(), nd++)
    //                         push_token_buffer(c);
    //                     if (nd == 0)
    //                         HANDLE_ERROR();
    //                 }
    //                 if (seendot && !seenexp)
    //                     HANDLE_ERROR();
    //                 break;
    //             }
    //             if (c == 'E' || c == 'e') {
    //                 if (seenexp)
    //                     break;
    //                 seenexp = 1;
    //                 seendot = seendot == 1 ? seendot : 2;
    //                 push_token_buffer(c);
    //                 c = yyinput();
    //                 if (!isdigit(c) && c != '+' && c != '-')
    //                     HANDLE_ERROR();
    //                 if (c == '+' || c == '-') {
    //                     push_token_buffer(c);
    //                     c = yyinput();
    //                     if (!isdigit(c))
    //                         HANDLE_ERROR();
    //                 }
    //             }
    //             if (c == '.') {
    //                 if (seendot)
    //                     break;
    //                 seendot = 1;
    //             }
    //             push_token_buffer(c);
    //             last = c;
    //         }
    //
    //         if (c == 'i')
    //             push_token_buffer(c); /* for getParseData */
    //
    //         /*NOTE: representation finished at this point:
    //         YYTEXT_PUSH('\0', yyp);
    //          */
    //         /* Make certain that things are okay. */
    //         if (c == 'L') {
    //             double a = R_atof(get_token_buffer().c_str());
    //             int b = (int) a;
    //             /* We are asked to create an integer via the L, so we
    //             check that the
    //                double and int values are the same. If not, this is a
    //                problem and we will not lose information and so use
    //                the numeric value.
    //             */
    //             if (a != (double) b) {
    //                 if (seendot == 1 && seenexp == 0)
    //                     fprintf(stderr,
    //                             "integer literal %s contains decimal;
    //                             using " "numeric value",
    //                             get_token_buffer().c_str());
    //                 else {
    //                     /* hide the L for the warning message */
    //                     fprintf(stderr,
    //                             "non-integer value %s qualified with L;
    //                             using " "numeric value",
    //                             get_token_buffer().c_str());
    //                 }
    //                 asNumeric = 1;
    //                 seenexp = 1;
    //             }
    //         }
    //
    //         if (c == 'i') {
    //             *yylval = mkComplex(ast_, get_token_buffer());
    //             return rastr::RParser::token::COMPLEX_CONST;
    //         } else if (c == 'L' && asNumeric == 0) {
    //             if (seendot == 1 && seenexp == 0)
    //                 fprintf(stderr,
    //                         "integer literal %s contains unnecessary
    //                         decimal point", get_token_buffer().c_str());
    //             *yylval = mkInt(ast_, get_token_buffer());
    //             return rastr::RParser::token::INT_CONST;
    // #if 0 /* do this to make 123 integer not double */
    //                                                                     }
    //                                                                     else
    //                                                                     if(!(seendot
    //                                                                     ||
    //                                                                     seenexp))
    //                                                                     {
    //                                                                 	if(c
    //                                                                 !=
    //                                                                 'L')
    //                                                                 unput_(c);
    //                                                                 	    double
    //                                                                 a =
    //                                                                 R_atof(get_token_buffer().c_str());
    //                                                                 	    int
    //                                                                 b =
    //                                                                 (int)
    //                                                                 a;
    //                                                                 if(a
    //                                                                 !=
    //                                                                 (double)
    //                                                                 b) {
    //                                                                           *yylval = mkFloat(ast_, get_token_buffer());
    //                                                                           return rastr::RParser::token::FLOAT_CONST;
    //                                                                       }
    //                                                                       else
    //                                                                       {
    //                                                                           *yylval = mkInt(ast_, get_token_buffer());
    //                                                                           return rastr::RParser::token::INT_CONST;
    //                                                                       }
    // #endif
    //         } else {
    //             if (c != 'L')
    //                 unput_(c);
    //             *yylval = mkFloat(ast_, get_token_buffer());
    //             return rastr::RParser::token::FLOAT_CONST;
    //         }
    //     }
};
