#include "IfBlock.h"
#include "Function.h"

int IfBlock::evaluate() {
    ifClause.condition.scope = scope;
    if(ifClause.condition.evaluate()) {
        ifClause.body.scope = scope;
        return ifClause.body.evaluate();
    }
    else if(elifClauses.size() > 0) {
        for(auto elifClause : elifClauses) {
            elifClause.condition.scope = scope;
            if(elifClause.condition.evaluate()) {
                elifClause.body.scope = scope;
                return elifClause.body.evaluate();
            }
        }
    }
    elseClause.body.scope = scope;
    return elseClause.body.evaluate();
}