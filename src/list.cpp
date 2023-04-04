#include <rastr/api.h>
#include "interop.h"
#include <vector>
#include "r_api.h"
#include <string>
#include "internal_api.h"


#include <vector>
#include <rastr/api.h>
#include <cstdio>
#include "r_api.h"
#include "logger.h"
#include "interop.h"
#include "utilities.h"
#include <sstream>

/* Material Design colors taken from
   https://material.io/design/color/the-color-system.html#tools-for-picking-colors
   Selected shade 500 from every color column */
static const char* ColorRed = "#F44336";
static const char* ColorPink = "#E91E63";
static const char* ColorPurple = "#9C27B0";
static const char* ColorDeepPurple = "#673AB7";
static const char* ColorIndigo = "#3F51B5";
static const char* ColorBlue = "#2196F3";
static const char* ColorLightBlue = "#03A9F4";
static const char* ColorCyan = "#00BCD4";
static const char* ColorTeal = "#009688";
static const char* ColorGreen = "#4CAF50";
static const char* ColorLightGreen = "#8BC34A";
static const char* ColorLime = "#CDDC39";
static const char* ColorYellow = "#FFEB3B";
static const char* ColorAmber = "#FFC107";
static const char* ColorOrange = "#FF9800";
static const char* ColorDeepOrange = "#FF5722";
static const char* ColorBrown = "#795548";
static const char* ColorGray = "#9E9E9E";
static const char* ColorBlueGray = "#607D8B";
static const char* ColorBlack = "#000000";
static const char* ColorWhite = "#FFFFFF";

#define EXPORT_EDGE(KIND, CHILD)                                  \
    rastr_node_t CHILD = rastr_##KIND##_##CHILD##_get(ast, node); \
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

#define EXPORT_EDGES_4(KIND, CHILD1, CHILD2, CHILD3, CHILD4) \
    EXPORT_EDGE_HEADER(4)                                    \
    EXPORT_EDGE(KIND, CHILD1)                                \
    EXPORT_EDGE(KIND, CHILD2)                                \
    EXPORT_EDGE(KIND, CHILD3)                                \
    EXPORT_EDGE(KIND, CHILD4)                                \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_5(KIND, CHILD1, CHILD2, CHILD3, CHILD4, CHILD5) \
    EXPORT_EDGE_HEADER(5)                                            \
    EXPORT_EDGE(KIND, CHILD1)                                        \
    EXPORT_EDGE(KIND, CHILD2)                                        \
    EXPORT_EDGE(KIND, CHILD3)                                        \
    EXPORT_EDGE(KIND, CHILD4)                                        \
    EXPORT_EDGE(KIND, CHILD5)                                        \
    EXPORT_EDGE_FOOTER()

