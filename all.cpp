// // ============== ast.hpp ==============
// #ifndef AST_HPP
// #define AST_HPP

// #include <memory>
// #include <string>
// #include <vector>

// // Forward declaration
// class CodegenVisitor;

// // Base expression class
// class ExprAST {
// public:
//     virtual ~ExprAST() = default;
    
//     // Visitor pattern for code generation
//     virtual void accept(CodegenVisitor& visitor) = 0;
// };

// // Expression class for numeric literals
// class NumberExprAST : public ExprAST {
//     double Val;

// public:
//     NumberExprAST(double Val) : Val(Val) {}
//     double getValue() const { return Val; }
    
//     void accept(CodegenVisitor& visitor) override;
// };

// // Expression class for referencing variables
// class VariableExprAST : public ExprAST {
//     std::string Name;

// public:
//     VariableExprAST(const std::string &Name) : Name(Name) {}
//     const std::string& getName() const { return Name; }
    
//     void accept(CodegenVisitor& visitor) override;
// };

// // Expression class for binary operators
// class BinaryExprAST : public ExprAST {
//     char Op;
//     std::unique_ptr<ExprAST> LHS, RHS;

// public:
//     BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
//         : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    
//     char getOperator() const { return Op; }
//     ExprAST* getLHS() const { return LHS.get(); }
//     ExprAST* getRHS() const { return RHS.get(); }
    
//     void accept(CodegenVisitor& visitor) override;
// };

// // Expression class for return statements
// class ReturnExprAST : public ExprAST {
//     std::unique_ptr<ExprAST> Expr;

// public:
//     ReturnExprAST(std::unique_ptr<ExprAST> Expr) : Expr(std::move(Expr)) {}
//     ExprAST* getExpr() const { return Expr.get(); }
    
//     void accept(CodegenVisitor& visitor) override;
// };

// // Expression class for blocks of code (multiple expressions)
// class BlockExprAST : public ExprAST {
//     std::vector<std::unique_ptr<ExprAST>> Expressions;
    
// public:
//     BlockExprAST(std::vector<std::unique_ptr<ExprAST>> Expressions)
//         : Expressions(std::move(Expressions)) {}
    
//     const std::vector<std::unique_ptr<ExprAST>>& getExpressions() const { return Expressions; }
    
//     void accept(CodegenVisitor& visitor) override;
// };

// // Full function definition
// class FunctionAST {
//     std::string Name;
//     std::vector<std::string> Args;
//     std::unique_ptr<ExprAST> Body;

// public:
//     FunctionAST(const std::string &Name, std::vector<std::string> Args, std::unique_ptr<ExprAST> Body)
//         : Name(Name), Args(std::move(Args)), Body(std::move(Body)) {}
    
//     const std::string& getName() const { return Name; }
//     const std::vector<std::string>& getArgs() const { return Args; }
//     ExprAST* getBody() const { return Body.get(); }
    
//     void accept(CodegenVisitor& visitor);
// };

// // Visitor interface for code generation
// class CodegenVisitor {
// public:
//     virtual ~CodegenVisitor() = default;
    
//     virtual void visit(NumberExprAST* expr) = 0;
//     virtual void visit(VariableExprAST* expr) = 0;
//     virtual void visit(BinaryExprAST* expr) = 0;
//     virtual void visit(ReturnExprAST* expr) = 0;
//     virtual void visit(BlockExprAST* expr) = 0;
//     virtual void visit(FunctionAST* func) = 0;
// };

// #endif

// // ============== ast.cpp ==============
// #include "ast.hpp"

// // Implementation of accept methods for the visitor pattern

// void NumberExprAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// void VariableExprAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// void BinaryExprAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// void ReturnExprAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// void BlockExprAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// void FunctionAST::accept(CodegenVisitor& visitor) {
//     visitor.visit(this);
// }

// // ============== codegen.hpp ==============
// #ifndef CODEGEN_HPP
// #define CODEGEN_HPP

// #include "ast.hpp"
// #include <iostream>
// #include <string>

// // LLVM IR Code Generator using visitor pattern
// class LLVMIRGenerator : public CodegenVisitor {
// private:
//     std::string Output;
//     int TempVarCounter = 0;
//     bool HasReturn = false;
    
