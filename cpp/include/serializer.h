#pragma once
#include "ast.h"
#include "dfa.h"
#include "nfa.h"
#include "token.h"
#include "minimizer.h"
#include <string>
std::string jsonEscape(const std::string& s);
std::string tokenTypeName(TokenType type);
std::string astToJson(const std::shared_ptr<ASTNode>& root);
std::string tokensToJson(const std::vector<Token>& tokens);
std::string nfaToJson(const NFA& nfa);
std::string dfaToJson(const DFA& dfa);

std::string minimizationTraceToJson(const std::vector<std::vector<std::set<int>>>& trace);
