#ifndef CODEGEN_HPP
#define CODEGEN_HPP

#include "ast.hpp"
#include <iostream>
#include <string>

// LLVM IR Code Generator using visitor pattern
class LLVMIRGenerator : public CodegenVisitor {
private:
    std::string Output;
    int TempVarCounter = 0;
    bool HasReturn = false;
    
    // Generate a unique temporary variable name
    std::string getNextTempVar() {
        return "%t" + std::to_string(TempVarCounter++);
    }

public:
    LLVMIRGenerator() : HasReturn(false) {}
    
    // Implementation of visitor methods
    void visit(NumberExprAST* expr) override;
    void visit(VariableExprAST* expr) override;
    void visit(BinaryExprAST* expr) override;
    void visit(ReturnExprAST* expr) override;
    void visit(BlockExprAST* expr) override;
    void visit(FunctionAST* func) override;
    
    // Get the generated LLVM IR
    std::string getIR() const { return Output; }
    
    // Check if a return statement was processed
    bool hasReturn() const { return HasReturn; }
    void setHasReturn(bool value) { HasReturn = value; }
};

void GenerateLLVMIR(FunctionAST* func);

#endif
