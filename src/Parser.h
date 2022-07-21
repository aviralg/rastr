#ifndef RASTR_PARSER_H
#define RASTR_PARSER_H

#include <rastr/api.h>
#include "Lexer.h"
#include "Input.h"
#include "utilities.h"
#include "interop.h"

const int LOWEST_PRECEDENCE = 0;
const int INVALID_PRECEDENCE = -1;

void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root);

//#define RETURN_IF_ERROR(node)

rastr_node_t UNDEFINED_NODE{(std::size_t)(-1)};

bool rastr_node_is_undefined(rastr_node_t node) {
    return node.index == (std::size_t)(-1);
}

class Parser {
  public:
    Parser(Input& input, std::size_t capacity)
        : ast_(rastr_ast_create(capacity))
        , lexer_(input, ast_)
        , saved_tok_(UNDEFINED_NODE) {
    }

    /*
    <prog>	::=	END_OF_INPUT
              | '\n'
              | <expr_or_assign_or_help> '\n'
              |	<expr_or_assign_or_help> ';'
    */
    rastr_ast_t parse_prog() {
        // while (true) {
        //    raster_node_t node = next_token_();
        //    rastr_node_type_t type = raster_node_type(node);
        //
        //    if (type == End) {
        //        children.push_back(node);
        //        break;
        //    }
        //
        //    else if (type == Newline) {
        //        continue;
        //    }
        //
        //    else {
        //        rastr_node_t expr = parse_expr(node, LOWEST_PRECEDENCE);
        //        RETURN_IF_ERROR(expr);
        //        rastr_node_t term = next_token_();
        //        RETURN_IF_ERROR(term);
        //        rastr_node_type_t term_type = rastr_node_type(term);
        //        if (term == Semicolon || term_type == Newline) {
        //            children.push_back(rastr_node_statement_create(expr,
        //            term));
        //        }
        //    }
        //}
        rastr_node_t node = parse_expr(LOWEST_PRECEDENCE, next_token_());
        rastr_ast_set_root(ast_, node);
        return ast_;
    }

    // expr ::=  NUM_CONST
    //        |	STR_CONST
    //        |	NULL_CONST
    //        |	PLACEHOLDER
    //        |	SYMBOL
    //        |	'{' <exprlist> '}'
    //        |	'(' <expr_or_assign_or_help> ')'
    //        |	'-' <expr> %prec UMINUS
    //        |	'+' <expr> %prec UMINUS
    //        |	'!' <expr> %prec UNOT
    //        |	'~' <expr> %prec TILDE
    //        |	'?' <expr_or_assign_or_help>
    //        |	<expr> ':'  <expr>
    //        |	<expr> '+'  <expr>
    //        |	<expr> '-' <expr>
    //        |	<expr> '*' <expr>
    //        |	<expr> '/' <expr>
    //        |	<expr> '^' <expr>
    //        |	<expr> SPECIAL <expr>
    //        |	<expr> '~' <expr>
    //        |	<expr> LT <expr>
    //        |	<expr> LE <expr>
    //        |	<expr> EQ <expr>
    //        |	<expr> NE <expr>
    //        |	<expr> GE <expr>
    //        |	<expr> GT <expr>
    //        |	<expr> AND <expr>
    //        |	<expr> OR <expr>
    //        |	<expr> AND2 <expr>
    //        |	<expr> OR2 <expr>
    //        |	<expr> PIPE <expr>
    //        |	<expr> PIPEBIND <expr>
    //        |	<expr> LEFT_ASSIGN <expr>
    //        |	<expr> RIGHT_ASSIGN <expr>
    //        |	FUNCTION '(' <formlist> ')' cr <expr_or_assign_or_help> %prec
    //        LOW |	'\\' '(' <formlist> ')' cr <expr_or_assign_or_help>
    //        %prec LOW |	<expr> '(' <sublist> ')' |	IF ifcond
    //        <expr_or_assign_or_help>
    //        |	IF ifcond <expr_or_assign_or_help> ELSE <expr_or_assign_or_help>
    //        |	FOR forcond <expr_or_assign_or_help> %prec FOR
    //        |	WHILE cond <expr_or_assign_or_help>
    //        |	REPEAT <expr_or_assign_or_help>
    //        |	<expr> LBB <sublist> ']' ']'
    //        |	<expr> '[' <sublist> ']'
    //        |	SYMBOL NS_GET SYMBOL
    //        |	SYMBOL NS_GET STR_CONST
    //        |	STR_CONST NS_GET SYMBOL
    //        |	STR_CONST NS_GET STR_CONST
    //        |	SYMBOL NS_GET_INT SYMBOL
    //        |	SYMBOL NS_GET_INT STR_CONST
    //        |	STR_CONST NS_GET_INT SYMBOL
    //        |	STR_CONST NS_GET_INT STR_CONST
    //        |	<expr> '$' SYMBOL
    //        |	<expr> '$' STR_CONST
    //        |	<expr> '@' SYMBOL
    //        |	<expr> '@' STR_CONST
    //        |	NEXT
    //        |	BREAK
    rastr_node_t parse_expr(int precedence, rastr_node_t fst_node) {
        rastr_node_type_t type = rastr_node_type(ast_, fst_node);
        rastr_node_t left = parse_prefix_expr(fst_node);

        if (rastr_node_is_undefined(left)) {
            rastr_log_error("1unhandled node type '%s'",
                            rastr_node_type_to_string(type));
        }

        while (true) {
            rastr_node_t node = next_token_();
            rastr_node_type_t cur_type = rastr_node_type(ast_, node);

            if (cur_type == End) {
                break;
            }

            int cur_precedence = get_precedence(cur_type, false);

            if (cur_precedence == INVALID_PRECEDENCE) {
                rastr_log_error("2unhandled node type '%s'",
                                rastr_node_type_to_string(cur_type));
            }

            if (cur_precedence <= precedence) {
                save_token_(node);
                break;
            }

            rastr_node_t new_left =
                parse_infix_expr(left, node, cur_precedence);

            if (!rastr_node_is_undefined(new_left)) {
                left = new_left;
                continue;
            }

            /* check if it is a terminator node */
            // new_left = parse_terminator_expr(left, node);
            //
            // if (new_left != UNDEFINED_NODE) {
            //     left = new_left;
            //     break;
            // }

            rastr_log_error(
                "3unhandled node type '%s'",
                rastr_node_type_to_string(rastr_node_type(ast_, node)));
        }

        return left;
    }

