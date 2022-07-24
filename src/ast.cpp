#include <rastr/api.h>
#include "internal_api.h"
#include "utilities.h"
#include "logger.h"
#include "Pool.h"

int id_counter = 0;

#define NODE_TYPE_ERROR(expected, actual)                 \
    fail_with("incorrect node type; expected %s, got %s", \
              expected,                                   \
              rastr_node_type_to_string(actual));

struct rastr_node_impl_t {
    rastr_node_type_t type;
    int id;

    union {
        struct {
            char* syntax;
        } operator_node;

        struct {
            char* syntax;
        } keyword_node;

        struct {
            char* message;
        } error_node;

        struct {
            char* syntax;
            int value;
        } logical_node;

        struct {
            char* syntax;
            int value;
        } integer_node;

        struct {
            char* syntax;
            double value;
        } real_node;

        struct {
            char* syntax;
            Rcomplex value;
        } complex_node;

        struct {
            char* syntax;
            char* value;
        } string_node;

        struct {
            char* syntax;
            char* value;
        } symbol_node;

        struct {
            rastr_node_t op;
            rastr_node_t expr;
        } unary_node;

        struct {
            rastr_node_t left_expr;
            rastr_node_t op;
            rastr_node_t right_expr;
        } binary_node;

        struct {
            int size;
            rastr_node_t* nodes;
        } sequence_node;

        struct {
            rastr_node_t left_brace;
            rastr_node_t expressions;
            rastr_node_t right_brace;
        } block_node;

        struct {
            rastr_node_t left_paren;
            rastr_node_t expr;
            rastr_node_t right_paren;
        } group_node;

        struct {
            rastr_node_t expr;
            rastr_node_t terminator;
        } statement_node;

        struct {
            rastr_node_t statements;
        } program_node;

        struct {
            rastr_node_t kw;
            rastr_node_t body;
        } rloop_node;

        struct {
            rastr_node_t kw;
            rastr_node_t cond;
            rastr_node_t body;
        } wloop_node;

        struct {
            rastr_node_t if_kw;
            rastr_node_t cond;
            rastr_node_t csq;
        } ifcond_node;

        struct {
            rastr_node_t if_kw;
            rastr_node_t cond;
            rastr_node_t csq;
            rastr_node_t else_kw;
            rastr_node_t alt;
        } ifelsecond_node;

        struct {
            rastr_node_t name;
            rastr_node_t op;
            rastr_node_t expr;
        } named_node;

        struct {
            rastr_node_t ldelim;
            rastr_node_t args;
            rastr_node_t rdelim;
        } arguments_node;

        struct {
            rastr_node_t fun;
            rastr_node_t args;
        } call_node;

        struct {
            rastr_node_t ldelim;
            rastr_node_t nodes;
            rastr_node_t rdelim;
        } indices_node;

        struct {
            rastr_node_t obj;
            rastr_node_t indices;
        } indexing_node;

    } node;
};

typedef rastr_node_impl_t* rastr_node_ptr_t;

void rastr_node_destroy(rastr_node_ptr_t ptr);

struct rastr_ast_impl_t {
    Pool<rastr_node_impl_t, rastr_node_destroy>* pool;
    rastr_node_t root;
};

const int INDENTATION = 4;

