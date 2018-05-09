#include "IfBlock.h"
#include "Function.h"

int IfBlock::evaluate(std::shared_ptr<Scope> scope) {
    if(ifClause.condition.evaluate(scope)) {
        return ifClause.body.evaluate(scope);
    }
    else if(elifClauses.size() > 0) {
        for(auto elifClause : elifClauses) {
            if(elifClause.condition.evaluate(scope)) {
                return elifClause.body.evaluate(scope);
            }
        }
    }
    return elseClause.body.evaluate(scope);
}