//     // Generate a unique temporary variable name
//     std::string getNextTempVar() {
//         return "%t" + std::to_string(TempVarCounter++);
//     }

// public:
//     LLVMIRGenerator() : HasReturn(false) {}
    
//     // Implementation of visitor methods
//     void visit(NumberExprAST* expr) override;
//     void visit(VariableExprAST* expr) override;
//     void visit(BinaryExprAST* expr) override;
//     void visit(ReturnExprAST* expr) override;
//     void visit(BlockExprAST* expr) override;
//     void visit(FunctionAST* func) override;
    
//     // Get the generated LLVM IR
//     std::string getIR() const { return Output; }
    
//     // Check if a return statement was processed
//     bool hasReturn() const { return HasReturn; }
//     void setHasReturn(bool value) { HasReturn = value; }
// };

// void GenerateLLVMIR(FunctionAST* func);

// #endif

// // ============== codegen.cpp ==============
// #include "codegen.hpp"
// #include <iostream>
// #include <sstream>

// // Implementation of visitor methods for LLVM IR generation

// void LLVMIRGenerator::visit(NumberExprAST* expr) {
//     // Store the number in a temporary variable - corrected to use LLVM IR's proper syntax
//     std::string tempVar = getNextTempVar();
//     Output += tempVar + " = fadd double 0.0, " + std::to_string(expr->getValue()) + "\n";
// }

// void LLVMIRGenerator::visit(VariableExprAST* expr) {
//     // Load the variable from memory - with proper type information
//     std::string tempVar = getNextTempVar();
//     Output += tempVar + " = load double, double* %" + expr->getName() + "\n";
// }

// void LLVMIRGenerator::visit(BinaryExprAST* expr) {
//     // First generate code for the left-hand side
//     expr->getLHS()->accept(*this);
//     std::string lhsVar = "%t" + std::to_string(TempVarCounter - 1);
    
//     // Then generate code for the right-hand side
//     expr->getRHS()->accept(*this);
//     std::string rhsVar = "%t" + std::to_string(TempVarCounter - 1);
    
//     // Now generate code for the operation
//     std::string tempVar = getNextTempVar();
    
//     std::string op;
//     switch (expr->getOperator()) {
//         case '+': op = "fadd"; break;
//         case '-': op = "fsub"; break;
//         case '*': op = "fmul"; break;
//         case '/': op = "fdiv"; break;
//         case '<': 
//             op = "fcmp olt"; 
//             Output += tempVar + " = " + op + " double " + lhsVar + ", " + rhsVar + "\n";
//             // Convert boolean result to double
//             std::string boolTempVar = tempVar;
//             tempVar = getNextTempVar();
//             Output += tempVar + " = uitofp i1 " + boolTempVar + " to double\n";
//             return;
//         default:
//             std::cerr << "Unknown binary operator: " << expr->getOperator() << "\n";
//             return;
//     }
    
//     Output += tempVar + " = " + op + " double " + lhsVar + ", " + rhsVar + "\n";
// }

// void LLVMIRGenerator::visit(ReturnExprAST* expr) {
//     // Generate code for the return value
//     expr->getExpr()->accept(*this);
//     std::string retVar = "%t" + std::to_string(TempVarCounter - 1);
    
//     // Generate return instruction
//     Output += "ret double " + retVar + "\n";
    
//     // Mark that we've processed a return statement
//     setHasReturn(true);
// }

// void LLVMIRGenerator::visit(BlockExprAST* expr) {
//     // Visit each expression in the block
//     const auto& expressions = expr->getExpressions();
    
//     if (expressions.empty()) {
//         // Handle empty block with proper return type
//         Output += "ret double 0.0\n";
//         setHasReturn(true);
//         return;
//     }
    
//     for (const auto& expression : expressions) {
//         expression->accept(*this);
        
//         // If we've processed a return statement, we can stop generating code
//         if (hasReturn()) {
//             break;
//         }
//     }
// }

// void LLVMIRGenerator::visit(FunctionAST* func) {
//     // Reset return flag
//     setHasReturn(false);
    
