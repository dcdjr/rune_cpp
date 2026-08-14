# rune

![CI](https://github.com/dcdjr/rune_cpp/actions/workflows/ci.yml/badge.svg)

`rune` is a prototype programming language implementation in C++20.

This project is meant to teach me how compilers work internally and how programming languages
are implemented, while strengthening my C++ and systems programming fundamentals. This is intended to be a
long term project.

## Current status

`rune` currently has a working lexer and recursive-descent parser capable
of parsing complete programs containing variable declarations and print
statements.

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

The lexer is covered by automated tests and is compiled with AddressSanitizer and UndefinedBehaviorSanitizer enabled.

## Example

Input source code:

```rune
let age = 19;
print age;
```

Token output:

```text
TOK_LET "let" at 1:1
TOK_IDENTIFIER "age" at 1:5
TOK_EQUAL "=" at 1:9
TOK_INT "19" at 1:11
TOK_SEMICOLON ";" at 1:13
TOK_PRINT "print" at 2:1
TOK_IDENTIFIER "age" at 2:7
TOK_SEMICOLON ";" at 2:10
TOK_EOF
```

## Requirements

- A C++20-compatible compiler
- GNU Make

The project currently uses `g++`.

## Build & run

Compile the `rune` executable:

```sh
make
```

This creates:

```text
runec
```

Pass a `rune` source file to the executable:

```sh
./runec path/to/program.rn
```

## Testing

Build and run the test suite:

```sh
make test
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
GRAMMAR.md         Contains rune's chosen grammar
```

## Roadmap

- [x] Expression AST
- [x] Recursive-descent expression parser
- [x] Statement AST
- [x] Variable declaration parsing
- [x] Print statement parsing
- [x] Whole-program parsing
- [ ] Tree-walk interpreter
- [ ] Runtime variable environment
- [ ] Functions and control flow
