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
    case Sequence:
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
    case Sequence:
        return "Sequence";
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
    case UnaryExpression:
        return "UnaryExpression";
    case BinaryExpression:
        return "BinaryExpression";
    default:
        fail_with("Unhandled node type %d", type);
    }
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
            ast, rastr_node_unary_expression_operator(ast, node), spaces + 12));

        const char* expr_str = StringView::duplicate(rastr_node_to_string(
            ast,
            rastr_node_unary_expression_expression(ast, node),
            spaces + 12));

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
            ast,
            rastr_node_binary_expression_operator(ast, node),
            spaces + 16));

        const char* left_expr_str = StringView::duplicate(rastr_node_to_string(
            ast,
            rastr_node_binary_expression_left_expression(ast, node),
            spaces + 16));

        const char* right_expr_str = StringView::duplicate(rastr_node_to_string(
            ast,
            rastr_node_binary_expression_right_expression(ast, node),
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

rastr_node_t rastr_node_unary_expression_operator(rastr_ast_t ast,
                                                  rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.unary_node.op;
}

rastr_node_t rastr_node_unary_expression_expression(rastr_ast_t ast,
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

rastr_node_t rastr_node_binary_expression_operator(rastr_ast_t ast,
                                                   rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.op;
}

rastr_node_t rastr_node_binary_expression_left_expression(rastr_ast_t ast,
                                                          rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.left_expr;
}

rastr_node_t rastr_node_binary_expression_right_expression(rastr_ast_t ast,
                                                           rastr_node_t node) {
    return rastr_ast_get_impl(ast, node)->node.binary_node.right_expr;
}
