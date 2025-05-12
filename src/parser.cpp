#include "parser.hpp"
#include "lexer.hpp"
#include "ast.hpp"
#include <iostream>
#include <memory>
#include <map>

int CurTok;
int getNextToken() { return CurTok = gettok(); }

// Operator precedence for binary operations
std::map<char, int> BinopPrecedence = {
    {'<', 10},
    {'+', 20},
    {'-', 20},
    {'*', 40},
    {'/', 40}
};

// Get the precedence of the current token
int GetTokenPrecedence() {
    if (!isascii(CurTok))
        return -1;

    int TokPrec = BinopPrecedence[CurTok];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

// Forward declarations
std::unique_ptr<ExprAST> ParseExpression();
std::unique_ptr<ExprAST> ParsePrimary();

// Parse number literals
std::unique_ptr<ExprAST> ParseNumberExpr() {
    auto Result = std::make_unique<NumberExprAST>(NumVal);
    getNextToken(); // consume the number
    return std::move(Result);
}

// Parse identifiers and function calls
std::unique_ptr<ExprAST> ParseIdentifierExpr() {
    std::string IdName = IdentifierStr;
    getNextToken(); // consume identifier
    
    // Simple variable reference
    return std::make_unique<VariableExprAST>(IdName);
}

// Parse parenthesized expressions
std::unique_ptr<ExprAST> ParseParenExpr() {
    getNextToken(); // consume '('
    auto V = ParseExpression();
    if (!V) {
        std::cerr << "Expected expression after '('\n";
        return nullptr;
    }

    if (CurTok != ')') {
        std::cerr << "Expected ')'\n";
        return nullptr;
    }
    getNextToken(); // consume ')'
    return V;
}

// Parse return statements
std::unique_ptr<ExprAST> ParseReturnExpr() {
    getNextToken(); // consume 'return'
    
    // Parse the return value
    auto RetVal = ParseExpression();
    if (!RetVal) {
        std::cerr << "Expected expression after 'return'\n";
        return nullptr;
    }
    
    // Consume the semicolon if present after return
    if (CurTok == tok_semicolon || CurTok == ';') {
        getNextToken(); // consume ';'
    }
    
    return std::make_unique<ReturnExprAST>(std::move(RetVal));
}

// Parse primary expressions
std::unique_ptr<ExprAST> ParsePrimary() {
    switch (CurTok) {
    case tok_identifier:
        return ParseIdentifierExpr();
    case tok_number:
        return ParseNumberExpr();
    case '(':
        return ParseParenExpr();
    case tok_return:
        return ParseReturnExpr();
    default:
        std::cerr << "Unknown token when expecting an expression: " << CurTok << "\n";
        return nullptr;
    }
}

// Parse binary operations with operator precedence
std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
    while (true) {
        // Get the precedence of the current token
        int TokPrec = GetTokenPrecedence();

        // If this is a binary operator with too low precedence, return the expression so far
        if (TokPrec < ExprPrec)
            return LHS;

        // We have a binary operator
        int BinOp = CurTok;
        getNextToken(); // consume binary operator

        // Parse the primary expression after the binary operator
        auto RHS = ParsePrimary();
        if (!RHS)
            return nullptr;

        // Get the precedence of the next operator
        int NextPrec = GetTokenPrecedence();
        if (TokPrec < NextPrec) {
            // If the next operator has higher precedence, parse it first
            RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
            if (!RHS)
                return nullptr;
        }

        // Merge LHS and RHS into a binary expression
        LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
    }
}

// Parse expressions
std::unique_ptr<ExprAST> ParseExpression() {
    auto LHS = ParsePrimary();
    if (!LHS)
        return nullptr;

    return ParseBinOpRHS(0, std::move(LHS));
}

// Parse a block of expressions
std::unique_ptr<ExprAST> ParseBlock() {
    std::vector<std::unique_ptr<ExprAST>> Expressions;
    
    while (CurTok != '}' && CurTok != tok_eof) {
        auto Expr = ParseExpression();
        if (!Expr)
            return nullptr;
        
        Expressions.push_back(std::move(Expr));
        
        // Check if the expression is a return statement
        bool isReturn = dynamic_cast<ReturnExprAST*>(Expressions.back().get()) != nullptr;
        
        // Expect a semicolon after each expression except return (return already consumed the semicolon if present)
        if (!isReturn) {
            if (CurTok != ';' && CurTok != tok_semicolon) {
                std::cerr << "Expected ';' after expression\n";
                return nullptr;
            }
            getNextToken(); // consume ';'
        }
        
        // If we've processed a return statement, we can stop parsing the block
        if (isReturn) {
            break;
        }
    }
    
    // Properly create a BlockExprAST with all expressions
    return std::make_unique<BlockExprAST>(std::move(Expressions));
}

// Parse function definitions
std::unique_ptr<FunctionAST> ParseFunction() {
    if (CurTok != tok_func) {
        std::cerr << "Expected 'func'\n";
        return nullptr;
    }
    getNextToken(); // consume 'func'

    if (CurTok != tok_identifier) {
        std::cerr << "Expected function name\n";
        return nullptr;
    }

    std::string FuncName = IdentifierStr;
    getNextToken(); // consume name

    if (CurTok != '(') {
        std::cerr << "Expected '('\n";
        return nullptr;
    }
    getNextToken();

    std::vector<std::string> Args;
    if (CurTok != ')') {  // Check if there are any arguments
        do {
            if (CurTok != tok_identifier) {
                std::cerr << "Expected identifier in argument list\n";
                return nullptr;
            }

            Args.push_back(IdentifierStr);
            getNextToken();
            
            if (CurTok != ',' && CurTok != ')')
                break;
                
            if (CurTok == ',')
                getNextToken();
                
        } while (CurTok != ')');
    }

    if (CurTok != ')') {
        std::cerr << "Expected ')'\n";
        return nullptr;
    }
    getNextToken();

    if (CurTok != '{') {
        std::cerr << "Expected '{'\n";
        return nullptr;
    }
    getNextToken();

    auto Body = ParseBlock();
    if (!Body)
        return nullptr;

    if (CurTok != '}') {
        std::cerr << "Expected '}'\n";
        return nullptr;
    }
    getNextToken();

    return std::make_unique<FunctionAST>(FuncName, std::move(Args), std::move(Body));
}