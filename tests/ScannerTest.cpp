#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ScannerTest"
#include <boost/test/unit_test.hpp>

#include <sstream>
#include <memory>
#include <vector>
#include "../scanner/IO.h"
#include "../scanner/Scanner.h"

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

BOOST_AUTO_TEST_CASE(if_elif_else) {
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

BOOST_AUTO_TEST_CASE(return_keyword) {
    Scanner s = makeScannerFromString("return");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::RETURN);
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

BOOST_AUTO_TEST_CASE(bool_constants) {
    Scanner s = makeScannerFromString("True False");

    Token t = s.getNextToken();
    Token f = s.getNextToken();

    BOOST_CHECK_EQUAL(t, Token::BOOL_VALUE);
    BOOST_CHECK_EQUAL(t.getBool(), true);
    BOOST_CHECK_EQUAL(f, Token::BOOL_VALUE);
    BOOST_CHECK_EQUAL(f.getBool(), false);
}

BOOST_AUTO_TEST_CASE(real_constants) {
    std::vector<double> reals = {10.3333333333, -0.03, -25.123, 0.75};
    std::stringstream ss;
    for (auto real: reals) {
        ss << real << " ";
    }
    Scanner s = makeScannerFromString(ss.str());

    for (auto real: reals) {
        Token t = s.getNextToken();
        BOOST_CHECK_EQUAL(t, Token::REAL_VALUE);
        BOOST_CHECK(abs(t.getReal() - real) < 0.001); // cant precisely compare doubles
    }
}

BOOST_AUTO_TEST_CASE(string_constants) {
    std::string text = "a string";
    Scanner s = makeScannerFromString("\"" + text + "\"");

    Token str = s.getNextToken();

    BOOST_CHECK_EQUAL(str, Token::STRING_VALUE);
    BOOST_CHECK_EQUAL(str.getString(), text);
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

BOOST_AUTO_TEST_CASE(assignment_operator) {
    Scanner s = makeScannerFromString(" = ");
    
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::ASSIGNMENT_OPERATOR);
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

BOOST_AUTO_TEST_CASE(separators) {
    Scanner s = makeScannerFromString(", :");

    BOOST_CHECK_EQUAL(s.getNextToken(), Token::COMMA);
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::COLON);
}

BOOST_AUTO_TEST_CASE(skip_comments) {
    Scanner s = makeScannerFromString("Int x\n# a comment\n# another comment");
    BOOST_CHECK_EQUAL(s.getNextToken(), Token::TYPE_KEYWORD);
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