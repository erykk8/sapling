#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "TokenTest"
#include <boost/test/unit_test.hpp>
#include "../token/Token.h"

BOOST_AUTO_TEST_SUITE(TokenTest)

BOOST_AUTO_TEST_CASE(get_type_after_default_constructor_returns_eot) {
    Token t;
    BOOST_CHECK_EQUAL(t.getType(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(get_type_after_type_constructor_returns_given_type) {
    Token t1(Token::CURLY_BRACE_OPEN), t2(Token::ARITHMETIC_OPERATOR), t3(Token::TYPE_KEYWORD);
    BOOST_CHECK_EQUAL(t1.getType(), Token::CURLY_BRACE_OPEN);
    BOOST_CHECK_EQUAL(t2.getType(), Token::ARITHMETIC_OPERATOR);
    BOOST_CHECK_EQUAL(t3.getType(), Token::TYPE_KEYWORD);
}

BOOST_AUTO_TEST_CASE(get_type_after_set_int_returns_int_value) {
    Token t;
    t.setInt(413);
    BOOST_CHECK_EQUAL(t.getType(), Token::INT_VALUE);
}

BOOST_AUTO_TEST_CASE(get_type_after_set_bool_returns_bool_value) {
    Token t;
    t.setBool(true);
    BOOST_CHECK_EQUAL(t.getType(), Token::BOOL_VALUE);
}

BOOST_AUTO_TEST_CASE(get_type_after_set_real_returns_real_value) {
    Token t;
    t.setReal(4.13);
    BOOST_CHECK_EQUAL(t.getType(), Token::REAL_VALUE);
}

BOOST_AUTO_TEST_CASE(get_type_after_set_string_returns_string_value) {
    Token t;
    t.setString("string");
    BOOST_CHECK_EQUAL(t.getType(), Token::STRING_VALUE);
}

BOOST_AUTO_TEST_CASE(get_int_after_set_int_returns_integer) {
    Token t;
    t.setInt(413);
    BOOST_CHECK_EQUAL(t.getInt(), 413);
}

BOOST_AUTO_TEST_CASE(get_bool_after_set_bool_returns_boolean) {
    Token t1, t2;
    t1.setBool(true);
    t2.setBool(false);
    BOOST_CHECK_EQUAL(t1.getBool(), true);
    BOOST_CHECK_EQUAL(t2.getBool(), false);
}

BOOST_AUTO_TEST_CASE(get_real_after_set_real_returns_real) {
    Token t;
    t.setReal(4.13);
    BOOST_CHECK_EQUAL(t.getReal(), 4.13);
}

BOOST_AUTO_TEST_CASE(get_string_after_set_string_returns_string) {
    Token t;
    t.setString("string123");
    BOOST_CHECK_EQUAL(t.getString(), "string123");
}

BOOST_AUTO_TEST_SUITE_END()