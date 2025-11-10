Custom Compiler Frontend (C++ + LLVM)

A modern compiler front-end implemented in C++17 that translates a custom programming language into LLVM Intermediate Representation (IR).
It demonstrates key compiler design concepts — lexical analysis, recursive descent parsing, AST construction, and LLVM-based code generation — using the Visitor Pattern for modularity.

🚀 Overview

This project implements a complete mini compiler pipeline, from source code to LLVM IR:

Stage	Description	Output
Lexer	Converts source code into tokens	Token stream
Parser	Builds syntax tree using recursive descent	Abstract Syntax Tree (AST)
AST	Represents code semantically for analysis	In-memory tree
Code Generator	Emits LLVM IR using LLVM C++ API	LLVM IR text/module
🏗️ Architecture Overview
🔹 1. Lexical Analyzer (Lexer)

Performs tokenization of identifiers, numbers, and keywords (func, return, etc.)

Implements skipping of whitespace and comments

Exposes gettok() to feed tokens to the parser

🔹 2. Parser

Implements recursive descent parsing

Handles operator precedence for binary operations (+, -, *, /, <)

Builds an Abstract Syntax Tree (AST) representation

🔹 3. Abstract Syntax Tree (AST)

Implements node classes for NumberExprAST, VariableExprAST, BinaryExprAST, ReturnExprAST, BlockExprAST, and FunctionAST

Uses the Visitor Pattern for clean separation between syntax and code generation

🔹 4. Code Generator (Backend)

Uses the LLVM C++ API (llvm::IRBuilder, llvm::Module, llvm::Function, etc.)

Generates real LLVM IR (not just text)

Produces correct memory allocations (alloca, store, load) and arithmetic instructions (fadd, fsub, fmul, etc.)

Can be extended to support additional data types and control flow constructs

🧩 Example Input
func calculate(x, y) {
    return x + y * 2.5;
}

🧾 Example LLVM IR Output
define double @calculate(double %x, double %y) {
entry:
  %x.addr = alloca double
  store double %x, double* %x.addr
  %y.addr = alloca double
  store double %y, double* %y.addr
  %0 = load double, double* %x.addr
  %1 = load double, double* %y.addr
  %2 = fmul double %1, 2.500000e+00
  %3 = fadd double %0, %2
  ret double %3
}

⚙️ Technologies Used
Component	Technology
Language	C++17
Compiler Backend	LLVM 16+
Build System	CMake
Parsing Strategy	Recursive Descent
Design Pattern	Visitor Pattern
Target Output	LLVM Intermediate Representation (IR)
🧱 Project Structure
.
├── include/
│   ├── ast.hpp
│   ├── lexer.hpp
│   ├── parser.hpp
│   └── codegen.hpp
├── src/
│   ├── ast.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
│   ├── codegen.cpp
│   └── main.cpp
├── build/                  # Generated build artifacts
├── CMakeLists.txt
└── README.md

🔧 Dependencies
🧩 Common

C++17 compiler

Linux/macOS → clang++ or g++

Windows → Visual Studio (MSVC) or LLVM’s clang++

LLVM development libraries

CMake ≥ 3.13

💻 Installation & Build Guide
🐧 Linux (Ubuntu/Debian)
# 1. Install dependencies
sudo apt update
sudo apt install llvm-16 llvm-16-dev clang-16 cmake build-essential

# 2. Clone project
git clone https://github.com/yourusername/custom-compiler.git
cd custom-compiler

# 3. Build project
mkdir build && cd build
cmake -DLLVM_DIR=/usr/lib/llvm-16/lib/cmake/llvm ..
make

# 4. Run the compiler
./my_lang


Then type:

func add(a, b) { return a + b; }


and press Ctrl+D to see the LLVM IR output.

🍎 macOS
# 1. Install dependencies
brew install llvm cmake

# 2. Add LLVM to PATH for CMake
export PATH="/usr/local/opt/llvm/bin:$PATH"
export LLVM_DIR="$(brew --prefix llvm)/lib/cmake/llvm"

# 3. Build
mkdir build && cd build
cmake -DLLVM_DIR=$LLVM_DIR ..
make

# 4. Run
./my_lang

🪟 Windows (MSYS2 or Visual Studio)
Option 1 — Using MSYS2 / MinGW
pacman -Syu
pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-llvm mingw-w64-x86_64-cmake make git

git clone https://github.com/yourusername/custom-compiler.git
cd custom-compiler
mkdir build && cd build
cmake -G "MinGW Makefiles" -DLLVM_DIR="C:/msys64/mingw64/lib/cmake/llvm" ..
mingw32-make
./my_lang.exe

Option 2 — Using Visual Studio

Install Visual Studio 2022 with “Desktop Development with C++”

Install LLVM via the official installer
→ https://github.com/llvm/llvm-project/releases

Open Developer Command Prompt:

mkdir build && cd build
cmake -DLLVM_DIR="C:\Program Files\LLVM\lib\cmake\llvm" ..
cmake --build . --config Release
my_lang.exe

🧠 How to Run

Execute the compiler:

./my_lang


Input your function:

func add(a, b) { return a + b; }


Press Ctrl + D (Linux/macOS) or Ctrl + Z + Enter (Windows)

LLVM IR output will be printed to the console.

🧩 Key Compiler Concepts Illustrated
Concept	Implementation
Lexical Analysis	Tokenization using gettok()
Recursive Descent Parsing	Manually written grammar rules
Abstract Syntax Tree (AST)	Object-oriented node hierarchy
Visitor Pattern	Clean decoupling of parsing and codegen
LLVM IRBuilder	Real IR emission via API calls
Semantic Correctness	Type-safe operations in IR
🧩 Future Enhancements

Add conditionals (if, else) and loops (while, for)

Type checking and multi-type support

Function calls and variable scopes

Constant folding and basic optimizations

Integration with lli (LLVM Interpreter) for direct execution

🧑‍💻 Author

Kavya Perepu
📧 perepukavyasri@gmail.com

🌐 LinkedIn
 · GitHub

🧾 License

This project is licensed under the MIT License — you are free to use, modify, and distribute it with attribution.