//     // Generate function header
//     Output = "define double @" + func->getName() + "(";
    
//     // Add function parameters
//     const auto& args = func->getArgs();
//     for (size_t i = 0; i < args.size(); ++i) {
//         if (i > 0) Output += ", ";
//         Output += "double %" + args[i];
//     }
//     Output += ") {\n";
    
//     // Add entry point label
//     Output += "entry:\n";
    
//     // Allocate memory for function parameters
//     for (const auto& arg : args) {
//         Output += "  %" + arg + ".addr = alloca double\n";
//         Output += "  store double %" + arg + ", double* %" + arg + ".addr\n";
//     }
    
//     // Generate code for the function body
//     func->getBody()->accept(*this);
    
//     // If the function doesn't end with a return statement, add one
//     if (!hasReturn()) {
//         Output += "  ret double 0.0\n";
//     }
    
//     // Close function
//     if (Output.back() != '\n') Output += "\n";
//     Output += "}\n";
// }

// void GenerateLLVMIR(FunctionAST* func) {
//     std::cout << "Generating LLVM IR...\n";
    
//     LLVMIRGenerator generator;
//     func->accept(generator);
    
//     std::cout << "Generated LLVM IR:\n";
//     std::cout << "==================\n";
//     std::cout << generator.getIR();
//     std::cout << "==================\n";
// }

// // ============== lexer.hpp ==============
// #ifndef LEXER_HPP
// #define LEXER_HPP

// #include <string>

// // Token types
// enum Token {
//     tok_eof = -1,

//     // Keywords
//     tok_func = -2,
//     tok_return = -3,

//     // Identifiers and literals
//     tok_identifier = -4,
//     tok_number = -5,
    
//     // Add some additional tokens for future expansion
//     tok_if = -6,
//     tok_else = -7,
//     tok_while = -8,
//     tok_semicolon = -9,
// };

// // These are defined in lexer.cpp and used elsewhere
// extern std::string IdentifierStr; // For tok_identifier
// extern double NumVal;             // For tok_number

// /**
//  * Returns the next token from standard input
//  * Updates IdentifierStr or NumVal as appropriate
//  */
// int gettok();

// #endif

// // ============== lexer.cpp ==============
// #include "lexer.hpp"
// #include <cctype>
// #include <cstdio>
// #include <cstdlib>
// #include <iostream>

// std::string IdentifierStr; // filled in if tok_identifier
// double NumVal;             // filled in if tok_number

// int gettok() {
//     static int LastChar = ' ';

//     // Skip whitespace
//     while (isspace(LastChar))
//         LastChar = getchar();

//     // Identifier: [a-zA-Z][a-zA-Z0-9]*
//     if (isalpha(LastChar) || LastChar == '_') {
//         IdentifierStr = LastChar;
//         while (isalnum((LastChar = getchar())) || LastChar == '_')
//             IdentifierStr += LastChar;

//         if (IdentifierStr == "func")
//             return tok_func;
//         if (IdentifierStr == "return")
//             return tok_return;
//         if (IdentifierStr == "if")
//             return tok_if;
//         if (IdentifierStr == "else")
//             return tok_else;
//         if (IdentifierStr == "while")
//             return tok_while;
//         return tok_identifier;
//     }

//     // Number: [0-9]+[.]?[0-9]*
//     if (isdigit(LastChar) || LastChar == '.') {
//         std::string NumStr;
//         bool hasDecimal = false;
        
//         do {
//             if (LastChar == '.')
//                 hasDecimal = true;
                
//             NumStr += LastChar;
//             LastChar = getchar();
//         } while (isdigit(LastChar) || (LastChar == '.' && !hasDecimal));

//         NumVal = strtod(NumStr.c_str(), nullptr);
//         return tok_number;
//     }

//     // Check for semicolon
//     if (LastChar == ';') {
//         LastChar = getchar();
//         return tok_semicolon;
//     }

//     // Comment until end of line
//     if (LastChar == '#') {
//         do
//             LastChar = getchar();
//         while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');

//         if (LastChar != EOF)
//             return gettok();
//     }

