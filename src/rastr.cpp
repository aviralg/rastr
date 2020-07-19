#include "rastr.hpp"

#include "IntegerLiteralExpressionRNode.hpp"
#include "DoubleLiteralExpressionRNode.hpp"
#include "CharacterLiteralExpressionRNode.hpp"
#include "ComplexLiteralExpressionRNode.hpp"
#include "LogicalLiteralExpressionRNode.hpp"
#include "RawLiteralExpressionRNode.hpp"
#include "ConditionRNode.hpp"
#include "DelimitedRNode.hpp"
#include "DelimiterRNode.hpp"
#include "ForLoopExpressionRNode.hpp"
#include "FunctionCallExpressionRNode.hpp"
#include "FunctionDefinitionExpressionRNode.hpp"
#include "IfConditionalExpressionRNode.hpp"
#include "IfElseConditionalExpressionRNode.hpp"
#include "InRNode.hpp"
#include "KeywordRNode.hpp"
#include "ParameterSequenceRNode.hpp"
#include "RepeatLoopExpressionRNode.hpp"
#include "SymbolExpressionRNode.hpp"
#include "WhileLoopExpressionRNode.hpp"
#include "BinaryExpressionRNode.hpp"

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
    ast::ArgumentSequenceRNode::initialize();
    ast::ConditionRNode::initialize();
    ast::DelimitedRNode::initialize();
    ast::DelimiterRNode::initialize();
    ast::ForLoopExpressionRNode::initialize();
    ast::FunctionCallExpressionRNode::initialize();
    ast::FunctionDefinitionExpressionRNode::initialize();
    ast::IfConditionalExpressionRNode::initialize();
    ast::IfElseConditionalExpressionRNode::initialize();
    ast::InRNode::initialize();
    ast::KeywordRNode::initialize();
    ast::ParameterSequenceRNode::initialize();
    ast::RepeatLoopExpressionRNode::initialize();
    ast::SymbolExpressionRNode::initialize();
    ast::WhileLoopExpressionRNode::initialize();
    ast::BinaryExpressionRNode::initialize();
}

} // namespace rastr
