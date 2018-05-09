#pragma once
#include "../token/Token.h"
#include <memory>

struct Scope;

struct Expression {
    virtual int evaluate(std::shared_ptr<Scope> scope) = 0;
};

struct IntValue : public Expression {
    Token value;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct PowerRaising : public Expression {
    std::shared_ptr<Expression> base;
    std::shared_ptr<PowerRaising> power;

    PowerRaising(int base = 1);
    ~PowerRaising() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct Multiplication : public Expression {
    PowerRaising a;
    std::shared_ptr<Multiplication> b;
    TokenType::Type type;

    Multiplication(int a = 1);
    ~Multiplication() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct Addition : public Expression {
    Multiplication a;
    std::shared_ptr<Addition> b;
    bool isSubtraction;

    Addition(int a = 0);
    ~Addition() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct NumericExpression : public Expression {
    Addition a;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Comparison : public Expression {
    std::shared_ptr<Expression> a;
    std::shared_ptr<Expression> b;

    TokenType::Type op;

    Comparison();
    ~Comparison() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Negation : public Expression {
    Comparison a;
    bool isActuallyNegation;

    Negation();
    ~Negation() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Conjunction : public Expression {
    Negation a;
    std::shared_ptr<Conjunction> b;

    Conjunction();
    ~Conjunction() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Disjunction : public Expression {
    Conjunction a;
    std::shared_ptr<Disjunction> b;
    
    Disjunction();
    ~Disjunction() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

class LogicalExpression : public Expression {
    public:
        Disjunction a;
        int evaluate(std::shared_ptr<Scope> scope);
        bool wasEvaluated = false;
        int value;
};