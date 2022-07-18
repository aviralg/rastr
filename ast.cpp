#include "ast.h"
#include "internal_api.h"
#include "utilities.h"
#include "logger.h"

#define NODE_TYPE_ERROR(expected, actual)                 \
    fail_with("incorrect node type; expected %s, got %s", \
              expected,                                   \
              rastr_node_type_to_string(actual));

/********************************************************************************
 Node
********************************************************************************/

const char* rastr_node_to_string(rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(node);
    const char* type_str = rastr_node_type_to_string(type);

    /********************************************************************************
      Operators
    ********************************************************************************/

    if (rastr_node_is_operator(node)) {
        return bufprintf("node {\n"
                         "    type:   %s;\n"
                         "    value:  %s;\n"
                         "    syntax: %s;\n"
                         "}",
                         type_str,
                         rastr_node_operator_value(node),
                         rastr_node_operator_syntax(node));
    }

    /********************************************************************************
      KEYWORDS
    ********************************************************************************/

    else if (rastr_node_is_keyword(node)) {
        return bufprintf("node {\n"
                         "    type:   %s;\n"
                         "    value:  %s;\n"
                         "    syntax: %s;\n"
                         "}",
                         type_str,
                         rastr_node_keyword_value(node),
                         rastr_node_keyword_syntax(node));
    }

    /********************************************************************************
      Delimiters
    ********************************************************************************/

    else if (rastr_node_is_delimiter(node)) {
        return bufprintf("node {\n"
                         "    type:   %s;\n"
                         "    value:  %s;\n"
                         "    syntax: %s;\n"
                         "}",
                         type_str,
                         rastr_node_delimiter_value(node),
                         rastr_node_delimiter_syntax(node));
    }

    /********************************************************************************
      Literals
    ********************************************************************************/

    else if (rastr_node_is_literal(node)) {
        switch (type) {
        case Null:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_null_syntax(node));
            break;

        case Logical:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %d;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_logical_value(node),
                             rastr_node_logical_syntax(node));
            break;

        case Integer:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %d;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_integer_value(node),
                             rastr_node_integer_syntax(node));
            break;

        case Real:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %f;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_real_value(node),
                             rastr_node_real_syntax(node));
            break;

        case Complex:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  {r: %f; i: %f};\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_complex_value(node).r,
                             rastr_node_complex_value(node).i,
                             rastr_node_complex_syntax(node));
            break;

        case String:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %s;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_string_value(node),
                             rastr_node_string_syntax(node));
            break;

        case Symbol:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %s;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_symbol_value(node),
                             rastr_node_symbol_syntax(node));
            break;

        case Placeholder:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    value:  %s;\n"
                             "    syntax: %s;\n"
                             "}",
                             type_str,
                             rastr_node_placeholder_value(node),
                             rastr_node_placeholder_syntax(node));
            break;

        default:
            fail_with("unhandled literal node of type '%s'", type_str);
        }

    }

    /********************************************************************************
      Terminators
    ********************************************************************************/

    else if (rastr_node_is_terminator(node)) {
        return bufprintf("node {\n"
                         "    type:   %s;\n"
                         "    value:  %s;\n"
                         "    syntax: %s;\n"
                         "}",
                         type_str,
                         rastr_node_terminator_value(node),
                         rastr_node_terminator_syntax(node));
    }

    /********************************************************************************
      Pseudo
    ********************************************************************************/

    else {
        switch (type) {
        case End:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "}",
                             type_str);
            break;

        case Error:
            return bufprintf("node {\n"
                             "    type:   %s;\n"
                             "    msg:    %s;\n"
                             "}",
                             type_str,
                             rastr_node_error_message(node));
            break;

        default:
            fail_with("failed to handle node with type '%s'", type_str);
            break;
        }
    }

    return "";
}

/********************************************************************************
 Type
********************************************************************************/

rastr_node_type_t rastr_node_type(rastr_node_t node) {
    return node.type;
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
    default:
        fail_with("Unhandled node type %d", type);
    }
}

/********************************************************************************
 Operators
********************************************************************************/