/********************************************************************************
 Node Type
********************************************************************************/
bool rastr_node_type_is_operator(rastr_node_type_t type) {
    switch (type) {
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
    case PublicNamespace:
    case PrivateNamespace:
    case Range:
    case Help:
    case SlotExtract:
    case Formula:
    case PartExtract:
    case AnonymousFunction:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_keyword(rastr_node_type_t type) {
    switch (type) {
    case Function:
    case While:
    case Repeat:
    case For:
    case In:
    case If:
    case Else:
    case Next:
    case Break:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_delimiter(rastr_node_type_t type) {
    switch (type) {
    case LeftParen:
    case RightParen:
    case LeftBrace:
    case RightBrace:
    case LeftBracket:
    case RightBracket:
    case DoubleLeftBracket:
    case DoubleRightBracket:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_terminator(rastr_node_type_t type) {
    switch (type) {
    case Semicolon:
    case Newline:
    case Comma:
        return true;
    default:
        return false;
    }
}

bool rastr_node_type_is_literal(rastr_node_type_t type) {
    switch (type) {
    case Null:
    case Logical:
    case Integer:
    case Real:
    case Complex:
    case String:
    case Symbol:
    case Placeholder:
        return true;
    default:
        return false;
    }
}

const char* rastr_node_type_to_string(rastr_node_type_t type) {
    switch (type) {
    case Special:
        return "Special";
    case Plus:
        return "Plus";
    case Minus:
        return "Minus";
    case Multiplication:
        return "Multiplication";
    case Division:
        return "Division";
    case Power:
        return "Power";
    case LessThan:
        return "LessThan";
    case LessThanEqual:
        return "LessThanEqual";
    case GreaterThan:
        return "GreaterThan";
    case GreaterThanEqual:
        return "GreaterThanEqual";
    case Equal:
        return "Equal";
    case NotEqual:
        return "NotEqual";
    case Not:
        return "Not";
    case And:
        return "And";
    case VectorizedAnd:
        return "VectorizedAnd";
    case Or:
        return "Or";
    case VectorizedOr:
        return "VectorizedOr";
    case EqualAssign:
        return "EqualAssign";
    case LeftAssign:
        return "LeftAssign";
    case RightAssign:
        return "RightAssign";
    case LeftSuperAssign:
        return "LeftSuperAssign";
    case RightSuperAssign:
        return "RightSuperAssign";
    case ColonAssign:
        return "ColonAssign";
    case PipeForward:
        return "PipeForward";
    case PipeBind:
        return "PipeBind";
    case PublicNamespace:
        return "PublicNamespace";
    case PrivateNamespace:
        return "PrivateNamespace";
    case Range:
        return "Range";
    case Help:
        return "Help";
    case SlotExtract:
        return "SlotExtract";
    case Formula:
        return "Formula";
    case PartExtract:
        return "PartExtract";
    case AnonymousFunction:
        return "AnonymousFunction";
    case Function:
        return "Function";
    case While:
        return "While";
    case Repeat:
        return "Repeat";
    case For:
        return "For";
    case In:
        return "In";
    case If:
        return "If";
    case Else:
        return "Else";
    case Next:
        return "Next";
    case Break:
        return "Break";
    case LeftParen:
        return "LeftParen";
    case RightParen:
        return "RightParen";
    case LeftBrace:
        return "LeftBrace";
    case RightBrace:
        return "RightBrace";
    case LeftBracket:
        return "LeftBracket";
    case RightBracket:
        return "RightBracket";
    case DoubleLeftBracket:
        return "DoubleLeftBracket";
    case DoubleRightBracket:
        return "DoubleRightBracket";
    case Semicolon:
        return "Semicolon";
    case Newline:
        return "Newline";
    case Comma:
        return "Comma";
    case Null:
        return "Null";
    case Logical:
        return "Logical";
    case Integer:
        return "Integer";
    case Real:
        return "Real";
    case Complex:
        return "Complex";
    case String:
        return "String";
    case Symbol:
        return "Symbol";
    case Placeholder:
        return "Placeholder";
    case End:
        return "End";
    case Error:
        return "Error";
    case Sequence:
        return "Sequence";
    case UnaryExpression:
        return "UnaryExpression";
    case BinaryExpression:
        return "BinaryExpression";
    case Block:
        return "Block";
    case Group:
        return "Group";
    case Statement:
        return "Statement";
    case Program:
        return "Program";
    case RepeatLoop:
        return "RepeatLoop";
    case WhileLoop:
        return "WhileLoop";
    case IfCond:
        return "IfCondition";
    case IfElseCond:
        return "IfElseCondition";
    case Named:
        return "Named";
    case Missing:
        return "Missing";
    case Call:
        return "Call";
    case Arguments:
        return "Arguments";
    case Indices:
        return "Indices";
    case Indexing:
        return "Indexing";
    }
    fail_with("Unhandled node type %d", type);
}

/********************************************************************************
 Ast
********************************************************************************/

rastr_ast_t rastr_ast_create(std::size_t capacity) {
    rastr_ast_t ast = (rastr_ast_t) malloc_or_fail(sizeof(rastr_ast_impl_t));
    ast->pool = new Pool<rastr_node_impl_t, rastr_node_destroy>(capacity);
    ast->root = rastr_node_t{(std::size_t)(-1)};
    return ast;
}

void rastr_ast_destroy(rastr_ast_t ast) {
    ast->pool->clear();
    delete ast->pool;
    free(ast);
}

rastr_node_t rastr_ast_root(rastr_ast_t ast) {
    return ast->root;
}

void rastr_ast_set_root(rastr_ast_t ast, rastr_node_t root) {
    ast->root = root;
}

rastr_node_ptr_t rastr_ast_get_impl(rastr_ast_t ast, rastr_node_t node) {
    return ast->pool->at(node.index);
}

struct rastr_node_pair_t {
    rastr_node_ptr_t ptr;
    rastr_node_t node;
};

rastr_node_pair_t rastr_node_create(rastr_ast_t ast, rastr_node_type_t type) {
    rastr_node_ptr_t ptr =
        (rastr_node_ptr_t) malloc_or_fail(sizeof(rastr_node_impl_t));
    ptr->type = type;
    ptr->id = id_counter++;

    std::size_t index = ast->pool->push_back(ptr);

    rastr_node_pair_t pair;
    pair.ptr = ptr;
    pair.node = rastr_node_t{index};

    return pair;
}

void rastr_node_destroy(rastr_node_ptr_t ptr) {
    rastr_node_type_t type = ptr->type;

    if (rastr_node_type_is_operator(type)) {
        free(ptr->node.operator_node.syntax);
    }

    else if (rastr_node_type_is_keyword(type)) {
        free(ptr->node.keyword_node.syntax);
    }

    else if (rastr_node_type_is_delimiter(type)) {
    }

    else if (rastr_node_type_is_terminator(type)) {
    }

    else if (type == Error) {
        free(ptr->node.error_node.message);
    }

    else if (type == Logical) {
        free(ptr->node.logical_node.syntax);
    }

    else if (type == Integer) {
        free(ptr->node.integer_node.syntax);
    }

    else if (type == Real) {
        free(ptr->node.real_node.syntax);
    }

    else if (type == Complex) {
        free(ptr->node.complex_node.syntax);
    }

    else if (type == String) {
        free(ptr->node.string_node.syntax);
        free(ptr->node.string_node.value);
    }

    else if (type == Symbol) {
        free(ptr->node.symbol_node.syntax);
        free(ptr->node.symbol_node.value);
    }

    free(ptr);
}

const char* rastr_ast_to_string(rastr_ast_t ast) {
    const char* root_str = StringView::duplicate(
        rastr_node_to_string(ast, rastr_ast_root(ast), INDENTATION));

    const char* result = bufprintf("ast {\n"
                                   "%s\n"
                                   "}\n",
                                   root_str);

    free((void*) root_str);
    return result;
}

/********************************************************************************
 Node
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->type;
}

int rastr_node_id(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->id;
}

const char*
rastr_node_to_string(rastr_ast_t ast, rastr_node_t node, int spaces) {
    rastr_node_type_t type = rastr_node_type(ast, node);
    const char* type_str = rastr_node_type_to_string(type);
    const std::string indent(spaces, ' ');
    const char* indentation = indent.c_str();

    /********************************************************************************
      Operators
    ********************************************************************************/

    if (rastr_node_is_operator(ast, node)) {
        return bufprintf("%snode {\n"
                         "%s    type:   %s;\n"
                         "%s    value:  %s;\n"
                         "%s    syntax: %s;\n"
                         "%s}",
                         indentation,
                         indentation,
                         type_str,
                         indentation,
                         rastr_node_operator_value(ast, node),
                         indentation,
                         rastr_node_operator_syntax(ast, node),
                         indentation);
    }

    /********************************************************************************
      KEYWORDS
    ********************************************************************************/

    else if (rastr_node_is_keyword(ast, node)) {
        return bufprintf("%snode {\n"
                         "%s    type:   %s;\n"
                         "%s    value:  %s;\n"
                         "%s    syntax: %s;\n"
                         "%s}",
                         indentation,
                         indentation,
                         type_str,
                         indentation,
                         rastr_node_keyword_value(ast, node),
                         indentation,
                         rastr_node_keyword_syntax(ast, node),
                         indentation);

    }

    /********************************************************************************
      Delimiters
    ********************************************************************************/

    else if (rastr_node_is_delimiter(ast, node)) {
        return bufprintf("%snode {\n"
                         "%s    type:   %s;\n"
                         "%s    value:  %s;\n"
                         "%s    syntax: %s;\n"
                         "%s}",
                         indentation,
                         indentation,
                         type_str,
                         indentation,
                         rastr_node_delimiter_value(ast, node),
                         indentation,
                         rastr_node_delimiter_syntax(ast, node),
                         indentation);
    }

    /********************************************************************************
      Literals
    ********************************************************************************/

    else if (rastr_node_is_literal(ast, node)) {
        switch (type) {
        case Null:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_null_syntax(ast, node),
                             indentation);
            break;

        case Logical:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %d;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_logical_value(ast, node),
                             indentation,
                             rastr_node_logical_syntax(ast, node),
                             indentation);
            break;

        case Integer:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %d;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_integer_value(ast, node),
                             indentation,
                             rastr_node_integer_syntax(ast, node),
                             indentation);
            break;

        case Real:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %f;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_real_value(ast, node),
                             indentation,
                             rastr_node_real_syntax(ast, node),
                             indentation);
            break;

        case Complex:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  {r: %f; i: %f};\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_complex_value(ast, node).r,
                             rastr_node_complex_value(ast, node).i,
                             indentation,
                             rastr_node_complex_syntax(ast, node),
                             indentation);
            break;

        case String:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %s;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_string_value(ast, node),
                             indentation,
                             rastr_node_string_syntax(ast, node),
                             indentation);
            break;

        case Symbol:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %s;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_symbol_value(ast, node),
                             indentation,
                             rastr_node_symbol_syntax(ast, node),
                             indentation);
            break;

        case Placeholder:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    value:  %s;\n"
                             "%s    syntax: %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_placeholder_value(ast, node),
                             indentation,
                             rastr_node_placeholder_syntax(ast, node),
                             indentation);
            break;

        default:
            fail_with("unhandled literal node of type '%s'", type_str);
        }

    }

    /********************************************************************************
      Terminators
    ********************************************************************************/

    else if (rastr_node_is_terminator(ast, node)) {
        return bufprintf("%snode {\n"
                         "%s    type:   %s;\n"
                         "%s    value:  %s;\n"
                         "%s    syntax: %s;\n"
                         "%s}",
                         indentation,
                         indentation,
                         type_str,
                         indentation,
                         rastr_node_terminator_value(ast, node),
                         indentation,
                         rastr_node_terminator_syntax(ast, node),
                         indentation);
    }

    /********************************************************************************
      Expressions
    ********************************************************************************/

    else if (type == UnaryExpression) {
        const char* op_str = StringView::duplicate(rastr_node_to_string(
            ast, rastr_node_unary_expression_op(ast, node), spaces + 12));

        const char* expr_str = StringView::duplicate(rastr_node_to_string(
            ast, rastr_node_unary_expression_expr(ast, node), spaces + 12));

        const char* result = bufprintf("%snode {\n"
                                       "%s    type:   %s;\n"
                                       "%s    op:     %s;\n"
                                       "%s    expr:   %s;\n"
                                       "%s}",
                                       indentation,
                                       indentation,
                                       type_str,
                                       indentation,
                                       op_str,
                                       indentation,
                                       expr_str,
                                       indentation);
        std::free((void*) op_str);
        std::free((void*) expr_str);

        return result;
    }

    else if (type == BinaryExpression) {
        const char* op_str = StringView::duplicate(rastr_node_to_string(
            ast, rastr_node_binary_expression_op(ast, node), spaces + 16));

        const char* left_expr_str = StringView::duplicate(rastr_node_to_string(
            ast,
            rastr_node_binary_expression_left_expr(ast, node),
            spaces + 16));

        const char* right_expr_str = StringView::duplicate(rastr_node_to_string(
            ast,
            rastr_node_binary_expression_right_expr(ast, node),
            spaces + 16));

        const char* result = bufprintf("%snode {\n"
                                       "%s    type:       %s;\n"
                                       "%s    op:         %s;\n"
                                       "%s    left_expr:  %s;\n"
                                       "%s    right_expr: %s;\n"
                                       "%s}",
                                       indentation,
                                       indentation,
                                       type_str,
                                       indentation,
                                       op_str,
                                       indentation,
                                       left_expr_str,
                                       indentation,
                                       right_expr_str,
                                       indentation);
        free((void*) op_str);
        free((void*) left_expr_str);
        free((void*) right_expr_str);

        return result;
    }

    /********************************************************************************
      Pseudo
    ********************************************************************************/

    else {
        switch (type) {
        case End:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation);
            break;

        case Error:
            return bufprintf("%snode {\n"
                             "%s    type:   %s;\n"
                             "%s    msg:    %s;\n"
                             "%s}",
                             indentation,
                             indentation,
                             type_str,
                             indentation,
                             rastr_node_error_message(ast, node),
                             indentation);
            break;

        default:
            fail_with("failed to handle node with type '%s'", type_str);
            break;
        }
    }

    return "";
}

