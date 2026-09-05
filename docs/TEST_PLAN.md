# Test Plan

| Category | Example | Expected |
|---|---|---|
| Literal | `a` / `a` | Accept |
| Literal | `a` / `b` | Reject |
| Concatenation | `abc` / `abc` | Accept |
| Star | `a*b` / `aaab` | Accept |
| Star | `a*b` / `aaa` | Reject |
| Union | `a|b` / `b` | Accept |
| Optional | `a?` / empty | Accept |
| Group | `(ab|ba)*` / `abba` | Accept |
| Complex | `(a|b)*abb` / `aabb` | Accept |
| Complex | `(a|b)*abb` / `abab` | Reject |
| Error | `(` | Error |
| Error | `a|` | Error |
| Error | `*` | Error |
| Error | `a**` | Error |
| Error | `|a` | Error |
| Error | `a(` | Error |
