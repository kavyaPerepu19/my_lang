#include <iostream>
#include "lexer.hpp"
#include "parser.hpp"
#include "codegen.hpp"

int main() {
    std::cout << "Enter code:\n";
    getNextToken();

    if (auto Func = ParseFunction()) {
        std::cout << "Parsed a function successfully!\n";
        GenerateLLVMIR(Func.get());
    } else {
        std::cerr << "Error parsing function.\n";
    }

    return 0;
}