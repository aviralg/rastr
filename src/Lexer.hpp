#ifndef RASTR_LEXER_HPP
#    define RASTR_LEXER_HPP

#    include "Parser.hxx"

#    include <iostream>
#    include <string>
//#include "parser/ParsingContext.hpp"

/* https://stackoverflow.com/questions/40663527/how-to-inherit-from-yyflexlexer
 */
#    if !defined(yyFlexLexerOnce)
#        include <FlexLexer.h>
#    endif

/* Tell flex which function to define */
#    undef YY_DECL
#    define YY_DECL                                          \
        int rastr::r::parser::Lexer::yylex_inner(            \
            rastr::r::parser::Parser::semantic_type* yylval, \
            rastr::r::parser::Parser::location_type* yylloc)

namespace rastr {
namespace r {
namespace parser {
/* https://westes.github.io/flex/manual/Cxx.html#Cxx */
class Lexer: public yyFlexLexer {
  public:
    Lexer(): Lexer(std::cin) {
    }

    explicit Lexer(std::istream& istream)
        : yyFlexLexer(istream, std::cout)
        , saved_yylval_(nullptr)
        , saved_yylloc_()
        , saved_token_(0)
        , saved_(false)
        , eat_lines_(false)
        , context_("")
        , token_buffer_("") {
    }

    int yylex_inner(rastr::r::parser::Parser::semantic_type* yylval,
                    rastr::r::parser::Parser::location_type* yylloc);

    int yylex_helper(rastr::r::parser::Parser::semantic_type* yylval,
                     rastr::r::parser::Parser::location_type* yylloc) {
        if (saved_) {
            *yylval = saved_yylval_;
            *yylloc = saved_yylloc_;
            saved_yylval_ = nullptr;
            saved_ = false;
            return saved_token_;
        } else {
            return yylex_inner(yylval, yylloc);
        }
    }

