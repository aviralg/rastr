#ifndef RASTR_PARSER_H
#define RASTR_PARSER_H

#include <rastr/api.h>
#include "Lexer.h"
#include "Input.h"
#include "utilities.h"
#include "interop.h"
#include <vector>
#include <iostream>

const int LOWEST_PRECEDENCE = 0;
const int INVALID_PRECEDENCE = -1;

void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root);

#define RETURN_IF_UNDEFINED(node)        \
    if (rastr_node_is_undefined(node)) { \
        return node;                     \
    }

rastr_node_t UNDEFINED_NODE{(std::size_t)(-1)};

bool rastr_node_is_undefined(rastr_node_t node) {
    return node.index == (std::size_t)(-1);
}

class Parser {
  public:
    Parser(Input& input, std::size_t capacity)
        : ast_(rastr_ast_create(capacity)), lexer_(input, ast_), saved_tok_() {
    }

    /*
    <prog>	::=	END_OF_INPUT
              | '\n'
              | <expr_or_assign_or_help> '\n'
              |	<expr_or_assign_or_help> ';'
    */

    /* a program is a sequence of zero or more statements, followed by an
     * optional expression, followed by End token  */
    // <program> ::= <statement>* <expression>? <eof>
    rastr_ast_t parse_prog() {
        std::vector<rastr_node_t> stmts;

        while (true) {
            rastr_node_t node = peek_token_();

            /* if <eof> is encountered, program has been parsed */
            if (rastr_node_type(ast_, node) == End) {
                consume_();
                break;
            }

            if (rastr_node_type(ast_, node) == Newline) {
                consume_();
                continue;
            }

            rastr_node_t stmt = parse_stmt_permissive(End);

            if (rastr_node_is_undefined(stmt)) {
                rastr_log_error("error encountered!");
                return ast_;
            }

            std::cerr << "here\n";
            std::cerr << "type is "
                      << rastr_node_type_to_string(rastr_node_type(ast_, stmt))
                      << "\n";

            stmts.push_back(stmt);
        }

        log_msg("making program");

        rastr_node_t program = rastr_pgm_node(ast_, stmts.size(), stmts.data());

        rastr_ast_set_root(ast_, program);
        return ast_;
    }

    /* parse complete expression followed by a terminator (\n or ;) */
    rastr_node_t parse_stmt() {
        rastr_node_t expr = parse_expr(LOWEST_PRECEDENCE);
        rastr_node_t terminator = peek_token_();

        if (rastr_node_is_terminator(ast_, terminator)) {
            consume_();
            return rastr_dlmtd_node(ast_, expr, terminator);
        }

        return UNDEFINED_NODE;
    }

