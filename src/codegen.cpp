#include "codegen.hpp"
#include <iostream>
#include <sstream>

void LLVMIRGenerator::visit(NumberExprAST* expr) {
    // Store the number in a temporary variable - corrected to use LLVM IR's proper syntax
    std::string tempVar = getNextTempVar();
    Output += tempVar + " = fadd double 0.0, " + std::to_string(expr->getValue()) + "\n";
}

void LLVMIRGenerator::visit(VariableExprAST* expr) {
    // Load the variable from memory - with proper type information
    std::string tempVar = getNextTempVar();
    Output += tempVar + " = load double, double* %" + expr->getName() + "\n";
}

void LLVMIRGenerator::visit(BinaryExprAST* expr) {
    // First generate code for the left-hand side
    expr->getLHS()->accept(*this);
    std::string lhsVar = "%t" + std::to_string(TempVarCounter - 1);
    
    // Then generate code for the right-hand side
    expr->getRHS()->accept(*this);
    std::string rhsVar = "%t" + std::to_string(TempVarCounter - 1);
    
    // Now generate code for the operation
    std::string tempVar = getNextTempVar();
    
    switch (expr->getOperator()) {
        case '+': {
            Output += tempVar + " = fadd double " + lhsVar + ", " + rhsVar + "\n";
            break;
        }
        case '-': {
            Output += tempVar + " = fsub double " + lhsVar + ", " + rhsVar + "\n";
            break;
        }
        case '*': {
            Output += tempVar + " = fmul double " + lhsVar + ", " + rhsVar + "\n";
            break;
        }
        case '/': {
            Output += tempVar + " = fdiv double " + lhsVar + ", " + rhsVar + "\n";
            break;
        }
        case '<': {
            // Generate comparison 
            std::string compVar = getNextTempVar();
            Output += compVar + " = fcmp olt double " + lhsVar + ", " + rhsVar + "\n";
            
            // Convert boolean to double (0.0 or 1.0)
            Output += tempVar + " = uitofp i1 " + compVar + " to double\n";
            break;
        }
        default: {
            std::cerr << "Unknown binary operator: " << expr->getOperator() << "\n";
            return;
        }
    }
}

void LLVMIRGenerator::visit(ReturnExprAST* expr) {
    // Generate code for the return value
    expr->getExpr()->accept(*this);
    std::string retVar = "%t" + std::to_string(TempVarCounter - 1);
    
    // Generate return instruction
    Output += "ret double " + retVar + "\n";
    
    // Mark that we've processed a return statement
    setHasReturn(true);
}

void LLVMIRGenerator::visit(BlockExprAST* expr) {
    // Visit each expression in the block
    const auto& expressions = expr->getExpressions();
    
    if (expressions.empty()) {
        // Handle empty block with proper return type
        Output += "ret double 0.0\n";
        setHasReturn(true);
        return;
    }
    
    for (const auto& expression : expressions) {
        expression->accept(*this);
        
        // If we've processed a return statement, we can stop generating code
        if (hasReturn()) {
            break;
        }
    }
}

void LLVMIRGenerator::visit(FunctionAST* func) {
    // Reset return flag
    setHasReturn(false);
    
    // Generate function header
    Output = "define double @" + func->getName() + "(";
    
    // Add function parameters
    const auto& args = func->getArgs();
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) Output += ", ";
        Output += "double %" + args[i];
    }
    Output += ") {\n";
    
    // Add entry point label
    Output += "entry:\n";
    
    // Allocate memory for function parameters
    for (const auto& arg : args) {
        Output += "  %" + arg + ".addr = alloca double\n";
        Output += "  store double %" + arg + ", double* %" + arg + ".addr\n";
    }
    
    // Generate code for the function body
    func->getBody()->accept(*this);
    
    // If the function doesn't end with a return statement, add one
    if (!hasReturn()) {
        Output += "  ret double 0.0\n";
    }
    
    // Close function
    if (Output.back() != '\n') Output += "\n";
    Output += "}\n";
}

void GenerateLLVMIR(FunctionAST* func) {
    std::cout << "Generating LLVM IR...\n";
    
    LLVMIRGenerator generator;
    func->accept(generator);
    
    std::cout << "Generated LLVM IR:\n";
    std::cout << "==================\n";
    std::cout << generator.getIR();
    std::cout << "==================\n";
}