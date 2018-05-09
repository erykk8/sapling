#include "Function.h"
#include <iostream>
#include <memory>

int InstructionBlock::evaluate() {
    returnExpression->scope = scope;
    return returnExpression->evaluate();
}

int FunctionCall::evaluate() {
    auto newScope = std::make_shared<Scope>();
    newScope->enclosingScope = scope;
    newScope->functions = scope->functions;
    newScope->parameters = parameters;

    std::cout << "evaluating " << functionName;
    std::cout << " in scope " << scope.get();
    std::cout << " within scope " << scope->enclosingScope.get() << std::endl;

    // evaluate parameters in the enclosing scope
    auto it = scope->parameters.find(functionName);
    if(it != scope->parameters.end()) {
        std::cout << "evaluating as parameter in enclosing scope" << std::endl;
        it->second->scope = scope->enclosingScope;
        return it->second->evaluate();
    }
    // evaluate function bodies in the new scope, with new parameter values sets
    auto it2 = scope->functions.find(functionName);
    if(it2 != scope->functions.end()) {
        InstructionBlock blockInstance = it2->second->body;
        blockInstance.scope = newScope;
        return blockInstance.evaluate();
    }

    throw std::runtime_error("Undefined reference to " + functionName);
}