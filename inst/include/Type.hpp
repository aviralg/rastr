#ifndef RASTR_AST_TYPE_HPP
#define RASTR_AST_TYPE_HPP

#include <string>

namespace rastr {
namespace ast {

enum class Type {
    /* Node */
    /*      */ UndefinedNode,
    /*     RNode */
    /*      */ DelimiterRNode,
    /*      */ KeywordRNode,
    /*      */ OperatorRNode,
    /*      */ BeginRNode,
    /*      */ EndRNode,
    /*      */ ProgramRNode,
    /*      */ FileRNode,
    /*      */ ExpressionSequenceRNode,
    /*         ConditionRNode */
    /*          */ ExpressionConditionRNode,
    /*          */ InConditionRNode,
    /*         ExpressionRNode */
    /*          */ NextExpressionRNode,
    /*          */ BreakExpressionRNode,
    /*          */ MissingExpressionRNode,
    /*          */ SymbolExpressionRNode,
    /*          */ TerminatedExpressionRNode,
    /*          */ GroupExpressionRNode,
    /*          */ BlockExpressionRNode,
    /*          */ FunctionDefinitionExpressionRNode,
    /*          */ FunctionCallExpressionRNode,
    /*          */ IndexingExpressionRNode,
    /*          */ SubsettingExpressionRNode,
    /*             LiteralExpressionRNode */
    /*              */ DoubleLiteralExpressionRNode,
    /*              */ IntegerLiteralExpressionRNode,
    /*              */ ComplexLiteralExpressionRNode,
    /*              */ LogicalLiteralExpressionRNode,
    /*              */ RawLiteralExpressionRNode,
    /*              */ CharacterLiteralExpressionRNode,
    /*              */ RawStringLiteralExpressionRNode,
    /*              */ ConstantLiteralExpressionRNode,
    /*             ConditionalExpressionRNode */
    /*              */ IfConditionalExpressionRNode,
    /*              */ IfElseConditionalExpressionRNode,
    /*             LoopExpressionRNode */
    /*              */ ForLoopExpressionRNode,
    /*              */ WhileLoopExpressionRNode,
    /*              */ RepeatLoopExpressionRNode,
    /*             OperationExpressionRNode */
    /*              */ BinaryOperationExpressionRNode,
    /*              */ UnaryOperationExpressionRNode,

};

const std::string type_to_string(const Type type);

Type string_to_type(const std::string& type);

} // namespace ast
} // namespace rastr

#endif /* RASTR_AST_TYPE_HPP */
