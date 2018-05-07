#include "Expression.h"
#include "../token/Token.h"
#include "Function.h"
#include <cmath>

using namespace TokenType;

int IntValue::evaluate(std::shared_ptr<Scope> scope) {
    return value.getInt();
}

int PowerRaising::evaluate(std::shared_ptr<Scope> scope) {
    if(!power) return base->evaluate(scope);
    return pow(base->evaluate(scope), power->evaluate(scope));
}

PowerRaising::PowerRaising(int base) : power(nullptr) {
    auto baseValue = new IntValue();
    baseValue->value.setInt(base);
    this->base = std::shared_ptr<Expression>(baseValue);
}

int Multiplication::evaluate(std::shared_ptr<Scope> scope) {
    if(!b) return a.evaluate(scope);
    if(isDivision) return a.evaluate(scope) / b->evaluate(scope);
    else return a.evaluate(scope) * b->evaluate(scope);
}

Multiplication::Multiplication(int a) : a(a), b(nullptr), isDivision(false) {
}

int Addition::evaluate(std::shared_ptr<Scope> scope) {
    if(!b) return a.evaluate(scope);
    if(isSubtraction) return a.evaluate(scope) - b->evaluate(scope);
    else return a.evaluate(scope) + b->evaluate(scope);
}

Addition::Addition(int a) : a(a), b(nullptr), isSubtraction(false) {
}

int NumericExpression::evaluate(std::shared_ptr<Scope> scope) {
    return a.evaluate(scope);
}

int Comparison::evaluate(std::shared_ptr<Scope> scope) {
    if(!b) {
        return a->evaluate(scope);
    }
    switch(op) {
        case LESS_THAN:
            return a->evaluate(scope) < b->evaluate(scope);
        case LESS_EQUAL:
            return a->evaluate(scope) <= b->evaluate(scope);
        case GREATER_THAN:
            return a->evaluate(scope) > b->evaluate(scope);
        case GREATER_EQUAL:
            return a->evaluate(scope) >= b->evaluate(scope);
        case EQUAL:
            return a->evaluate(scope) == b->evaluate(scope);
        case NOT_EQUAL:
            return a->evaluate(scope) != b->evaluate(scope);
    }
}

Comparison::Comparison() : b(nullptr) {
}

int Negation::evaluate(std::shared_ptr<Scope> scope) {
    if(!isActuallyNegation) {
        return a.evaluate(scope);
    }
    else {
        return !(bool)a.evaluate(scope);
    }
}

Negation::Negation() : isActuallyNegation(false) {
}

Conjunction::Conjunction() : b(nullptr) {
}

int Conjunction::evaluate(std::shared_ptr<Scope> scope) {
    if(!b) {
        return a.evaluate(scope);
    }
    else {
        return (bool)a.evaluate(scope) && (bool)b->evaluate(scope);
    }
}

Disjunction::Disjunction() : b(nullptr) {
}

int Disjunction::evaluate(std::shared_ptr<Scope> scope) {
    if(!b) {
        return a.evaluate(scope);
    }
    else {
        return (bool)a.evaluate(scope) || (bool)b->evaluate(scope);
    }
}

int LogicalExpression::evaluate(std::shared_ptr<Scope> scope) {
    if(!isSet) {
        value = a.evaluate(scope);
        isSet = true;
    }
    return value;
}