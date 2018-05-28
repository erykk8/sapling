#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ParserSemanticTest"
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../parser/Parser.h"

BOOST_AUTO_TEST_SUITE(ParserSemanticTest)

std::unique_ptr<Parser> makeParserFromString(std::string string) {
    auto ss = std::make_shared<std::stringstream>();
    *ss << string;
    std::unique_ptr<InputReader> sr(new StreamReader(ss));
    auto s = std::make_unique<Scanner>(std::move(sr));
    return std::make_unique<Parser>(std::move(s));
}

BOOST_AUTO_TEST_CASE(simple_main) {
    auto p = makeParserFromString("let main = 0");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 0);
}

BOOST_AUTO_TEST_CASE(two_functions) {
    auto p = makeParserFromString("let x=5\nlet main = x+1");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 6);
}

BOOST_AUTO_TEST_CASE(multi_arg_functions) {
    auto p = makeParserFromString("let sum(x, y) = x + y\nlet main = sum(1, 4)");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 5);
}

BOOST_AUTO_TEST_CASE(simple_recursion) {
    auto p = makeParserFromString("let twoTo(x) = if(x == 0) 1 else twoTo(x - 1)*2\n"
                                    "let main = twoTo(10)");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 1024);
}

BOOST_AUTO_TEST_CASE(nested_function_call) {
    auto p = makeParserFromString("let twoTo(x) = if(x == 0) 1 else twoTo(x - 1)*2\n"
                                    "let main = twoTo(twoTo(2))");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 16);
}

BOOST_AUTO_TEST_CASE(fibonacci) {
    auto p = makeParserFromString("let fibonacci(i) = if(i == 0) 0 elif(i == 1) 1 else fibonacci(i - 1) + fibonacci(i - 2)\n"
                                    "let main = fibonacci(10)");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 55);
}

BOOST_AUTO_TEST_CASE(operator_priorities) {
    auto p = makeParserFromString("let main = 2+2*2^2");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 10);
}

BOOST_AUTO_TEST_CASE(simple_if) {
    auto p = makeParserFromString("let main = if(1 == 1) 1 else -1");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(complex_if) {
    auto p = makeParserFromString("let main = if(1 == 2) 1 elif(1 == 3) 0 else -1");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), -1);
}

BOOST_AUTO_TEST_CASE(false_bool_expression) {
    auto p = makeParserFromString("let main = 1 > 0 and 5 < 4");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 0);
}

BOOST_AUTO_TEST_CASE(true_bool_expression) {
    auto p = makeParserFromString("let main = 1 > 0 or 5 < 4");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(lazy_evaluation) {
    auto p = makeParserFromString("let main = if(1 == 1) 1 else 1/0");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 1);
}

BOOST_AUTO_TEST_CASE(lazy_evaluation_2) {
    auto p = makeParserFromString("let a(x, y) = x\nlet main = a(1, 1/0)");
    BOOST_CHECK_EQUAL(p->parse()->evaluate(), 1);
}

BOOST_AUTO_TEST_SUITE_END()