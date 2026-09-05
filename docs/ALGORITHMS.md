# Algorithms

## Thompson construction
Each AST operator is converted into a fragment with one entry and one exit. Concatenation links fragments with ε, union introduces a new split and merge, star adds bypass and loop ε-transitions, plus adds a loop without the bypass, and optional adds a bypass.

## ε-closure
Starting from a set of NFA states, repeatedly follow ε-transitions until no new states can be reached.

## Subset construction
The ε-closure of the NFA start state becomes DFA state 0. For every DFA state and input symbol, move through matching NFA transitions, take ε-closure, and assign the resulting set a DFA state ID if it is new.

## Partition refinement
Start with accepting and non-accepting groups. For each state, build a signature containing the partition ID reached by each alphabet symbol. States with different signatures are split. Repeat until no group changes.