//     // Check for end of file. Don't eat the EOF.
//     if (LastChar == EOF)
//         return tok_eof;

//     // Otherwise, return the character as its ASCII value.
//     int ThisChar = LastChar;
//     LastChar = getchar();
//     return ThisChar;
// }

// // ============== parser.hpp ==============
// #ifndef PARSER_HPP
// #define PARSER_HPP

// #include <memory>
// #include "ast.hpp"

// extern int CurTok;
// int getNextToken();

// std::unique_ptr<FunctionAST> ParseFunction();

// #endif

// // ============== parser.cpp ==============
// #include "parser.hpp"
// #include "lexer.hpp"
// #include "ast.hpp"
// #include <iostream>
// #include <memory>
// #include <map>

// int CurTok;
// int getNextToken() { return CurTok = gettok(); }

// // Operator precedence for binary operations
// std::map<char, int> BinopPrecedence = {
//     {'<', 10},
//     {'+', 20},
//     {'-', 20},
//     {'*', 40},
//     {'/', 40}
// };

// // Get the precedence of the current token
// int GetTokenPrecedence() {
//     if (!isascii(CurTok))
//         return -1;

//     int TokPrec = BinopPrecedence[CurTok];
//     if (TokPrec <= 0)
//         return -1;
//     return TokPrec;
// }

// // Forward declarations
// std::unique_ptr<ExprAST> ParseExpression();
// std::unique_ptr<ExprAST> ParsePrimary();

// // Parse number literals
// std::unique_ptr<ExprAST> ParseNumberExpr() {
//     auto Result = std::make_unique<NumberExprAST>(NumVal);
//     getNextToken(); // consume the number
//     return std::move(Result);
// }

// // Parse identifiers and function calls
// std::unique_ptr<ExprAST> ParseIdentifierExpr() {
//     std::string IdName = IdentifierStr;
//     getNextToken(); // consume identifier
    
//     // Simple variable reference
//     return std::make_unique<VariableExprAST>(IdName);
// }

// // Parse parenthesized expressions
// std::unique_ptr<ExprAST> ParseParenExpr() {
//     getNextToken(); // consume '('
//     auto V = ParseExpression();
//     if (!V) {
//         std::cerr << "Expected expression after '('\n";
//         return nullptr;
//     }

//     if (CurTok != ')') {
//         std::cerr << "Expected ')'\n";
//         return nullptr;
//     }
//     getNextToken(); // consume ')'
//     return V;
// }

// // Parse return statements
// std::unique_ptr<ExprAST> ParseReturnExpr() {
//     getNextToken(); // consume 'return'
    
//     // Parse the return value
//     auto RetVal = ParseExpression();
//     if (!RetVal) {
//         std::cerr << "Expected expression after 'return'\n";
//         return nullptr;
//     }
    
//     // Consume the semicolon if present after return
//     if (CurTok == tok_semicolon || CurTok == ';') {
//         getNextToken(); // consume ';'
//     }
    
//     return std::make_unique<ReturnExprAST>(std::move(RetVal));
// }

// // Parse primary expressions
// std::unique_ptr<ExprAST> ParsePrimary() {
//     switch (CurTok) {
//     case tok_identifier:
//         return ParseIdentifierExpr();
//     case tok_number:
//         return ParseNumberExpr();
//     case '(':
//         return ParseParenExpr();
//     case tok_return:
//         return ParseReturnExpr();
//     default:
//         std::cerr << "Unknown token when expecting an expression: " << CurTok << "\n";
//         return nullptr;
//     }
// }

// // Parse binary operations with operator precedence
// std::unique_ptr<ExprAST> ParseBinOpRHS(int ExprPrec, std::unique_ptr<ExprAST> LHS) {
//     while (true) {
//         // Get the precedence of the current token
//         int TokPrec = GetTokenPrecedence();

//         // If this is a binary operator with too low precedence, return the expression so far
//         if (TokPrec < ExprPrec)
//             return LHS;

//         // We have a binary operator
//         int BinOp = CurTok;
//         getNextToken(); // consume binary operator

//         // Parse the primary expression after the binary operator
//         auto RHS = ParsePrimary();
//         if (!RHS)
//             return nullptr;

