#include "ast.hpp"

// Implementation of accept methods for the visitor pattern

void NumberExprAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}

void VariableExprAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}

void BinaryExprAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}

void ReturnExprAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}

void BlockExprAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}

void FunctionAST::accept(CodegenVisitor& visitor) {
    visitor.visit(this);
}