bool rastr_node_is_operator(rastr_node_t node) {
    switch (rastr_node_type(node)) {
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

rastr_node_t rastr_node_operator_from_view(const StringView& syntax_view,
                                           rastr_node_type_t type) {
    rastr_node_t node;
    node.type = type;
    node.operator_node.syntax = syntax_view.materialize();
    return node;
}

rastr_node_t rastr_node_operator(const char* syntax, rastr_node_type_t type) {
    return rastr_node_operator_from_view(StringView(syntax), type);
}

const char* rastr_node_operator_value(rastr_node_t node) {
    return rastr_node_operator_syntax(node);
}

const char* rastr_node_operator_syntax(rastr_node_t node) {
    return node.operator_node.syntax;
}

/********************************************************************************
 KEYWORDS
********************************************************************************/

bool rastr_node_is_keyword(rastr_node_t node) {
    switch (rastr_node_type(node)) {
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

rastr_node_t rastr_node_keyword(const char* syntax, rastr_node_type_t type) {
    rastr_node_t node;
    node.type = type;
    node.keyword_node.syntax = StringView::duplicate(syntax);
    return node;
}

const char* rastr_node_keyword_value(rastr_node_t node) {
    return rastr_node_keyword_syntax(node);
}

const char* rastr_node_keyword_syntax(rastr_node_t node) {
    return node.keyword_node.syntax;
}

/********************************************************************************
 Delimiters
********************************************************************************/

bool rastr_node_is_delimiter(rastr_node_t node) {
    switch (rastr_node_type(node)) {
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

rastr_node_t rastr_node_delimiter(rastr_node_type_t type) {
    /* TODO: return error if not delimiter */
    rastr_node_t node;
    node.type = type;
    return node;
}

const char* rastr_node_delimiter_value(rastr_node_t node) {
    return rastr_node_delimiter_syntax(node);
}

const char* rastr_node_delimiter_syntax(rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(node);

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
bool rastr_node_is_terminator(rastr_node_t node) {
    switch (rastr_node_type(node)) {
    case Semicolon:
    case Newline:
    case Comma:
        return true;
    default:
        return false;
    }
}

rastr_node_t rastr_node_terminator(rastr_node_type_t type) {
    /* TODO: return error if not delimiter */
    rastr_node_t node;
    node.type = type;
    return node;
}

const char* rastr_node_terminator_value(rastr_node_t node) {
    return rastr_node_terminator_syntax(node);
}

const char* rastr_node_terminator_syntax(rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(node);

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
rastr_node_t rastr_node_end() {
    rastr_node_t node;
    node.type = End;
    return node;
}

// Error
rastr_node_t rastr_node_error(const char* fmt, ...) {
    rastr_node_t node;
    node.type = Error;

    std::va_list args;
    va_start(args, fmt);
    node.error_node.message = StringView::duplicate(vbufprintf(fmt, args));
    va_end(args);

    return node;
}

const char* rastr_node_error_message(rastr_node_t node) {
    return node.error_node.message;
}

/********************************************************************************
 Literals
********************************************************************************/

bool rastr_node_is_literal(rastr_node_t node) {
    switch (rastr_node_type(node)) {
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

// null
rastr_node_t rastr_node_null() {
    rastr_node_t node;
    node.type = Null;
    return node;
}

const char* rastr_node_null_syntax(rastr_node_t node) {
    return "NULL";
}

// logical
rastr_node_t rastr_node_logical(const char* syntax, int value) {
    rastr_node_t node;
    node.type = Logical;
    node.logical_node.syntax = StringView::duplicate(syntax);
    node.logical_node.value = value;
    return node;
}

int rastr_node_logical_value(rastr_node_t node) {
    return node.logical_node.value;
}

const char* rastr_node_logical_syntax(rastr_node_t node) {
    return node.logical_node.syntax;
}

// integer
rastr_node_t rastr_node_integer(const char* syntax, int value) {
    rastr_node_t node;
    node.type = Integer;
    node.integer_node.syntax = StringView::duplicate(syntax);
    node.integer_node.value = value;
    return node;
}

int rastr_node_integer_value(rastr_node_t node) {
    return node.integer_node.value;
}

const char* rastr_node_integer_syntax(rastr_node_t node) {
    return node.integer_node.syntax;
}

// real
rastr_node_t rastr_node_real(const char* syntax, double value) {
    rastr_node_t node;
    node.type = Real;
    node.real_node.syntax = StringView::duplicate(syntax);
    node.real_node.value = value;
    return node;
}

double rastr_node_real_value(rastr_node_t node) {
    return node.real_node.value;
}

const char* rastr_node_real_syntax(rastr_node_t node) {
    return node.real_node.syntax;
}

// complex
rastr_node_t rastr_node_complex(const char* syntax, Rcomplex value) {
    rastr_node_t node;
    node.type = Complex;
    node.complex_node.syntax = StringView::duplicate(syntax);
    node.complex_node.value = value;
    return node;
}

Rcomplex rastr_node_complex_value(rastr_node_t node) {
    return node.complex_node.value;
}

const char* rastr_node_complex_syntax(rastr_node_t node) {
    return node.complex_node.syntax;
}

// string
rastr_node_t rastr_node_string_from_view(const StringView& syntax_view,
                                         const StringView& value_view) {
    rastr_node_t node;
    node.type = String;
    node.string_node.syntax = syntax_view.materialize();
    node.string_node.value = value_view.materialize();
    return node;
}

rastr_node_t rastr_node_string(const char* syntax, const char* value) {
    return rastr_node_string_from_view(StringView(syntax), StringView(value));
}

const char* rastr_node_string_syntax(rastr_node_t node) {
    return node.string_node.syntax;
}

const char* rastr_node_string_value(rastr_node_t node) {
    return node.string_node.value;
}

bool rastr_node_string_is_raw(rastr_node_t node) {
    char first = node.string_node.syntax[0];
    return first == 'r' || first == 'R';
}

// symbol
rastr_node_t rastr_node_symbol_from_view(const StringView& syntax_view,
                                         const StringView& value_view) {
    rastr_node_t node;
    node.type = Symbol;
    node.symbol_node.syntax = syntax_view.materialize();
    node.symbol_node.value = value_view.materialize();
    return node;
}

rastr_node_t rastr_node_symbol(const char* syntax, const char* value) {
    return rastr_node_symbol_from_view(StringView(syntax), StringView(value));
}

const char* rastr_node_symbol_value(rastr_node_t node) {
    return node.symbol_node.value;
}

const char* rastr_node_symbol_syntax(rastr_node_t node) {
    return node.symbol_node.syntax;
}

bool rastr_node_symbol_is_quoted(rastr_node_t node) {
    return node.symbol_node.syntax[0] == '`';
}

// placeholder
rastr_node_t rastr_node_placeholder() {
    rastr_node_t node;
    node.type = Placeholder;
    return node;
}

const char* rastr_node_placeholder_value(rastr_node_t node) {
    return "_";
}

const char* rastr_node_placeholder_syntax(rastr_node_t node) {
    return "_";
}
