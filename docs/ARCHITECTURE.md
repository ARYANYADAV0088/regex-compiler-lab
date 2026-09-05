# Architecture

## Data flow
```text
Regex source
    ↓
Lexer
    ↓
Raw tokens
    ↓
Explicit CONCAT insertion
    ↓
Recursive-descent Parser
    ↓
AST
    ↓
Thompson Builder
    ↓
ε-NFA
    ↓
ε-closure + move
    ↓
DFA
    ↓
Partition Refinement
    ↓
Minimal DFA
    ↓
DFA Simulation
    ↓
Accept / Reject + state path
```

## Modules
- `lexer.*`: lexical classification and implicit concatenation.
- `parser.*`: grammar and precedence.
- `ast.*`: syntax-tree representation.
- `nfa.*`: Thompson construction.
- `dfa.*`: subset construction.
- `minimizer.*`: partition refinement.
- `matcher.*`: execution.
- `serializer.*`: JSON interface to the browser.
- `backend/app.py`: HTTP API.
- `frontend/*`: interactive presentation.
