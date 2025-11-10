

# Custom Compiler Frontend (C++ + LLVM)

A modern compiler front-end implemented in **C++17** that translates a custom programming language into **LLVM Intermediate Representation (IR)**.
It demonstrates key compiler design concepts such as **lexical analysis**, **recursive descent parsing**, **AST construction**, and **LLVM-based code generation**, using the **Visitor Pattern** for modularity.

---

## Overview

This project implements a complete mini compiler pipeline — from source code to LLVM IR:

| Stage              | Description                                | Output                     |
| ------------------ | ------------------------------------------ | -------------------------- |
| **Lexer**          | Converts source code into tokens           | Token stream               |
| **Parser**         | Builds syntax tree using recursive descent | Abstract Syntax Tree (AST) |
| **AST**            | Represents code semantically for analysis  | In-memory tree             |
| **Code Generator** | Emits LLVM IR using the LLVM C++ API       | LLVM IR module             |

---

## Architecture Overview

### 1. Lexical Analyzer (Lexer)

* Performs tokenization of identifiers, numbers, and keywords (`func`, `return`, etc.)
* Skips whitespace and comments
* Exposes `gettok()` to feed tokens to the parser

### 2. Parser

* Implements recursive descent parsing
* Handles operator precedence for binary operations (`+`, `-`, `*`, `/`, `<`)
* Builds an Abstract Syntax Tree (AST) representation

### 3. Abstract Syntax Tree (AST)

* Defines node classes:
  `NumberExprAST`, `VariableExprAST`, `BinaryExprAST`, `ReturnExprAST`, `BlockExprAST`, and `FunctionAST`
* Uses the Visitor Pattern to separate syntax and code generation logic

### 4. Code Generator (Backend)

* Uses the **LLVM C++ API** (`llvm::IRBuilder`, `llvm::Module`, `llvm::Function`, etc.)
* Generates real LLVM IR (not just text-based)
* Produces correct allocations (`alloca`, `store`, `load`) and arithmetic instructions (`fadd`, `fsub`, `fmul`, etc.)
* Easily extensible to new constructs and data types

---

## Example Input

```cpp
func calculate(x, y) {
    return x + y * 2.5;
}
```

### Corresponding LLVM IR Output

```llvm
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
```

---

## Technologies Used

| Component         | Technology                            |
| ----------------- | ------------------------------------- |
| Language          | C++17                                 |
| Compiler Backend  | LLVM 16+                              |
| Build System      | CMake                                 |
| Parsing Technique | Recursive Descent                     |
| Design Pattern    | Visitor Pattern                       |
| Target Output     | LLVM Intermediate Representation (IR) |

---

## Project Structure

```
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
```

---

## Dependencies

### Common Requirements

* C++17 compiler

  * Linux/macOS: `clang++` or `g++`
  * Windows: MSVC or `clang++`
* LLVM development libraries
* CMake ≥ 3.13

---

## Installation and Build Guide

### Linux (Ubuntu/Debian)

```bash
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
```

When prompted:

```
func add(a, b) { return a + b; }
```

Then press **Ctrl + D** to see the generated LLVM IR.

---

### macOS

```bash
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
```

---

### Windows

#### Option 1 — Using MSYS2 / MinGW

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-clang mingw-w64-x86_64-llvm mingw-w64-x86_64-cmake make git

git clone https://github.com/yourusername/custom-compiler.git
cd custom-compiler
mkdir build && cd build
cmake -G "MinGW Makefiles" -DLLVM_DIR="C:/msys64/mingw64/lib/cmake/llvm" ..
mingw32-make
./my_lang.exe
```

#### Option 2 — Using Visual Studio

1. Install **Visual Studio 2022** with “Desktop Development with C++”
2. Install **LLVM** from the official release:
   [https://github.com/llvm/llvm-project/releases](https://github.com/llvm/llvm-project/releases)
3. Open the **Developer Command Prompt**:

   ```cmd
   mkdir build && cd build
   cmake -DLLVM_DIR="C:\Program Files\LLVM\lib\cmake\llvm" ..
   cmake --build . --config Release
   my_lang.exe
   ```

---

## How to Run

1. Execute the compiler:

   ```bash
   ./my_lang
   ```
2. Input your function:

   ```cpp
   func add(a, b) { return a + b; }
   ```
3. End input:

   * Linux/macOS → **Ctrl + D**
   * Windows → **Ctrl + Z** then **Enter**
4. The LLVM IR will be printed to the console.

---

## Key Compiler Concepts Illustrated

| Concept                       | Implementation                         |
| ----------------------------- | -------------------------------------- |
| **Lexical Analysis**          | Tokenization using `gettok()`          |
| **Recursive Descent Parsing** | Manual grammar rules                   |
| **Abstract Syntax Tree**      | Object-oriented node hierarchy         |
| **Visitor Pattern**           | Decouples parsing from code generation |
| **LLVM IRBuilder**            | Generates real LLVM IR                 |
| **Semantic Correctness**      | Ensures type-safe operations           |



## Testing the Compiler

Once the project is successfully built, you can test the compiler with a simple program that returns the result of `2 + 3`. This demonstrates the full pipeline:
**Custom language → LLVM IR → Object file → Native executable → Output**

### Step 1: Create a Test Program

Create a file named `program.txt` in your project directory:

```bash
cat > program.txt << 'EOF'
func test() {
    return 2 + 3;
}
EOF
```

This defines a simple function `test()` that returns the sum of 2 and 3.

---

### Step 2: Generate LLVM IR

Run your compiler on this source file to produce an LLVM IR file:

```bash
# From the build directory
cd build
./my_lang < ../program.txt > output.ll
```

Inspect the generated IR:

```bash
cat output.ll
```

You should see something like:

```llvm
; ModuleID = 'MyModule'
source_filename = "MyModule"

define double @test() {
entry:
  ret double 5.000000e+00
}
```

This shows that your compiler successfully translated `2 + 3` into a function that returns `5.0` in LLVM IR.

---

### Step 3: Compile LLVM IR to Object Code

Convert the IR to an object file using the LLVM static compiler:

```bash
llc output.ll -filetype=obj -o test.o
```

---

### Step 4: Create a Driver Program

This small C program will call your compiled `test()` function and print its result.

```bash
cat > driver.c << 'EOF'
#include <stdio.h>

double test();

int main() {
    printf("%.0f\n", test());
    return 0;
}
EOF
```

---

### Step 5: Link and Run

Now link your object file with the driver to create a native executable:

```bash
clang test.o driver.c -o run_test
./run_test
```

You should see:

```
5
```

Congratulations — you have successfully compiled, assembled, linked, and executed code generated by your custom compiler.

---

### Optional: Run the LLVM IR Directly

If you want to interpret the LLVM IR without compiling to native code, use LLVM’s JIT interpreter (`lli`):

```bash
lli output.ll
```

## Author

**Kavya Perepu**
Email: [perepukavyasri@gmail.com](mailto:perepukavyasri@gmail.com)
LinkedIn: [linkedin.com/in/kavyaperepu](https://linkedin.com/in/kavyaperepu)
GitHub: [github.com/yourusername](https://github.com/yourusername)

---

## License

This project is licensed under the **MIT License**.
You are free to use, modify, and distribute it with proper attribution.

---

Would you like me to add a **“Run and Execute with LLVM Tools”** section next (showing how to pipe your compiler’s IR into `llvm-as` and `lli` to execute code directly, like a real compiler)? It makes your README look research-grade and functional like `clang`.
