#include <rastr/api.h>
#include <cstdio>
#include "logger.h"
#include "interop.h"
#include "utilities.h"

/* Material Design colors taken from
   https://material.io/design/color/the-color-system.html#tools-for-picking-colors
   Selected shade 500 from every color column */
const char* ColorRed = "#F44336";
const char* ColorPink = "#E91E63";
const char* ColorPurple = "#9C27B0";
const char* ColorDeepPurple = "#673AB7";
const char* ColorIndigo = "#3F51B5";
const char* ColorBlue = "#2196F3";
const char* ColorLightBlue = "#03A9F4";
const char* ColorCyan = "#00BCD4";
const char* ColorTeal = "#009688";
const char* ColorGreen = "#4CAF50";
const char* ColorLightGreen = "#8BC34A";
const char* ColorLime = "#CDDC39";
const char* ColorYellow = "#FFEB3B";
const char* ColorAmber = "#FFC107";
const char* ColorOrange = "#FF9800";
const char* ColorDeepOrange = "#FF5722";
const char* ColorBrown = "#795548";
const char* ColorGray = "#9E9E9E";
const char* ColorBlueGray = "#607D8B";
const char* ColorBlack = "#000000";
const char* ColorWhite = "#FFFFFF";

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast, int depth);
void rastr_export_to_dot_node(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth);
void rastr_export_to_dot_operator(FILE* file,
                                  rastr_ast_t ast,
                                  rastr_node_t node,
                                  int depth);
void rastr_export_to_dot_keyword(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth);
void rastr_export_to_dot_delimiter(FILE* file,
                                   rastr_ast_t ast,
                                   rastr_node_t node,
                                   int depth);
void rastr_export_to_dot_terminator(FILE* file,
                                    rastr_ast_t ast,
                                    rastr_node_t node,
                                    int depth);
void rastr_export_to_dot_null(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth);
void rastr_export_to_dot_logical(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth);
void rastr_export_to_dot_integer(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth);
void rastr_export_to_dot_real(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth);
void rastr_export_to_dot_complex(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth);
void rastr_export_to_dot_string(FILE* file,
                                rastr_ast_t ast,
                                rastr_node_t node,
                                int depth);
void rastr_export_to_dot_symbol(FILE* file,
                                rastr_ast_t ast,
                                rastr_node_t node,
                                int depth);
void rastr_export_to_dot_placeholder(FILE* file,
                                     rastr_ast_t ast,
                                     rastr_node_t node,
                                     int depth);
void rastr_export_to_dot_unary_expression(FILE* file,
                                          rastr_ast_t ast,
                                          rastr_node_t node,
                                          int depth);
void rastr_export_to_dot_binary_expression(FILE* file,
                                           rastr_ast_t ast,
                                           rastr_node_t node,
                                           int depth);
void rastr_export_to_dot_group(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth);
void rastr_export_to_dot_block(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth);
void rastr_export_to_dot_program(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth);
void rastr_export_to_dot_sequence(FILE* file,
                                  rastr_ast_t ast,
                                  rastr_node_t node,
                                  int depth);
void rastr_export_to_dot_statement(FILE* file,
                                   rastr_ast_t ast,
                                   rastr_node_t node,
                                   int depth);
void rastr_export_to_dot_end(FILE* file,
                             rastr_ast_t ast,
                             rastr_node_t node,
                             int depth);
void rastr_export_to_dot_error(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth);
void rastr_export_to_dot_rloop(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth);

void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor);
void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor,
                    const char* field,
                    const char* value);
void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor,
                    const char* field1,
                    const char* value1,
                    const char* field2,
                    const char* value2);
void write_edge(FILE* file,
                rastr_ast_t ast,
                rastr_node_t parent,
                rastr_node_t child,
                const char* label);