#define EXPORT_EDGES_SEQ(KIND, LEN, SEQ)                             \
    EXPORT_EDGE_HEADER(rastr_##KIND##_##LEN##_get(ast, node))        \
    const rastr_node_t* seq = rastr_##KIND##_##SEQ##_get(ast, node); \
    int len = rastr_##KIND##_##LEN##_get(ast, node);                 \
                                                                     \
    for (int i = 0; i < len; ++i) {                                  \
        rastr_node_t child = seq[i];                                 \
        write_edge_(ast, node, child, bufprintf("seq[%d]", i));      \
    }                                                                \
    EXPORT_EDGE_FOOTER()

class StringStream {
  public:
    StringStream() {
    }

    void format(const char* format, ...) {
        va_list args;
        va_start(args, format);
        sprintf(buffer_, format, args);
        va_end(args);

        stream_ << buffer_;
    }

    char* extract() {
        return cppstr_to_cstr(stream_.str());
    }

  private:
    char buffer_[10240];
    std::stringstream stream_;
};

class DotTransformer: public AstWalker {
  public:
    DotTransformer(): AstWalker(), stream_(new StringStream()) {
    }

    virtual ~DotTransformer() {
        delete stream_;
    }

    bool pre_op(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_op_syn_get(ast, node), NULL);

        EXPORT_EDGES_2(op, gap, loc);

        return true;
    }

    bool pre_bkt(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_bkt_syn_get(ast, node), NULL);

        EXPORT_EDGES_2(bkt, gap, loc);

        return true;
    }

    bool pre_dlmtr(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_dlmtr_syn_get(ast, node), NULL);

        EXPORT_EDGES_2(dlmtr, gap, loc);

        return true;
    }

    bool pre_null(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, "syn", rastr_null_syn_get(ast, node), NULL);

        EXPORT_EDGES_2(null, gap, loc);

        return true;
    }

    bool pre_lgl(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_lgl_syn_get(ast, node),
                    "val",
                    bufprintf("%d", rastr_lgl_val_get(ast, node)),
                    NULL);

        EXPORT_EDGES_2(lgl, gap, loc);

        return true;
    }

    bool pre_int(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_int_syn_get(ast, node),
                    "val",
                    bufprintf("%d", rastr_int_val_get(ast, node)),
                    NULL);

        EXPORT_EDGES_2(int, gap, loc);

        return true;
    }

    bool pre_dbl(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_dbl_syn_get(ast, node),
                    "val",
                    bufprintf("%f", rastr_dbl_val_get(ast, node)),
                    NULL);

        EXPORT_EDGES_2(dbl, gap, loc);

        return true;
    }

    bool pre_cpx(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_cpx_syn_get(ast, node),
                    "val",
                    bufprintf("{r: %d, i: %d}",
                              rastr_cpx_val_get(ast, node).r,
                              rastr_cpx_val_get(ast, node).i),
                    NULL);

        EXPORT_EDGES_2(cpx, gap, loc);

        return true;
    }

    bool pre_chr(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_chr_syn_get(ast, node),
                    "val",
                    rastr_chr_val_get(ast, node),
                    NULL);

        EXPORT_EDGES_2(chr, gap, loc);

        return true;
    }

    bool pre_sym(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "syn",
                    rastr_sym_syn_get(ast, node),
                    "val",
                    rastr_sym_val_get(ast, node),
                    NULL);

        EXPORT_EDGES_2(sym, gap, loc);

        return true;
    }

    bool pre_blk(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(blk, lbkt, exprs, rbkt)

        return true;
    }

    bool pre_grp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(grp, lbkt, expr, rbkt);

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

        EXPORT_EDGES_2(rlp, op, body);

        return true;
    }

    bool pre_wlp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(wlp, op, cond, body);

        return true;
    }

    bool pre_flp(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(flp, op, iter, body);

        return true;
    }

    bool pre_icond(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(icond, iop, cond, ibody);

        return true;
    }

    bool pre_iecond(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_5(iecond, iop, cond, ibody, eop, ebody);

        return true;
    }

    bool pre_fndefn(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(fndefn, op, pars, body);

        return true;
    }

    bool pre_fncall(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_4(fncall, fn, lbkt, args, rbkt);

        return true;
    }

    bool pre_sub(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_4(sub, obj, lbkt, args, rbkt);

        return true;
    }

    bool pre_idx(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_5(idx, obj, lbkt, args, rbkt1, rbkt2);

        return true;
    }

    bool pre_aexpr(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_2(aexpr, ann, expr)

        return true;
    }

    bool pre_exprs(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "len",
                    bufprintf("%d", rastr_exprs_len_get(ast, node)),
                    NULL);

        EXPORT_EDGES_SEQ(exprs, len, seq)

        return true;
    }

    bool pre_pars(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "len",
                    bufprintf("%d", rastr_pars_len_get(ast, node)),
                    NULL);

        EXPORT_EDGES_SEQ(pars, len, seq)

        return true;
    }

    bool pre_dpar(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(dpar, name, op, expr)

        return true;
    }

    bool pre_ndpar(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_1(ndpar, name)

        return true;
    }

    bool pre_args(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast,
                    node,
                    "len",
                    bufprintf("%d", rastr_args_len_get(ast, node)),
                    NULL);

        EXPORT_EDGES_SEQ(args, len, seq)

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

    bool pre_cond(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(cond, lbkt, expr, rbkt)

        return true;
    }

    bool pre_iter(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_5(iter, lbkt, var, op, expr, rbkt)

        return true;
    }

    bool pre_pgm(rastr_ast_t ast, rastr_node_t node) override {
        write_node_(ast, node, NULL);

        EXPORT_EDGES_3(pgm, beg, exprs, end)

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
        write_node_(ast, node, "val", rastr_gap_val_get(ast, node), NULL);

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

        sprintf(lrow, "%d", rastr_loc_lrow_get(ast, node));
        sprintf(lcol, "%d", rastr_loc_lcol_get(ast, node));
        sprintf(lchr, "%d", rastr_loc_lchr_get(ast, node));
        sprintf(lbyte, "%d", rastr_loc_lbyte_get(ast, node));
        sprintf(rrow, "%d", rastr_loc_rrow_get(ast, node));
        sprintf(rcol, "%d", rastr_loc_rcol_get(ast, node));
        sprintf(rchr, "%d", rastr_loc_rchr_get(ast, node));
        sprintf(rbyte, "%d", rastr_loc_rbyte_get(ast, node));

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

    char* transform(rastr_ast_t ast, rastr_node_t node, int depth) {
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

        stream_->format("%s", graph_tmpl);

        depths_.push_back(depth);

        this->walk(ast, rastr_ast_root_get(ast));

        stream_->format("}");

        return stream_->extract();
    }

    void walk(rastr_ast_t ast, rastr_node_t node) override {
        if (depths_.back() != 0) {
            AstWalker::walk(ast, node);
        }
        depths_.pop_back();
    }

  private:
    StringStream* stream_;
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

        stream_->format(header_tmpl, id, fillcolor, type_str, id, type_str, id);
    }

    void write_footer_() {
        const char* footer_tmpl = R"-(
                 </table>>
    ]
)-";

        /* note: the indirection of substituting footer in %s is to
           avoid format-security error on Ubuntu
           https://stackoverflow.com/questions/17260409/fprintf-error-format-not-a-string-literal-and-no-format-arguments-werror-for*/
        stream_->format("%s", footer_tmpl);
    }

    void write_row_(const char* field, const char* value) {
        std::string esc_value = escape_label_(value);

        const char* row_tmpl = R"-(
                      <tr><td align="left">%s</td><td>➜</td><td align="left">%s</td></tr>)-";

        stream_->format(row_tmpl, field, esc_value.c_str());
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

        stream_->format(edge_tmpl,
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
        case RASTR_OP_SP:
        case RASTR_OP_PLUS:
        case RASTR_OP_MINUS:
        case RASTR_OP_MUL:
        case RASTR_OP_DIV:
        case RASTR_OP_POW:
        case RASTR_OP_POW2:
        case RASTR_OP_LESS:
        case RASTR_OP_LESS_EQ:
        case RASTR_OP_GREAT:
        case RASTR_OP_GREAT_EQ:
        case RASTR_OP_EQ:
        case RASTR_OP_NOT_EQ:
        case RASTR_OP_NOT:
        case RASTR_OP_AND:
        case RASTR_OP_VEC_AND:
        case RASTR_OP_OR:
        case RASTR_OP_VEC_OR:
        case RASTR_OP_EQ_ASGN:
        case RASTR_OP_LT_ASGN:
        case RASTR_OP_RT_ASGN:
        case RASTR_OP_LT_SUP_ASGN:
        case RASTR_OP_RT_SUP_ASGN:
        case RASTR_OP_COLON_ASGN:
        case RASTR_OP_PIPE_FWD:
        case RASTR_OP_PIPE_BIND:
        case RASTR_OP_PUB_NS:
        case RASTR_OP_PVT_NS:
        case RASTR_OP_RANGE:
        case RASTR_OP_HELP:
        case RASTR_OP_SLOT:
        case RASTR_OP_FORMULA:
        case RASTR_OP_PART:
        case RASTR_OP_FN:
        case RASTR_OP_FN2:
        case RASTR_OP_WHILE:
        case RASTR_OP_REPEAT:
        case RASTR_OP_FOR:
        case RASTR_OP_IN:
        case RASTR_OP_IF:
        case RASTR_OP_ELSE:
        case RASTR_OP_NEXT:
        case RASTR_OP_BREAK:
            return ColorRed;
            break;

            /********************************************************************************
             Brackets
            ********************************************************************************/
        case RASTR_BKT_LT_RND:
        case RASTR_BKT_RT_RND:
        case RASTR_BKT_LT_CURL:
        case RASTR_BKT_RT_CURL:
        case RASTR_BKT_LT_SQR:
        case RASTR_BKT_RT_SQR:
        case RASTR_BKT_LT_DBL_SQR:
            return ColorPink;
            break;

            /********************************************************************************
             Delimiters
            ********************************************************************************/
        case RASTR_DLMTR_SCOL:
        case RASTR_DLMTR_COM:
            return ColorPurple;
            break;

            /********************************************************************************
              Literals
            ********************************************************************************/
        case RASTR_NULL:
            return ColorGreen;
            break;

        case RASTR_LGL:
            return ColorGreen;
            break;

        case RASTR_INT:
            return ColorGreen;
            break;

        case RASTR_DBL:
            return ColorGreen;
            break;

        case RASTR_CPX:
            return ColorGreen;
            break;

        case RASTR_CHR:
            return ColorGreen;
            break;

        case RASTR_SYM:
            return ColorGreen;
            break;

        /********************************************************************************
          Expressions
        ********************************************************************************/
        case RASTR_BLK:
            return ColorDeepPurple;
            break;

        case RASTR_GRP:
            return ColorIndigo;
            break;
        case RASTR_NUOP:
            return ColorBlue;
            break;
        case RASTR_UNOP:
            return ColorBlue;
            break;
        case RASTR_BINOP:
            return ColorBlue;
            break;
        case RASTR_RLP:
            return ColorTeal;
            break;
        case RASTR_WLP:
            return ColorTeal;
            break;
        case RASTR_FLP:
            return ColorTeal;
            break;
        case RASTR_ICOND:
            return ColorLightGreen;
            break;
        case RASTR_IECOND:
            return ColorLightGreen;
            break;
        case RASTR_FNDEFN:
            return ColorLime;
            break;
        case RASTR_FNCALL:
            return ColorYellow;
            break;
        case RASTR_SUB:
            return ColorYellow;
            break;
        case RASTR_IDX:
            return ColorYellow;
            break;
            /********************************************************************************
              Miscellaneous
            ********************************************************************************/
            /* TODO: choose a different color */
        case RASTR_AEXPR:
            return ColorAmber;
            break;
        case RASTR_EXPRS:
            return ColorAmber;
            break;
        case RASTR_PARS:
            return ColorAmber;
            break;
        case RASTR_DPAR:
            return ColorOrange;
            break;
        case RASTR_NDPAR:
            return ColorOrange;
            break;
        case RASTR_ARGS:
            return ColorBrown;
            break;
        case RASTR_NARG:
            return ColorDeepOrange;
            break;
        case RASTR_PARG:
            return ColorDeepOrange;
            break;
        case RASTR_COND:
            return ColorBrown;
            break;
        case RASTR_ITER:
            return ColorBrown;
            break;
        case RASTR_PGM:
            return ColorLightBlue;
            break;
        case RASTR_DLMTD:
            return ColorCyan;
            break;
        case RASTR_MSNG:
            return ColorBlueGray;
            break;
        case RASTR_BEG:
            return ColorGray;
            break;
        case RASTR_END:
            return ColorGray;
            break;
        case RASTR_GAP:
            return ColorBlack;
            break;
        case RASTR_LOC:
            return ColorBlack;
            break;
        case RASTR_ERR:
            return ColorBlack;
            break;
        }

        return ColorBlack;
    }
};

