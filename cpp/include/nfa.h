#pragma once
#include "ast.h"
#include <set>
#include <vector>
struct NFATransition { int from,to; char symbol; };
struct NFA { int start=-1, accept=-1, states=0; std::vector<NFATransition> transitions; std::set<char> alphabet; };
class ThompsonBuilder { NFA nfa; int newState(); std::pair<int,int> buildNode(const std::shared_ptr<ASTNode>&); public: NFA build(const std::shared_ptr<ASTNode>& root); };
