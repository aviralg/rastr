#ifndef RASTR_AST_TYPE_HPP
#define RASTR_AST_TYPE_HPP

#include <string>

namespace rastr {
namespace ast {

enum class Type {
    DoubleLiteralExpressionRNode,
    IntegerLiteralExpressionRNode,
    ComplexLiteralExpressionRNode,
    LogicalLiteralExpressionRNode,
    RawLiteralExpressionRNode,
    CharacterLiteralExpressionRNode,
    RawStringLiteralExpressionRNode,
    ConstantLiteralExpressionRNode,
    NextExpressionRNode,
    BreakExpressionRNode,
    DelimiterRNode,
    TerminatedExpressionRNode,
    SymbolExpressionRNode,
    KeywordRNode,
    ForLoopExpressionRNode,
    WhileLoopExpressionRNode,
    RepeatLoopExpressionRNode,
    ExpressionSequenceRNode,
    FunctionDefinitionExpressionRNode,
    FunctionCallExpressionRNode,
    IfConditionalExpressionRNode,
    IfElseConditionalExpressionRNode,
    OperatorRNode,
    BinaryOperationExpressionRNode,
    UnaryOperationExpressionRNode,
    InRNode,
    IndexingExpressionRNode,
    SubsettingExpressionRNode,
    BlockExpressionRNode,
    MissingExpressionRNode,
    GroupExpressionRNode,
    BeginRNode,
    EndRNode,
    ProgramRNode,
    SpacingRNode,
    UndefinedNode,
};

const std::string type_to_string(const Type type);

Type string_to_type(const std::string& type);

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_TYPE_HPP */
