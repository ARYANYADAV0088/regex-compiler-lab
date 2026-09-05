#pragma once
#include "dfa.h"
#include <set>
#include <vector>

class DFAMinimizer {
    std::vector<std::vector<std::set<int>>> trace;
public:
    DFA minimize(const DFA& dfa);
    const std::vector<std::vector<std::set<int>>>& getTrace() const { return trace; }
};
