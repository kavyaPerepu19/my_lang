# Simple Functional Language Compiler

## Project Overview
This is a complete compiler implementation that translates a simple functional programming language into LLVM Intermediate Representation (IR). The compiler follows traditional compiler design principles with distinct phases: lexical analysis, parsing, and code generation.

## Architecture Overview

### 1. **Lexical Analysis (Lexer)**
**Files:** `lexer.hpp`, `lexer.cpp`

The lexer is responsible for breaking the input source code into tokens (smallest meaningful units).

**Key Components:**
- **Token Types:** Defined as an enum including keywords (`func`, `return`), identifiers, numbers, and operators
- **Global Variables:** 
  - `IdentifierStr`: Stores identifier names
  - `NumVal`: Stores numeric values
- **Main Function:** `gettok()` - reads characters and returns token types

**Supported Tokens:**
- Keywords: `func`, `return`, `if`, `else`, `while`
- Literals: Numbers (integers and floats)
- Identifiers: Variable and function names
- Operators: `+`, `-`, `*`, `/`, `<`
- Delimiters: `(`, `)`, `{`, `}`, `;`
- Comments: Lines starting with `#`

**Key Algorithm:**
```
1. Skip whitespace
2. If character is alphabetic → parse identifier/keyword
3. If character is digit → parse number
4. If character is special symbol → return as token
5. Handle comments and EOF
```

### 2. **Abstract Syntax Tree (AST)**
**Files:** `ast.hpp`, `ast.cpp`

The AST represents the hierarchical structure of the parsed program using the **Visitor Pattern**.

**Expression Classes:**
- **`ExprAST`**: Base class for all expressions
- **`NumberExprAST`**: Numeric literals (e.g., `42`, `3.14`)
- **`VariableExprAST`**: Variable references (e.g., `x`, `count`)
- **`BinaryExprAST`**: Binary operations (e.g., `a + b`, `x * y`)
- **`ReturnExprAST`**: Return statements (e.g., `return x + 1`)
- **`BlockExprAST`**: Code blocks containing multiple expressions
- **`FunctionAST`**: Complete function definitions

**Visitor Pattern Implementation:**
- Each AST node has an `accept()` method
- `CodegenVisitor` interface defines visit methods for each node type
- This allows adding new operations (like optimization) without modifying AST classes

### 3. **Parser (Syntax Analysis)**
**Files:** `parser.hpp`, `parser.cpp`

The parser converts tokens into an AST using **recursive descent parsing** with **operator precedence**.

**Key Features:**
- **Operator Precedence:** Handles mathematical operator precedence correctly
  - `*`, `/` have precedence 40
  - `+`, `-` have precedence 20  
  - `<` has precedence 10
- **Recursive Descent:** Each grammar rule has a corresponding parse function

**Parsing Functions:**
- `ParseFunction()`: Parses complete function definitions
- `ParseExpression()`: Parses expressions with operator precedence
- `ParsePrimary()`: Parses basic expressions (numbers, variables, parentheses)
- `ParseBinOpRHS()`: Handles binary operator precedence
- `ParseBlock()`: Parses code blocks

**Grammar (Simplified):**
```
Function := 'func' IDENTIFIER '(' Args ')' '{' Block '}'
Block := Expression ';' Block | ε
Expression := Primary BinOpRHS
Primary := NUMBER | IDENTIFIER | '(' Expression ')' | 'return' Expression
```

### 4. **Code Generation**
**Files:** `codegen.hpp`, `codegen.cpp`

Generates LLVM IR using the **Visitor Pattern**.

**`LLVMIRGenerator` Class:**
- Implements `CodegenVisitor` interface
- Maintains output string and temporary variable counter
- Tracks return statements

**Code Generation Strategy:**
- **Numbers**: Load into temporary variables using `fadd double 0.0, value`
- **Variables**: Load from memory with `load double, double* %varname`
- **Binary Operations**: Generate code for operands, then combine
- **Functions**: Create LLVM function with proper calling convention
- **Memory Management**: Allocate stack space for function parameters

**LLVM IR Features Generated:**
- Function definitions with proper signatures
- Memory allocation for parameters
- Arithmetic operations (fadd, fsub, fmul, fdiv)
- Comparison operations (fcmp)
- Return statements
- Proper SSA (Static Single Assignment) form

### 5. **Main Driver**
**File:** `main.cpp`

Simple driver that:
1. Reads input from stdin
2. Parses a function
3. Generates and outputs LLVM IR

## Language Features

### Supported Syntax:
```javascript
func add(x, y) {
    return x + y;
}

func complex(a, b, c) {
    return a * b + c / 2.0;
}

func comparison(x, y) {
    return x < y;
}
```

### Data Types:
- Only **double-precision floating-point** numbers
- No integers, strings, or complex types

### Operations:
- Arithmetic: `+`, `-`, `*`, `/`
- Comparison: `<` (returns 0.0 or 1.0)
- Function calls (basic support)

## Technical Highlights

### 1. **Visitor Pattern**
- Separates data structure (AST) from operations (code generation)
- Makes it easy to add new backends (could add x86 generator, interpreter, etc.)
- Clean separation of concerns

### 2. **Operator Precedence Parsing**
- Handles mathematical expressions correctly
- More efficient than building full parse trees for operators
- Uses precedence climbing algorithm

### 3. **LLVM IR Generation**
- Generates proper SSA form
- Handles type conversion (bool to double for comparisons)
- Proper function calling conventions
- Memory management for parameters

### 4. **Error Handling**
- Parser provides meaningful error messages
- Graceful handling of syntax errors
- Proper cleanup of resources

## Potential Interview Questions & Answers

### Q: "Why did you choose the Visitor Pattern?"
**A:** "The Visitor Pattern separates the AST structure from operations performed on it. This means I can add new operations like optimization passes, different code generators, or interpreters without modifying the AST classes. It follows the Open/Closed Principle - open for extension, closed for modification."

### Q: "How does your parser handle operator precedence?"
**A:** "I use precedence climbing with a precedence table. The `ParseBinOpRHS` function recursively handles operators based on their precedence levels. Higher precedence operators are parsed first, ensuring correct evaluation order like `2 + 3 * 4` becoming `2 + (3 * 4)`."

### Q: "Why generate LLVM IR instead of assembly?"
**A:** "LLVM IR is platform-independent and provides powerful optimization passes. It's in SSA form which makes optimizations easier, and LLVM can target multiple architectures. It's also more readable and maintainable than raw assembly."

### Q: "How would you extend this for more complex features?"
**A:** "For variables, I'd add symbol tables for scope management. For control flow, I'd add AST nodes for if/while and generate proper basic blocks. For types, I'd add a type system with type checking passes. The visitor pattern makes adding these features straightforward."

### Q: "What are the limitations of your current design?"
**A:** "Currently limited to double types only, no variables/assignments, no control flow, and basic error recovery. The lexer reads from stdin only, and there's no symbol table for variable scoping."

This project demonstrates solid understanding of compiler construction, design patterns, and code generation - excellent for interviews!
