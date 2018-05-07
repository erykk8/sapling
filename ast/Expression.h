#pragma once
#include "../token/Token.h"
#include <memory>

struct Scope;

struct Expression {
    virtual int evaluate(std::shared_ptr<Scope> scope) = 0;
};

struct IntValue : Expression {
    Token value;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct PowerRaising {
    std::shared_ptr<Expression> base;
    std::shared_ptr<PowerRaising> power;

    PowerRaising(int base = 1);
    ~PowerRaising() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct Multiplication {
    PowerRaising a;
    std::shared_ptr<Multiplication> b;
    bool isDivision;

    Multiplication(int a = 1);
    ~Multiplication() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct Addition {
    Multiplication a;
    std::shared_ptr<Addition> b;
    bool isSubtraction;

    Addition(int a = 0);
    ~Addition() {}

    int evaluate(std::shared_ptr<Scope> scope);
};

struct NumericExpression : Expression {
    Addition a;
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Comparison {
    std::shared_ptr<Expression> a;
    std::shared_ptr<Expression> b;

    TokenType::Type op;

    Comparison();
    ~Comparison() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Negation {
    Comparison a;
    bool isActuallyNegation;

    Negation();
    ~Negation() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Conjunction {
    Negation a;
    std::shared_ptr<Conjunction> b;

    Conjunction();
    ~Conjunction() {}
    int evaluate(std::shared_ptr<Scope> scope);
};

struct Disjunction {
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
    private:
        bool isSet = false;
        int value; 
};