/********************************************************************************
 Operators
********************************************************************************/
bool rastr_node_is_operator(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_operator(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_operator_from_view(rastr_ast_t ast,
                                           const StringView& syntax_view,
                                           rastr_node_type_t type) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    pair.ptr->node.operator_node.syntax = syntax_view.materialize();
    return pair.node;
}

rastr_node_t rastr_node_operator(rastr_ast_t ast,
                                 const char* syntax,
                                 rastr_node_type_t type) {
    return rastr_node_operator_from_view(ast, StringView(syntax), type);
}

const char* rastr_node_operator_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_operator_syntax(ast, node);
}

const char* rastr_node_operator_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.operator_node.syntax;
}

/********************************************************************************
 KEYWORDS
********************************************************************************/
bool rastr_node_is_keyword(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_keyword(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_keyword(rastr_ast_t ast,
                                const char* syntax,
                                rastr_node_type_t type) {
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    pair.ptr->node.keyword_node.syntax = StringView::duplicate(syntax);
    return pair.node;
}

const char* rastr_node_keyword_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_keyword_syntax(ast, node);
}

const char* rastr_node_keyword_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.keyword_node.syntax;
}

/********************************************************************************
 Delimiters
********************************************************************************/
bool rastr_node_is_delimiter(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_delimiter(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_delimiter(rastr_ast_t ast, rastr_node_type_t type) {
    /* TODO: return error if not delimiter */
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    return pair.node;
}

const char* rastr_node_delimiter_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_delimiter_syntax(ast, node);
}

const char* rastr_node_delimiter_syntax(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
    case LeftParen:
        return "(";
    case RightParen:
        return ")";
    case LeftBrace:
        return "{";
    case RightBrace:
        return "}";
    case LeftBracket:
        return "[";
    case RightBracket:
        return "]";
    case DoubleLeftBracket:
        return "[[";
    case DoubleRightBracket:
        return "]]";
    default:
        NODE_TYPE_ERROR("delimiter", type);
    }
}

