#include "minimizer.h"
#include <map>
#include <vector>

static int trans(const DFA& d, int s, char a) {
    for (const auto& t : d.transitions)
        if (t.from == s && t.symbol == a) return t.to;
    return -1;
}

DFA DFAMinimizer::minimize(const DFA& d) {
    trace.clear();
    if (d.states <= 1) {
        trace.push_back({std::set<int>{0}});
        return d;
    }

    std::set<int> non;
    for (int i = 0; i < d.states; ++i)
        if (!d.accept.count(i)) non.insert(i);

    std::vector<std::set<int>> p;
    if (!d.accept.empty()) p.push_back(d.accept);
    if (!non.empty()) p.push_back(non);
    trace.push_back(p);

    bool changed = true;
    while (changed) {
        changed = false;
        std::map<int, int> cls;
        for (int i = 0; i < (int)p.size(); ++i)
            for (int s : p[i]) cls[s] = i;

        std::vector<std::set<int>> np;
        for (const auto& g : p) {
            std::map<std::vector<int>, std::set<int>> buckets;
            for (int s : g) {
                std::vector<int> sig;
                for (char a : d.alphabet) {
                    int t = trans(d, s, a);
                    sig.push_back(t < 0 ? -1 : cls[t]);
                }
                buckets[sig].insert(s);
            }
            for (auto& kv : buckets) np.push_back(kv.second);
            if (buckets.size() > 1) changed = true;
        }
        p = np;
        trace.push_back(p);
    }

    DFA r;
    r.states = (int)p.size();
    r.alphabet = d.alphabet;
    std::vector<int> cls(d.states);
    for (int i = 0; i < (int)p.size(); ++i)
        for (int s : p[i]) cls[s] = i;

    for (const auto& group : p) r.subsets.push_back(group);
    for (int i = 0; i < (int)p.size(); ++i)
        for (int s : p[i])
            if (d.accept.count(s)) r.accept.insert(i);

    r.start = cls[d.start];
    for (int i = 0; i < (int)p.size(); ++i) {
        int representative = *p[i].begin();
        for (char a : d.alphabet) {
            int t = trans(d, representative, a);
            if (t < 0) continue;
            int j = cls[t];
            bool exists = false;
            for (const auto& e : r.transitions)
                if (e.from == i && e.to == j && e.symbol == a) exists = true;
            if (!exists) r.transitions.push_back({i, j, a});
        }
    }
    return r;
}
