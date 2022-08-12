#ifndef RASTR_PARSER_H
#define RASTR_PARSER_H

#include <rastr/api.h>
#include "Lexer.h"
#include "Input.h"
#include "utilities.h"
#include "interop.h"
#include <vector>
#include <iostream>
#include <sstream>
#include "internal_api.h"

const int LOWEST_PRECEDENCE = 0;
const int INVALID_PRECEDENCE = -1;

/* TODO: remove this. */
void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root);

#define PROPAGATE_ERROR(node)                   \
    if (rastr_node_type(ast_, node) == Error) { \
        res = node;                             \
        goto end;                               \
    }

#define PROPAGATE_ERROR_IF_NOT(node, type, msg) \
    if (rastr_node_type(ast_, node) != type) {  \
        res = pcont_error(msg);                 \
        goto end;                               \
    }

#define PROPAGATE_ERROR_IF(node, type, msg)    \
    if (rastr_node_type(ast_, node) == type) { \
        res = pcont_error(msg);                \
        goto end;                              \
    }

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
    Parser(Input& input, rastr_ast_t& ast)
        : ast_(ast), lexer_(input, ast_), saved_tok_(), pcont_() {
    }

    rastr_node_t parse_prog() {
        rastr_node_t res;
        rastr_node_t end;

        pcont_push("<pgm> ▸ <stmt>* <expr>? <eof>");

        std::vector<rastr_node_t> stmts;

        rastr_node_t beg = next_token_();
        PROPAGATE_ERROR_IF_NOT(beg, Beg, "expected '<beg>'")

        while (true) {
            rastr_node_t node = peek_token_();

            /* if <eof> is encountered, program has been parsed */
            if (rastr_node_type(ast_, node) == End) {
                consume_();
                end = node;
                break;
            }

            /* this case happens if there are comments or spaces at the
               beginning of the file. since we have not yet read a stmt (which
               would have eaten up subsequent newlines), we have to eat and
               destroy this newlines until we encounter a non-newline token */
            else if (rastr_node_type(ast_, node) == Newline) {
                consume_();
                rastr_node_destroy(ast_, node);
                continue;
            }

            else {
                rastr_node_t stmt = parse_stmt(End);
                PROPAGATE_ERROR(stmt);

                stmts.push_back(stmt);
            }
        }

        res = rastr_pgm_node(ast_, beg, stmts.size(), stmts.data(), end);

    end:
        pcont_pop();
        return res;
    }

    /* parse complete expression followed by an actual terminator (\n or ;) or
     * a contextual terminator such as } or ) */
    rastr_node_t parse_stmt(rastr_node_type_t cont_term_type) {
        rastr_node_t res;
        rastr_node_t terminator;
        rastr_node_type_t term_type;

        pcont_push("<stmt> ▸ <expr> ; | <expr> \\n | <expr> <eof>");

        rastr_node_t expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        terminator = peek_token_();
        term_type = rastr_node_type(ast_, terminator);

        if (term_type == cont_term_type || term_type == End) {
            res = expr;
        }

        /* TODO: replace this with direct check for term_type */
        else if (rastr_node_is_terminator(ast_, terminator)) {
            while (rastr_node_is_terminator(ast_, terminator)) {
                consume_();
                /* attach delimiter if ; or , */
                if (term_type != Newline) {
                    expr = rastr_dlmtd_node(ast_, expr, terminator);
                }
                /* delete node if Newline */
                else {
                    rastr_node_destroy(ast_, terminator);
                }

                terminator = peek_token_();
                term_type = rastr_node_type(ast_, terminator);
            }
            res = expr;
        }

        else {
            /* TODO: add token type/value */
            res = pcont_error("expected ';' or '\n'");
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_expr(int precedence) {
        pcont_push("<expr>");

        rastr_node_t res = parse_prefix_expr();
        PROPAGATE_ERROR(res);

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

            if (cur_precedence <= precedence) {
                break;
            }

            res = parse_infix_expr(cur_precedence, res);
            PROPAGATE_ERROR(res);

            /* check if it is a terminator node */
            // new_left = parse_terminator_expr(left, node);
            //
            // if (new_left != UNDEFINED_NODE) {
            //     left = new_left;
            //     break;
            // }
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_prefix_expr() {
        rastr_node_t res;

        rastr_node_t op = next_token_();
        rastr_node_type_t type = rastr_node_type(ast_, op);

        /* null, logical, real, integer, complex, string, and symbol don't need
         * extra parsing for completion*/
        if (rastr_node_is_literal(ast_, op)) {
            res = op;
            PROPAGATE_ERROR(res);
        }

        else if (type == LeftParen) {
            res = parse_grp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == LeftBrace) {
            res = parse_blk(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == Repeat) {
            res = parse_rlp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == While) {
            res = parse_wlp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == For) {
            res = parse_flp(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == If) {
            res = parse_iecnd(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == Function || type == AnonymousFunction) {
            res = parse_fndefn(op);
            PROPAGATE_ERROR(res);
        }

        else if (type == Next || type == Break) {
            res = parse_nuop(op);
            PROPAGATE_ERROR(res);
        }

        else {
            int precedence = get_precedence(type, true);

            rastr_node_t expr = parse_expr(precedence);
            PROPAGATE_ERROR(expr);

            res = rastr_unop_node(ast_, op, expr);
        }

    end:
        return res;
    }

    rastr_node_t parse_infix_expr(int precedence, rastr_node_t left) {
        rastr_node_t res;

        rastr_node_t op = next_token_();
        rastr_node_type_t type = rastr_node_type(ast_, op);

        if (type == LeftParen) {
            res = parse_fncall(left, op);
            PROPAGATE_ERROR(res);
        }

        else if (type == LeftBracket) {
            res = parse_idx(left, op);
            PROPAGATE_ERROR(res);
        }

        else if (type == DoubleLeftBracket) {
            res = parse_sub(left, op);
            PROPAGATE_ERROR(res);
        }

        else {
            /* to correctly parse right-associative operators, reduce precedence
             * by 1 */
            if (type == Power || type == LeftAssign ||
                type == LeftSuperAssign || type == EqualAssign) {
                precedence = precedence - 1;
            }

            rastr_node_t right = parse_expr(precedence);
            PROPAGATE_ERROR(right);

            res = rastr_binop_node(ast_, left, op, right);
        }

    end:
        return res;
    }

    rastr_node_t parse_grp(rastr_node_t left_paren) {
        rastr_node_t res;
        rastr_node_t expr;
        rastr_node_t right_paren;

        pcont_push("<grp>  ▸ ( <expr> )");

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        right_paren = next_token_();
        PROPAGATE_ERROR_IF_NOT(right_paren, RightParen, "expected ')'")

        res = rastr_grp_node(ast_, left_paren, expr, right_paren);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_blk(rastr_node_t lbrack) {
        rastr_node_t res;
        rastr_node_t rbrack;
        rastr_node_t stmt;

        pcont_push("<blk> ▸ { <stmt>* <expr>? }");

        std::vector<rastr_node_t> exprs;

        while (true) {
            rastr_node_t node = peek_token_();
            rastr_node_type_t type = rastr_node_type(ast_, node);

            if (type == RightBrace) {
                consume_();
                rbrack = node;
                break;
            }

            // TODO: consume_();
            PROPAGATE_ERROR_IF(node, End, "unexpected <eof>");

            stmt = parse_stmt(RightBrace);
            PROPAGATE_ERROR(stmt);

            exprs.push_back(stmt);
        }

        lexer_.disable_eat_lines();

        res = rastr_blk_node(ast_, lbrack, exprs.size(), exprs.data(), rbrack);

    end:
        pcont_pop();
        return res;
    }

    /* repeat <expr> */
    rastr_node_t parse_rlp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t body;

        pcont_push("<rlp> ▸ repeat <expr>");

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_rlp_node(ast_, kw, body);

    end:
        pcont_pop();
        return res;
    }

    /* while <cond> <expr> */
    rastr_node_t parse_wlp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t cond;
        rastr_node_t body;

        pcont_push("<wlp> ▸ while <cond> <expr>");

        cond = parse_cond();
        PROPAGATE_ERROR(cond);

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_wlp_node(ast_, kw, cond, body);

    end:
        pcont_pop();
        return res;
    }

    /* for <iter> <expr> */
    rastr_node_t parse_flp(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t iter;
        rastr_node_t body;

        pcont_push("<flp> ▸ for <iter> <expr>");

        iter = parse_iter();
        PROPAGATE_ERROR(iter);

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_flp_node(ast_, kw, iter, body);

    end:
        pcont_pop();
        return res;
    }

    /* <icnd> | <iecnd> : if <cond> <expr> [else <expr>] */
    rastr_node_t parse_iecnd(rastr_node_t if_kw) {
        rastr_node_t res;
        rastr_node_t cond;
        rastr_node_t csq;
        rastr_node_t else_kw;
        rastr_node_t alt;

        pcont_push("<icnd> | <iecnd> ▸ if <cond> <expr> [else <expr>]");

        cond = parse_cond();
        PROPAGATE_ERROR(cond);

        csq = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(csq);

        else_kw = peek_token_();

        /* there is no else following the if */
        if (rastr_node_type(ast_, else_kw) != Else) {
            res = rastr_icnd_node(ast_, if_kw, cond, csq);
        }
        /* else follows if */
        else {
            consume_();

            alt = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(alt);

            res = rastr_iecnd_node(ast_, if_kw, cond, csq, else_kw, alt);
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_fndefn(rastr_node_t kw) {
        rastr_node_t res;
        rastr_node_t params;
        rastr_node_t body;

        pcont_push("<fndefn> ▸ function <params> <expr>");

        params = parse_params();
        PROPAGATE_ERROR(params);

        lexer_.enable_eat_lines();

        body = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(body);

        res = rastr_fndefn_node(ast_, kw, params, body);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_nuop(rastr_node_t op) {
        rastr_node_t res;

        pcont_push("<nuop> ▸ <op>");

        res = rastr_nuop_node(ast_, op);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_fncall(rastr_node_t fun, rastr_node_t lbrack) {
        rastr_node_t res;
        rastr_node_t args;

        pcont_push("<fncall> ▸ <fun> <args>");

        args = parse_args(lbrack);
        PROPAGATE_ERROR(args);

        res = rastr_fncall_node(ast_, fun, args);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_idx(rastr_node_t obj, rastr_node_t lbrack) {
        rastr_node_t res;
        rastr_node_t inds;

        pcont_push("<idx> ▸ <obj> <inds>");

        inds = parse_args(lbrack);
        PROPAGATE_ERROR(inds);

        res = rastr_idx_node(ast_, obj, inds);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_sub(rastr_node_t obj, rastr_node_t lbrack) {
        rastr_node_t res;
        rastr_node_t inds;

        pcont_push("<sub> ▸ <obj> <inds>");

        inds = parse_args(lbrack);
        PROPAGATE_ERROR(inds);

        res = rastr_sub_node(ast_, obj, inds);

    end:
        pcont_pop();
        return res;
    }

    /* <cond>: ( <expr> ) */
    rastr_node_t parse_cond() {
        rastr_node_t res;
        rastr_node_t lbrack;
        rastr_node_t expr;
        rastr_node_t rbrack;

        pcont_push("<cond> ▸ ( <expr> )");

        lbrack = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbrack, LeftParen, "expected '('")

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr)

        rbrack = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbrack, RightParen, "expected ')'")

        lexer_.enable_eat_lines();
        res = rastr_cnd_node(ast_, lbrack, expr, rbrack);

    end:
        pcont_pop();
        return res;
    }

    /* <iter>: (<var> in <expr>) */
    rastr_node_t parse_iter() {
        rastr_node_t res;
        rastr_node_t lbrack;
        rastr_node_t var;
        rastr_node_t kw;
        rastr_node_t expr;
        rastr_node_t rbrack;

        pcont_push("<iter> ▸ (<var> in <expr>)");

        lbrack = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbrack, LeftParen, "expected '('")

        var = next_token_();
        PROPAGATE_ERROR_IF_NOT(var, Symbol, "expected symbol")

        kw = next_token_();
        PROPAGATE_ERROR_IF_NOT(kw, In, "expected 'in'")

        expr = parse_expr(LOWEST_PRECEDENCE);
        PROPAGATE_ERROR(expr);

        rbrack = next_token_();
        PROPAGATE_ERROR_IF_NOT(rbrack, RightParen, "expected ')'")

        lexer_.enable_eat_lines();

        res = rastr_iter_node(ast_, lbrack, var, kw, expr, rbrack);

    end:
        pcont_pop();
        return res;
    }

    /* <params> : (  | (<param>,)* <param> ) */
    rastr_node_t parse_params() {
        rastr_node_t res;
        rastr_node_t lbrack;
        rastr_node_t rbrack;
        rastr_node_t node;
        rastr_node_t param;
        std::vector<rastr_node_t> params;

        pcont_push("<params> : (  | (<param>,)* <param> )");

        lbrack = next_token_();
        PROPAGATE_ERROR_IF_NOT(lbrack, LeftParen, "expected '('")

        while (true) {
            node = peek_token_();
            rastr_node_type_t type = rastr_node_type(ast_, node);

            if (type == RightParen) {
                consume_();
                rbrack = node;
                break;
            }

            PROPAGATE_ERROR_IF(node, End, "unexpected <eof>")

            param = parse_param();
            PROPAGATE_ERROR(param);

            node = peek_token_();
            if (rastr_node_type(ast_, node) == Comma) {
                consume_();
                param = rastr_dlmtd_node(ast_, param, node);
            }

            params.push_back(param);
        }

        res = rastr_params_node(
            ast_, lbrack, params.size(), params.data(), rbrack);

    end:
        pcont_pop();
        return res;
    }

    /* <param> : <symbol> | <symbol> = <expr> */
    rastr_node_t parse_param() {
        rastr_node_t res;
        rastr_node_t name;
        rastr_node_t op;
        rastr_node_t expr;

        pcont_push("<param> : <symbol> | <symbol> = <expr>");

        name = next_token_();
        PROPAGATE_ERROR_IF_NOT(name, Symbol, "expected <symbol>")

        op = peek_token_();

        /* <param> is of the form <symbol> = <expr> */
        if (rastr_node_type(ast_, op) == EqualAssign) {
            consume_();

            expr = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(expr)

            res = rastr_dparam_node(ast_, name, op, expr);
        }

        /* <param> is of the form <symbol> */
        else {
            res = rastr_ndparam_node(ast_, name);
        }

    end:
        pcont_pop();
        return res;
    }

    /* <args> : (  | (<arg>,)* <arg> ) */
    rastr_node_t parse_args(rastr_node_t lbrack) {
        rastr_node_t res;
        rastr_node_t rbrack;
        rastr_node_t next_rbrack;
        rastr_node_t node;
        rastr_node_t arg;
        std::vector<rastr_node_t> args;

        pcont_push("<args> : (  | (<arg>,)* <arg> )");

        rastr_node_type_t lbrack_type = rastr_node_type(ast_, lbrack);

        while (true) {
            node = peek_token_();
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
                next_rbrack = next_token_();

                PROPAGATE_ERROR_IF_NOT(next_rbrack, RightBracket, "expected ]");

                /* to retain the gap, it is easier to change type of rbrack */
                /* TODO: read gap from next_rbrack */
                rastr_dlmtr_set_type(ast_, rbrack, DoubleRightBracket);

                /* destroy these nodes as they are not needed */
                rastr_node_destroy(ast_, next_rbrack);

                break;
            }

            PROPAGATE_ERROR_IF(node, End, "unexpected <eof>")

            arg = parse_arg();
            PROPAGATE_ERROR(arg)

            node = peek_token_();
            if (rastr_node_type(ast_, node) == Comma) {
                consume_();
                lexer_.enable_eat_lines();
                arg = rastr_dlmtd_node(ast_, arg, node);
            }

            args.push_back(arg);
        }

        res = rastr_args_node(ast_, lbrack, args.size(), args.data(), rbrack);

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_arg() {
        rastr_node_t res;
        rastr_node_t name;
        rastr_node_t op;
        rastr_node_t mexpr;

        pcont_push("<arg> : <mexpr> | <symbol> = <mexpr> | <str> = <mexpr> | "
                   "<null> = <mexpr>");

        name = peek_token_();
        rastr_node_type_t name_type = rastr_node_type(ast_, name);

        /* <arg> is of the form <mexpr> */
        if (name_type != Symbol && name_type != String && name_type != Null) {
            rastr_node_t mexpr = parse_mexpr();
            PROPAGATE_ERROR(mexpr)

            res = rastr_parg_node(ast_, mexpr);
        }

        /* <arg> may have any of the following forms:
           <symbol> = <mexpr>
           <str> = <mexpr>
           <null> = <mexpr> */
        else {
            consume_();
            op = peek_token_();

            /* <arg> is <mexpr> */
            if (rastr_node_type(ast_, op) != EqualAssign) {
                push_token_(name);

                mexpr = parse_mexpr();
                PROPAGATE_ERROR(mexpr)

                res = rastr_parg_node(ast_, mexpr);
            }

            /* <arg> has one of the following forms:
               <symbol> = <mexpr>
               <str> = <mexpr>
               <null> = <mexpr> */
            else {
                consume_();

                mexpr = parse_mexpr();
                PROPAGATE_ERROR(mexpr)

                res = rastr_narg_node(ast_, name, op, mexpr);
            }
        }

    end:
        pcont_pop();
        return res;
    }

    rastr_node_t parse_mexpr() {
        rastr_node_t res;
        rastr_node_t node;

        pcont_push("<mexpr> : <msng> | <expr>");

        node = peek_token_();
        rastr_node_type_t type = rastr_node_type(ast_, node);

        if (type == Comma || type == RightParen || type == RightBracket) {
            res = rastr_msng_node(ast_, rastr_gap_node(ast_, 0, nullptr));
        }

        else {
            res = parse_expr(LOWEST_PRECEDENCE);
            PROPAGATE_ERROR(res);
        }

    end:
        pcont_pop();
        return res;
    }

    void pcont_push(const char* prod) {
        pcont_.push_back(prod);
    }

    void pcont_pop() {
        pcont_.pop_back();
    }

    rastr_node_t pcont_error(const char* msg) {
        std::ostringstream sstr;

        sstr << "\nparsing error: " << msg << std::endl;

        for (int i = pcont_.size() - 1; i >= 1; --i) {
            sstr << "               ├╴ " << pcont_[i] << std::endl;
        }

        sstr << "               └╴ " << pcont_[0];

        std::string str = sstr.str();

        return rastr_err_node(ast_, str.c_str());
    }

  private:
    rastr_ast_t ast_;
    Lexer lexer_;
    std::vector<rastr_node_t> saved_tok_;
    std::vector<const char*> pcont_;
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
    // %left    '$' '@'// %left    NS_GET NS_GET_INT
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
