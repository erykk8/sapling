#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ScannerTest"
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../IO.h"
#include "../Scanner.h"

Scanner makeScannerFromString(std::string string) {
    std::shared_ptr<std::stringstream> ss(new std::stringstream());
    *ss << string;
    std::shared_ptr<StreamReader> sr(new StreamReader(ss));
    return Scanner(sr);
}

BOOST_AUTO_TEST_SUITE(ScannerTest)

BOOST_AUTO_TEST_CASE(empty_input_returns_EOT) {
    Scanner s = makeScannerFromString("");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(last_token_is_EOT) {
    Scanner s = makeScannerFromString("Int");
    s.getNextToken();
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_CASE(only_if_elif_else) {
    Scanner s = makeScannerFromString("if elif else");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::IF);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ELIF);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ELSE);
}

BOOST_AUTO_TEST_CASE(type_keywords) {
    Scanner s = makeScannerFromString("Int Real Bool String Set List Void");

    for(int i = 0; i < 7; ++i) {
        BOOST_CHECK_EQUAL(s.getNextToken(), Token::TYPE_KEYWORD);
    }
}

BOOST_AUTO_TEST_CASE(ignore_leading_whitespace) {
    Scanner s = makeScannerFromString("     \t\t\t     Int");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::TYPE_KEYWORD);
}

BOOST_AUTO_TEST_CASE(return_arrow) {
    Scanner s = makeScannerFromString("=>");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::RETURN_ARROW);
}

BOOST_AUTO_TEST_CASE(int_constants) {
    Scanner s = makeScannerFromString("34 -129");
    Token t1 = s.getNextToken();
    Token t2 = s.getNextToken();

    BOOST_CHECK_EQUAL(t1.getType(), Token::INT_VALUE);
    BOOST_CHECK_EQUAL(t1.getInt(), 34);
    BOOST_CHECK_EQUAL(t2.getType(), Token::INT_VALUE);
    BOOST_CHECK_EQUAL(t2.getInt(), -129);
}

BOOST_AUTO_TEST_CASE(braces) {
    Scanner s = makeScannerFromString("{} () []");
    std::vector<Token::Type> v = { Token::CURLY_BRACE_OPEN, Token::CURLY_BRACE_CLOSE,
                                    Token::BRACE_OPEN, Token::BRACE_CLOSE,
                                    Token::SQUARE_BRACE_OPEN, Token::SQUARE_BRACE_CLOSE };

    for(auto type : v) {
        BOOST_CHECK_EQUAL(s.getNextToken(), type);
    }

}

BOOST_AUTO_TEST_CASE(variable_assignment) {
    Scanner s = makeScannerFromString("Int x = 413");
    std::vector<Token::Type> v = { Token::TYPE_KEYWORD, Token::IDENTIFIER,
                                    Token::ASSIGNMENT_OPERATOR, Token::INT_VALUE };

    for(auto type : v) {
        BOOST_CHECK_EQUAL(s.getNextToken(), type);
    }
}

BOOST_AUTO_TEST_CASE(arithmetic_operators) {
    Scanner s = makeScannerFromString("^*/+//-");

    for(int i = 0; i < 6; ++i) {
        BOOST_CHECK_EQUAL(s.getNextToken(), Token::ARITHMETIC_OPERATOR);
    }
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT); // ensure // is treated as one operator
}

BOOST_AUTO_TEST_CASE(comparison_operators) {
    Scanner s = makeScannerFromString("< <= > >= == !=");

    for(int i = 0; i < 6; ++i) {
        BOOST_CHECK_EQUAL(s.getNextToken(), Token::COMPARISON_OPERATOR);
    }
}

BOOST_AUTO_TEST_CASE(logical_operators) {
    Scanner s = makeScannerFromString("and or not");

    for(int i = 0; i < 3; ++i) {
        BOOST_CHECK_EQUAL(s.getNextToken(), Token::LOGICAL_OPERATOR);
    }
}

BOOST_AUTO_TEST_CASE(identifiers) {
    Scanner s = makeScannerFromString("functionName function_name function123");

    for(int i = 0; i < 3; ++i) {
        BOOST_CHECK_EQUAL(s.getNextToken(), Token::IDENTIFIER);
    }
}

BOOST_AUTO_TEST_CASE(skip_comments) {
    Scanner s = makeScannerFromString("Int x\n# a comment\n# another comment");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::TYPE_KEYWORD);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::IDENTIFIER);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::EOT);
}

BOOST_AUTO_TEST_SUITE_END()