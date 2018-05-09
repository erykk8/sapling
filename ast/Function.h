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

struct InstructionBlock : public Expression {
    std::shared_ptr<Expression> returnExpression;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Function {
    TokenType::Type returnType;
    std::string identifier;
    std::vector<Parameter> parameters;
    InstructionBlock body;
};

struct FunctionCall : public Expression {
    std::string functionName;
    std::map<std::string, std::shared_ptr<Expression>> parameters;

    int evaluate(std::shared_ptr<Scope> scope); 
};