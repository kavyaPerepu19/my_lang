# Custom Compiler Project

## Overview

A sophisticated compiler front-end implemented in modern C++, demonstrating advanced language processing and code generation techniques. The project translates a custom programming language into LLVM Intermediate Representation (IR), showcasing compiler design principles and low-level code generation.

## Project Architecture

### Key Components

1. **Lexical Analyzer**
   - Implements robust tokenization of source code
   - Handles numeric literals, identifiers, and language keywords
   - Provides flexible token recognition

2. **Parser**
   - Utilizes recursive descent parsing strategy
   - Implements operator precedence handling
   - Constructs Abstract Syntax Tree (AST) for semantic analysis

3. **Abstract Syntax Tree (AST)**
   - Designed using the Visitor design pattern
   - Supports multiple language constructs
   - Enables flexible syntax tree manipulation

4. **Code Generator**
   - Transforms AST to LLVM Intermediate Representation
   - Generates efficient intermediate code
   - Supports floating-point arithmetic operations

## Technical Specifications

- **Language**: C++17
- **Backend**: LLVM
- **Parsing Technique**: Recursive Descent
- **Design Pattern**: Visitor Pattern

## Supported Features

- Floating-point arithmetic expressions
- Function definitions
- Basic return statements
- Operator precedence parsing

## Example Language Syntax

```cpp
func calculate(x, y) {
    return x + y * 2.5;
}
```

## Prerequisites

- Modern C++ Compiler (C++17 or later)
- LLVM Development Libraries
- CMake

## Build Instructions

```bash
# Clone the repository
git clone https://github.com/yourusername/custom-compiler.git

# Build the project
mkdir build && cd build
cmake ..
make
```

## Project Structure

```
.
├── src/
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── ast.cpp
│   ├── codegen.cpp
│   └── main.cpp
├── include/
│   ├── lexer.hpp
│   ├── parser.hpp
│   ├── ast.hpp
│   └── codegen.hpp
└── CMakeLists.txt
```

## Technical Challenges Addressed

- Implementing a robust lexical analyzer
- Designing an extensible Abstract Syntax Tree
- Generating valid LLVM Intermediate Representation
- Handling operator precedence in parsing
- Managing memory efficiently with modern C++ features

## Future Enhancements

- Expand language feature set
- Implement additional data type support
- Enhance error handling mechanisms


## Contact

Kavya Perepu - perepukavyasri@gmail.com
