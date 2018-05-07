#pragma once

#include "../token/Token.h"
#include "Expression.h"
#include "Function.h"
#include <vector>

struct ConditionalClause {
    LogicalExpression condition;
    InstructionBlock body;
};

struct IfBlock : Expression {
    int evaluate(std::shared_ptr<Scope> scope);

    ConditionalClause ifClause;
    std::vector<ConditionalClause> elifClauses;
    ConditionalClause elseClause;
};