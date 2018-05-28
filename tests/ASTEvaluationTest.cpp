#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ASTExpressionTest"
#include <boost/test/unit_test.hpp>
#include "../ast/Expression.h"
#include "../ast/Function.h"

BOOST_AUTO_TEST_SUITE(ASTExpressionTest)

BOOST_AUTO_TEST_CASE(int_value) {
    Scope s;
    IntValue i;
    i.value = 30;
    BOOST_CHECK_EQUAL(i.evaluate(s), 30);
}

BOOST_AUTO_TEST_CASE(power_raising_to_one) {
    Scope s;
    PowerRaising p(42);
    BOOST_CHECK_EQUAL(p.evaluate(s), 42);
}

BOOST_AUTO_TEST_CASE(power_raising_to_x) {
    Scope s;
    PowerRaising p(2);
    p.power = std::make_unique<PowerRaising>(10);
    BOOST_CHECK_EQUAL(p.evaluate(s), 1024);
}

BOOST_AUTO_TEST_CASE(multiplication) {
    Scope s;
    Multiplication m(11);
    m.b = std::make_unique<Multiplication>(12);
    BOOST_CHECK_EQUAL(m.evaluate(s), 11*12);
}

BOOST_AUTO_TEST_CASE(division) {
    Scope s;
    Multiplication m(20);
    m.b = std::make_unique<Multiplication>(5);
    m.type = Multiplication::DIVIDE;
    BOOST_CHECK_EQUAL(m.evaluate(s), 20/5);
}

BOOST_AUTO_TEST_CASE(modulo) {
    Scope s;
    Multiplication m(8);
    m.b = std::make_unique<Multiplication>(3);
    m.type = Multiplication::MODULO;
    BOOST_CHECK_EQUAL(m.evaluate(s), 8%3);
}

BOOST_AUTO_TEST_CASE(addition) {
    Scope s;
    Addition a(5);
    a.b = std::make_unique<Addition>(7);
    BOOST_CHECK_EQUAL(a.evaluate(s), 5+7);
}

BOOST_AUTO_TEST_CASE(subtraction) {
    Scope s;
    Addition a(5);
    a.b = std::make_unique<Addition>(7);
    a.isSubtraction = true;
    BOOST_CHECK_EQUAL(a.evaluate(s), 5-7);
}

BOOST_AUTO_TEST_CASE(numeric_expression) {
    Scope s;
    NumericExpression n;
    n.a = std::make_unique<Addition>(10);
    BOOST_CHECK_EQUAL(n.evaluate(s), 10);
}

BOOST_AUTO_TEST_CASE(comparison_lt) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::LESS_THAN;
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(!c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(comparison_le) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::LESS_EQUAL;
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(comparison_gt) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::GREATER_THAN;
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(!c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(comparison_ge) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::GREATER_EQUAL;
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(comparison_eq) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::EQUAL;
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(!c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(comparison_ne) {
    Scope s;
    Comparison c;
    c.a = std::make_unique<IntValue>(10);
    c.b = std::make_unique<IntValue>(20);
    c.op = Comparison::NOT_EQUAL;
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(5);
    BOOST_ASSERT(c.evaluate(s));

    c.b = std::make_unique<IntValue>(10);
    BOOST_ASSERT(!c.evaluate(s));
}

BOOST_AUTO_TEST_CASE(negation) {
    Scope s;
    Negation n;
    n.isActuallyNegation = true;
    n.a = std::make_unique<Comparison>();
    n.a->a = std::make_unique<IntValue>(5);
}

std::unique_ptr<Negation> makeNegation(int value, bool isActuallyNegation = false) {
    auto n = std::make_unique<Negation>();
    n->isActuallyNegation = isActuallyNegation;
    n->a = std::make_unique<Comparison>();
    n->a->a = std::make_unique<IntValue>(value);
    return n;
}

BOOST_AUTO_TEST_CASE(conjunction) {
    Scope s;
    Conjunction c;
    c.a = std::move(makeNegation(0));
    c.b = std::make_unique<Conjunction>();
    c.b->a = std::move(makeNegation(0));
    BOOST_ASSERT(!c.evaluate(s));

    c.a->isActuallyNegation = true;
    BOOST_ASSERT(!c.evaluate(s));

    c.b->a->isActuallyNegation = true;
    BOOST_ASSERT(c.evaluate(s));
}

std::unique_ptr<Conjunction> makeConjunction(int a, int b = 1) {
    auto c = std::make_unique<Conjunction>();
    c->a = std::move(makeNegation(a));
    c->b = std::make_unique<Conjunction>();
    c->b->a = std::move(makeNegation(b));
    return c;
}

BOOST_AUTO_TEST_CASE(disjunction) {
    Scope s;
    Disjunction d;
    d.a = std::move(makeConjunction(1));
    d.b = std::make_unique<Disjunction>();
    d.b->a = std::move(makeConjunction(1));
    BOOST_ASSERT(d.evaluate(s));

    d.b->a = std::move(makeConjunction(0));
    BOOST_ASSERT(d.evaluate(s));

    d.a = std::move(makeConjunction(0));
    BOOST_ASSERT(!d.evaluate(s));
}

BOOST_AUTO_TEST_CASE(logical_expression) {
    Scope s;
    LogicalExpression l;

    l.a = std::make_unique<Disjunction>();
    l.a->a = std::move(makeConjunction(1));

    BOOST_ASSERT(l.evaluate(s));
}

BOOST_AUTO_TEST_SUITE_END()