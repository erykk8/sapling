#pragma once

#include "../token/Token.h"
#include "Expression.h"
#include "Function.h"
#include <vector>
#include <memory>

struct ConditionalClause {
    std::unique_ptr<Expression> condition;
    std::unique_ptr<InstructionBlock> body;
};

struct IfBlock : public Expression {
    int evaluate(const Scope& scope) const;

    std::unique_ptr<ConditionalClause> ifClause;
    std::vector<std::unique_ptr<ConditionalClause>> elifClauses;
    std::unique_ptr<ConditionalClause> elseClause;
};