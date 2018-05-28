#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "IOTest"

#include <boost/test/unit_test.hpp>

#include <sstream>
#include "../scanner/IO.h"

std::unique_ptr<StreamReader> makeStreamReaderFromString(std::string string) {
    auto ss = std::make_shared<std::stringstream>();
    *ss << string;
    return std::make_unique<StreamReader>(ss);
}

BOOST_AUTO_TEST_SUITE(IOTest)

BOOST_AUTO_TEST_CASE(next_char_on_empty_string_returns_eot) {
    auto sr = makeStreamReaderFromString("");
    BOOST_CHECK_EQUAL(sr->peekChar(), -1);
    BOOST_CHECK_EQUAL(sr->nextChar(), -1);
}

BOOST_AUTO_TEST_CASE(next_char_on_string_returns_first_char) {
    auto sr = makeStreamReaderFromString("test");
    BOOST_CHECK_EQUAL(sr->peekChar(), 't');
    BOOST_CHECK_EQUAL(sr->nextChar(), 't');
}

BOOST_AUTO_TEST_CASE(next_char_after_next_char_on_string_returns_second_char) {
    auto sr = makeStreamReaderFromString("test");
    sr->nextChar();
    BOOST_CHECK_EQUAL(sr->peekChar(), 'e');
    BOOST_CHECK_EQUAL(sr->nextChar(), 'e');
}

BOOST_AUTO_TEST_CASE(next_char_after_skip_line_returns_first_char_in_next_line) {
    auto sr = makeStreamReaderFromString("test\nnewline");
    sr->skipLine();
    BOOST_CHECK_EQUAL(sr->peekChar(), 'n');
    BOOST_CHECK_EQUAL(sr->nextChar(), 'n');
}

BOOST_AUTO_TEST_CASE(nonalphanumeric_characters_work) {
    auto sr = makeStreamReaderFromString("(){}[]");
    BOOST_CHECK_EQUAL(sr->peekChar(), '(');
    BOOST_CHECK_EQUAL(sr->nextChar(), '(');
    BOOST_CHECK_EQUAL(sr->nextChar(), ')');
}


BOOST_AUTO_TEST_CASE(next_char_after_skip_whitespace_returns_first_char_in_next_word) {
    auto sr = makeStreamReaderFromString("      \n\n\nskip test");
    std::function<bool(char)> whiteSpace = [](char c) -> bool { return c == ' ' || c == '\n'; };
    sr->skip(whiteSpace);
    BOOST_CHECK_EQUAL(sr->peekChar(), 's');
    BOOST_CHECK_EQUAL(sr->nextChar(), 's');
}

BOOST_AUTO_TEST_SUITE_END()