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

Scanner makeScannerFromString(std::string string) {
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    *ss << string;
    std::shared_ptr<StreamReader> sr(new StreamReader(ss));
    return Scanner(sr);
}

BOOST_AUTO_TEST_CASE(empty_input_returns_EOT) {
    Scanner s = makeScannerFromString("");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(last_token_is_EOT) {
    Scanner s = makeScannerFromString("Int");
    s.getNextToken();
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(ignore_leading_whitespace) {
    Scanner s = makeScannerFromString("     \t\t\t     ");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(if_keyword) {
    Scanner s = makeScannerFromString("if");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::IF);
}

BOOST_AUTO_TEST_CASE(elif_keyword) {
    Scanner s = makeScannerFromString("elif");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ELIF);
}

BOOST_AUTO_TEST_CASE(else_keyword) {
    Scanner s = makeScannerFromString("else");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ELSE);
}

BOOST_AUTO_TEST_CASE(int_type) {
    Scanner s = makeScannerFromString("Int");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::INT_TYPE);
}

BOOST_AUTO_TEST_CASE(real_type) {
    Scanner s = makeScannerFromString("Real");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::REAL_TYPE);
}

BOOST_AUTO_TEST_CASE(bool_type) {
    Scanner s = makeScannerFromString("Bool");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::BOOL_TYPE);
}

BOOST_AUTO_TEST_CASE(string_type) {
    Scanner s = makeScannerFromString("String");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::STRING_TYPE);
}

BOOST_AUTO_TEST_CASE(void_type) {
    Scanner s = makeScannerFromString("Void");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::VOID_TYPE);
}

BOOST_AUTO_TEST_CASE(return_arrow) {
    Scanner s = makeScannerFromString("=>");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::RETURN_ARROW);
}

BOOST_AUTO_TEST_CASE(return_keyword) {
    Scanner s = makeScannerFromString("return");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::RETURN);
}

BOOST_AUTO_TEST_CASE(positive_int_constant) {
    Scanner s = makeScannerFromString("34");
    Token t1 = s.getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::INT_VALUE);
    BOOST_CHECK_EQUAL(t1.getInt(), 34);
}

BOOST_AUTO_TEST_CASE(negative_int_constant) {
    Scanner s = makeScannerFromString("-139");
    Token t1 = s.getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::INT_VALUE);
    BOOST_CHECK_EQUAL(t1.getInt(), -139);
}

BOOST_AUTO_TEST_CASE(true_constant) {
    Scanner s = makeScannerFromString("True");
    Token t1 = s.getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::BOOL_VALUE);
    BOOST_CHECK(t1.getBool());
}

BOOST_AUTO_TEST_CASE(false_constant) {
    Scanner s = makeScannerFromString("False");
    Token t1 = s.getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::BOOL_VALUE);
    BOOST_CHECK(!t1.getBool());
}

BOOST_AUTO_TEST_CASE(big_real_constant) {
    double real = 1024.33333333333;
    std::stringstream ss;
    ss << real;
    Scanner s = makeScannerFromString(ss.str());
    Token t = s.getNextToken();
    BOOST_CHECK_EQUAL(t, Token::REAL_VALUE);
    BOOST_CHECK_CLOSE(t.getReal(), real, 0.1);
}

BOOST_AUTO_TEST_CASE(small_real_constant) {
    double real = 0.75;
    std::stringstream ss;
    ss << real;
    Scanner s = makeScannerFromString(ss.str());
    Token t = s.getNextToken();
    BOOST_CHECK_EQUAL(t, Token::REAL_VALUE);
    BOOST_CHECK_CLOSE(t.getReal(), real, 0.1);
}

BOOST_AUTO_TEST_CASE(negative_real_constant) {
    double real = -0.03;
    std::stringstream ss;
    ss << real;
    Scanner s = makeScannerFromString(ss.str());
    Token t = s.getNextToken();
    BOOST_CHECK_EQUAL(t, Token::REAL_VALUE);
    BOOST_CHECK_CLOSE(t.getReal(), real, 0.1);
}


BOOST_AUTO_TEST_CASE(string_constant) {
    std::string text = "a string";
    Scanner s = makeScannerFromString("\"" + text + "\"");

    Token str = s.getNextToken();

    BOOST_CHECK_EQUAL(str, Token::STRING_VALUE);
    BOOST_CHECK_EQUAL(str.getString(), text);
}

