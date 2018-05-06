#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParserTest"
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../parser/Parser.h"

BOOST_AUTO_TEST_SUITE(ParserTest)

Parser makeParserFromString(std::string string) {
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    *ss << string;
    std::shared_ptr<StreamReader> sr(new StreamReader(ss));
    std::shared_ptr<Scanner> s(new Scanner(sr));
    return Parser(s);
}

BOOST_AUTO_TEST_CASE(empty_input_is_parsed) {
    Parser p = makeParserFromString("");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(int_variable_is_parsed) {
    Parser p = makeParserFromString("Int x = 5");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(string_variable_is_parsed) {
    Parser p = makeParserFromString("String hello = \"Hello world!\"");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(int_function_with_no_args_is_parsed) {
    Parser p = makeParserFromString("Int x() = 5");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(int_function_with_one_arg_is_parsed) {
    Parser p = makeParserFromString("Int x(Int y) = y + 5");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(many_one_line_functions_are_parsed) {
    Parser p = makeParserFromString("Int x = 5\nReal y = 0.5");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(multiline_function_is_parsed) {
    Parser p = makeParserFromString("Int x = {\nInt y = 2\nreturn y^3\n}");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(function_with_if_is_parsed) {
    Parser p = makeParserFromString("Int x = if(1 < 2) 4 else -1");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(function_with_if_elif_else_is_parsed) {
    Parser p = makeParserFromString("Int x = if(1 < 2) 4 elif(1 > 2) 8 else -1");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(many_complex_functions_are_parsed) {
    Parser p = makeParserFromString("Int x = {\n"
                                    "\tInt y = 2^3 * 1/2\n"
                                    "\treturn if(y < 128) 2 else 314\n"
                                    "}"
                                    "Bool z = {\n"
                                    "return if (x == 2) True\n"
                                    "elif (x == 314) False\n"
                                    "}");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(numeric_expression_is_parsed) {
    Parser p = makeParserFromString("Int x = (2 + (3^5)^10) * -1");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(logical_expression_is_parsed) {
    Parser p = makeParserFromString("Bool x = (50*2 <= 100) and (2 + 2 == 4) or False");
    BOOST_CHECK_NO_THROW(p.parse());
}

BOOST_AUTO_TEST_CASE(dangling_operator_is_not_parsed) {
    Parser p = makeParserFromString("Int x = 5 *");
    BOOST_CHECK_THROW(p.parse(), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(missing_braces_are_not_parsed) {
    Parser p = makeParserFromString("Int x = (3 + 4 - 6) * (2*2");
    BOOST_CHECK_THROW(p.parse(), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()