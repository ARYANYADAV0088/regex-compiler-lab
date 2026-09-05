#pragma once
#include "nfa.h"
#include <map>
#include <set>
#include <vector>
struct DFATransition { int from,to; char symbol; };
struct DFA { int start=0, states=0; std::set<int> accept; std::vector<DFATransition> transitions; std::vector<std::set<int>> subsets; std::set<char> alphabet; };
class DFABuilder { public: DFA build(const NFA& nfa); };