    rastr_node_t parse_prefix_expr(rastr_node_t op) {
        /* null, logical, real, integer, complex, string, symbol, and
         * placeholder don't need extra parsing for completion*/
        if (rastr_node_is_literal(ast_, op)) {
            return op;
        }

        rastr_node_type_t type = rastr_node_type(ast_, op);

        int precedence = get_precedence(type, true);

        if (precedence == INVALID_PRECEDENCE) {
            return UNDEFINED_NODE;
        }

        rastr_node_t expr = parse_expr(precedence, next_token_());
        return rastr_node_unary_expression(ast_, op, expr);
    }

    rastr_node_t
    parse_infix_expr(rastr_node_t left, rastr_node_t op, int precedence) {
        rastr_node_t right = parse_expr(precedence, next_token_());
        return rastr_node_binary_expression(ast_, left, op, right);
    }

  private:
    rastr_ast_t ast_;
    Lexer lexer_;
    rastr_node_t saved_tok_;
    // %left    '?'
    // %left    LOW WHILE FOR REPEAT
    // %right   IF
    // %left    ELSE
    // %right   LEFT_ASSIGN
    // %right   EQ_ASSIGN
    // %left    RIGHT_ASSIGN
    // %left    '~' TILDE
    // %left    OR OR2
    // %left    AND AND2
    // %left    UNOT NOT
    // %nonassoc  GT GE LT LE EQ NE
    // %left		'+' '-'
    // %left    '*' '/'
    // %left    SPECIAL PIPE
    // %left    PIPEBIND
    // %left    ':'
    // %left    UMINUS UPLUS
    // %right   '^'
    // %left    '$' '@'
    // %left    NS_GET NS_GET_INT
    // %nonassoc '(' '[' LBB
    int get_precedence(rastr_node_type_t type, bool prefix) {
        if (prefix) {
            switch (type) {
            case Help:
                return 1;
            case Formula:
                return 8;
            case Not:
                return 11;
            case Minus:
            case Plus:
                return 18;
            default:
                return INVALID_PRECEDENCE;
            }
        }

        else {
            switch (type) {
            case Help:
                return 1;
            case While:
            case For:
            case Repeat:
                return 2;
            case If:
                return 3;
            case Else:
                return 4;
            case LeftAssign:
            case LeftSuperAssign:
            case ColonAssign:
                return 5;
            case EqualAssign:
                return 6;
            case RightAssign:
            case RightSuperAssign:
                return 7;
            case Formula:
                return 8;
            case Or:
            case VectorizedOr:
                return 9;
            case And:
            case VectorizedAnd:
                return 10;
            case Not:
                return 11;
            case LessThan:
            case LessThanEqual:
            case GreaterThan:
            case GreaterThanEqual:
            case Equal:
            case NotEqual:
                return 12;
            case Plus:
            case Minus:
                return 13;
            case Multiplication:
            case Division:
                return 14;
            case Special:
            case PipeForward:
                return 15;
            case PipeBind:
                return 16;
            case Sequence:
                return 17;
            case Power:
                return 19;
            case PartExtract:
            case SlotExtract:
                return 20;
            case PublicNamespace:
            case PrivateNamespace:
                return 21;
            case LeftParen:
            case LeftBracket:
            case DoubleLeftBracket:
                return 22;
            default:
                return INVALID_PRECEDENCE;
            }
        }
    }

    void save_token_(rastr_node_t node) {
        saved_tok_ = node;
    }

    rastr_node_t next_token_() {
        if (!rastr_node_is_undefined(saved_tok_)) {
            rastr_node_t tok = saved_tok_;
            saved_tok_ = UNDEFINED_NODE;
            return tok;
        }

        return lexer_.next_token();
    }
};

#endif /* RASTR_PARSER_H */
