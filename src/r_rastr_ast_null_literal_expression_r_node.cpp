#include "r_rastr_ast_null_literal_expression_r_node.h"
#include "NullLiteralExpressionRNode.hpp"
#include "r_cast.hpp"

using rastr::ast::NullLiteralExpressionRNode;
using rastr::ast::NullLiteralExpressionRNodeSPtr;

SEXP r_rastr_ast_null_literal_expression_r_node_create(SEXP r_representation) {
    const char* representation = CHAR(asChar(r_representation));

    NullLiteralExpressionRNodeSPtr node =
        std::make_shared<NullLiteralExpressionRNode>(representation);

    return to_sexp<NullLiteralExpressionRNode>(node);
}
