#pragma once
#include "../token/Token.h"
#include "Expression.h"
#include "Parameter.h"

#include <string>
#include <map>
#include <memory>

struct Function;

struct Scope {
        Scope() : enclosingScope(nullptr) {}
        ~Scope() = default;

        std::shared_ptr<Expression> getValue(std::string name);
        
        std::map<std::string, std::shared_ptr<Expression>> identifiers;
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
};

struct FunctionCall : Expression {
    FunctionCall();
    ~FunctionCall() = default;
    std::string functionName;
    std::shared_ptr<Scope> parameterScope;
    int evaluate(std::shared_ptr<Scope> scope);
};