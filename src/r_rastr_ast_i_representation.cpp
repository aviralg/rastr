#include "r_rastr_ast_i_representation.h"
#include "IRepresentation.hpp"
#include "r_cast.hpp"

using rastr::ast::IRepresentation;
using rastr::ast::IRepresentationSPtr;

SEXP r_rastr_ast_i_representation_get_representation(SEXP r_i_representation) {
    IRepresentationSPtr i_representation =
        from_sexp<IRepresentation>(r_i_representation);

    const std::string& representation = i_representation->get_representation();

    return mkString(representation.c_str());
}
