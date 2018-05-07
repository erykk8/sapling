#include "Function.h"
#include <iostream>

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
    std::cout << "ins block eval" << std::endl;
    return returnExpression->evaluate(scope);
}

int FunctionCall::evaluate(std::shared_ptr<Scope> scope) {
    if(!isSet) {
        parameterScope->enclosingScope = scope;
        if(isParameter) {
            value = scope->getValue(functionName)->evaluate(scope);
        }
        else {
            value = scope->getValue(functionName)->evaluate(parameterScope);
        }
        isSet = true;
    }
    return value;
}

FunctionCall::FunctionCall() {
    parameterScope = std::make_shared<Scope>();
}