#include "Program.h"
#include "Function.h"

Program::Program() {
    scope = std::make_shared<Scope>();
}

int Program::evaluate() {
    // TODO - arguments to main possibly
    auto it = scope->functions.find("main");
    if(it == scope->functions.end()) {
        throw std::runtime_error("Undefined reference to main");
    }
    return it->second->body.evaluate(scope);
}