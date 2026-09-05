#pragma once
#include "dfa.h"
#include <string>
#include <vector>
struct MatchStep { char symbol{}; int from=-1; int to=-1; bool transitionFound=false; };
struct MatchResult { bool accepted=false; std::vector<int> path; std::vector<MatchStep> steps; std::string error; };
MatchResult match(const DFA& dfa,const std::string& input);