/********************************************************************************
 Terminators
********************************************************************************/
bool rastr_node_is_terminator(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_terminator(rastr_node_type(ast, node));
}

rastr_node_t rastr_node_terminator(rastr_ast_t ast, rastr_node_type_t type) {
    /* TODO: return error if not delimiter */
    rastr_node_pair_t pair = rastr_node_create(ast, type);
    return pair.node;
}

const char* rastr_node_terminator_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_terminator_syntax(ast, node);
}

const char* rastr_node_terminator_syntax(rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
    case Semicolon:
        return ";";
    case Newline:
        return "\n";
    case Comma:
        return ",";
    default:
        NODE_TYPE_ERROR("terminator", type);
    }
}

/*******************************************************************************
 Meta
*******************************************************************************/

// End
rastr_node_t rastr_node_end(rastr_ast_t ast) {
    rastr_node_pair_t pair = rastr_node_create(ast, End);
    return pair.node;
}

// Error
rastr_node_t rastr_node_error(rastr_ast_t ast, const char* fmt, ...) {
    rastr_node_pair_t pair = rastr_node_create(ast, Error);

    std::va_list args;
    va_start(args, fmt);
    pair.ptr->node.error_node.message =
        StringView::duplicate(vbufprintf(fmt, args));
    va_end(args);

    return pair.node;
}

