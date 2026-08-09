# rune

![CI](https://github.com/dcdjr/rune_cpp/actions/workflows/ci.yml/badge.svg)

`rune` is a prototype programming language implementation in C++20.

This project is meant to teach me how compilers work internally and how programming languages
are implemented, while strengthening my C++ and systems programming fundamentals. This is intended to be a
long term project.

## Current status

`rune` is early in development. It currently has a working lexer that converts source code into a sequence of tokens.

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
tests/             Automated tests  
Makefile           Build and test configuration  
```

## Roadmap

- [x] Lexer
- [x] Lexer tests
- [x] Source position tracking
- [x] Continuous integration
- [ ] Expression AST
- [ ] Recursive-descent parser
- [ ] Variable declarations
- [ ] Tree-walk interpreter
- [ ] Functions and control flow
