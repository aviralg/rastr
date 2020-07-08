#include "Type.hpp"

namespace rastr {
namespace ast {

const std::string type_to_string(const Type type) {
    switch (type) {
    case Type::DoubleLiteralRNode:
        return "DoubleLiteralRNode";
    case Type::IntegerLiteralRNode:
        return "IntegerLiteralRNode";
    case Type::ComplexLiteralRNode:
        return "ComplexLiteralRNode";
    case Type::LogicalLiteralRNode:
        return "LogicalLiteralRNode";
    case Type::RawLiteralRNode:
        return "RawLiteralRNode";
    case Type::CharacterLiteralRNode:
        return "CharacterLiteralRNode";
    case Type::UndefinedNode:
        return "UndefinedNode";
    }
    return "UndefinedNode";
}

Type string_to_type(const std::string& type) {
    if (type == "DoubleLiteralRNode") {
        return Type::DoubleLiteralRNode;
    } else if (type == "IntegerLiteralRNode") {
        return Type::IntegerLiteralRNode;
    } else if (type == "ComplexLiteralRNode") {
        return Type::ComplexLiteralRNode;
    } else if (type == "LogicalLiteralRNode") {
        return Type::LogicalLiteralRNode;
    } else if (type == "RawLiteralRNode") {
        return Type::RawLiteralRNode;
    } else if (type == "CharacterLiteralRNode") {
        return Type::CharacterLiteralRNode;
    } else {
        return Type::UndefinedNode;
    }
}

} // namespace ast
} // namespace rastr
