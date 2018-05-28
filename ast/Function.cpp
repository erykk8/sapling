#include "Function.h"
#include <iostream>
#include <memory>

int InstructionBlock::evaluate(const Scope& scope) const {
    return returnExpression->evaluate(scope);
}

int FunctionCall::evaluate(const Scope& scope) const {
    auto newScope = std::make_unique<Scope>();
    newScope->enclosingScope = &scope;
    newScope->parameters = &parameters;

    if(scope.parameters != nullptr) {
        auto it = scope.parameters->find(functionName);
        if(it != scope.parameters->end()) {
            // evaluate parameters in the enclosing scope
            return it->second->evaluate(*(scope.enclosingScope));
        }
    }
    
    // evaluate function bodies in the new scope, with new parameter values sets
    const Function& function = scope.getFunction(functionName);
    return function.body->evaluate(*newScope);
}

const Function& Scope::getFunction(std::string name) const {
    auto it = functions.find(name);
    if(it != functions.end()) {
        return *(it->second);
    }
    auto scope = enclosingScope;
    while(scope != nullptr) {
        it = scope->functions.find(name);
        if(it != scope->functions.end()) {
            return *(it->second);
        }
        scope = scope->enclosingScope;
    }
    throw std::runtime_error("Undefined reference to " + name);
}