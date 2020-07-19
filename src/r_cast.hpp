#ifndef RASTR_R_CAST_HPP
#define RASTR_R_CAST_HPP

#include <memory>
#include "ExpressionRNode.hpp"
#include "CharacterLiteralExpressionRNode.hpp"
#include "ComplexLiteralExpressionRNode.hpp"
#include "DoubleLiteralExpressionRNode.hpp"
#include "FunctionCallExpressionRNode.hpp"
#include "FunctionDefinitionExpressionRNode.hpp"
#include "IfConditionalExpressionRNode.hpp"
#include "IfElseConditionalExpressionRNode.hpp"
#include "IntegerLiteralExpressionRNode.hpp"
#include "LogicalLiteralExpressionRNode.hpp"
#include "RawLiteralExpressionRNode.hpp"
#include "RepeatLoopExpressionRNode.hpp"
#include "SymbolExpressionRNode.hpp"
#include "Type.hpp"
#include "InRNode.hpp"
#include "WhileLoopExpressionRNode.hpp"
#include "ForLoopExpressionRNode.hpp"
#include "BinaryExpressionRNode.hpp"

template <typename T>
void destroy_sexp(SEXP r_node) {
    delete static_cast<std::shared_ptr<T>*>(R_ExternalPtrAddr(r_node));
    R_SetExternalPtrAddr(r_node, NULL);
}

template <typename T>
std::shared_ptr<T> from_sexp(SEXP r_node) {
    void* node = R_ExternalPtrAddr(r_node);
    if (node == NULL) {
        Rf_error("from_sexp: object is null");
    } else {
        return *static_cast<std::shared_ptr<T>*>(node);
    }
}

template <typename T>
SEXP to_sexp(std::shared_ptr<T> node) {
    SEXP r_node = PROTECT(R_MakeExternalPtr(
        new std::shared_ptr<T>(node), R_NilValue, R_NilValue));

    R_RegisterCFinalizerEx(r_node, destroy_sexp<T>, TRUE);

    setAttrib(r_node, R_ClassSymbol, T::get_class());

    UNPROTECT(1);

    return r_node;
}

template <>
inline SEXP to_sexp<rastr::ast::ExpressionRNode>(
    std::shared_ptr<rastr::ast::ExpressionRNode> node) {
    using rastr::ast::BinaryExpressionRNode;
    using rastr::ast::BinaryExpressionRNodeSPtr;
    using rastr::ast::CharacterLiteralExpressionRNode;
    using rastr::ast::CharacterLiteralExpressionRNodeSPtr;
    using rastr::ast::ComplexLiteralExpressionRNode;
    using rastr::ast::ComplexLiteralExpressionRNodeSPtr;
    using rastr::ast::DoubleLiteralExpressionRNode;
    using rastr::ast::DoubleLiteralExpressionRNodeSPtr;
    using rastr::ast::ForLoopExpressionRNode;
    using rastr::ast::ForLoopExpressionRNodeSPtr;
    using rastr::ast::FunctionCallExpressionRNode;
    using rastr::ast::FunctionCallExpressionRNodeSPtr;
    using rastr::ast::FunctionDefinitionExpressionRNode;
    using rastr::ast::FunctionDefinitionExpressionRNodeSPtr;
    using rastr::ast::IfConditionalExpressionRNode;
    using rastr::ast::IfConditionalExpressionRNodeSPtr;
    using rastr::ast::IfElseConditionalExpressionRNode;
    using rastr::ast::IfElseConditionalExpressionRNodeSPtr;
    using rastr::ast::IntegerLiteralExpressionRNode;
    using rastr::ast::IntegerLiteralExpressionRNodeSPtr;
    using rastr::ast::LogicalLiteralExpressionRNode;
    using rastr::ast::LogicalLiteralExpressionRNodeSPtr;
    using rastr::ast::RawLiteralExpressionRNode;
    using rastr::ast::RawLiteralExpressionRNodeSPtr;
    using rastr::ast::RepeatLoopExpressionRNode;
    using rastr::ast::RepeatLoopExpressionRNodeSPtr;
    using rastr::ast::SymbolExpressionRNode;
    using rastr::ast::SymbolExpressionRNodeSPtr;
    using rastr::ast::Type;
    using rastr::ast::WhileLoopExpressionRNode;
    using rastr::ast::WhileLoopExpressionRNodeSPtr;

    Type type = node->get_type();

    if (type == Type::DoubleLiteralExpressionRNode) {
        DoubleLiteralExpressionRNodeSPtr downcasted_node =
            std::static_pointer_cast<DoubleLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::IntegerLiteralExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<IntegerLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::ComplexLiteralExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<ComplexLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::LogicalLiteralExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<LogicalLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::RawLiteralExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<RawLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::CharacterLiteralExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<CharacterLiteralExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::SymbolExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<SymbolExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::ForLoopExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<ForLoopExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::WhileLoopExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<WhileLoopExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::RepeatLoopExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<RepeatLoopExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::FunctionDefinitionExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<FunctionDefinitionExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::FunctionCallExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<FunctionCallExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::IfConditionalExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<IfConditionalExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::IfElseConditionalExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<IfElseConditionalExpressionRNode>(node);
        return to_sexp(downcasted_node);
    } else if (type == Type::BinaryExpressionRNode) {
        auto downcasted_node =
            std::static_pointer_cast<BinaryExpressionRNode>(node);
        return to_sexp(downcasted_node);
    }

    std::string type_str(type_to_string(type));
    Rf_error("to_sexp::'%s' object not handled", type_str.c_str());
    return R_NilValue;
}

template <>
inline SEXP
to_sexp<rastr::ast::RNode>(std::shared_ptr<rastr::ast::RNode> node) {
    using rastr::ast::ExpressionRNode;
    using rastr::ast::ExpressionRNodeSPtr;
    using rastr::ast::InRNode;
    using rastr::ast::InRNodeSPtr;
    using rastr::ast::Type;

    Type type = node->get_type();

    if (type == Type::InRNode) {
        InRNodeSPtr downcasted_node = std::static_pointer_cast<InRNode>(node);
        return to_sexp(downcasted_node);
    } else if (node->is_expression_node()) {
        ExpressionRNodeSPtr downcasted_node =
            std::dynamic_pointer_cast<ExpressionRNode>(node);
        return to_sexp<ExpressionRNode>(downcasted_node);
    }

    std::string type_str(type_to_string(type));
    Rf_error("to_sexp::'%s' object not handled", type_str.c_str());
    return R_NilValue;
}


#endif /* RASTR_R_CAST_HPP */