    /* parse complete expression followed by an actual terminator (\n or ;) or
     * a pseudo terminator such as } or ) */
    rastr_node_t parse_stmt_permissive(rastr_node_type_t terminator_type) {
        log_msg("before expr");
        rastr_node_t expr = parse_expr(LOWEST_PRECEDENCE);
        log_msg("after expr");

        if (rastr_node_is_undefined(expr)) {
            log_msg("here");
            return UNDEFINED_NODE;
        }

        rastr_node_t terminator = peek_token_();

        if (rastr_node_is_terminator(ast_, terminator)) {
            consume_();
            return rastr_dlmtd_node(ast_, expr, terminator);
        }

        else if (rastr_node_type(ast_, terminator) == terminator_type) {
            return expr;
        }

        else if (rastr_node_type(ast_, terminator) == End) {
            return expr;
        }

        return UNDEFINED_NODE;
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
    //        |	IF <ifcond> <expr_or_assign_or_help> ELSE
    //        <expr_or_assign_or_help>
    //        |	FOR <forcond> <expr_or_assign_or_help> %prec FOR
    //        |	WHILE <cond> <expr_or_assign_or_help>
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
    rastr_node_t parse_expr(int precedence, bool missing = false) {
        rastr_node_t left = parse_prefix_expr();

        if (rastr_node_is_undefined(left)) {
            rastr_log_error(
                "1unhandled node type '%s'",
                rastr_node_type_to_string(rastr_node_type(ast_, left)));
        }

        while (true) {
            rastr_node_t node = peek_token_();
            rastr_node_type_t cur_type = rastr_node_type(ast_, node);

            /* terminator is encountered, return; */
            if (rastr_node_is_terminator(ast_, node) || cur_type == End) {
                break;
            }

            ///* if parse_expr is called from parse_block or parse_group, the
            //   expression will be delimited by right paren or right brace. */
            // else if (cur_type == End || cur_type == RightParen || cur_type ==
            // RightBrace) {
            //    break;
            //}

            int cur_precedence = get_precedence(cur_type, false);

            if (cur_precedence == INVALID_PRECEDENCE) {
                rastr_log_error("2unhandled node type '%s', %s",
                                rastr_node_type_to_string(cur_type),
                                rastr_node_symbol_value(ast_, node));
            }

            if (cur_precedence <= precedence) {
                break;
            }

            rastr_node_t new_left = parse_infix_expr(cur_precedence, left);

            if (!rastr_node_is_undefined(new_left)) {
                left = new_left;
                continue;
            }

            else {
                return new_left;
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

    rastr_node_t parse_prefix_expr() {
        log_msg("begin");

        rastr_node_t op = next_token_();
        rastr_node_type_t type = rastr_node_type(ast_, op);

        /* null, logical, real, integer, complex, string, symbol, and
         * placeholder don't need extra parsing for completion*/
        if (rastr_node_is_literal(ast_, op)) {
            return op;
        }

        else if (type == LeftParen) {
            return parse_group(op);
        }

        else if (type == LeftBrace) {
            return parse_block(op);
        }

        else if (type == Repeat) {
            return parse_repeat(op);
        }

        else if (type == While) {
            return parse_while(op);
        }

        else if (type == If) {
            return parse_if_else(op);
        }

        else if (type == Function || type == AnonymousFunction) {
            return parse_definition(op);
        }

        else if (type == Next) {
            return op;
        }

        else if (type == Break) {
            return op;
        }

        int precedence = get_precedence(type, true);

        if (precedence == INVALID_PRECEDENCE) {
            return UNDEFINED_NODE;
        }

        if (type == End) {
            volatile int stop = 1;
            while (stop) {
                ;
            }
        }

        log_msg("token type %s\n", rastr_node_type_to_string(type));

        rastr_node_t expr = parse_expr(precedence);
        return rastr_unop_node(ast_, op, expr);
    }

    rastr_node_t parse_infix_expr(int precedence, rastr_node_t left) {
        rastr_node_t op = next_token_();
        rastr_node_type_t type = rastr_node_type(ast_, op);

        if (type == LeftParen) {
            return parse_call(left, op);
        }

        else if (type == LeftBracket) {
            return parse_indexing(left, op);
        }

        else if (type == DoubleLeftBracket) {
            return parse_subsetting(left, op);
        }

        else {
            /* to correctly parse right-associative operators, reduce precedence
             * by 1 */
            if (type == Power || type == LeftAssign ||
                type == LeftSuperAssign || type == EqualAssign) {
                precedence = precedence - 1;
            }

            rastr_node_t right = parse_expr(precedence);
            if (rastr_node_is_undefined(right)) {
                return UNDEFINED_NODE;
            }

            return rastr_binop_node(ast_, left, op, right);
        }
    }

    rastr_node_t parse_definition(rastr_node_t kw) {
        rastr_node_t lbrack = next_token_();

        if (rastr_node_type(ast_, lbrack) != LeftParen) {
            return UNDEFINED_NODE;
        }

        rastr_node_t params = parse_formlist(lbrack);
        RETURN_IF_UNDEFINED(params);

        lexer_.enable_eat_lines();

        rastr_node_t body = parse_expr(LOWEST_PRECEDENCE);

        RETURN_IF_UNDEFINED(body);

        return rastr_fndefn_node(ast_, kw, params, body);
    }

    rastr_node_t parse_call(rastr_node_t fun, rastr_node_t lbrack) {
        rastr_node_t args = parse_sublist(lbrack);
        RETURN_IF_UNDEFINED(args);

        return rastr_fncall_node(ast_, fun, args);
    }

    rastr_node_t parse_indexing(rastr_node_t obj, rastr_node_t lbrack) {
        rastr_node_t inds = parse_sublist(lbrack);
        RETURN_IF_UNDEFINED(inds);

        return rastr_idx_node(ast_, obj, inds);
    }

    rastr_node_t parse_subsetting(rastr_node_t obj, rastr_node_t lbrack) {
        rastr_node_t inds = parse_sublist(lbrack);
        RETURN_IF_UNDEFINED(inds);

        return rastr_sub_node(ast_, obj, inds);
    }

    rastr_node_t parse_condition(rastr_node_t lbrack) {
        rastr_node_t expr = parse_expr(LOWEST_PRECEDENCE);
        rastr_node_t rbrack = next_token_();

        if (rastr_node_type(ast_, rbrack) != RightParen) {
            return UNDEFINED_NODE;
        }

        return rastr_cnd_node(ast_, lbrack, expr, rbrack);
    }

    rastr_node_t parse_if_else(rastr_node_t if_kw) {
        rastr_node_t lbrack = next_token_();

        if (rastr_node_type(ast_, lbrack) != LeftParen) {
            return UNDEFINED_NODE;
        }

        rastr_node_t cond = parse_condition(lbrack);
        RETURN_IF_UNDEFINED(cond);

        rastr_node_t csq = parse_expr(LOWEST_PRECEDENCE);
        RETURN_IF_UNDEFINED(csq);

        rastr_node_t else_kw = peek_token_();

        if (rastr_node_type(ast_, else_kw) != Else) {
            return rastr_icnd_node(ast_, if_kw, cond, csq);
        }

        consume_();

        rastr_node_t alt = parse_expr(LOWEST_PRECEDENCE);
        RETURN_IF_UNDEFINED(alt);

        return rastr_iecnd_node(ast_, if_kw, cond, csq, else_kw, alt);
    }

    rastr_node_t parse_group(rastr_node_t left_paren) {
        rastr_node_t expr = parse_expr(LOWEST_PRECEDENCE);
        rastr_node_t right_paren = next_token_();

        if (rastr_node_type(ast_, right_paren) != RightParen) {
            return UNDEFINED_NODE;
        }

        return rastr_grp_node(ast_, left_paren, expr, right_paren);
    }

    // <exprlist> ::=
    //              | <expr_or_assign_or_help>
    //              | <exprlist> ';' <expr_or_assign_or_help>
    //              | <exprlist> ';'
    //              | <exprlist> '\n' <expr_or_assign_or_help>
    //              | <exprlist> '\n'
    ;
    rastr_node_t parse_block(rastr_node_t lbrack) {
        rastr_node_t rbrack = UNDEFINED_NODE;
        std::vector<rastr_node_t> exprs;

        while (true) {
            rastr_node_t node = peek_token_();
            rastr_node_type_t type = rastr_node_type(ast_, node);

            if (type == RightBrace) {
                consume_();
                rbrack = node;
                break;
            }

            if (type == End) {
                consume_();
                return UNDEFINED_NODE;
            }

            exprs.push_back(parse_stmt_permissive(RightBrace));
        }

        return rastr_blk_node(ast_, lbrack, exprs.size(), exprs.data(), rbrack);
    }

    // sublist:	sub				{ $$ = xxsublist1($1);	  }
    //        |	sublist cr ',' sub		{ $$ = xxsublist2($1,$4); }
    //        ;
    //
    // sub:
    //    |	expr_or_help
    //    |	SYMBOL EQ_ASSIGN
    //    |	SYMBOL EQ_ASSIGN expr_or_help
    //    |	STR_CONST EQ_ASSIGN
    //    |	STR_CONST EQ_ASSIGN expr_or_help
    //    |	NULL_CONST EQ_ASSIGN
    //    |	NULL_CONST EQ_ASSIGN expr_or_help
    //     ;
    rastr_node_t parse_sub() {
        rastr_node_t name = peek_token_();
        rastr_node_type_t name_type = rastr_node_type(ast_, name);

        if (name_type != Symbol && name_type != String && name_type != Null) {
            return rastr_parg_node(ast_, parse_sub_expr());
        }

        consume_();
        rastr_node_t eq_asgn = peek_token_();

        if (rastr_node_type(ast_, eq_asgn) != EqualAssign) {
            push_token_(name);
            return rastr_parg_node(ast_, parse_sub_expr());
        }

        consume_();
        rastr_node_t expr = parse_sub_expr();

        return rastr_narg_node(ast_, name, eq_asgn, expr);
    }

    /* parses <missing> or <expr_or_help> */
    rastr_node_t parse_sub_expr() {
        rastr_node_t node = peek_token_();
        rastr_node_type_t type = rastr_node_type(ast_, node);

        if (type == Comma || type == RightParen || type == RightBracket) {
            return rastr_msng_node(ast_);
        }

        else {
            return parse_expr(LOWEST_PRECEDENCE);
        }
    }

    rastr_node_t parse_sublist(rastr_node_t lbrack) {
        std::vector<rastr_node_t> exprs;
        rastr_node_t rbrack;
        rastr_node_type_t lbrack_type = rastr_node_type(ast_, lbrack);

        while (true) {
            rastr_node_t node = peek_token_();
            rastr_node_type_t type = rastr_node_type(ast_, node);

            if (lbrack_type == LeftParen && type == RightParen) {
                rbrack = node;
                consume_();
                break;
            }

            else if (lbrack_type == LeftBracket && type == RightBracket) {
                rbrack = node;
                consume_();
                break;
            }

            else if (lbrack_type == DoubleLeftBracket && type == RightBracket) {
                rbrack = node;
                consume_();
                rastr_node_t next_rbrack = next_token_();

                if (rastr_node_type(ast_, next_rbrack) == RightBracket) {
                    // TODO: destroy these nodes
                    // rastr_node_destroy(ast_, rbrack);
                    // rastr_node_destroy(ast_, next_rbrack);
                    rbrack = rastr_node_delimiter(ast_, DoubleRightBracket);

                    break;
                }

                return UNDEFINED_NODE;
            }

            else if (type == End) {
                consume_();
                return UNDEFINED_NODE;
            }

            rastr_node_t sub = parse_sub();
            lexer_.enable_eat_lines();

            node = peek_token_();
            if (rastr_node_type(ast_, node) == Comma) {
                consume_();
                sub = rastr_dlmtd_node(ast_, sub, node);
            }

            exprs.push_back(sub);
        }

        return rastr_args_node(
            ast_, lbrack, exprs.size(), exprs.data(), rbrack);
    }

    // formlist:					{ $$ = xxnullformal(); }
    //     |	SYMBOL				{ $$ = xxfirstformal0($1);
    //     modif_token( &@1, SYMBOL_FORMALS ) ; } |	SYMBOL EQ_ASSIGN
    //     expr_or_help	{ $$ = xxfirstformal1($1,$3); 	modif_token( &@1,
    //     SYMBOL_FORMALS ) ; modif_token( &@2, EQ_FORMALS ) ; } |
    //     formlist ',' SYMBOL		{ $$ = xxaddformal0($1,$3, &@3);
    //     modif_token( &@3, SYMBOL_FORMALS ) ; } |	formlist ',' SYMBOL
    //     EQ_ASSIGN expr_or_help { $$ = xxaddformal1($1,$3,$5,&@3);
    //     modif_token( &@3, SYMBOL_FORMALS ) ; modif_token( &@4, EQ_FORMALS )
    //     ;}
    rastr_node_t parse_formlist(rastr_node_t lbrack) {
        std::vector<rastr_node_t> exprs;
        rastr_node_t rbrack;

        while (true) {
            rastr_node_t node = peek_token_();
            rastr_node_type_t type = rastr_node_type(ast_, node);

            if (type == RightParen) {
                consume_();
                rbrack = node;
                break;
            }

            if (type == End) {
                consume_();
                return UNDEFINED_NODE;
            }

            rastr_node_t param = parse_expr(LOWEST_PRECEDENCE);

            node = peek_token_();
            if (rastr_node_type(ast_, node) == Comma) {
                consume_();
                param = rastr_dlmtd_node(ast_, param, node);
            }

            exprs.push_back(param);
        }

        return rastr_params_node(
            ast_, lbrack, exprs.size(), exprs.data(), rbrack);
    }

    rastr_node_t parse_repeat(rastr_node_t kw) {
        rastr_node_t body = parse_expr(LOWEST_PRECEDENCE);
        return rastr_rlp_node(ast_, kw, body);
    }

    rastr_node_t parse_while(rastr_node_t kw) {
        rastr_node_t lbrack = next_token_();

        if (rastr_node_type(ast_, lbrack) != LeftParen) {
            return UNDEFINED_NODE;
        }

        rastr_node_t cond = parse_condition(lbrack);
        RETURN_IF_UNDEFINED(cond);

        rastr_node_t body = parse_expr(LOWEST_PRECEDENCE);
        RETURN_IF_UNDEFINED(body);

        return rastr_wlp_node(ast_, kw, cond, body);
    }

  private:
    rastr_ast_t ast_;
    Lexer lexer_;
    std::vector<rastr_node_t> saved_tok_;
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
                return LOWEST_PRECEDENCE;
            }
        }

        else {
            switch (type) {
            case Help:
                return 1;
            // case While:
            // case For:
            // case Repeat:
            //     return 2;
            // case If:
            //     return 3;
            // case Else:
            //     return 4;
            case EqualAssign:
                return 5;
            case LeftAssign:
            case LeftSuperAssign:
            case ColonAssign:
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
            case Range:
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
                return LOWEST_PRECEDENCE;
            }
        }
    }

    rastr_node_t peek_token_() {
        if (saved_tok_.empty()) {
            saved_tok_.push_back(lexer_.next_token());
        }
        return saved_tok_.back();
    }

    rastr_node_t next_token_() {
        if (!saved_tok_.empty()) {
            rastr_node_t tok = saved_tok_.back();
            saved_tok_.pop_back();
            return tok;
        }

        return lexer_.next_token();
    }

    void consume_() {
        saved_tok_.pop_back();
    }

    void push_token_(rastr_node_t node) {
        saved_tok_.push_back(node);
    }
};

#endif /* RASTR_PARSER_H */
