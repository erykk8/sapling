#pragma once
#include "../token/Token.h"
#include "Expression.h"

#include <string>
#include <map>
#include <memory>

struct Function;

struct Scope {
    const std::map<std::string, std::unique_ptr<Expression>>* parameters = nullptr;
    std::map<std::string, std::unique_ptr<Function>> functions;

    const Scope* enclosingScope = nullptr;
    const Function& getFunction(std::string name) const;
};

struct InstructionBlock : public Expression {
    std::unique_ptr<Expression> returnExpression;
    int evaluate(const Scope& scope) const;
};

struct Function {
    std::string identifier;
    std::vector<std::string> parameters;
    std::unique_ptr<InstructionBlock> body;
};

struct FunctionCall : public Expression {
    std::string functionName;
    std::map<std::string, std::unique_ptr<Expression>> parameters;

    int evaluate(const Scope& scope) const; 
};