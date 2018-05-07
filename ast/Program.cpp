#include "Program.h"

int Program::evaluate() {
    // TODO - arguments to main possibly
    functions["main"]->body.evaluate(std::shared_ptr<Scope>(this));
}