#pragma once

#include "Function.h"
#include <memory>

struct Program {
    Program();
    ~Program() = default;
    std::unique_ptr<Scope> scope;
    int evaluate() const;
};