const char* rastr_node_error_message(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.error_node.message;
}

/********************************************************************************
 Literals
********************************************************************************/
bool rastr_node_is_literal(rastr_ast_t ast, rastr_node_t node) {
    return rastr_node_type_is_literal(rastr_node_type(ast, node));
}

// null
rastr_node_t rastr_node_null(rastr_ast_t ast) {
    rastr_node_pair_t pair = rastr_node_create(ast, Null);
    return pair.node;
}

const char* rastr_node_null_syntax(rastr_ast_t ast, rastr_node_t node) {
    return "NULL";
}

// logical
rastr_node_t
rastr_node_logical(rastr_ast_t ast, const char* syntax, int value) {
    rastr_node_pair_t pair = rastr_node_create(ast, Logical);
    pair.ptr->node.logical_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.logical_node.value = value;
    return pair.node;
}

int rastr_node_logical_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.value;
}

const char* rastr_node_logical_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.logical_node.syntax;
}

// integer
rastr_node_t
rastr_node_integer(rastr_ast_t ast, const char* syntax, int value) {
    rastr_node_pair_t pair = rastr_node_create(ast, Integer);
    pair.ptr->node.integer_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.integer_node.value = value;
    return pair.node;
}

int rastr_node_integer_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.value;
}

const char* rastr_node_integer_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.integer_node.syntax;
}

// real
rastr_node_t
rastr_node_real(rastr_ast_t ast, const char* syntax, double value) {
    rastr_node_pair_t pair = rastr_node_create(ast, Real);
    pair.ptr->node.real_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.real_node.value = value;
    return pair.node;
}

double rastr_node_real_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.value;
}

const char* rastr_node_real_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.real_node.syntax;
}

// complex
rastr_node_t
rastr_node_complex(rastr_ast_t ast, const char* syntax, Rcomplex value) {
    rastr_node_pair_t pair = rastr_node_create(ast, Complex);
    pair.ptr->node.complex_node.syntax = StringView::duplicate(syntax);
    pair.ptr->node.complex_node.value = value;
    return pair.node;
}

Rcomplex rastr_node_complex_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.value;
}

const char* rastr_node_complex_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.complex_node.syntax;
}