SEXP r_rastr_export_to_dot(SEXP r_ast, SEXP r_filepath, SEXP r_depth) {
    SEXPTYPE type = TYPEOF(r_filepath);

    if (type != STRSXP) {
        Rf_error("expected a filepath of type string, received a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_filepath);

    if (length != 1) {
        Rf_error("expected a filepath string of size 1, received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_filepath, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ instead");
        return R_NilValue;
    }

    const char* filepath = CHAR(str_elt);

    rastr_ast_t ast = rastr_ast_from_sexp(r_ast);

    int depth = INTEGER(r_depth)[0];

    rastr_export_to_dot(ast, filepath, depth);

    return R_NilValue;
}

void rastr_export_to_dot(rastr_ast_t ast, const char* filepath, int depth) {
    FILE* file = fopen(filepath, "w");

    if (file == nullptr) {
        rastr_log_error("cannot open file '%s'", filepath);
    }

    rastr_export_to_dot_ast(file, ast, depth);
    fclose(file);
}

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast, int depth) {
    fprintf(file,
            "digraph ast {\n"
            "    node [fontname  = \"Courier New\"\n"
            "          fontsize  = 12\n"
            "          style     = \"filled, bold\"\n"
            "          penwidth  = 2\n"
            "          fontcolor = \"white\"\n"
            "          shape     = \"Mrecord\"]\n"
            "\n"
            "    edge [fontname  = \"Courier New\"\n"
            "          penwidth  = 2\n"
            "          fontsize  = 12\n"
            "          fontcolor = \"black\"]\n"
            "\n"
            "    graph [fontsize = 10\n"
            "           labelloc = \"t\"\n"
            "           label    = \"\"\n"
            "           splines  = false\n"
            "           overlap  = false\n"
            "           forcelabels = true\n"
            "           center = true\n"
            "           rankdir  = \"TD\"]\n"
            "\n"
            "    ratio = auto;\n"
            "    charset=\"UTF-8\"");

    rastr_export_to_dot_node(file, ast, rastr_ast_root(ast), depth);

    fprintf(file, "}");
}

void rastr_export_to_dot_node(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth) {
    if (depth == 0) {
        return;
    }

    rastr_node_type_t type = rastr_node_type(ast, node);

    switch (type) {
        /********************************************************************************
         Operators
        ********************************************************************************/
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
        rastr_export_to_dot_operator(file, ast, node, depth);
        return;

        /********************************************************************************
         KEYWORDS
        ********************************************************************************/
    case Function:
    case While:
    case Repeat:
    case For:
    case In:
    case If:
    case Else:
    case Next:
    case Break:
        rastr_export_to_dot_keyword(file, ast, node, depth);
        return;

        /********************************************************************************
         Delimiters
        ********************************************************************************/
    case LeftParen:
    case RightParen:
    case LeftBrace:
    case RightBrace:
    case LeftBracket:
    case RightBracket:
    case DoubleLeftBracket:
    case DoubleRightBracket:
        rastr_export_to_dot_delimiter(file, ast, node, depth);
        return;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case Semicolon:
    case Newline:
    case Comma:
        rastr_export_to_dot_terminator(file, ast, node, depth);
        return;

        /********************************************************************************
         Literals
        ********************************************************************************/
    case Null:
        rastr_export_to_dot_null(file, ast, node, depth);
        return;

    case Logical:
        rastr_export_to_dot_logical(file, ast, node, depth);
        return;

    case Integer:
        rastr_export_to_dot_integer(file, ast, node, depth);
        return;

    case Real:
        rastr_export_to_dot_real(file, ast, node, depth);
        return;

    case Complex:
        rastr_export_to_dot_complex(file, ast, node, depth);
        return;

    case String:
        rastr_export_to_dot_string(file, ast, node, depth);
        return;

    case Symbol:
        rastr_export_to_dot_symbol(file, ast, node, depth);
        return;

    case Placeholder:
        rastr_export_to_dot_placeholder(file, ast, node, depth);
        return;

        /********************************************************************************
         Expressions
        ********************************************************************************/
    case UnaryExpression:
        rastr_export_to_dot_unary_expression(file, ast, node, depth);
        return;

    case BinaryExpression:
        rastr_export_to_dot_binary_expression(file, ast, node, depth);
        return;

    case Block:
        rastr_export_to_dot_block(file, ast, node, depth);
        return;

    case Group:
        rastr_export_to_dot_group(file, ast, node, depth);
        return;

        /********************************************************************************
         Statement
        ********************************************************************************/
    case Statement:
        rastr_export_to_dot_statement(file, ast, node, depth);
        return;

        /********************************************************************************
         Program
        ********************************************************************************/
    case Program:
        rastr_export_to_dot_program(file, ast, node, depth);
        return;

        /********************************************************************************
         Sequence
        ********************************************************************************/
    case Sequence:
        rastr_export_to_dot_sequence(file, ast, node, depth);
        return;

        /********************************************************************************
         End
        ********************************************************************************/
    case End:
        rastr_export_to_dot_end(file, ast, node, depth);
        return;

        /********************************************************************************
         Error
        ********************************************************************************/
    case Error:
        rastr_export_to_dot_error(file, ast, node, depth);
        return;

        /********************************************************************************
         Repeat
        ********************************************************************************/
    case RepeatLoop:
        rastr_export_to_dot_rloop(file, ast, node, depth);
        return;
    }

    fail_with("unexpected node of type '%s'", rastr_node_type_to_string(type));
}

void rastr_export_to_dot_operator(FILE* file,
                                  rastr_ast_t ast,
                                  rastr_node_t node,
                                  int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorRed,
                   "CODE",
                   rastr_node_operator_syntax(ast, node));
}

