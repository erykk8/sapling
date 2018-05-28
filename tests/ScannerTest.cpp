#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ScannerTest"
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../scanner/IO.h"
#include "../scanner/Scanner.h"

BOOST_AUTO_TEST_SUITE(ScannerTest)

std::unique_ptr<Scanner> makeScannerFromString(std::string string) {
    auto ss = std::make_shared<std::stringstream>();
    *ss << string;
    std::unique_ptr<InputReader> sr(new StreamReader(ss));
    return std::make_unique<Scanner>(std::move(sr));
}

BOOST_AUTO_TEST_CASE(empty_input_returns_EOT) {
    auto s = makeScannerFromString("");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::EOT);
}

BOOST_AUTO_TEST_CASE(last_token_is_EOT) {
    auto s = makeScannerFromString("Int");
    s->getNextToken();
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::EOT);
}

BOOST_AUTO_TEST_CASE(ignore_leading_whitespace) {
    auto s = makeScannerFromString("     \t\t\t     ");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::EOT);
}

BOOST_AUTO_TEST_CASE(if_keyword) {
    auto s = makeScannerFromString("if");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::IF);
}

BOOST_AUTO_TEST_CASE(elif_keyword) {
    auto s = makeScannerFromString("elif");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::ELIF);
}

BOOST_AUTO_TEST_CASE(else_keyword) {
    auto s = makeScannerFromString("else");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::ELSE);
}

BOOST_AUTO_TEST_CASE(let) {
    auto s = makeScannerFromString("let");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::LET);
}

BOOST_AUTO_TEST_CASE(return_arrow) {
    auto s = makeScannerFromString("=>");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::RETURN_ARROW);
}

BOOST_AUTO_TEST_CASE(return_keyword) {
    auto s = makeScannerFromString("return");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::RETURN);
}

BOOST_AUTO_TEST_CASE(positive_int_constant) {
    auto s = makeScannerFromString("34");
    Token t1 = s->getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), TokenType::INT_VALUE);
    BOOST_CHECK_EQUAL(t1.getInt(), 34);
}

BOOST_AUTO_TEST_CASE(negative_int_constant) {
    auto s = makeScannerFromString("-139");
    Token t1 = s->getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), TokenType::INT_VALUE);
    BOOST_CHECK_EQUAL(t1.getInt(), -139);
}

BOOST_AUTO_TEST_CASE(true_constant) {
    auto s = makeScannerFromString("True");
    Token t1 = s->getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), TokenType::INT_VALUE);
    BOOST_CHECK(t1.getInt());
}

BOOST_AUTO_TEST_CASE(false_constant) {
    auto s = makeScannerFromString("False");
    Token t1 = s->getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), TokenType::INT_VALUE);
    BOOST_CHECK(!t1.getInt());
}

BOOST_AUTO_TEST_CASE(curly_brace_open) {
    auto s = makeScannerFromString("{");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::CURLY_BRACE_OPEN);
}

BOOST_AUTO_TEST_CASE(curly_brace_close) {
    auto s = makeScannerFromString("}");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::CURLY_BRACE_CLOSE);
}

BOOST_AUTO_TEST_CASE(brace_open) {
    auto s = makeScannerFromString("(");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::BRACE_OPEN);
}

BOOST_AUTO_TEST_CASE(brace_close) {
    auto s = makeScannerFromString(")");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::BRACE_CLOSE);
}

BOOST_AUTO_TEST_CASE(assignment_operator) {
    auto s = makeScannerFromString(" = ");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::ASSIGNMENT_OPERATOR);
}

BOOST_AUTO_TEST_CASE(power_operator) {
    auto s = makeScannerFromString("^");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::POWER);
}

BOOST_AUTO_TEST_CASE(multiply_operator) {
    auto s = makeScannerFromString("*");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::MULTIPLY);
}

BOOST_AUTO_TEST_CASE(divide_operator) {
    auto s = makeScannerFromString("/");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::DIVIDE);
}

BOOST_AUTO_TEST_CASE(add_operator) {
    auto s = makeScannerFromString("+");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::ADD);
}

BOOST_AUTO_TEST_CASE(subtract_operator) {
    auto s = makeScannerFromString(" - ");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::SUBTRACT);
}

BOOST_AUTO_TEST_CASE(less_than) {
    auto s = makeScannerFromString("<");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::LESS_THAN);
}

BOOST_AUTO_TEST_CASE(greater_than) {
    auto s = makeScannerFromString(">");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::GREATER_THAN);
}

BOOST_AUTO_TEST_CASE(less_equal) {
    auto s = makeScannerFromString("<=");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::LESS_EQUAL);
}

BOOST_AUTO_TEST_CASE(greater_equal) {
    auto s = makeScannerFromString(">=");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::GREATER_EQUAL);
}

BOOST_AUTO_TEST_CASE(equal) {
    auto s = makeScannerFromString("==");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::EQUAL);
}

BOOST_AUTO_TEST_CASE(not_equal) {
    auto s = makeScannerFromString("!=");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::NOT_EQUAL);
}

BOOST_AUTO_TEST_CASE(and_keyword) {
    auto s = makeScannerFromString("and");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::AND);
}

BOOST_AUTO_TEST_CASE(not_keyword) {
    auto s = makeScannerFromString("not");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::NOT);
}

BOOST_AUTO_TEST_CASE(or_keyword) {
    auto s = makeScannerFromString("or");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::OR);
}

BOOST_AUTO_TEST_CASE(identifier) {
    auto s = makeScannerFromString("functionName_123");
    Token t = s->getNextToken();
    BOOST_CHECK_EQUAL(t, TokenType::IDENTIFIER);
    BOOST_CHECK_EQUAL(t.getString(), "functionName_123");
}

BOOST_AUTO_TEST_CASE(comma) {
    auto s = makeScannerFromString(",");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::COMMA);
}

BOOST_AUTO_TEST_CASE(skip_comments) {
    auto s = makeScannerFromString("let x\n# a comment\n# another comment");
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::LET);
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::IDENTIFIER);
    BOOST_CHECK_EQUAL(s->getNextToken(), TokenType::EOT);
}

BOOST_AUTO_TEST_CASE(fail_to_parse_unused_characters) {
    std::vector<std::string> chars = {"@", "\\", "&", "|", "?", "~", "`", "'", "$", ";"};
    for (auto character: chars) {
        auto s = makeScannerFromString(character);
        BOOST_CHECK_THROW(s->getNextToken(), std::runtime_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()