//         // Get the precedence of the next operator
//         int NextPrec = GetTokenPrecedence();
//         if (TokPrec < NextPrec) {
//             // If the next operator has higher precedence, parse it first
//             RHS = ParseBinOpRHS(TokPrec + 1, std::move(RHS));
//             if (!RHS)
//                 return nullptr;
//         }

//         // Merge LHS and RHS into a binary expression
//         LHS = std::make_unique<BinaryExprAST>(BinOp, std::move(LHS), std::move(RHS));
//     }
// }

// // Parse expressions
// std::unique_ptr<ExprAST> ParseExpression() {
//     auto LHS = ParsePrimary();
//     if (!LHS)
//         return nullptr;

//     return ParseBinOpRHS(0, std::move(LHS));
// }

// // Parse a block of expressions
// std::unique_ptr<ExprAST> ParseBlock() {
//     std::vector<std::unique_ptr<ExprAST>> Expressions;
    
//     while (CurTok != '}' && CurTok != tok_eof) {
//         auto Expr = ParseExpression();
//         if (!Expr)
//             return nullptr;
        
//         Expressions.push_back(std::move(Expr));
        
//         // Check if the expression is a return statement
//         bool isReturn = dynamic_cast<ReturnExprAST*>(Expressions.back().get()) != nullptr;
        
//         // Expect a semicolon after each expression except return (return already consumed the semicolon if present)
//         if (!isReturn) {
//             if (CurTok != ';' && CurTok != tok_semicolon) {
//                 std::cerr << "Expected ';' after expression\n";
//                 return nullptr;
//             }
//             getNextToken(); // consume ';'
//         }
        
//         // If we've processed a return statement, we can stop parsing the block
//         if (isReturn) {
//             break;
//         }
//     }
    
//     // Properly create a BlockExprAST with all expressions
//     return std::make_unique<BlockExprAST>(std::move(Expressions));
// }

// // Parse function definitions
// std::unique_ptr<FunctionAST> ParseFunction() {
//     if (CurTok != tok_func) {
//         std::cerr << "Expected 'func'\n";
//         return nullptr;
//     }
//     getNextToken(); // consume 'func'

//     if (CurTok != tok_identifier) {
//         std::cerr << "Expected function name\n";
//         return nullptr;
//     }

//     std::string FuncName = IdentifierStr;
//     getNextToken(); // consume name

//     if (CurTok != '(') {
//         std::cerr << "Expected '('\n";
//         return nullptr;
//     }
//     getNextToken();

//     std::vector<std::string> Args;
//     if (CurTok != ')') {  // Check if there are any arguments
//         do {
//             if (CurTok != tok_identifier) {
//                 std::cerr << "Expected identifier in argument list\n";
//                 return nullptr;
//             }

//             Args.push_back(IdentifierStr);
//             getNextToken();
            
//             if (CurTok != ',' && CurTok != ')')
//                 break;
                
//             if (CurTok == ',')
//                 getNextToken();
                
//         } while (CurTok != ')');
//     }

//     if (CurTok != ')') {
//         std::cerr << "Expected ')'\n";
//         return nullptr;
//     }
//     getNextToken();

//     if (CurTok != '{') {
//         std::cerr << "Expected '{'\n";
//         return nullptr;
//     }
//     getNextToken();

//     auto Body = ParseBlock();
//     if (!Body)
//         return nullptr;

//     if (CurTok != '}') {
//         std::cerr << "Expected '}'\n";
//         return nullptr;
//     }
//     getNextToken();

//     return std::make_unique<FunctionAST>(FuncName, std::move(Args), std::move(Body));
// }

// // ============== main.cpp ==============
// #include <iostream>
// #include "lexer.hpp"
// #include "parser.hpp"
// #include "codegen.hpp"

// int main() {
//     std::cout << "Enter code:\n";
//     getNextToken();

//     if (auto Func = ParseFunction()) {
//         std::cout << "Parsed a function successfully!\n";
//         GenerateLLVMIR(Func.get());
//     } else {
//         std::cerr << "Error parsing function.\n";
//     }

//     return 0;
// }