void rastr_export_to_dot_keyword(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorPink,
                   "CODE",
                   rastr_node_keyword_syntax(ast, node));
}

void rastr_export_to_dot_delimiter(FILE* file,
                                   rastr_ast_t ast,
                                   rastr_node_t node,
                                   int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorPurple,
                   "CODE",
                   rastr_node_delimiter_syntax(ast, node));
}

void rastr_export_to_dot_terminator(FILE* file,
                                    rastr_ast_t ast,
                                    rastr_node_t node,
                                    int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorDeepPurple,
                   "CODE",
                   rastr_node_terminator_syntax(ast, node));
}

void rastr_export_to_dot_null(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_null_syntax(ast, node));
}

void rastr_export_to_dot_logical(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_logical_syntax(ast, node),
                   "VALUE",
                   bufprintf("%d", rastr_node_logical_value(ast, node)));
}

void rastr_export_to_dot_integer(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_integer_syntax(ast, node),
                   "VALUE",
                   bufprintf("%d", rastr_node_integer_value(ast, node)));
}

void rastr_export_to_dot_real(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_real_syntax(ast, node),
                   "VALUE",
                   bufprintf("%f", rastr_node_real_value(ast, node)));
}

void rastr_export_to_dot_complex(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_complex_syntax(ast, node),
                   "VALUE",
                   bufprintf("{r: %d, i: %d}",
                             rastr_node_complex_value(ast, node).r,
                             rastr_node_complex_value(ast, node).i));
}

void rastr_export_to_dot_string(FILE* file,
                                rastr_ast_t ast,
                                rastr_node_t node,
                                int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_string_syntax(ast, node),
                   "VALUE",
                   rastr_node_string_value(ast, node));
}

void rastr_export_to_dot_symbol(FILE* file,
                                rastr_ast_t ast,
                                rastr_node_t node,
                                int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_symbol_syntax(ast, node),
                   "VALUE",
                   rastr_node_symbol_value(ast, node));
}

void rastr_export_to_dot_placeholder(FILE* file,
                                     rastr_ast_t ast,
                                     rastr_node_t node,
                                     int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorIndigo,
                   "CODE",
                   rastr_node_placeholder_syntax(ast, node),
                   "VALUE",
                   rastr_node_placeholder_value(ast, node));
}

void rastr_export_to_dot_unary_expression(FILE* file,
                                          rastr_ast_t ast,
                                          rastr_node_t node,
                                          int depth) {
    write_dot_node(file, ast, node, ColorBlue);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t op = rastr_node_unary_expression_operator(ast, node);
    rastr_export_to_dot_node(file, ast, op, depth);
    write_edge(file, ast, node, op, "op");

    rastr_node_t expr = rastr_node_unary_expression_expression(ast, node);
    rastr_export_to_dot_node(file, ast, expr, depth);
    write_edge(file, ast, node, expr, "expr");
}