// string
rastr_node_t rastr_node_string_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         const StringView& value_view) {
    rastr_node_pair_t pair = rastr_node_create(ast, String);
    pair.ptr->node.string_node.syntax = syntax_view.materialize();
    pair.ptr->node.string_node.value = value_view.materialize();
    return pair.node;
}

rastr_node_t
rastr_node_string(rastr_ast_t ast, const char* syntax, const char* value) {
    return rastr_node_string_from_view(
        ast, StringView(syntax), StringView(value));
}

const char* rastr_node_string_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.syntax;
}

const char* rastr_node_string_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.string_node.value;
}

bool rastr_node_string_is_raw(rastr_ast_t ast, rastr_node_t node) {
    const char* syntax = rastr_node_string_syntax(ast, node);
    const char first = syntax[0];
    return first == 'r' || first == 'R';
}

// symbol
rastr_node_t rastr_node_symbol_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         const StringView& value_view) {
    rastr_node_pair_t pair = rastr_node_create(ast, Symbol);
    pair.ptr->node.symbol_node.syntax = syntax_view.materialize();
    pair.ptr->node.symbol_node.value = value_view.materialize();
    return pair.node;
}

rastr_node_t
rastr_node_symbol(rastr_ast_t ast, const char* syntax, const char* value) {
    return rastr_node_symbol_from_view(
        ast, StringView(syntax), StringView(value));
}

const char* rastr_node_symbol_value(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.value;
}

const char* rastr_node_symbol_syntax(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.symbol_node.syntax;
}

bool rastr_node_symbol_is_quoted(rastr_ast_t ast, rastr_node_t node) {
    const char* syntax = rastr_node_symbol_syntax(ast, node);
    return syntax[0] == '`';
}

// placeholder
rastr_node_t rastr_node_placeholder(rastr_ast_t ast) {
    rastr_node_pair_t pair = rastr_node_create(ast, Placeholder);
    return pair.node;
}

const char* rastr_node_placeholder_value(rastr_ast_t ast, rastr_node_t node) {
    return "_";
}

const char* rastr_node_placeholder_syntax(rastr_ast_t ast, rastr_node_t node) {
    return "_";
}

/********************************************************************************
 Unary Expression
********************************************************************************/
rastr_node_t rastr_node_unary_expression(rastr_ast_t ast,
                                         rastr_node_t op,
                                         rastr_node_t expr) {
    /* TODO: return error if not delimiter */
    rastr_node_pair_t pair = rastr_node_create(ast, UnaryExpression);
    pair.ptr->node.unary_node.op = op;
    pair.ptr->node.unary_node.expr = expr;
    return pair.node;
}

rastr_node_t rastr_node_unary_expression_op(rastr_ast_t ast,
                                            rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.unary_node.op;
}

rastr_node_t rastr_node_unary_expression_expr(rastr_ast_t ast,
                                              rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.unary_node.expr;
}

/********************************************************************************
 Binary Expression
********************************************************************************/
rastr_node_t rastr_node_binary_expression(rastr_ast_t ast,
                                          rastr_node_t left_expr,
                                          rastr_node_t op,
                                          rastr_node_t right_expr) {
    /* TODO: return error if not delimiter */
    rastr_node_pair_t pair = rastr_node_create(ast, BinaryExpression);
    pair.ptr->node.binary_node.left_expr = left_expr;
    pair.ptr->node.binary_node.op = op;
    pair.ptr->node.binary_node.right_expr = right_expr;
    return pair.node;
}

rastr_node_t rastr_node_binary_expression_op(rastr_ast_t ast,
                                             rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.op;
}

rastr_node_t rastr_node_binary_expression_left_expr(rastr_ast_t ast,
                                                    rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.left_expr;
}

rastr_node_t rastr_node_binary_expression_right_expr(rastr_ast_t ast,
                                                     rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.right_expr;
}

/********************************************************************************
 Sequence
********************************************************************************/
rastr_node_t
rastr_node_sequence(rastr_ast_t ast, rastr_node_t* nodes, int size) {
    rastr_node_pair_t pair = rastr_node_create(ast, Sequence);
    pair.ptr->node.sequence_node.size = size;

    std::size_t bytes = size * sizeof(rastr_node_t);
    pair.ptr->node.sequence_node.nodes = (rastr_node_t*) malloc_or_fail(bytes);
    std::memcpy(pair.ptr->node.sequence_node.nodes, nodes, bytes);

    return pair.node;
}

int rastr_node_sequence_size(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.sequence_node.size;
}

rastr_node_t* rastr_node_sequence_nodes(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.sequence_node.nodes;
}

