#include "Expression.h"
#include "../token/Token.h"
#include "Function.h"
#include <cmath>
#include <iostream>

using namespace TokenType;

IntValue::IntValue(int value) : value(value) {}

int IntValue::evaluate(const Scope& scope) const {
    return value;
}

int PowerRaising::evaluate(const Scope& scope) const {
    if(!power) return base->evaluate(scope);
    return pow(base->evaluate(scope), power->evaluate(scope));
}

PowerRaising::PowerRaising(int base) : power(nullptr) {
    auto baseValue = new IntValue();
    baseValue->value = base;
    this->base = std::unique_ptr<Expression>(baseValue);
}

int Multiplication::evaluate(const Scope& scope) const {
    if(!b) return a->evaluate(scope);
    switch(type) {
        case MULTIPLY:
            return a->evaluate(scope) * b->evaluate(scope);
        case DIVIDE:
            return a->evaluate(scope) / b->evaluate(scope);
        case MODULO:
            return a->evaluate(scope) % b->evaluate(scope);
    }
}

Multiplication::Multiplication(int a) : b(nullptr), type(MULTIPLY) {
    this->a = std::make_unique<PowerRaising>(a);
}

int Addition::evaluate(const Scope& scope) const {
    if(!b) return a->evaluate(scope);
    if(isSubtraction) return a->evaluate(scope) - b->evaluate(scope);
    else return a->evaluate(scope) + b->evaluate(scope);
}

Addition::Addition(int a) : b(nullptr), isSubtraction(false) {
    this->a = std::make_unique<Multiplication>(a);
}

int NumericExpression::evaluate(const Scope& scope) const {
    return a->evaluate(scope);
}

int Comparison::evaluate(const Scope& scope) const {
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

Comparison::Comparison() : a(nullptr), b(nullptr) {
}

int Negation::evaluate(const Scope& scope) const {
    if(!isActuallyNegation) {
        return a->evaluate(scope);
    }
    else {
        return !(a->evaluate(scope));
    }
}

Negation::Negation() : a(nullptr), isActuallyNegation(false) {
}

Conjunction::Conjunction() : a(nullptr), b(nullptr) {
}

int Conjunction::evaluate(const Scope& scope) const {
    if(!b) {
        return a->evaluate(scope);
    }
    else {
        return a->evaluate(scope) && b->evaluate(scope);
    }
}

Disjunction::Disjunction() : a(nullptr), b(nullptr) {
}

int Disjunction::evaluate(const Scope& scope) const {
    if(!b) {
        return a->evaluate(scope);
    }
    else {
        return a->evaluate(scope) || b->evaluate(scope);
    }
}

int LogicalExpression::evaluate(const Scope& scope) const {
    return a->evaluate(scope);
}

NumericExpression::NumericExpression() : a(nullptr) {
}

LogicalExpression::LogicalExpression() : a(nullptr) {
}