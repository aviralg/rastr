#include "r_rastr_ast_i_keyword.h"
#include "IKeyword.hpp"
#include "r_cast.hpp"

using rastr::ast::IKeyword;
using rastr::ast::IKeywordSPtr;
using rastr::ast::KeywordRNode;
using rastr::ast::KeywordRNodeSPtr;

SEXP r_rastr_ast_i_keyword_get_keyword(SEXP r_i_keyword) {
    IKeywordSPtr i_keyword = from_sexp<IKeyword>(r_i_keyword);

    KeywordRNodeSPtr keyword = i_keyword->get_keyword();

    return to_sexp<KeywordRNode>(keyword);
}

SEXP r_rastr_ast_i_keyword_set_keyword(SEXP r_i_keyword, SEXP r_keyword) {
    IKeywordSPtr i_keyword = from_sexp<IKeyword>(r_i_keyword);

    KeywordRNodeSPtr keyword = from_sexp<KeywordRNode>(r_keyword);

    i_keyword->set_keyword(keyword);

    return r_i_keyword;
}
