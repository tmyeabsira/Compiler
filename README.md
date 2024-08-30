# Compiler Project

## Overview

This project contains various components and stages of a compiler implementation. Each stage represents a different part of the compilation process, ranging from lexical analysis to parsing and optimization. The project is organized into directories, each representing a specific phase of the compiler.

## Directory Structure

The project is divided into the following main directories:

- **one/**: Contains files related to the initial phase of lexical analysis.
- **two/**: Contains files for both lexical analysis and parsing, including the generation of a parser from a grammar.
- **three/**: Contains a parser implementation in Python.
- **four/**: Contains the optimizer for the compiler.
- **five/**: Contains an advanced parser with additional functionalities, including a symbol table.

### Detailed File Description

### one/

- **lexer**: Executable for the lexical analysis phase.
- **lex.yy.c**: C source code generated by the lexical analyzer (Flex).
- **scanner.l**: Flex file containing rules for tokenizing input text.

### two/

- **lexer.l**: Flex file for lexical analysis.
- **arithmetic.y**: Yacc file defining the grammar for arithmetic expressions.
- **arithmetic.h**: Header file generated by Yacc.
- **arithmetic.tab.c**: C source code generated by Yacc for the parser.
- **arithmetic.tab.h**: Header file containing token definitions.
- **lex.yy.c**: C source code generated by the lexical analyzer.
- **parser.py**: Python script for parsing (specifics are based on implementation).

### three/

- **parser.py**: Python script for parsing (specifics are based on implementation).

### four/

- **optimizer**: Executable for the optimization phase.
- **optimizer.c**: C source code for the optimizer.
- **test.txt**: Test input file to verify the optimizer's functionality.

### five/

- **myparser**: Executable for the advanced parser.
- **lexer.l**: Flex file for lexical analysis.
- **parser.y**: Yacc file defining the grammar.
- **parser.tab.c**: C source code generated by Yacc for the parser.
- **parser.tab.h**: Header file containing token definitions.
- **lex.yy.c**: C source code generated by the lexical analyzer.
- **symbol_table.c**: C source code for managing the symbol table.
- **symbol_table.h**: Header file for the symbol table.
- **test.txt**: Test input file to verify the parser and symbol table functionality.

## Getting Started

### Prerequisites

To build and run the components in this project, you will need:

- **Flex**: A tool for generating scanners (lexical analyzers).
- **Bison**: A parser generator (a replacement for Yacc).
- **GCC**: GNU Compiler Collection for compiling C code.
- **Python**

### Building the Project

1. **Lexical Analysis (one/)**
    - Navigate to the `one/` directory.
    - Run `flex scanner.l` to generate the `lex.yy.c` file.
    - Compile the generated file using GCC: `gcc lex.yy.c -o lexer`.
2. **Parsing and Lexical Analysis (two/)**
    - Navigate to the `two/` directory.
    - Run `bison -d arithmetic.y` to generate the `arithmetic.tab.c` and `arithmetic.tab.h` files.
    - Run `flex lexer.l` to generate the `lex.yy.c` file.
    - Compile the generated files: `gcc lex.yy.c arithmetic.tab.c -o parser`.
    
    **OR**
    
    - Navigate to the `two/` directory.
    - Run `python3 parser.py`
3. **Syntax error (three/)**
    - Navigate to the `three/` directory.
    - Run `python3 parser.py`
4. **Optimization (four/)**
    - Navigate to the `four/` directory.
    - Compile the optimizer: `gcc optimizer.c -o optimizer`.
5. **Symbol Table (five/)**
    - Navigate to the `five/` directory.
    - Run `bison -d parser.y` to generate the parser files.
    - Run `flex lexer.l` to generate the lexical analyzer file.
    - Compile the files along with the symbol table: `gcc lex.yy.c parser.tab.c symbol_table.c -o myparser`.

### Running the Project

- Each executable can be run from its respective directory. For example:
    - To run the lexer in `one/`, use `./lexer`.
    - To run the parser in `two/`, use `./parser`.
    - To run the optimizer in `four/`, use `./optimizer`.
    - To run the advanced parser in `five/`, use `./myparser`.

### Testing

- Test files (`test.txt`) are provided in relevant directories. You can redirect input from these files to test the executables, e.g., `./myparser < test.txt`.

## Contributors

1. Abdulhamid Umer, IE5933
2. Armatem Samuel, KI7158
3. Blen Yonas, FW0277
4. Mikias Gebreselassie, UF4336
5. Naol Girma, TL7247
6. Yeabsira Tesfaye, AN6576
