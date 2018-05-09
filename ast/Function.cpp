#include "Function.h"
#include <iostream>
#include <memory>

int InstructionBlock::evaluate(std::shared_ptr<Scope> scope) {
    return returnExpression->evaluate(scope);
}

int FunctionCall::evaluate(std::shared_ptr<Scope> scope) {
    auto newScope = std::make_shared<Scope>();
    newScope->enclosingScope = scope;
    newScope->functions = scope->functions;
    newScope->parameters = parameters;

    // evaluate parameters in the enclosing scope
    auto it = scope->parameters.find(functionName);
    if(it != scope->parameters.end()) {
        return it->second->evaluate(scope->enclosingScope);
    }
    // evaluate function bodies in the new scope, with new parameter values sets
    auto it2 = scope->functions.find(functionName);
    if(it2 != scope->functions.end()) {
        return it2->second->body.evaluate(newScope);
    }

    throw std::runtime_error("Undefined reference to " + functionName);
}