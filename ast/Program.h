#pragma once

#include "Function.h"
#include <memory>

struct Program {
    Program();
    ~Program() = default;
    std::shared_ptr<Scope> scope;
    int evaluate();
};