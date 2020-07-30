#include "rastr.hpp"
#include "ast.hpp"

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
    ast::DoubleLiteralExpressionRNode::initialize();
    ast::IntegerLiteralExpressionRNode::initialize();
    ast::ComplexLiteralExpressionRNode::initialize();
    ast::LogicalLiteralExpressionRNode::initialize();
    ast::RawLiteralExpressionRNode::initialize();
    ast::CharacterLiteralExpressionRNode::initialize();
    ast::RawStringLiteralExpressionRNode::initialize();
    ast::ConstantLiteralExpressionRNode::initialize();
    ast::NextExpressionRNode::initialize();
    ast::BreakExpressionRNode::initialize();
    ast::TerminatedExpressionRNode::initialize();
    ast::DelimiterRNode::initialize();
    ast::ConditionRNode::initialize();
    ast::SymbolExpressionRNode::initialize();
    ast::KeywordRNode::initialize();
    ast::ForLoopExpressionRNode::initialize();
    ast::WhileLoopExpressionRNode::initialize();
    ast::RepeatLoopExpressionRNode::initialize();
    ast::ExpressionSequenceRNode::initialize();
    ast::FunctionDefinitionExpressionRNode::initialize();
    ast::FunctionCallExpressionRNode::initialize();
    ast::IfConditionalExpressionRNode::initialize();
    ast::IfElseConditionalExpressionRNode::initialize();
    ast::OperatorRNode::initialize();
    ast::BinaryExpressionRNode::initialize();
    ast::UnaryExpressionRNode::initialize();
    ast::InRNode::initialize();
    ast::IndexingExpressionRNode::initialize();
    ast::BlockExpressionRNode::initialize();
    ast::MissingExpressionRNode::initialize();
    ast::GroupExpressionRNode::initialize();
    ast::EndRNode::initialize();
    ast::ProgramRNode::initialize();
}

} // namespace rastr