void rastr_export_to_dot_binary_expression(FILE* file,
                                           rastr_ast_t ast,
                                           rastr_node_t node,
                                           int depth) {
    write_dot_node(file, ast, node, ColorLightBlue);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t left_expr =
        rastr_node_binary_expression_left_expression(ast, node);
    rastr_export_to_dot_node(file, ast, left_expr, depth);
    write_edge(file, ast, node, left_expr, "left_expr");

    rastr_node_t op = rastr_node_binary_expression_operator(ast, node);
    rastr_export_to_dot_node(file, ast, op, depth);
    write_edge(file, ast, node, op, "op");

    rastr_node_t right_expr =
        rastr_node_binary_expression_right_expression(ast, node);
    rastr_export_to_dot_node(file, ast, right_expr, depth);
    write_edge(file, ast, node, right_expr, "right_expr");
}

void rastr_export_to_dot_group(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth) {
    write_dot_node(file, ast, node, ColorCyan);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t left_paren = rastr_node_group_left_paren(ast, node);
    rastr_export_to_dot_node(file, ast, left_paren, depth);
    write_edge(file, ast, node, left_paren, "left_paren");

    rastr_node_t expr = rastr_node_group_expr(ast, node);
    rastr_export_to_dot_node(file, ast, expr, depth);
    write_edge(file, ast, node, expr, "expr");

    rastr_node_t right_paren = rastr_node_group_right_paren(ast, node);
    rastr_export_to_dot_node(file, ast, right_paren, depth);
    write_edge(file, ast, node, right_paren, "right_paren");
}

void rastr_export_to_dot_block(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth) {
    write_dot_node(file, ast, node, ColorTeal);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t left_brace = rastr_node_block_left_brace(ast, node);
    rastr_export_to_dot_node(file, ast, left_brace, depth);
    write_edge(file, ast, node, left_brace, "left_brace");

    rastr_node_t expressions = rastr_node_block_expressions(ast, node);
    rastr_export_to_dot_node(file, ast, expressions, depth);
    write_edge(file, ast, node, expressions, "expressions");

    rastr_node_t right_brace = rastr_node_block_right_brace(ast, node);
    rastr_export_to_dot_node(file, ast, right_brace, depth);
    write_edge(file, ast, node, right_brace, "right_brace");
}

void rastr_export_to_dot_program(FILE* file,
                                 rastr_ast_t ast,
                                 rastr_node_t node,
                                 int depth) {
    write_dot_node(file, ast, node, ColorGreen);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t stmts = rastr_node_program_statements(ast, node);
    rastr_export_to_dot_node(file, ast, stmts, depth);
    write_edge(file, ast, node, stmts, "statements");
}

void rastr_export_to_dot_sequence(FILE* file,
                                  rastr_ast_t ast,
                                  rastr_node_t node,
                                  int depth) {
    write_dot_node(file, ast, node, ColorLightGreen);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t* nodes = rastr_node_sequence_nodes(ast, node);
    int size = rastr_node_sequence_size(ast, node);

    for (int i = 0; i < size; ++i) {
        rastr_node_t child = nodes[i];
        rastr_export_to_dot_node(file, ast, child, depth);
        write_edge(file, ast, node, child, bufprintf("nodes[%d]", i));
    }
}

void rastr_export_to_dot_statement(FILE* file,
                                   rastr_ast_t ast,
                                   rastr_node_t node,
                                   int depth) {
    write_dot_node(file, ast, node, ColorLime);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t expr = rastr_node_statement_expr(ast, node);
    rastr_export_to_dot_node(file, ast, expr, depth);
    write_edge(file, ast, node, expr, "expr");

    rastr_node_t terminator = rastr_node_statement_terminator(ast, node);
    rastr_export_to_dot_node(file, ast, terminator, depth);
    write_edge(file, ast, node, terminator, "terminator");
}

void rastr_export_to_dot_end(FILE* file,
                             rastr_ast_t ast,
                             rastr_node_t node,
                             int depth) {
    write_dot_node(file, ast, node, ColorAmber);
}

void rastr_export_to_dot_error(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth) {
    write_dot_node(file,
                   ast,
                   node,
                   ColorYellow,
                   "MESSAGE",
                   rastr_node_error_message(ast, node));
}

