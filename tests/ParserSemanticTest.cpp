#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParserSemanticTest"
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../parser/Parser.h"

BOOST_AUTO_TEST_SUITE(ParserSemanticTest)

Parser makeParserFromString(std::string string) {
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    *ss << string;
    std::shared_ptr<StreamReader> sr(new StreamReader(ss));
    std::shared_ptr<Scanner> s(new Scanner(sr));
    return Parser(s);
}

BOOST_AUTO_TEST_CASE(simple_main) {
    Parser p = makeParserFromString("let main = 0");
    BOOST_CHECK_EQUAL(p.evaluate(), 0);
}

BOOST_AUTO_TEST_CASE(two_functions) {
    Parser p = makeParserFromString("let x=5\nlet main = x+1");
    BOOST_CHECK_EQUAL(p.evaluate(), 6);
}

BOOST_AUTO_TEST_CASE(multi_arg_functions) {
    Parser p = makeParserFromString("let sum(x, y) = x + y\nlet main = sum(1, 4)");
    BOOST_CHECK_EQUAL(p.evaluate(), 5);
}

BOOST_AUTO_TEST_CASE(simple_recursion) {
    Parser p = makeParserFromString("let twoTo(x) = if(x == 0) 1 else twoTo(x - 1)*2\n"
                                    "let main = twoTo(10)");
    BOOST_CHECK_EQUAL(p.evaluate(), 1024);
}

BOOST_AUTO_TEST_CASE(nested_function_call) {
    Parser p = makeParserFromString("let twoTo(x) = if(x == 0) 1 else twoTo(x - 1)*2\n"
                                    "let main = twoTo(twoTo(2))");
    BOOST_CHECK_EQUAL(p.evaluate(), 16);
}

BOOST_AUTO_TEST_CASE(fibonacci) {
    Parser p = makeParserFromString("let fibonacci(i) = if(i == 0) 0 elif(i == 1) 1 else fibonacci(i - 1) + fibonacci(i - 2)\n"
                                    "let main = fibonacci(10)");
    BOOST_CHECK_EQUAL(p.evaluate(), 55);
}

BOOST_AUTO_TEST_CASE(operator_priorities) {
    Parser p = makeParserFromString("let main = 2+2*2^2");
    BOOST_CHECK_EQUAL(p.evaluate(), 10);
}

BOOST_AUTO_TEST_CASE(simple_if) {
    Parser p = makeParserFromString("let main = if(1 == 1) 1 else -1");
    BOOST_CHECK_EQUAL(p.evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(complex_if) {
    Parser p = makeParserFromString("let main = if(1 == 2) 1 elif(1 == 3) 0 else -1");
    BOOST_CHECK_EQUAL(p.evaluate(), -1);
}

BOOST_AUTO_TEST_CASE(false_bool_expression) {
    Parser p = makeParserFromString("let main = 1 > 0 and 5 < 4");
    BOOST_CHECK_EQUAL(p.evaluate(), 0);
}

BOOST_AUTO_TEST_CASE(true_bool_expression) {
    Parser p = makeParserFromString("let main = 1 > 0 or 5 < 4");
    BOOST_CHECK_EQUAL(p.evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(lazy_evaluation) {
    Parser p = makeParserFromString("let main = if(1 == 1) 1 else 1/0");
    BOOST_CHECK_EQUAL(p.evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(lazy_evaluation_2) {
    Parser p = makeParserFromString("let a(x, y) = x\nlet main = a(1, 1/0)");
    BOOST_CHECK_EQUAL(p.evaluate(), 1);
}

BOOST_AUTO_TEST_SUITE_END()