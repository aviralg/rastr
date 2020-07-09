#include "Type.hpp"

namespace rastr {
namespace ast {

const std::string type_to_string(const Type type) {
    switch (type) {
    case Type::DoubleLiteralExpressionRNode:
        return "DoubleLiteralExpressionRNode";
    case Type::IntegerLiteralExpressionRNode:
        return "IntegerLiteralExpressionRNode";
    case Type::ComplexLiteralExpressionRNode:
        return "ComplexLiteralExpressionRNode";
    case Type::LogicalLiteralExpressionRNode:
        return "LogicalLiteralExpressionRNode";
    case Type::RawLiteralExpressionRNode:
        return "RawLiteralExpressionRNode";
    case Type::CharacterLiteralExpressionRNode:
        return "CharacterLiteralExpressionRNode";
    case Type::UndefinedNode:
        return "UndefinedNode";
    }
    return "UndefinedNode";
}

Type string_to_type(const std::string& type) {
    if (type == "DoubleLiteralExpressionRNode") {
        return Type::DoubleLiteralExpressionRNode;
    } else if (type == "IntegerLiteralExpressionRNode") {
        return Type::IntegerLiteralExpressionRNode;
    } else if (type == "ComplexLiteralExpressionRNode") {
        return Type::ComplexLiteralExpressionRNode;
    } else if (type == "LogicalLiteralExpressionRNode") {
        return Type::LogicalLiteralExpressionRNode;
    } else if (type == "RawLiteralExpressionRNode") {
        return Type::RawLiteralExpressionRNode;
    } else if (type == "CharacterLiteralExpressionRNode") {
        return Type::CharacterLiteralExpressionRNode;
    } else {
        return Type::UndefinedNode;
    }
}

} // namespace ast
} // namespace rastr