BOOST_AUTO_TEST_CASE(curly_brace_open) {
    Scanner s = makeScannerFromString("{");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::CURLY_BRACE_OPEN);
}

BOOST_AUTO_TEST_CASE(curly_brace_close) {
    Scanner s = makeScannerFromString("}");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::CURLY_BRACE_CLOSE);
}

BOOST_AUTO_TEST_CASE(brace_open) {
    Scanner s = makeScannerFromString("(");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::BRACE_OPEN);
}

BOOST_AUTO_TEST_CASE(brace_close) {
    Scanner s = makeScannerFromString(")");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::BRACE_CLOSE);
}

BOOST_AUTO_TEST_CASE(square_brace_open) {
    Scanner s = makeScannerFromString("[");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::SQUARE_BRACE_OPEN);
}

BOOST_AUTO_TEST_CASE(square_brace_close) {
    Scanner s = makeScannerFromString("]");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::SQUARE_BRACE_CLOSE);
}

BOOST_AUTO_TEST_CASE(assignment_operator) {
    Scanner s = makeScannerFromString(" = ");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ASSIGNMENT_OPERATOR);
}

BOOST_AUTO_TEST_CASE(power_operator) {
    Scanner s = makeScannerFromString("^");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::POWER);
}

BOOST_AUTO_TEST_CASE(multiply_operator) {
    Scanner s = makeScannerFromString("*");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::MULTIPLY);
}

BOOST_AUTO_TEST_CASE(divide_operator) {
    Scanner s = makeScannerFromString("/");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::DIVIDE);
}

BOOST_AUTO_TEST_CASE(int_divide_operator) {
    Scanner s = makeScannerFromString("//");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::INT_DIVIDE);
}

BOOST_AUTO_TEST_CASE(add_operator) {
    Scanner s = makeScannerFromString("+");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ADD);
}

BOOST_AUTO_TEST_CASE(subtract_operator) {
    Scanner s = makeScannerFromString(" - ");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::SUBTRACT);
}

BOOST_AUTO_TEST_CASE(less_than) {
    Scanner s = makeScannerFromString("<");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::LESS_THAN);
}

BOOST_AUTO_TEST_CASE(greater_than) {
    Scanner s = makeScannerFromString(">");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::GREATER_THAN);
}

BOOST_AUTO_TEST_CASE(less_equal) {
    Scanner s = makeScannerFromString("<=");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::LESS_EQUAL);
}

BOOST_AUTO_TEST_CASE(greater_equal) {
    Scanner s = makeScannerFromString(">=");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::GREATER_EQUAL);
}

BOOST_AUTO_TEST_CASE(equal) {
    Scanner s = makeScannerFromString("==");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EQUAL);
}

BOOST_AUTO_TEST_CASE(not_equal) {
    Scanner s = makeScannerFromString("!=");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::NOT_EQUAL);
}

BOOST_AUTO_TEST_CASE(and_keyword) {
    Scanner s = makeScannerFromString("and");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::AND);
}

BOOST_AUTO_TEST_CASE(not_keyword) {
    Scanner s = makeScannerFromString("not");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::NOT);
}

BOOST_AUTO_TEST_CASE(or_keyword) {
    Scanner s = makeScannerFromString("or");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::OR);
}

BOOST_AUTO_TEST_CASE(identifier) {
    Scanner s = makeScannerFromString("functionName_123");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::IDENTIFIER);
}

BOOST_AUTO_TEST_CASE(comma) {
    Scanner s = makeScannerFromString(",");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::COMMA);
}

BOOST_AUTO_TEST_CASE(skip_comments) {
    Scanner s = makeScannerFromString("Int x\n# a comment\n# another comment");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::INT_TYPE);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::IDENTIFIER);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(fail_to_parse_unused_characters) {
    std::vector<std::string> chars = {"@", "%", "\\", "&", "|", "?", "~", "`", "'", "$", ";"};
    for (auto character: chars) {
        Scanner s = makeScannerFromString(character);
        BOOST_CHECK_THROW(s.getNextToken(), std::runtime_error);
    }
}

BOOST_AUTO_TEST_SUITE_END()