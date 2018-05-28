#include "IfBlock.h"
#include "Function.h"

int IfBlock::evaluate(const Scope& scope) const {
    if(ifClause->condition->evaluate(scope)) {
        return ifClause->body->evaluate(scope);
    }
    for(auto const& elifClause : elifClauses) {
        if(elifClause->condition->evaluate(scope)) {
            return elifClause->body->evaluate(scope);
        }
    }
    return elseClause->body->evaluate(scope);
}