/********************************************************************************
 Block
********************************************************************************/
rastr_node_t rastr_node_block(rastr_ast_t ast,
                              rastr_node_t left_brace,
                              rastr_node_t expressions,
                              rastr_node_t right_brace) {
    rastr_node_pair_t pair = rastr_node_create(ast, Block);
    pair.ptr->node.block_node.left_brace = left_brace;
    pair.ptr->node.block_node.expressions = expressions;
    pair.ptr->node.block_node.right_brace = right_brace;
    return pair.node;
}

rastr_node_t rastr_node_block_left_brace(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.block_node.left_brace;
}

rastr_node_t rastr_node_block_expressions(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.block_node.expressions;
}

rastr_node_t rastr_node_block_right_brace(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.block_node.right_brace;
}

/********************************************************************************
 Group
********************************************************************************/
rastr_node_t rastr_node_group(rastr_ast_t ast,
                              rastr_node_t left_paren,
                              rastr_node_t expr,
                              rastr_node_t right_paren) {
    rastr_node_pair_t pair = rastr_node_create(ast, Group);
    pair.ptr->node.group_node.left_paren = left_paren;
    pair.ptr->node.group_node.expr = expr;
    pair.ptr->node.group_node.right_paren = right_paren;
    return pair.node;
}

rastr_node_t rastr_node_group_left_paren(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.group_node.left_paren;
}

rastr_node_t rastr_node_group_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.group_node.expr;
}

rastr_node_t rastr_node_group_right_paren(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.group_node.right_paren;
}

/********************************************************************************
 Statement
********************************************************************************/
rastr_node_t rastr_node_statement(rastr_ast_t ast,
                                  rastr_node_t expr,
                                  rastr_node_t terminator) {
    rastr_node_pair_t pair = rastr_node_create(ast, Statement);
    pair.ptr->node.statement_node.expr = expr;
    pair.ptr->node.statement_node.terminator = terminator;
    return pair.node;
}

rastr_node_t rastr_node_statement_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.statement_node.expr;
}

rastr_node_t rastr_node_statement_terminator(rastr_ast_t ast,
                                             rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.statement_node.terminator;
}

/********************************************************************************
 Program
********************************************************************************/
rastr_node_t rastr_node_program(rastr_ast_t ast, rastr_node_t statements) {
    rastr_node_pair_t pair = rastr_node_create(ast, Program);
    pair.ptr->node.program_node.statements = statements;
    return pair.node;
}

rastr_node_t rastr_node_program_statements(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.program_node.statements;
}

/********************************************************************************
 RepeatLoop
********************************************************************************/
rastr_node_t
rastr_node_rloop(rastr_ast_t ast, rastr_node_t kw, rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, RepeatLoop);
    pair.ptr->node.rloop_node.kw = kw;
    pair.ptr->node.rloop_node.body = body;
    return pair.node;
}

rastr_node_t rastr_node_rloop_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.rloop_node.kw;
}

rastr_node_t rastr_node_rloop_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.rloop_node.body;
}

/********************************************************************************
 WhileLoop
********************************************************************************/
rastr_node_t rastr_node_wloop(rastr_ast_t ast,
                              rastr_node_t kw,
                              rastr_node_t cond,
                              rastr_node_t body) {
    rastr_node_pair_t pair = rastr_node_create(ast, WhileLoop);
    pair.ptr->node.wloop_node.kw = kw;
    pair.ptr->node.wloop_node.cond = cond;
    pair.ptr->node.wloop_node.body = body;
    return pair.node;
}

rastr_node_t rastr_node_wloop_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wloop_node.kw;
}

rastr_node_t rastr_node_wloop_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wloop_node.cond;
}

rastr_node_t rastr_node_wloop_body(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.wloop_node.body;
}

/********************************************************************************
 If
********************************************************************************/
rastr_node_t rastr_node_ifcond(rastr_ast_t ast,
                               rastr_node_t if_kw,
                               rastr_node_t cond,
                               rastr_node_t csq) {
    rastr_node_pair_t pair = rastr_node_create(ast, IfCond);
    pair.ptr->node.ifcond_node.if_kw = if_kw;
    pair.ptr->node.ifcond_node.cond = cond;
    pair.ptr->node.ifcond_node.csq = csq;
    return pair.node;
}

rastr_node_t rastr_node_ifcond_if_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifcond_node.if_kw;
}

rastr_node_t rastr_node_ifcond_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifcond_node.cond;
}

rastr_node_t rastr_node_ifcond_csq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifcond_node.csq;
}

