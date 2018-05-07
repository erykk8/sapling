#pragma once
#include "../token/Token.h"
#include "Expression.h"
#include "Parameter.h"

#include <string>
#include <map>
#include <memory>

struct Function;

struct Scope {
        std::map<std::string, std::shared_ptr<Expression>> parameters;
        std::map<std::string, std::shared_ptr<Function>> functions;

        std::shared_ptr<Scope> enclosingScope;
};

struct InstructionBlock {
    std::shared_ptr<Expression> returnExpression;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Function {
    TokenType::Type returnType;
    std::string identifier;
    std::vector<Parameter> parameters;
    InstructionBlock body;
    std::shared_ptr<Scope> scope;

    int evaluate(std::map<std::string, std::shared_ptr<Expression>> parameters, std::shared_ptr<Scope> scope);
};

struct FunctionCall : Expression {
    std::string functionName;
    std::map<std::string, std::shared_ptr<Expression>> parameters;

    int evaluate(std::shared_ptr<Scope> scope); 
};