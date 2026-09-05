# Regex Compiler Lab

## Chapter 1: Introduction
This project implements an educational regular-expression compiler pipeline. A regular expression is transformed through lexical analysis, parsing, abstract syntax tree construction, Thompson ε-NFA construction, subset-construction DFA generation, DFA minimization, and execution by string matching.

## Chapter 2: Problem Statement
Typical regex matchers hide the internal compilation process. The project provides a transparent implementation that exposes the intermediate representations and algorithms used to transform a regular expression into an executable finite automaton.

## Chapter 3: Objectives
- Implement a custom regex lexer and parser.
- Construct and visualize an AST.
- Convert the AST to an ε-NFA using Thompson's construction.
- Convert the NFA to a DFA using ε-closure and subset construction.
- Minimize the DFA using partition refinement.
- Execute strings against the minimized DFA and show the traversal path.
- Detect malformed regular expressions with useful errors.
- Provide an interactive browser-based demonstration.

## Chapter 4: Background Study
The implementation uses regular languages, regular expressions, finite automata, recursive-descent parsing, Thompson construction, ε-closure, subset construction, and DFA minimization by partition refinement.

## Chapter 5: System Design
```text
Browser UI
   |
   | JSON/HTTP
   v
Flask API
   |
   | subprocess
   v
C++17 Compiler Engine
   |
   +-- Lexer
   +-- Parser / AST
   +-- Thompson NFA
   +-- Subset DFA
   +-- DFA Minimizer
   +-- Matcher
```

## Chapter 6: Methodology
1. Tokenize the source regular expression.
2. Insert explicit concatenation tokens where concatenation is implicit.
3. Parse according to operator precedence.
4. Construct the AST.
5. Build an ε-NFA fragment for each AST node.
6. Compute ε-closures and construct DFA states as sets of NFA states.
7. Partition DFA states into equivalent classes and refine the partitions until stable.
8. Simulate the minimized DFA on the supplied test string.

## Chapter 7: Compiler Design Concepts Used
### Lexical Analysis
The lexer recognizes literals, union, repetition operators, parentheses, and escape sequences.

### Syntax Analysis
A recursive-descent parser implements the precedence hierarchy:
```text
Expression -> Union
Union      -> Concat ('|' Concat)*
Concat     -> Repeat Repeat*
Repeat     -> Atom ('*' | '+' | '?')?
Atom       -> CHAR | '(' Expression ')'
```

### AST
AST nodes represent SYMBOL, UNION, CONCAT, STAR, PLUS and OPTIONAL.

### Intermediate Representations
The ε-NFA and DFA act as explicit intermediate representations between source syntax and execution.

### Optimization
DFA minimization uses partition refinement and reports each refinement round.

### Execution
The matcher follows DFA transitions for each input character and reports the complete state path.

### Error Handling
Lexical and parser errors include the relevant position whenever possible.

## Chapter 8: Implementation
The compiler core is implemented in C++17. Flask provides a small HTTP bridge. The frontend uses HTML, CSS and JavaScript and generates SVG visualizations from actual compiler data returned as JSON.

## Chapter 9: Testing and Results
The test suite covers literal matching, union, concatenation, repetition, optional expressions, grouped expressions, complex expressions, empty-string matching where the regex permits it, and malformed expressions. The application also supports interactive testing from the browser.

## Chapter 10: Conclusion
The project demonstrates a complete regular-expression language-processing pipeline and exposes its internal representations instead of treating matching as a black box.

## Chapter 11: Future Enhancements
- Character classes such as `[a-z]`.
- Wildcard `.` support.
- Unicode-aware symbols.
- Interactive graph editing.
- Export of automata as SVG/PNG.
- More formal parser diagnostics and recovery.
- Additional minimization algorithms for comparison.

## References
- Aho, Lam, Sethi, Ullman, *Compilers: Principles, Techniques, and Tools*.
- Hopcroft, Motwani, Ullman, *Introduction to Automata Theory, Languages, and Computation*.
- Official C++17 and Python/Flask documentation.
