#pragma once
#include "ast.h"
#include "token.h"
#include <vector>
#include <stdexcept>
struct ParserError: std::runtime_error { using std::runtime_error::runtime_error; };
class Parser { const std::vector<Token>& tokens; size_t pos=0; public: explicit Parser(const std::vector<Token>& t):tokens(t){} std::shared_ptr<ASTNode> parse(); private: std::shared_ptr<ASTNode> parseUnion(); std::shared_ptr<ASTNode> parseConcat(); std::shared_ptr<ASTNode> parseRepeat(); std::shared_ptr<ASTNode> parseAtom(); bool at(TokenType t) const; const Token& current() const; };
