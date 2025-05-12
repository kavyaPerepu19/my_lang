#ifndef AST_HPP
#define AST_HPP

#include <memory>
#include <string>
#include <vector>

// Forward declaration
class CodegenVisitor;

// Base expression class
class ExprAST {
public:
    virtual ~ExprAST() = default;
    
    // Visitor pattern for code generation
    virtual void accept(CodegenVisitor& visitor) = 0;
};

// Expression class for numeric literals
class NumberExprAST : public ExprAST {
    double Val;

public:
    NumberExprAST(double Val) : Val(Val) {}
    double getValue() const { return Val; }
    
    void accept(CodegenVisitor& visitor) override;
};

// Expression class for referencing variables
class VariableExprAST : public ExprAST {
    std::string Name;

public:
    VariableExprAST(const std::string &Name) : Name(Name) {}
    const std::string& getName() const { return Name; }
    
    void accept(CodegenVisitor& visitor) override;
};

// Expression class for binary operators
class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS;

public:
    BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
    
    char getOperator() const { return Op; }
    ExprAST* getLHS() const { return LHS.get(); }
    ExprAST* getRHS() const { return RHS.get(); }
    
    void accept(CodegenVisitor& visitor) override;
};

// Expression class for return statements
class ReturnExprAST : public ExprAST {
    std::unique_ptr<ExprAST> Expr;

public:
    ReturnExprAST(std::unique_ptr<ExprAST> Expr) : Expr(std::move(Expr)) {}
    ExprAST* getExpr() const { return Expr.get(); }
    
    void accept(CodegenVisitor& visitor) override;
};

// Expression class for blocks of code (multiple expressions)
class BlockExprAST : public ExprAST {
    std::vector<std::unique_ptr<ExprAST>> Expressions;
    
public:
    BlockExprAST(std::vector<std::unique_ptr<ExprAST>> Expressions)
        : Expressions(std::move(Expressions)) {}
    
    const std::vector<std::unique_ptr<ExprAST>>& getExpressions() const { return Expressions; }
    
    void accept(CodegenVisitor& visitor) override;
};

// Full function definition
class FunctionAST {
    std::string Name;
    std::vector<std::string> Args;
    std::unique_ptr<ExprAST> Body;

public:
    FunctionAST(const std::string &Name, std::vector<std::string> Args, std::unique_ptr<ExprAST> Body)
        : Name(Name), Args(std::move(Args)), Body(std::move(Body)) {}
    
    const std::string& getName() const { return Name; }
    const std::vector<std::string>& getArgs() const { return Args; }
    ExprAST* getBody() const { return Body.get(); }
    
    void accept(CodegenVisitor& visitor);
};

// Visitor interface for code generation
class CodegenVisitor {
public:
    virtual ~CodegenVisitor() = default;
    
    virtual void visit(NumberExprAST* expr) = 0;
    virtual void visit(VariableExprAST* expr) = 0;
    virtual void visit(BinaryExprAST* expr) = 0;
    virtual void visit(ReturnExprAST* expr) = 0;
    virtual void visit(BlockExprAST* expr) = 0;
    virtual void visit(FunctionAST* func) = 0;
};

#endif