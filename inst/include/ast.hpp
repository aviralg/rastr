#ifndef RASTR_AST_HPP
#define RASTR_AST_HPP

#include "BinaryOperationExpressionRNode.hpp"
#include "BlockExpressionRNode.hpp"
#include "ConstantLiteralExpressionRNode.hpp"
#include "CharacterLiteralExpressionRNode.hpp"
#include "ComplexLiteralExpressionRNode.hpp"
#include "NullLiteralExpressionRNode.hpp"
#include "NextExpressionRNode.hpp"
#include "BreakExpressionRNode.hpp"
#include "ConditionalExpressionRNode.hpp"
#include "ConditionRNode.hpp"
#include "DelimiterRNode.hpp"
#include "DoubleLiteralExpressionRNode.hpp"
#include "ExpressionRNode.hpp"
#include "TerminatedExpressionRNode.hpp"
#include "ExpressionSequenceRNode.hpp"
#include "ForLoopExpressionRNode.hpp"
#include "FunctionCallExpressionRNode.hpp"
#include "FunctionDefinitionExpressionRNode.hpp"
#include "GroupExpressionRNode.hpp"
#include "IfConditionalExpressionRNode.hpp"
#include "IfElseConditionalExpressionRNode.hpp"
#include "IndexingExpressionRNode.hpp"
#include "InConditionRNode.hpp"
#include "ExpressionConditionRNode.hpp"
#include "IntegerLiteralExpressionRNode.hpp"
#include "KeywordRNode.hpp"
#include "LiteralExpressionRNode.hpp"
#include "LogicalLiteralExpressionRNode.hpp"
#include "LoopExpressionRNode.hpp"
#include "MissingExpressionRNode.hpp"
#include "OperatorRNode.hpp"
#include "RepeatLoopExpressionRNode.hpp"
#include "SymbolExpressionRNode.hpp"
#include "UnaryOperationExpressionRNode.hpp"
#include "WhileLoopExpressionRNode.hpp"
#include "RawStringLiteralExpressionRNode.hpp"
#include "SubsettingExpressionRNode.hpp"
#include "EndNode.hpp"
#include "BeginNode.hpp"
#include "RProgramNode.hpp"
#include "RFileNode.hpp"
#include "SymbolRNode.hpp"
#include "ParameterSequenceRNode.hpp"

template <typename T>
std::shared_ptr<T> wrap(void* ptr) {
    return std::shared_ptr<T>(static_cast<T*>(ptr));
}

#endif /* RASTR_AST_HPP */
