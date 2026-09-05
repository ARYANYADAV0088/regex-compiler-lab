#include "lexer.h"
#include "parser.h"
#include "nfa.h"
#include "dfa.h"
#include "minimizer.h"
#include "matcher.h"
#include "serializer.h"
#include <chrono>
#include <iostream>
#include <string>

static void baseJson(const std::string& regex,
                     const std::vector<Token>& tokens,
                     const std::shared_ptr<ASTNode>& ast,
                     const NFA& nfa,
                     const DFA& dfa,
                     const DFA& mini,
                     const DFAMinimizer& mm,
                     long long ms) {
    std::cout << "{\"ok\":true"
              << ",\"regex\":\"" << jsonEscape(regex) << "\""
              << ",\"tokens\":" << tokensToJson(tokens)
              << ",\"ast\":" << astToJson(ast)
              << ",\"nfa\":" << nfaToJson(nfa)
              << ",\"dfa\":" << dfaToJson(dfa)
              << ",\"minimized\":" << dfaToJson(mini)
              << ",\"minimizationTrace\":" << minimizationTraceToJson(mm.getTrace())
              << ",\"stats\":{"
              << "\"tokens\":" << tokens.size()-1
              << ",\"alphabet\":" << nfa.alphabet.size()
              << ",\"nfaStates\":" << nfa.states
              << ",\"nfaTransitions\":" << nfa.transitions.size()
              << ",\"dfaStates\":" << dfa.states
              << ",\"dfaTransitions\":" << dfa.transitions.size()
              << ",\"minimizedStates\":" << mini.states
              << ",\"minimizedTransitions\":" << mini.transitions.size()
              << ",\"compileTimeMs\":" << ms
              << "}}";
}

int main(int argc, char** argv) {
    try {
        if (argc < 2) {
            std::cerr << "Usage: regex_engine <regex> [--match string]\n";
            return 2;
        }

        std::string regex = argv[1];
        auto startTime = std::chrono::steady_clock::now();

        Lexer lex(regex);
        auto raw = lex.tokenize();
        auto toks = insertConcat(raw);
        Parser p(toks);
        auto ast = p.parse();
        ThompsonBuilder tb;
        auto nfa = tb.build(ast);
        DFABuilder db;
        auto dfa = db.build(nfa);
        DFAMinimizer mm;
        auto mini = mm.minimize(dfa);

        if (argc >= 4 && std::string(argv[2]) == "--match") {
            auto r = match(mini, argv[3]);
            std::cout << "{\"ok\":true,\"accepted\":"
                      << (r.accepted ? "true" : "false")
                      << ",\"path\":[";
            for (size_t i = 0; i < r.path.size(); ++i) {
                if (i) std::cout << ",";
                std::cout << r.path[i];
            }
            std::cout << "],\"steps\":[";
            for (size_t i = 0; i < r.steps.size(); ++i) {
                if (i) std::cout << ",";
                const auto& st = r.steps[i];
                std::cout << "{\"symbol\":\"" << jsonEscape(std::string(1, st.symbol))
                          << "\",\"from\":" << st.from
                          << ",\"to\":" << st.to
                          << ",\"transitionFound\":" << (st.transitionFound ? "true" : "false") << "}";
            }
            std::cout << "]";
            if (!r.error.empty())
                std::cout << ",\"message\":\"" << jsonEscape(r.error) << "\"";
            std::cout << "}";
            return 0;
        }

        auto endTime = std::chrono::steady_clock::now();
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        baseJson(regex, toks, ast, nfa, dfa, mini, mm, ms);
    }
    catch (const std::exception& e) {
        std::cout << "{\"ok\":false,\"error\":\"" << jsonEscape(e.what()) << "\"}";
        return 1;
    }
}
