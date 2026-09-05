#pragma once
#include <string>

enum class TokenType { CHAR, UNION, STAR, PLUS, QUESTION, LPAREN, RPAREN, CONCAT, END };

struct Token { TokenType type; char value{}; int pos{}; };
std::string tokenTypeName(TokenType type);
