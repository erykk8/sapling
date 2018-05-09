#pragma once
#include "../token/Token.h"
#include <memory>

struct Scope;

struct Expression {
    virtual int evaluate() = 0;
    std::shared_ptr<Scope> scope;
};

struct IntValue : public Expression {
    Token value;
    int evaluate();
};

struct PowerRaising : public Expression {
    std::shared_ptr<Expression> base;
    std::shared_ptr<PowerRaising> power;

    PowerRaising(int base = 1);
    ~PowerRaising() {}

    int evaluate();
};

struct Multiplication : public Expression {
    PowerRaising a;
    std::shared_ptr<Multiplication> b;
    bool isDivision;

    Multiplication(int a = 1);
    ~Multiplication() {}

    int evaluate();
};

struct Addition : public Expression {
    Multiplication a;
    std::shared_ptr<Addition> b;
    bool isSubtraction;

    Addition(int a = 0);
    ~Addition() {}

    int evaluate();
};

struct NumericExpression : public Expression {
    Addition a;
    int evaluate();
};

struct Comparison : public Expression {
    std::shared_ptr<Expression> a;
    std::shared_ptr<Expression> b;

    TokenType::Type op;

    Comparison();
    ~Comparison() {}
    int evaluate();
};

struct Negation : public Expression {
    Comparison a;
    bool isActuallyNegation;

    Negation();
    ~Negation() {}
    int evaluate();
};

struct Conjunction : public Expression {
    Negation a;
    std::shared_ptr<Conjunction> b;

    Conjunction();
    ~Conjunction() {}
    int evaluate();
};

struct Disjunction : public Expression {
    Conjunction a;
    std::shared_ptr<Disjunction> b;
    
    Disjunction();
    ~Disjunction() {}
    int evaluate();
};

class LogicalExpression : public Expression {
    public:
        Disjunction a;
        int evaluate();
        bool wasEvaluated = false;
        int value;
};