/********************************************************************************
 IfElse
********************************************************************************/
rastr_node_t rastr_node_ifelsecond(rastr_ast_t ast,
                                   rastr_node_t if_kw,
                                   rastr_node_t cond,
                                   rastr_node_t csq,
                                   rastr_node_t else_kw,
                                   rastr_node_t alt) {
    rastr_node_pair_t pair = rastr_node_create(ast, IfElseCond);
    pair.ptr->node.ifelsecond_node.if_kw = if_kw;
    pair.ptr->node.ifelsecond_node.cond = cond;
    pair.ptr->node.ifelsecond_node.csq = csq;
    pair.ptr->node.ifelsecond_node.else_kw = else_kw;
    pair.ptr->node.ifelsecond_node.alt = alt;
    return pair.node;
}

rastr_node_t rastr_node_ifelsecond_if_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifelsecond_node.if_kw;
}

rastr_node_t rastr_node_ifelsecond_cond(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifelsecond_node.cond;
}

rastr_node_t rastr_node_ifelsecond_csq(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifelsecond_node.csq;
}

rastr_node_t rastr_node_ifelsecond_else_kw(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifelsecond_node.else_kw;
}

rastr_node_t rastr_node_ifelsecond_alt(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.ifelsecond_node.alt;
}

/********************************************************************************
 Named
********************************************************************************/
rastr_node_t rastr_node_named(rastr_ast_t ast,
                              rastr_node_t name,
                              rastr_node_t op,
                              rastr_node_t expr) {
    rastr_node_pair_t pair = rastr_node_create(ast, Named);
    pair.ptr->node.named_node.name = name;
    pair.ptr->node.named_node.op = op;
    pair.ptr->node.named_node.expr = expr;
    return pair.node;
}

rastr_node_t rastr_node_named_name(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.named_node.name;
}

rastr_node_t rastr_node_named_op(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.named_node.op;
}

rastr_node_t rastr_node_named_expr(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.named_node.expr;
}

/********************************************************************************
 Missing
********************************************************************************/
rastr_node_t rastr_node_missing(rastr_ast_t ast) {
    rastr_node_pair_t pair = rastr_node_create(ast, Missing);
    return pair.node;
}

/********************************************************************************
 Arguments
********************************************************************************/
rastr_node_t rastr_node_arguments(rastr_ast_t ast,
                                  rastr_node_t ldelim,
                                  rastr_node_t args,
                                  rastr_node_t rdelim) {
    rastr_node_pair_t pair = rastr_node_create(ast, Arguments);
    pair.ptr->node.arguments_node.ldelim = ldelim;
    pair.ptr->node.arguments_node.args = args;
    pair.ptr->node.arguments_node.rdelim = rdelim;
    return pair.node;
}

rastr_node_t rastr_node_arguments_ldelim(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.arguments_node.ldelim;
}

rastr_node_t rastr_node_arguments_args(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.arguments_node.args;
}

rastr_node_t rastr_node_arguments_rdelim(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.arguments_node.rdelim;
}

/********************************************************************************
 Call
********************************************************************************/
rastr_node_t
rastr_node_call(rastr_ast_t ast, rastr_node_t fun, rastr_node_t args) {
    rastr_node_pair_t pair = rastr_node_create(ast, Call);
    pair.ptr->node.call_node.fun = fun;
    pair.ptr->node.call_node.args = args;
    return pair.node;
}

rastr_node_t rastr_node_call_fun(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.call_node.fun;
}

rastr_node_t rastr_node_call_args(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.call_node.args;
}

/********************************************************************************
 Indices
********************************************************************************/
rastr_node_t rastr_node_indices(rastr_ast_t ast,
                                rastr_node_t ldelim,
                                rastr_node_t nodes,
                                rastr_node_t rdelim) {
    rastr_node_pair_t pair = rastr_node_create(ast, Indices);
    pair.ptr->node.indices_node.ldelim = ldelim;
    pair.ptr->node.indices_node.nodes = nodes;
    pair.ptr->node.indices_node.rdelim = rdelim;
    return pair.node;
}

rastr_node_t rastr_node_indices_ldelim(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.indices_node.ldelim;
}

rastr_node_t rastr_node_indices_nodes(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.indices_node.nodes;
}

rastr_node_t rastr_node_indices_rdelim(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.indices_node.rdelim;
}

/********************************************************************************
 Indexing
********************************************************************************/
rastr_node_t
rastr_node_indexing(rastr_ast_t ast, rastr_node_t obj, rastr_node_t indices) {
    rastr_node_pair_t pair = rastr_node_create(ast, Indexing);
    pair.ptr->node.indexing_node.obj = obj;
    pair.ptr->node.indexing_node.indices = indices;
    return pair.node;
}

rastr_node_t rastr_node_indexing_obj(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.indexing_node.obj;
}

rastr_node_t rastr_node_indexing_indices(rastr_ast_t ast, rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.indexing_node.indices;
}
