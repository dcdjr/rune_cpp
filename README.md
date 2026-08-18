# rune

![CI](https://github.com/dcdjr/rune_cpp/actions/workflows/ci.yml/badge.svg)

`rune` is a prototype programming language implementation in C++20.

This project is meant to teach me how programming languages work internally while strengthening my C++ and systems programming fundamentals. It is intended to be a long-term learning project that I can continue expanding as I learn more about language implementation.

## Current status

`rune` currently has a working lexer, recursive-descent parser, AST, and tree-walk interpreter.

Programs can contain variable declarations, arithmetic expressions, and print statements. Source files are lexed into tokens, parsed into an AST, and then executed by the interpreter.

The lexer currently supports:

- Identifiers
- Integer literals
- `let` and `print` keywords
- Arithmetic operators
- The assignment operator
- Parentheses
- Semicolons
- Single-line comments
- Line and column tracking
- Error tokens for unsupported characters

The parser currently supports:

- Integer and variable expressions
- Arithmetic expressions
- Operator precedence and left associativity
- Parenthesized expressions
- let declarations
- print statements
- Multi-statement program parsing

The interpreter currently supports:

- Integer expression evaluation
- Arithmetic with +, -, *, and /
- Variable definitions and lookup
- let statement execution
- print statement execution
- Runtime errors for undefined variables and division by zero

The lexer, parser, and interpreter are covered by automated tests. Builds use AddressSanitizer and UndefinedBehaviorSanitizer during development, and the test suite runs automatically through GitHub Actions.

## Example

Example `rune` program:

```rune
let number1 = (5 + 3) * 2;
let number2 = 80 / 20;

let product = number1 * number2;

print product;
```

Running:

```sh
./build/runei examples/example1.rn
```

produces:

```text
64
```

The program moves through the following pipeline:

```text
source code
    ↓
lexer
    ↓
tokens
    ↓
parser
    ↓
abstract syntax tree
    ↓
interpreter
    ↓
program output
```

## Grammar

The current grammar is documented in `GRAMMAR.md`.

```text
program         -> statement* EOF

statement       -> let_statement | print_statement
let_statement   -> "let" IDENTIFIER "=" expression ";"
print_statement -> "print" expression ";"

expression      -> term (("+" | "-") term)*
term            -> factor (("*" | "/") factor)*
factor          -> INT | IDENTIFIER | "(" expression ")"
```

## Requirements

- A C++20-compatible compiler
- GNU Make

The project currently uses `g++`.

## Build & run

Compile the `runei` executable:

```sh
make
```

This creates:

```text
build/runei
```

Pass a `rune` source file to the executable:

```sh
./build/runei path/to/program.rn
```

## Testing

Build and run the test suite:

```sh
make test
```

Individual test suites can also be run with:

```sh
make lexer_tests
make parser_tests
make interpreter_tests
```

## Cleaning

Remove generated executables:

```sh
make clean
```

## Project structure

```text
include/rune/      Public headers  
src/               Implementation  
examples/          Examples rune programs
tests/             Automated tests  
Makefile           Build and test configuration  
GRAMMAR.md         Current rune grammar
```

## Roadmap

- [x] Expression AST
- [x] Recursive-descent expression parser
- [x] Statement AST
- [x] Variable declaration parsing
- [x] Print statement parsing
- [x] Whole-program parsing
- [x] Tree-walk interpreter
- [x] Runtime variable environment
- [ ] Variable reassignment
- [ ] Comparison and boolean operators
- [ ] Control flow
- [ ] Functions
- [ ] Improved error reporting
