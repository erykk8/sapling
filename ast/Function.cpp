#include "Function.h"
#include <iostream>
#include <memory>

int InstructionBlock::evaluate(std::shared_ptr<Scope> scope) {
    return returnExpression->evaluate(scope);
}

int Function::evaluate(std::map<std::string, std::shared_ptr<Expression>> parameters, std::shared_ptr<Scope> evalScope) {
    scope = std::make_shared<Scope>();
    scope->functions = evalScope->functions;
    scope->parameters = parameters;

    return body.evaluate(scope);
}

int FunctionCall::evaluate(std::shared_ptr<Scope> scope) {
    auto it = scope->parameters.find(functionName);
    if(it != scope->parameters.end()) {
        return it->second->evaluate(scope->enclosingScope);
    }
    auto it2 = scope->functions.find(functionName);
    if(it2 != scope->functions.end()) {
        if(parameters.size() > 0) {
            return it2->second->evaluate(parameters, scope);
        }
        else {
            return it2->second->body.evaluate(scope);
        }
    }
}