#include "Expression.h"
#include "../token/Token.h"
#include "Function.h"
#include <cmath>
#include <iostream>

using namespace TokenType;

int IntValue::evaluate() {
    std::cout << "evaluating value " << value.getInt() << std::endl;
    return value.getInt();
}

int PowerRaising::evaluate() {
    base->scope = scope;
    if(!power) return base->evaluate();
    power->scope = scope;
    return pow(base->evaluate(), power->evaluate());
}

PowerRaising::PowerRaising(int base) : power(nullptr) {
    auto baseValue = new IntValue();
    baseValue->value.setInt(base);
    this->base = std::shared_ptr<Expression>(baseValue);
}

int Multiplication::evaluate() {
    a.scope = scope;
    if(!b) return a.evaluate();
    b->scope = scope;
    if(isDivision) return a.evaluate() / b->evaluate();
    else return a.evaluate() * b->evaluate();
}

Multiplication::Multiplication(int a) : a(a), b(nullptr), isDivision(false) {
}

int Addition::evaluate() {
    a.scope = scope;
    if(!b) return a.evaluate();
    b->scope = scope;
    if(isSubtraction) return a.evaluate() - b->evaluate();
    else return a.evaluate() + b->evaluate();
}

Addition::Addition(int a) : a(a), b(nullptr), isSubtraction(false) {
}

int NumericExpression::evaluate() {
    a.scope = scope;
    return a.evaluate();
}

int Comparison::evaluate() {
    a->scope = scope;
    if(!b) {
        return a->evaluate();
    }
    b->scope = scope;
    switch(op) {
        case LESS_THAN:
            return a->evaluate() < b->evaluate();
        case LESS_EQUAL:
            return a->evaluate() <= b->evaluate();
        case GREATER_THAN:
            return a->evaluate() > b->evaluate();
        case GREATER_EQUAL:
            return a->evaluate() >= b->evaluate();
        case EQUAL:
            return a->evaluate() == b->evaluate();
        case NOT_EQUAL:
            return a->evaluate() != b->evaluate();
    }
}

Comparison::Comparison() : b(nullptr) {
}

int Negation::evaluate() {
    a.scope = scope;
    if(!isActuallyNegation) {
        return a.evaluate();
    }
    else {
        return !(bool)a.evaluate();
    }
}

Negation::Negation() : isActuallyNegation(false) {
}

Conjunction::Conjunction() : b(nullptr) {
}

int Conjunction::evaluate() {
    a.scope = scope;
    if(!b) {
        return a.evaluate();
    }
    else {
        b->scope = scope;
        return (bool)a.evaluate() && (bool)b->evaluate();
    }
}

Disjunction::Disjunction() : b(nullptr) {
}

int Disjunction::evaluate() {
    a.scope = scope;
    if(!b) {
        return a.evaluate();
    }
    else {
        b->scope = scope;
        return (bool)a.evaluate() || (bool)b->evaluate();
    }
}

int LogicalExpression::evaluate() {
    a.scope = scope;
    value = a.evaluate();
    std::cout << " logical expression value = " << value << std::endl;
    return value;
}
    