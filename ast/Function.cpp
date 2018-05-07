#include "Function.h"

std::shared_ptr<Expression> Scope::getValue(std::string name) {
    auto it = identifiers.find(name);
    if(it != identifiers.end()) {
        return it->second;
    }

    auto it2 = functions.find(name);

    if(it2 != functions.end()) {
        return it2->second->body.returnExpression;
    }

    if(enclosingScope) {
        return enclosingScope->getValue(name);
    }

    throw std::runtime_error("Identifier " + name + " not found in current scope");
}

int InstructionBlock::evaluate(std::shared_ptr<Scope> scope) {
    return returnExpression->evaluate(scope);
}

int FunctionCall::evaluate(std::shared_ptr<Scope> scope) {
    parameterScope->enclosingScope = scope;
    return scope->getValue(functionName)->evaluate(parameterScope);
}

FunctionCall::FunctionCall() {
    parameterScope = std::make_shared<Scope>();
}