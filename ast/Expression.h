#pragma once
#include "../token/Token.h"
#include <memory>

struct Scope;

struct Expression {
    virtual int evaluate(const Scope& scope) const = 0;
};

struct IntValue : public Expression {
    int value;
    int evaluate(const Scope& scope) const;

    IntValue(int value = 0);
    ~IntValue() = default;
};

struct PowerRaising : public Expression {
    std::unique_ptr<Expression> base;
    std::unique_ptr<PowerRaising> power;

    PowerRaising(int base = 1);
    ~PowerRaising() = default;

    int evaluate(const Scope& scope) const;
};

struct Multiplication : public Expression {
    std::unique_ptr<PowerRaising> a;
    std::unique_ptr<Multiplication> b;

    enum Type {
        MULTIPLY, DIVIDE, MODULO
    };

    Type type;

    Multiplication(int a = 1);
    ~Multiplication() = default;

    int evaluate(const Scope& scope) const;
};

struct Addition : public Expression {
    std::unique_ptr<Multiplication> a;
    std::unique_ptr<Addition> b;
    bool isSubtraction;

    Addition(int a = 0);
    ~Addition() = default;

    int evaluate(const Scope& scope) const;
};

struct NumericExpression : public Expression {
    std::unique_ptr<Addition> a;
    int evaluate(const Scope& scope) const;

    NumericExpression();
    ~NumericExpression() = default;
};

struct Comparison : public Expression {
    std::unique_ptr<Expression> a;
    std::unique_ptr<Expression> b;

    enum Type {
        LESS_THAN, GREATER_THAN,
        LESS_EQUAL, GREATER_EQUAL,
        EQUAL, NOT_EQUAL
    };

    Type op;

    Comparison();
    ~Comparison() = default;
    int evaluate(const Scope& scope) const;
};

struct Negation : public Expression {
    std::unique_ptr<Comparison> a;
    bool isActuallyNegation;

    Negation();
    ~Negation() = default;
    int evaluate(const Scope& scope) const;
};

struct Conjunction : public Expression {
    std::unique_ptr<Negation> a;
    std::unique_ptr<Conjunction> b;

    Conjunction();
    ~Conjunction() = default;
    int evaluate(const Scope& scope) const;
};

struct Disjunction : public Expression {
    std::unique_ptr<Conjunction> a;
    std::unique_ptr<Disjunction> b;
    
    Disjunction();
    ~Disjunction() = default;
    int evaluate(const Scope& scope) const;
};

struct LogicalExpression : public Expression {
    std::unique_ptr<Disjunction> a;
    int evaluate(const Scope& scope) const;

    LogicalExpression();
    ~LogicalExpression() = default;
};