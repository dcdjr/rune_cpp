# rune Grammar

## Current grammar

```text
statement       -> let_statement
let_statement   -> "let" IDENTIFIER "=" expression ";"

expression      -> term (("+" | "-") term)*
term            -> factor (("*" | "/") factor)*
factor          -> INT | IDENTIFIER | "(" expression ")"
```
