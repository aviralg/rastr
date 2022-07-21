#include <rastr/api.h>
#include <cstdio>
#include "logger.h"
#include "interop.h"

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast);
void rastr_export_to_dot_node(FILE* file, rastr_ast_t ast, rastr_node_t node);

SEXP r_rastr_export_to_dot(SEXP r_ast, SEXP r_filepath) {
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
    rastr_export_to_dot(ast, filepath);

    return R_NilValue;
}

void rastr_export_to_dot(rastr_ast_t ast, const char* filepath) {
    FILE* fp = fopen(filepath, "w");

    if (fp == nullptr) {
        rastr_log_error("cannot open file '%s'", filepath);
    }

    rastr_export_to_dot_ast(fp, ast);
    fclose(fp);
}

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast) {
    fprintf(file,
            "digraph ast {\n"
            "    node [fontname  = \"Courier New\"\n"
            "          fontsize  = 12\n"
            "          style     = \"filled, bold\"\n"
            "          penwidth  = 2\n"
            "          fillcolor = \"white\"\n"
            "          shape     = \"Mrecord\"]\n"
            "\n"
            "    edge [fontname  = \"Courier New\"\n"
            "          penwidth  = 1\n"
            "          fontsize  = 10\n"
            "          fontcolor = \"black\"]\n"
            "\n"
            "    graph [fontsize = 10\n"
            "           labelloc = \"t\"\n"
            "           label    = \"\"\n"
            "           splines  = true\n"
            "           overlap  = false\n"
            "           rankdir  = \"TD\"]\n"
            "    ratio = auto;\n");

    rastr_export_to_dot_node(file, ast, rastr_ast_root(ast));

    fprintf(file, "}");
}

void rastr_export_to_dot_node(FILE* file, rastr_ast_t ast, rastr_node_t node) {
    rastr_node_type_t type = rastr_node_type(ast, node);
    const char* type_str = rastr_node_type_to_string(type);
    int id = rastr_node_id(ast, node);

    /********************************************************************************
      Operators
    ********************************************************************************/

    if (rastr_node_is_operator(ast, node)) {
        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id,
                rastr_node_operator_syntax(ast, node));
    }

    /********************************************************************************
      KEYWORDS
    ********************************************************************************/

    else if (rastr_node_is_keyword(ast, node)) {
        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id,
                rastr_node_keyword_syntax(ast, node));
    }

    /********************************************************************************
      Delimiters
    ********************************************************************************/

    else if (rastr_node_is_delimiter(ast, node)) {
        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id,
                rastr_node_delimiter_syntax(ast, node));
    }

    /********************************************************************************
      Literals
    ********************************************************************************/

    else if (rastr_node_is_literal(ast, node)) {
        switch (type) {
        case Null:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_null_syntax(ast, node));
            break;

        case Logical:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %d</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_logical_syntax(ast, node),
                    rastr_node_logical_value(ast, node));
            break;

        case Integer:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %d</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_integer_syntax(ast, node),
                    rastr_node_integer_value(ast, node));
            break;

        case Real:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %f</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_real_syntax(ast, node),
                    rastr_node_real_value(ast, node));
            break;

        case Complex:
            fprintf(
                file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; {real: %f, imaginary: %f}</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id,
                rastr_node_complex_syntax(ast, node),
                rastr_node_complex_value(ast, node).r,
                rastr_node_complex_value(ast, node).i);
            break;

        case String:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %s</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_string_syntax(ast, node),
                    rastr_node_string_value(ast, node));
            break;

        case Symbol:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %s</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_symbol_syntax(ast, node),
                    rastr_node_symbol_value(ast, node));
            break;

        case Placeholder:
            fprintf(file,
                    "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                    "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                    "                         <tr><td align=\"left\" port=\"r1\">VALUE  -&gt; %s</td></tr>\n"
                    "                     </table>>]\n",
                    id,
                    type_str,
                    id,
                    rastr_node_placeholder_syntax(ast, node),
                    rastr_node_placeholder_value(ast, node));
            break;

        default:
            fail_with("unhandled literal node of type '%s'", type_str);
        }
    }

    /********************************************************************************
      Terminators
    ********************************************************************************/

    else if (rastr_node_is_terminator(ast, node)) {
        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r1\">SYNTAX -&gt; %s</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id,
                rastr_node_terminator_syntax(ast, node));
    }

    /********************************************************************************
      Expressions
    ********************************************************************************/

    else if (type == UnaryExpression) {

        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id);

        rastr_node_t op = rastr_node_unary_expression_operator(ast, node);

        rastr_export_to_dot_node(file, ast, op);

        fprintf(file,
                "\"node-%d\" -> \"node-%d\" [label = \"op\"]\n",
                rastr_node_id(ast, node),
                rastr_node_id(ast, op));

        rastr_node_t expr = rastr_node_unary_expression_expression(ast, node);

        rastr_export_to_dot_node(file, ast, expr);

        fprintf(file,
                "\"node-%d\" -> \"node-%d\" [label = \"expr\"]\n",
                rastr_node_id(ast, node),
                rastr_node_id(ast, expr));

    }

    else if (type == BinaryExpression) {

        fprintf(file,
                "\"node-%d\"[label = <<table border=\"0\" cellborder=\"0\" bgcolor=\"white\">\n"
                "                         <tr><td bgcolor=\"black\" align=\"center\" colspan=\"2\" cellpadding=\"6\"><font color=\"white\"><B>%s</B></font></td></tr>\n"
                "                         <tr><td align=\"left\" port=\"r0\">ID     -&gt; %d</td></tr>\n"
                "                     </table>>]\n",
                id,
                type_str,
                id);

        rastr_node_t left_expr =
            rastr_node_binary_expression_left_expression(ast, node);

        rastr_export_to_dot_node(file, ast, left_expr);

        fprintf(file,
                "\"node-%d\" -> \"node-%d\" [label = \"left-expr\"]\n",
                rastr_node_id(ast, node),
                rastr_node_id(ast, left_expr));

        rastr_node_t op = rastr_node_binary_expression_operator(ast, node);

        rastr_export_to_dot_node(file, ast, op);

        fprintf(file,
                "\"node-%d\" -> \"node-%d\" [label = \"op\"]\n",
                rastr_node_id(ast, node),
                rastr_node_id(ast, op));

        rastr_node_t right_expr =
            rastr_node_binary_expression_right_expression(ast, node);

        rastr_export_to_dot_node(file, ast, right_expr);

        fprintf(file,
                "\"node-%d\" -> \"node-%d\" [label = \"right-expr\"]\n",
                rastr_node_id(ast, node),
                rastr_node_id(ast, right_expr));
    }

    /********************************************************************************
      Pseudo
    ********************************************************************************/

    else {
        fail_with("unexpected node of type '%s'", type_str);
    }
}
