# rune Grammar

## Current grammar

```text
statement       -> let_statement | print_statement
let_statement   -> "let" IDENTIFIER "=" expression ";"
print_statement -> "print" expression ";"

expression      -> term (("+" | "-") term)*
term            -> factor (("*" | "/") factor)*
factor          -> INT | IDENTIFIER | "(" expression ")"
```
