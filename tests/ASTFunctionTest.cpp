#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ASTExpressionTest"
#include <boost/test/unit_test.hpp>
#include "../ast/Function.h"
#include "../ast/IfBlock.h"

BOOST_AUTO_TEST_SUITE(ASTFunctionTest)

BOOST_AUTO_TEST_CASE(instruction_block) {
    Scope s;
    InstructionBlock i;
    i.returnExpression = std::make_unique<IntValue>(4);
    BOOST_CHECK_EQUAL(i.evaluate(s), 4);
}

BOOST_AUTO_TEST_CASE(conditional_clause) {
    Scope s;
    ConditionalClause c;
    c.condition = std::make_unique<IntValue>(1);
    c.body = std::make_unique<InstructionBlock>();
    c.body->returnExpression = std::make_unique<IntValue>(12);

    BOOST_ASSERT(c.condition->evaluate(s));
    BOOST_CHECK_EQUAL(c.body->evaluate(s), 12);
}

BOOST_AUTO_TEST_CASE(if_else_block) {
    Scope s;
    IfBlock i;
    i.ifClause = std::make_unique<ConditionalClause>();
    i.ifClause->condition = std::make_unique<IntValue>(1);
    i.ifClause->body = std::make_unique<InstructionBlock>();
    i.ifClause->body->returnExpression = std::make_unique<IntValue>(42);

    i.elseClause->body = std::make_unique<InstructionBlock>();
    i.elseClause->body->returnExpression = std::make_unique<IntValue>(33);

    BOOST_CHECK_EQUAL(i.evaluate(s), 42);

    i.ifClause->condition = std::make_unique<IntValue>(0);
    BOOST_CHECK_EQUAL(i.evaluate(s), 33);
}

BOOST_AUTO_TEST_CASE(if_elif_else_block) {
    Scope s;
    IfBlock i;
    i.ifClause = std::make_unique<ConditionalClause>();
    i.ifClause->condition = std::make_unique<IntValue>(0);
    i.ifClause->body = std::make_unique<InstructionBlock>();
    i.ifClause->body->returnExpression = std::make_unique<IntValue>(42);

    i.elifClauses.push_back(std::move(std::make_unique<ConditionalClause>()));
    i.elifClauses[0]->condition = std::make_unique<IntValue>(0);
    
    i.elifClauses.push_back(std::move(std::make_unique<ConditionalClause>()));
    i.elifClauses[1]->condition = std::make_unique<IntValue>(1);
    i.elifClauses[1]->body = std::make_unique<InstructionBlock>();
    i.elifClauses[1]->body->returnExpression = std::make_unique<IntValue>(72);

    i.elseClause->body = std::make_unique<InstructionBlock>();
    i.elseClause->body->returnExpression = std::make_unique<IntValue>(33);

    BOOST_CHECK_EQUAL(i.evaluate(s), 72);
}

BOOST_AUTO_TEST_SUITE_END()