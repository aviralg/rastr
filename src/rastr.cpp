#include "rastr.hpp"

#include "IntegerLiteralExpressionRNode.hpp"
#include "DoubleLiteralExpressionRNode.hpp"
#include "CharacterLiteralExpressionRNode.hpp"
#include "ComplexLiteralExpressionRNode.hpp"
#include "LogicalLiteralExpressionRNode.hpp"
#include "RawLiteralExpressionRNode.hpp"

namespace rastr {

SEXP UndefinedObject = NULL;

SEXP get_undefined_object() {
    return UndefinedObject;
}

bool is_undefined_object(SEXP object) {
    return object == UndefinedObject;
}

bool is_defined_object(SEXP object) {
    return !(is_undefined_object(object));
}

SEXP create_class(const std::vector<std::string>& class_names) {
    int size = class_names.size();

    SEXP r_class_names = PROTECT(allocVector(STRSXP, size));

    for (int index = 0; index < size; ++index) {
        SET_STRING_ELT(
            r_class_names, index, mkChar(class_names[index].c_str()));
    }

    UNPROTECT(1);

    return r_class_names;
}

void initialize() {
    ast::IntegerLiteralExpressionRNode::initialize();
    ast::DoubleLiteralExpressionRNode::initialize();
    ast::CharacterLiteralExpressionRNode::initialize();
    ast::ComplexLiteralExpressionRNode::initialize();
    ast::LogicalLiteralExpressionRNode::initialize();
    ast::RawLiteralExpressionRNode::initialize();
}

} // namespace rastr
