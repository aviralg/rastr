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

#define EXPORT_CHILD(NODE_TYPE, CHILD)                                \
    rastr_node_t CHILD = rastr_node_##NODE_TYPE##_##CHILD(ast, node); \
    rastr_export_to_dot_node(file, ast, CHILD, depth);                \
    write_edge(file, ast, node, CHILD, #CHILD);

#define EXPORT_CHILDREN_1(NODE_TYPE, CHILD1) \
    --depth;                                 \
    if (depth != 0) {                        \
        EXPORT_CHILD(NODE_TYPE, CHILD1)      \
    };

#define EXPORT_CHILDREN_2(NODE_TYPE, CHILD1, CHILD2) \
    --depth;                                         \
    if (depth != 0) {                                \
        EXPORT_CHILD(NODE_TYPE, CHILD1)              \
        EXPORT_CHILD(NODE_TYPE, CHILD2)              \
    };

#define EXPORT_CHILDREN_3(NODE_TYPE, CHILD1, CHILD2, CHILD3) \
    --depth;                                                 \
    if (depth != 0) {                                        \
        EXPORT_CHILD(NODE_TYPE, CHILD1)                      \
        EXPORT_CHILD(NODE_TYPE, CHILD2)                      \
        EXPORT_CHILD(NODE_TYPE, CHILD3)                      \
    };

#define EXPORT_CHILDREN_5(NODE_TYPE, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
    --depth;                                                                 \
    if (depth != 0) {                                                        \
        EXPORT_CHILD(NODE_TYPE, CHILD1)                                      \
        EXPORT_CHILD(NODE_TYPE, CHILD2)                                      \
        EXPORT_CHILD(NODE_TYPE, CHILD3)                                      \
        EXPORT_CHILD(NODE_TYPE, CHILD4)                                      \
        EXPORT_CHILD(NODE_TYPE, CHILD5)                                      \
    };

std::string escape_dot_label(const char* label) {
    std::string label_str(label);
    string_replace(label_str, "\\", "\\\\");
    string_replace(label_str, "{", "\\{");
    string_replace(label_str, "}", "\\}");
    string_replace(label_str, "<", "&lt;");
    string_replace(label_str, ">", "&gt;");
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

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast, int depth);
void rastr_export_to_dot_node(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth);

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
            "           splines  = true\n"
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
        write_dot_node(file,
                       ast,
                       node,
                       ColorRed,
                       "CODE",
                       rastr_node_operator_syntax(ast, node));
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
        write_dot_node(file,
                       ast,
                       node,
                       ColorPink,
                       "CODE",
                       rastr_node_keyword_syntax(ast, node));
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
        write_dot_node(file,
                       ast,
                       node,
                       ColorPurple,
                       "CODE",
                       rastr_node_delimiter_syntax(ast, node));
        return;

        /********************************************************************************
         Terminators
        ********************************************************************************/
    case Semicolon:
    case Newline:
    case Comma:
        write_dot_node(file,
                       ast,
                       node,
                       ColorDeepPurple,
                       "CODE",
                       rastr_node_terminator_syntax(ast, node));
        return;

        /********************************************************************************
         Literals
        ********************************************************************************/
    case Null:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_null_syntax(ast, node));
        return;

    case Logical:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_logical_syntax(ast, node),
                       "VALUE",
                       bufprintf("%d", rastr_node_logical_value(ast, node)));
        return;

    case Integer:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_integer_syntax(ast, node),
                       "VALUE",
                       bufprintf("%d", rastr_node_integer_value(ast, node)));
        return;

    case Real:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_real_syntax(ast, node),
                       "VALUE",
                       bufprintf("%f", rastr_node_real_value(ast, node)));
        return;

    case Complex:
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
        return;

    case String:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_string_syntax(ast, node),
                       "VALUE",
                       rastr_node_string_value(ast, node));
        return;

    case Symbol:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_symbol_syntax(ast, node),
                       "VALUE",
                       rastr_node_symbol_value(ast, node));
        return;

    case Placeholder:
        write_dot_node(file,
                       ast,
                       node,
                       ColorIndigo,
                       "CODE",
                       rastr_node_placeholder_syntax(ast, node),
                       "VALUE",
                       rastr_node_placeholder_value(ast, node));
        return;

        /********************************************************************************
         Expressions
        ********************************************************************************/
    case UnaryExpression:
        write_dot_node(file, ast, node, ColorBlue);
        EXPORT_CHILDREN_2(unary_expression, op, expr);
        return;

    case BinaryExpression:
        write_dot_node(file, ast, node, ColorLightBlue);
        EXPORT_CHILDREN_3(binary_expression, left_expr, op, right_expr);
        return;

    case Block:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_3(block, left_brace, expressions, right_brace);
        return;

    case Group:
        write_dot_node(file, ast, node, ColorCyan);
        EXPORT_CHILDREN_3(group, left_paren, expr, right_paren);
        return;

        /********************************************************************************
         Statement
        ********************************************************************************/
    case Statement:
        write_dot_node(file, ast, node, ColorLime);
        EXPORT_CHILDREN_2(statement, expr, terminator);
        return;

        /********************************************************************************
         Program
        ********************************************************************************/
    case Program:
        write_dot_node(file, ast, node, ColorGreen);
        EXPORT_CHILDREN_1(program, statements);
        return;

        /********************************************************************************
         Sequence
        ********************************************************************************/
    case Sequence:
        write_dot_node(file, ast, node, ColorLightGreen);
        --depth;

        if (depth != 0) {
            rastr_node_t* nodes = rastr_node_sequence_nodes(ast, node);
            int size = rastr_node_sequence_size(ast, node);

            for (int i = 0; i < size; ++i) {
                rastr_node_t child = nodes[i];
                rastr_export_to_dot_node(file, ast, child, depth);
                write_edge(file, ast, node, child, bufprintf("nodes[%d]", i));
            }
        }

        return;

        /********************************************************************************
         End
        ********************************************************************************/
    case End:
        write_dot_node(file, ast, node, ColorBlack);
        return;

        /********************************************************************************
         Error
        ********************************************************************************/
    case Error:
        write_dot_node(file,
                       ast,
                       node,
                       ColorBlack,
                       "MESSAGE",
                       rastr_node_error_message(ast, node));
        return;

        /********************************************************************************
         Repeat
        ********************************************************************************/
    case RepeatLoop:
        write_dot_node(file, ast, node, ColorYellow);
        EXPORT_CHILDREN_2(rloop, kw, body);
        return;

        /********************************************************************************
         While
        ********************************************************************************/
    case WhileLoop:
        write_dot_node(file, ast, node, ColorBrown);
        EXPORT_CHILDREN_3(wloop, kw, cond, body);
        return;

    case IfCond:
        write_dot_node(file, ast, node, ColorAmber);
        EXPORT_CHILDREN_3(ifcond, if_kw, cond, csq);
        return;

    case IfElseCond:
        write_dot_node(file, ast, node, ColorOrange);
        EXPORT_CHILDREN_5(ifelsecond, if_kw, cond, csq, else_kw, alt);
        return;

        /********************************************************************************
         Error
        ********************************************************************************/
    case Missing:
        write_dot_node(file, ast, node, ColorBlack);
        return;

    case Arguments:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_3(arguments, ldelim, args, rdelim);
        return;

    case Call:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_2(call, fun, args);
        return;

    case Indices:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_3(indices, ldelim, nodes, rdelim);
        return;

    case Indexing:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_2(indexing, obj, indices);
        return;

    case Parameters:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_3(parameters, ldelim, seq, rdelim);
        return;

    case FunctionDefinition:
        write_dot_node(file, ast, node, ColorTeal);
        EXPORT_CHILDREN_3(fndef, kw, params, body);
        return;
    }

    fail_with("unexpected node of type '%s'", rastr_node_type_to_string(type));
}
