# Regex Compiler Lab

**Compiler Design Laboratory Project | Individual Project**

A complete educational regular-expression compiler and automata workbench implemented with a C++17 compiler core, Flask API, and interactive HTML/CSS/JavaScript frontend.


## 🚀 Live Demo

**[Open Regex Compiler Lab](https://regex-compiler-lab.onrender.com)**

## Full pipeline
```text
Regex
  ↓
Lexer
  ↓
Explicit Concatenation
  ↓
Recursive-Descent Parser
  ↓
AST
  ↓
Thompson ε-NFA
  ↓
ε-Closure + Subset Construction
  ↓
DFA
  ↓
Partition-Refinement Minimization
  ↓
Minimized DFA
  ↓
String Execution + Traversal
```

## Features
- Custom lexer and parser
- Operator precedence and implicit concatenation
- Escape sequences for literal metacharacters
- AST visualization
- Thompson ε-NFA generation
- NFA transition table
- ε-closure based DFA subset construction
- DFA state/subset table
- DFA minimization with refinement trace
- Before/after optimization statistics
- Minimized DFA visualization
- String matcher with state path and per-character execution trace
- Lexical and syntax error reporting
- Compilation statistics and timing
- Browser-based interactive UI
- Automated regression tests

## Supported syntax
| Syntax | Meaning |
|---|---|
| `a` | literal character |
| `a\|b` | escaped `|` literal when escaped; unescaped `|` means union |
| `a|b` | union |
| `ab` | implicit concatenation |
| `a*` | zero or more |
| `a+` | one or more |
| `a?` | optional |
| `(ab)` | grouping |
| `\*` | literal `*` |

Whitespace is intentionally rejected to keep the grammar unambiguous.

## Windows setup
Requirements:
- Python 3
- MinGW-w64/MSYS2 with `g++` in PATH

From PowerShell:
```powershell
.\run_windows.bat
```
Then open:
```text
http://127.0.0.1:5000
```

## Manual build
```powershell
g++ -std=c++17 -O2 -Icpp\include cpp\src\*.cpp -o cpp\regex_engine.exe
python -m pip install -r requirements.txt
python backend\app.py
```

## Tests
After building:
```powershell
python tests\test_engine.py
```

## Documentation
- `docs/PROJECT_REPORT.md` — report-ready chapters
- `docs/ARCHITECTURE.md` — architecture and data flow
- `docs/ALGORITHMS.md` — algorithm explanations
- `docs/TEST_PLAN.md` — test matrix
- `docs/PHASE_MAPPING.md` — mapping to the laboratory manual

## Important academic note
The automata algorithms are implemented in the C++ core. The frontend visualizes the actual JSON output from that implementation rather than hardcoding example diagrams.

## Interactive Toolbox

The frontend includes an experimental toolbox built on the real compiler output:
- Static regex complexity analysis
- Minimized-DFA language equivalence checking with counterexamples
- Short-string language explorer using batch matching
- C++ matcher code generation from the minimized DFA
- Local compilation benchmark with min/average/max timings
- SVG export of the visible automaton
- Presentation mode, history, command palette, and animated execution replay
