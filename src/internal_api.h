#ifndef RASTR_INTERNAL_API_H
#define RASTR_INTERNAL_API_H

#include "StringView.h"

rastr_node_t rastr_node_operator_from_view(rastr_ast_t ast,
                                           const StringView& syntax_view,
                                           rastr_node_type_t type);

rastr_node_t rastr_node_string_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         const StringView& value_view);

rastr_node_t rastr_node_symbol_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view,
                                         const StringView& value_view);

rastr_node_t rastr_node_integer_from_view(rastr_ast_t ast,
                                          const StringView& syntax_view);

rastr_node_t rastr_node_double_from_view(rastr_ast_t ast,
                                         const StringView& syntax_view);

rastr_node_t rastr_node_complex_from_view(rastr_ast_t ast,
                                          const StringView& syntax_view);

#endif /* RASTR_INTERNAL_API_H */
