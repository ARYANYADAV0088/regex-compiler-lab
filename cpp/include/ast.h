#pragma once
#include <memory>
#include <string>

enum class ASTType { SYMBOL, CONCAT, UNION, STAR, PLUS, OPTIONAL };
struct ASTNode { ASTType type; char value{}; std::shared_ptr<ASTNode> left, right; explicit ASTNode(ASTType t, char v=0):type(t),value(v){} };
std::string astTypeName(ASTType type);
