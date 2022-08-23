#include <vector>
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

#define EXPORT_EDGE(KIND, CHILD)                            \
    rastr_node_t CHILD = rastr_##KIND##_##CHILD(ast, node); \
    write_edge_(ast, node, CHILD, #CHILD);

#define EXPORT_EDGE_HEADER(n) \
    --depths_.back();         \
    repeat_depths_(n);        \
    if (depths_.back() != 0) {
//
#define EXPORT_EDGE_FOOTER() }

#define EXPORT_EDGES_1(KIND, CHILD1) \
    EXPORT_EDGE_HEADER(1)            \
    EXPORT_EDGE(KIND, CHILD1)        \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_2(KIND, CHILD1, CHILD2) \
    EXPORT_EDGE_HEADER(2)                    \
    EXPORT_EDGE(KIND, CHILD1)                \
    EXPORT_EDGE(KIND, CHILD2)                \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_3(KIND, CHILD1, CHILD2, CHILD3) \
    EXPORT_EDGE_HEADER(3)                            \
    EXPORT_EDGE(KIND, CHILD1)                        \
    EXPORT_EDGE(KIND, CHILD2)                        \
    EXPORT_EDGE(KIND, CHILD3)                        \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_5(KIND, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
    EXPORT_EDGE_HEADER(5)                                            \
    EXPORT_EDGE(KIND, CHILD1)                                        \
    EXPORT_EDGE(KIND, CHILD2)                                        \
    EXPORT_EDGE(KIND, CHILD3)                                        \
    EXPORT_EDGE(KIND, CHILD4)                                        \
    EXPORT_EDGE(KIND, CHILD5)                                        \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_BRACK_SEQ(KIND, LBRACK, LEN, SEQ, RBRACK) \
    EXPORT_EDGE_HEADER(2 + rastr_##KIND##_##LEN(ast, node))    \
    EXPORT_EDGE(KIND, LBRACK)                                  \
    EXPORT_EDGES_SEQ_INNER(KIND, LEN, SEQ)                     \
    EXPORT_EDGE(KIND, RBRACK)                                  \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_SEQ(KIND, LEN, SEQ)                \
    EXPORT_EDGE_HEADER(rastr_##KIND##_##LEN(ast, node)) \
    EXPORT_EDGES_SEQ_INNER(KIND, LEN, SEQ)              \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_SEQ_INNER(KIND, LEN, SEQ)                  \
    const rastr_node_t* seq = rastr_##KIND##_##SEQ(ast, node);  \
    int len = rastr_##KIND##_##LEN(ast, node);                  \
                                                                \
    for (int i = 0; i < len; ++i) {                             \
        rastr_node_t child = seq[i];                            \
        write_edge_(ast, node, child, bufprintf("seq[%d]", i)); \
    }

class DotSerializer: public AstWalker {
  public:
    DotSerializer(FILE* file): AstWalker(), file_(file) {
    }

    bool pre_op(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_op_syn(ast, node), NULL);

        EXPORT_EDGES_2(op, gap, loc);

        return true;
    }

    bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(
            ast, node, "syn", rastr_node_delimiter_syntax(ast, node), NULL);

        EXPORT_EDGES_2(dlmtr, gap, loc);

        return true;
    }

    bool pre_term(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(
            ast, node, "syn", rastr_node_terminator_syntax(ast, node), NULL);

        EXPORT_EDGES_2(term, gap, loc);

        return true;
    }

    bool pre_null(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_node_null_syntax(ast, node), NULL);

        EXPORT_EDGES_2(null, gap, loc);

        return true;
    }

    bool pre_logical(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_logical_syntax(ast, node),
                    "val",
                    bufprintf("%d", rastr_node_logical_value(ast, node)),
                    NULL);

        EXPORT_EDGES_2(logical, gap, loc);

        return true;
    }

    bool pre_integer(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_integer_syntax(ast, node),
                    "val",
                    bufprintf("%d", rastr_node_integer_value(ast, node)),
                    NULL);

        EXPORT_EDGES_2(integer, gap, loc);

        return true;
    }

    bool pre_real(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_real_syntax(ast, node),
                    "val",
                    bufprintf("%f", rastr_node_real_value(ast, node)),
                    NULL);

        EXPORT_EDGES_2(real, gap, loc);

        return true;
    }

    bool pre_complex(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_complex_syntax(ast, node),
                    "val",
                    bufprintf("{r: %d, i: %d}",
                              rastr_node_complex_value(ast, node).r,
                              rastr_node_complex_value(ast, node).i),
                    NULL);

        EXPORT_EDGES_2(complex, gap, loc);

        return true;
    }

    bool pre_string(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_string_syntax(ast, node),
                    "val",
                    rastr_node_string_value(ast, node),
                    NULL);

        EXPORT_EDGES_2(string, gap, loc);

        return true;
    }

    bool pre_symbol(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_node_symbol_syntax(ast, node),
                    "val",
                    rastr_node_symbol_value(ast, node),
                    NULL);

        EXPORT_EDGES_2(symbol, gap, loc);

        return true;
    }

    bool pre_blk(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(
            ast, node, "len", bufprintf("%d", rastr_blk_len(ast, node)), NULL);

        EXPORT_EDGES_BRACK_SEQ(blk, lbrack, len, seq, rbrack)

        return true;
    }

    bool pre_grp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(grp, lbrack, expr, rbrack);

        return true;
    }

    bool pre_nuop(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_1(nuop, op);

        return true;
    }

    bool pre_unop(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(unop, op, expr);

        return true;
    }

    bool pre_binop(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(binop, lexpr, op, rexpr);

        return true;
    }

    bool pre_rlp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(rlp, kw, body);

        return true;
    }

    bool pre_wlp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(wlp, kw, cond, body);

        return true;
    }

    bool pre_flp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(flp, kw, iter, body);

        return true;
    }

    bool pre_icnd(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(icnd, ikw, cond, ibody);

        return true;
    }

    bool pre_iecnd(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_5(iecnd, ikw, cond, ibody, ekw, ebody);

        return true;
    }

    bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(fndefn, hd, params, body);

        return true;
    }

    bool pre_fncall(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(fncall, fun, args);

        return true;
    }

    bool pre_sub(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(sub, obj, inds);

        return true;
    }

    bool pre_idx(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(idx, obj, inds);

        return true;
    }

    bool pre_params(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "len",
                    bufprintf("%d", rastr_params_len(ast, node)),
                    NULL);

        EXPORT_EDGES_BRACK_SEQ(params, lbrack, len, seq, rbrack)

        return true;
    }

    bool pre_dparam(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(dparam, name, op, expr)

        return true;
    }

    bool pre_ndparam(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_1(ndparam, name)

        return true;
    }

    bool pre_args(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(
            ast, node, "len", bufprintf("%d", rastr_args_len(ast, node)), NULL);

        EXPORT_EDGES_BRACK_SEQ(args, lbrack, len, seq, rbrack)

        return true;
    }

    bool pre_narg(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(narg, name, op, expr)

        return true;
    }

    bool pre_parg(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_1(parg, expr)

        return true;
    }

    bool pre_cnd(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(cnd, lbrack, expr, rbrack)

        return true;
    }

    bool pre_iter(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_5(iter, lbrack, var, kw, expr, rbrack)

        return true;
    }

    bool pre_pgm(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(
            ast, node, "len", bufprintf("%d", rastr_pgm_len(ast, node)), NULL);

        EXPORT_EDGES_BRACK_SEQ(pgm, beg, len, seq, end)

        return true;
    }

    bool pre_dlmtd(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(dlmtd, expr, dlmtr)

        return true;
    }

    bool pre_msng(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(msng, gap, loc)

        return true;
    }

    bool pre_beg(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_1(beg, loc)

        return true;
    }

    bool pre_end(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(end, gap, loc)

        return true;
    }

    bool pre_gap(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "val", rastr_gap_val(ast, node), NULL);

        EXPORT_EDGES_1(gap, loc)

        return true;
    }

    bool pre_loc(rastr_ast_t ast, rastr_node_t node) override {
        char lrow[10];
        char lcol[10];
        char lchr[10];
        char lbyte[10];
        char rrow[10];
        char rcol[10];
        char rchr[10];
        char rbyte[10];

        sprintf(lrow, "%d", rastr_pos_lrow(ast, node));
        sprintf(lcol, "%d", rastr_pos_lcol(ast, node));
        sprintf(lchr, "%d", rastr_pos_lchr(ast, node));
        sprintf(lbyte, "%d", rastr_pos_lbyte(ast, node));
        sprintf(rrow, "%d", rastr_pos_rrow(ast, node));
        sprintf(rcol, "%d", rastr_pos_rcol(ast, node));
        sprintf(rchr, "%d", rastr_pos_rchr(ast, node));
        sprintf(rbyte, "%d", rastr_pos_rbyte(ast, node));

        write_node_(ast,
                    node,
                    "lrow",
                    lrow,
                    "lcol",
                    lcol,
                    "lchr",
                    lchr,
                    "lbyte",
                    lbyte,
                    "rrow",
                    rrow,
                    "rcol",
                    rcol,
                    "rchr",
                    rchr,
                    "rbyte",
                    rbyte,
                    NULL);

        return true;
    }

    void write(rastr_ast_t ast, rastr_node_t node, int depth) {
        const char* graph_tmpl = R"-(
digraph ast {

    graph [fontsize = 10
           labelloc = "t"
           label    = ""
           splines  = true
           overlap  = false
           forcelabels = true
           center = true
           rankdir  = "TD"]

    node [fontname  = "Courier New"
          fontsize  = 12
          style     = "filled, bold"
          penwidth  = 2
          fontcolor = "white"
          shape     = "Mrecord"]

    edge [fontname  = "Courier New"
          penwidth  = 2
          fontsize  = 12
          fontcolor = "black"]

    ratio = auto;
    charset="UTF-8"
)-";

        fprintf(file_, "%s", graph_tmpl);

        depths_.push_back(depth);

        this->walk(ast, rastr_ast_root(ast));

        fprintf(file_, "}");
    }

    void walk(rastr_ast_t ast, rastr_node_t node) override {
        if (depths_.back() != 0) {
            AstWalker::walk(ast, node);
        }
        depths_.pop_back();
    }

  private:
    FILE* file_;
    std::vector<int> depths_;

    void repeat_depths_(int n) {
        int depth = depths_.back();

        for (int i = 0; i < n; ++i) {
            depths_.push_back(depth);
        }
    }

    std::string escape_label_(const char* label) {
        std::string label_str(label == nullptr ? "" : label);
        string_replace(label_str, "\\", "\\\\");
        string_replace(label_str, "|", "\\|");
        string_replace(label_str, "{", "\\{");
        string_replace(label_str, "}", "\\}");
        string_replace(label_str, "&", "&amp;");
        string_replace(label_str, "<", "&lt;");
        string_replace(label_str, ">", "&gt;");
        return label_str;
    }

    void write_header_(rastr_ast_t ast, rastr_node_t node) {
        int id = rastr_node_id(ast, node);
        rastr_node_type_t type = rastr_node_type(ast, node);
        const char* type_str = rastr_node_type_to_string(type);
        const char* fillcolor = get_color_(type);

        const char* header_tmpl = R"-(
    "node-%d"[
         fillcolor ="%s"
         tooltip = "%s#%d"
         label = <<table border='0' cellborder='0'>
                      <tr><td align="center" colspan="3"><B>%s</B></td></tr>
                      <tr><td align="left">id</td><td>➜</td><td align="left">%d</td></tr>)-";

        fprintf(file_, header_tmpl, id, fillcolor, type_str, id, type_str, id);
    }

    void write_footer_() {
        const char* footer_tmpl = R"-(
                 </table>>
    ]
)-";

        /* note: the indirection of substituting footer in %s is to
           avoid format-security error on Ubuntu
           https://stackoverflow.com/questions/17260409/fprintf-error-format-not-a-string-literal-and-no-format-arguments-werror-for*/
        fprintf(file_, "%s", footer_tmpl);
    }

    void write_row_(const char* field, const char* value) {
        std::string esc_value = escape_label_(value);

        const char* row_tmpl = R"-(
                      <tr><td align="left">%s</td><td>➜</td><td align="left">%s</td></tr>)-";

        fprintf(file_, row_tmpl, field, esc_value.c_str());
    }

    void write_node_(rastr_ast_t ast, rastr_node_t node, ...) {
        write_header_(ast, node);

        va_list pairs;
        va_start(pairs, node);

        while (true) {
            const char* field = va_arg(pairs, const char*);
            if (field == NULL)
                break;
            const char* value = va_arg(pairs, const char*);
            write_row_(field, value);
        }

        va_end(pairs);

        write_footer_();
    }

    void write_edge_(rastr_ast_t ast,
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
        tooltip = "%s#%d ➜ %s#%d"
        edgetooltip = "%s#%d ➜ %s#%d"
        labeltooltip = "%s#%d ➜ %s#%d"
        headtooltip = "%s#%d ➜ %s#%d"
        tailtooltip = "%s#%d ➜ %s#%d"
    ]
)-";

        fprintf(file_,
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

    const char* get_color_(rastr_node_type_t type) {
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
        case Power2:
        case LessThan:
        case LessThanEqual:
        case GreaterThan:
        case GreaterThanEqual:
        case Equal:
        case NotEqual:
        case Not:
        case And:
        case VecAnd:
        case Or:
        case VecOr:
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
        case Function2:
        case Function:
        case While:
        case Repeat:
        case For:
        case In:
        case If:
        case Else:
        case Next:
        case Break:
            return ColorRed;
            break;

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
            return ColorPink;
            break;

            /********************************************************************************
              Terminators
            ********************************************************************************/
        case Semicolon:
        case Newline:
        case Comma:
            return ColorPurple;
            break;

        /********************************************************************************
          Literals
        ********************************************************************************/
        case Null:
            return ColorGreen;
            break;
        case Logical:
            return ColorGreen;
            break;
        case Integer:
            return ColorGreen;
            break;
        case Real:
            return ColorGreen;
            break;
        case Complex:
            return ColorGreen;
            break;
        case String:
            return ColorGreen;
            break;
        case Symbol:
            return ColorGreen;
            break;

        /********************************************************************************
          Expressions
        ********************************************************************************/
        case Block:
            return ColorDeepPurple;
            break;
        case Group:
            return ColorIndigo;
            break;
        case NullaryOperation:
            return ColorBlue;
            break;
        case UnaryOperation:
            return ColorBlue;
            break;
        case BinaryOperation:
            return ColorBlue;
            break;
        case RepeatLoop:
            return ColorTeal;
            break;
        case WhileLoop:
            return ColorTeal;
            break;
        case ForLoop:
            return ColorTeal;
            break;
        case IfConditional:
            return ColorLightGreen;
            break;
        case IfElseConditional:
            return ColorLightGreen;
            break;
        case FunctionDefinition:
            return ColorLime;
            break;
        case FunctionCall:
            return ColorYellow;
            break;
        case Subset:
            return ColorYellow;
            break;
        case Index:
            return ColorYellow;
            break;

        /********************************************************************************
          Miscellaneous
        ********************************************************************************/
        case Parameters:
            return ColorAmber;
            break;
        case DefaultParameter:
            return ColorOrange;
            break;
        case NonDefaultParameter:
            return ColorOrange;
            break;
        case Arguments:
            return ColorBrown;
            break;
        case NamedArgument:
            return ColorDeepOrange;
            break;
        case PositionalArgument:
            return ColorDeepOrange;
            break;
        case Condition:
            return ColorBrown;
            break;
        case Iteration:
            return ColorBrown;
            break;
        case Program:
            return ColorLightBlue;
            break;
        case Delimited:
            return ColorCyan;
            break;
        case Missing:
            return ColorBlueGray;
            break;
        case Beg:
            return ColorGray;
            break;
        case End:
            return ColorGray;
            break;
        case Gap:
            return ColorBlack;
            break;
        case Location:
            return ColorBlack;
            break;
        case Error:
            return ColorBlack;
            break;
        }

        return ColorBlack;
    }
};