struct data_t {
    DotTransformer* transformer;
    rastr_ast_t ast;
    rastr_node_t node;
};

static SEXP transform(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    // TODO: expose depth argument to R level after implementing for to_list and
    // to_df
    return (SEXP)data->transformer->transform(data->ast, data->node, INT_MAX);
}

static void cleanup(void* ptr) {
    data_t* data = static_cast<data_t*>(ptr);
    delete data->transformer;
}

//char* rastr_to_dot(rastr_ast_t ast, rastr_node_t node) {
//    DotTransformer* transformer = new DotTransformer();
//    data_t data{transformer, ast, node};
//    return (char*) R_ExecWithCleanup(transform, &data, cleanup, &data);
//}
//
//SEXP r_rastr_to_dot(SEXP r_ast, SEXP r_node) {
//    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
//    rastr_node_t node = rastr_node_unwrap(r_node);
//    char* str = rastr_to_dot(ast, node);
//    SEXP r_str = rastr_str_wrap(str);
//    free(str);
//    return r_str;
//}


SEXP rastr_to_list(rastr_ast_t ast, rastr_node_t node) {
    return R_NilValue;
}

SEXP r_rastr_to_list(SEXP r_ast, SEXP r_node) {
    rastr_ast_t ast = rastr_ast_unwrap(r_ast);
    rastr_node_t node = rastr_node_unwrap(r_node);
    return rastr_to_list(ast, node);
}