    int yylex(rastr::r::parser::Parser::semantic_type* yylval,
              rastr::r::parser::Parser::location_type* yylloc) {
        int token;

    again:
        token = yylex_helper(yylval, yylloc);

        // std::cout << *yylval;

        /* Newlines must be handled in a context */
        /* sensitive way.  The following block of */
        /* deals directly with newlines in the */
        /* body of "if" statements. */

        if (token == Parser::token::NEWLINE) {
            if (should_eat_lines() || peek_context() == '[' ||
                peek_context() == '(')
                goto again;

            /* The essence of this is that in the body of */
            /* an "if", any newline must be checked to */
            /* see if it is followed by an "else". */
            /* such newlines are discarded. */

            if (peek_context() == 'i') {
                /* Find the next non-newline token */

                while (token == Parser::token::NEWLINE) {
                    token = yylex_helper(yylval, yylloc);
                    // std::cout << *yylval;
                }

                /* If we encounter "}", ")" or "]" then */
                /* we know that all immediately preceding */
                /* "if" bodies have been terminated. */
                /* The corresponding "i" values are */
                /* popped off the context stack. */

                if (token == Parser::token::RBRACE ||
                    token == Parser::token::RPAREN ||
                    token == Parser::token::RSQPAREN) {
                    while (peek_context() == 'i')
                        pop_context_if('i');
                    pop_context();
                    return token;
                }

                /* When a "," is encountered, it terminates */
                /* just the immediately preceding "if" body */
                /* so we pop just a single "i" of the */
                /* context stack. */

                if (token == Parser::token::COMMA) {
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

                if (token == Parser::token::ELSE) {
                    enable_eat_lines();
                    pop_context_if('i');
                    return Parser::token::ELSE;
                } else {
                    pop_context_if('i');
                    saved_token_ = token;
                    saved_yylval_ = *yylval;
                    saved_yylloc_ = *yylloc;
                    saved_ = true;
                    *yylval = new rastr::ast::DelimiterRNode("\n");
                    return Parser::token::NEWLINE;
                }
            } else {
                return Parser::token::NEWLINE;
            }
        }

        /* Additional context sensitivities */

        switch (token) {
            /* Any newlines immediately following the */
            /* the following tokens are discarded. The */
            /* expressions are clearly incomplete. */

        case Parser::token::PLUS:
        case Parser::token::MINUS:
        case Parser::token::ASTERISK:
        case Parser::token::SLASH:
        case Parser::token::CARET:
        case Parser::token::LT:
        case Parser::token::LE:
        case Parser::token::GE:
        case Parser::token::GT:
        case Parser::token::EQ:
        case Parser::token::NE:
        case Parser::token::OR:
        case Parser::token::AND:
        case Parser::token::OR2:
        case Parser::token::AND2:
        case Parser::token::SPECIAL:
        case Parser::token::FUNCTION:
        case Parser::token::WHILE:
        case Parser::token::REPEAT:
        case Parser::token::FOR:
        case Parser::token::IN:
        case Parser::token::QUESTION:
        case Parser::token::EXCLAMATION:
        case Parser::token::COLON:
        case Parser::token::TILDE:
        case Parser::token::DOLLAR:
        case Parser::token::AT:
        case Parser::token::LEFT_ASSIGN:
        case Parser::token::RIGHT_ASSIGN:
        case Parser::token::EQ_ASSIGN:
            enable_eat_lines();
            break;

            /* Push any "if" statements found and */
            /* discard any immediately following newlines. */

        case Parser::token::IF:
            if (peek_context() == '{' || peek_context() == '[' ||
                peek_context() == '(' || peek_context() == 'i') {
                push_context('i');
            }
            enable_eat_lines();
            break;

            /* Terminate any immediately preceding "if" */
            /* statements and discard any immediately */
            /* following newlines. */

        case Parser::token::ELSE:
            pop_context_if('i');
            enable_eat_lines();
            break;

            /* These tokens terminate any immediately */
            /* preceding "if" statements. */

        case Parser::token::SEMICOLON:
        case Parser::token::COMMA:
            pop_context_if('i');
            break;

            /* Any newlines following these tokens can */
            /* indicate the end of an expression. */

        case Parser::token::SYMBOL:
        case Parser::token::STR_CONST:
        case Parser::token::LITERAL_CONST:
        case Parser::token::INT_CONST:
        case Parser::token::FLOAT_CONST:
        case Parser::token::COMPLEX_CONST:
        case Parser::token::RAW_STRING_CONST:
        case Parser::token::NULL_CONST:
        case Parser::token::NEXT:
        case Parser::token::BREAK:
            disable_eat_lines();
            break;

            /* Handle brackets, braces and parentheses */
        case Parser::token::LBB:
            push_context('[');
            push_context('[');
            break;

        case Parser::token::LSQPAREN:
            push_context('[');
            break;

        case Parser::token::LBRACE:
            push_context('{');
            enable_eat_lines();
            break;

        case Parser::token::LPAREN:
            push_context('(');
            break;

        case Parser::token::RSQPAREN:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            disable_eat_lines();
            break;

        case Parser::token::RBRACE:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            break;

        case Parser::token::RPAREN:
            while (peek_context() == 'i')
                pop_context_if('i');
            pop_context();
            disable_eat_lines();
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

  private:
    void unput_(int c);

    /* This is only called following ., so we only care if it is
   an ANSI digit or not */
    int typeofnext();

    rastr::r::parser::Parser::token_type
    numeric_token(rastr::r::parser::Parser::semantic_type* yylval, char c);

    double R_atof(const char* number) {
        return atof(number);
    }

    void clear_token_buffer() {
        token_buffer_.clear();
    }

    void push_token_buffer(char ch) {
        token_buffer_.push_back(ch);
    }

    std::string& get_token_buffer() {
        return token_buffer_;
    }

    bool matched_pair(char left, char right) {
        if (left == '(') {
            return right == ')';
        }
        if (left == '{') {
            return right == '}';
        }
        if (left == '[') {
            return right == ']';
        }
        if (left == '|') {
            return right == '|';
        }
        return false;
    }

    rastr::ast::RNode* saved_yylval_;
    Parser::location_type saved_yylloc_;
    int saved_token_;
    bool saved_;
    bool eat_lines_;
    std::string context_;
    std::string token_buffer_;
};

} // namespace parser
} // namespace r
} // namespace rastr

#endif /* RASTR_LEXER_HPP */

/*
 *<quoted_identifier>{
    `                           { BEGIN(INITIAL); std::cout <<
"QuotedIdentifer(" << get_token_buffer() << ")"; }
    \\`                         { get_token_buffer().append(yytext);  }
    [^\\`]*                     { get_token_buffer().append(yytext); }
}
 */