void rastr_export_to_dot_ast(FILE* file, rastr_ast_t ast, int depth);
void rastr_export_to_dot_node(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth);

SEXP r_rastr_export_to_dot(SEXP r_ast, SEXP r_filepath, SEXP r_depth) {
    SEXPTYPE type = TYPEOF(r_filepath);

    if (type != STRSXP) {
        Rf_error("expected a filepath of type string, received "
                 "a value of type "
                 "%s instead",
                 Rf_type2str(type));
        return R_NilValue;
    }

    int length = Rf_length(r_filepath);

    if (length != 1) {
        Rf_error("expected a filepath string of size 1, "
                 "received a string of "
                 "size %d instead",
                 length);
        return R_NilValue;
    }

    SEXP str_elt = STRING_ELT(r_filepath, 0);

    if (str_elt == NA_STRING) {
        Rf_error("expected a filepath, received NA_character_ "
                 "instead");
        return R_NilValue;
    }

    const char* filepath = CHAR(str_elt);

    rastr_ast_t ast = rastr_ast_unwrap(r_ast);

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
    return rastr_export_to_dot_node(file, ast, rastr_ast_root(ast), depth);
}

void rastr_export_to_dot_node(FILE* file,
                              rastr_ast_t ast,
                              rastr_node_t node,
                              int depth) {
    DotSerializer* dot_ser = new DotSerializer(file);
    dot_ser->write(ast, node, depth);
    delete dot_ser;
}
