#pragma once
#include "token.h"
#include <string>
#include <vector>
#include <stdexcept>
struct LexerError: std::runtime_error { using std::runtime_error::runtime_error; };
class Lexer { std::string input; public: explicit Lexer(std::string s):input(std::move(s)){} std::vector<Token> tokenize() const; };
std::vector<Token> insertConcat(const std::vector<Token>& tokens);
