#include "Program.h"
#include "Function.h"

Program::Program() {
    scope = std::make_shared<Scope>();
    scope->enclosingScope = nullptr;
}

int Program::evaluate() {
    // TODO - arguments to main possibly
    auto it = scope->functions.find("main");
    if(it == scope->functions.end()) {
        throw std::runtime_error("Undefined reference to main");
    }
    it->second->body.scope = scope;
    return it->second->body.evaluate();
}