void rastr_export_to_dot_rloop(FILE* file,
                               rastr_ast_t ast,
                               rastr_node_t node,
                               int depth) {
    write_dot_node(file, ast, node, ColorOrange);

    --depth;

    if (depth == 0) {
        return;
    }

    rastr_node_t kw = rastr_node_rloop_kw(ast, node);
    rastr_export_to_dot_node(file, ast, kw, depth);
    write_edge(file, ast, node, kw, "kw");

    rastr_node_t body = rastr_node_rloop_body(ast, node);
    rastr_export_to_dot_node(file, ast, body, depth);
    write_edge(file, ast, node, body, "body");
}

std::string escape_dot_label(const char* label) {
    std::string label_str(label);
    string_replace(label_str, "{", "\\{");
    string_replace(label_str, "}", "\\}");
    return label_str;
}

void write_dot_node_header(FILE* file,
                           rastr_ast_t ast,
                           rastr_node_t node,
                           const char* fillcolor) {
    int id = rastr_node_id(ast, node);
    rastr_node_type_t type = rastr_node_type(ast, node);
    const char* type_str = rastr_node_type_to_string(type);

    const char* header_tmpl = R"-(
    "node-%d"[
         fillcolor ="%s"
         tooltip = "%s#%d"
         label = <<table border='0' cellborder='0'>
                      <tr><td align="center" colspan="3"><B>%s</B></td></tr>
                      <tr><td align="left">ID</td><td>-&gt;</td><td align="left">%d</td></tr>)-";

    fprintf(file, header_tmpl, id, fillcolor, type_str, id, type_str, id);
}

void write_dot_node_footer(FILE* file) {
    const char* footer_tmpl = R"-(
                 </table>>
    ]
)-";

    /* note: the indirection of substituting footer in %s is to avoid
       format-security error on Ubuntu
       https://stackoverflow.com/questions/17260409/fprintf-error-format-not-a-string-literal-and-no-format-arguments-werror-for*/
    fprintf(file, "%s", footer_tmpl);
}

void write_dot_node_row(FILE* file, const char* field, const char* value) {
    std::string esc_value = escape_dot_label(value);

    const char* row_tmpl = R"-(
                      <tr><td align="left">%s</td><td>-&gt;</td><td align="left">%s</td></tr>)-";

    fprintf(file, row_tmpl, field, esc_value.c_str());
}

void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor) {
    write_dot_node_header(file, ast, node, fillcolor);
    write_dot_node_footer(file);
}

void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor,
                    const char* field,
                    const char* value) {
    write_dot_node_header(file, ast, node, fillcolor);
    write_dot_node_row(file, field, value);
    write_dot_node_footer(file);
}

void write_dot_node(FILE* file,
                    rastr_ast_t ast,
                    rastr_node_t node,
                    const char* fillcolor,
                    const char* field1,
                    const char* value1,
                    const char* field2,
                    const char* value2) {
    write_dot_node_header(file, ast, node, fillcolor);
    write_dot_node_row(file, field1, value1);
    write_dot_node_row(file, field2, value2);
    write_dot_node_footer(file);
}

void write_edge(FILE* file,
                rastr_ast_t ast,
                rastr_node_t parent,
                rastr_node_t child,
                const char* label) {
    int par_id = rastr_node_id(ast, parent);
    rastr_node_type_t par_type = rastr_node_type(ast, parent);
    const char* par_type_str = rastr_node_type_to_string(par_type);

    int chd_id = rastr_node_id(ast, child);
    rastr_node_type_t chd_type = rastr_node_type(ast, child);
    const char* chd_type_str = rastr_node_type_to_string(chd_type);

    const char* edge_tmpl = R"-(
    "node-%d" -> "node-%d" [
        label = "%s"
        tooltip = "%s#%d -> %s#%d"
        edgetooltip = "%s#%d -> %s#%d"
        labeltooltip = "%s#%d -> %s#%d"
        headtooltip = "%s#%d -> %s#%d"
        tailtooltip = "%s#%d -> %s#%d"
    ]
)-";

    fprintf(file,
            edge_tmpl,
            par_id,
            chd_id,
            label,
            par_type_str,
            par_id,
            chd_type_str,
            chd_id,
            par_type_str,
            par_id,
            chd_type_str,
            chd_id,
            par_type_str,
            par_id,
            chd_type_str,
            chd_id,
            par_type_str,
            par_id,
            chd_type_str,
            chd_id,
            par_type_str,
            par_id,
            chd_type_str,
            chd_id);
}
