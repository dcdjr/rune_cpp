# rune Grammar

## Current grammar

```text
program             -> statement* EOF

statement           -> let_statement | print_statement | reassign_statement
let_statement       -> "let" IDENTIFIER "=" expression ";"
print_statement     -> "print" expression ";"
reassign_statement  -> IDENTIFIER "=" expression ";"

expression          -> term (("+" | "-") term)*
term                -> factor (("*" | "/") factor)*
factor              -> INT | IDENTIFIER | "(" expression ")"
```
