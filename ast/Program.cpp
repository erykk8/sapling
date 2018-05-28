#include "Program.h"
#include "Function.h"

Program::Program() {
    scope = std::make_unique<Scope>();
    scope->enclosingScope = nullptr;
}

int Program::evaluate() const {
    auto it = scope->functions.find("main");
    if(it == scope->functions.end()) {
        throw std::runtime_error("Undefined reference to main");
    }
    return it->second->body->evaluate(*scope);
}