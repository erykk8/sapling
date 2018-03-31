#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "IOTest"

#include <boost/test/unit_test.hpp>

#include <sstream>
#include "../IO.h"

BOOST_AUTO_TEST_SUITE(IOTest)

BOOST_AUTO_TEST_CASE(next_char_on_empty_string_returns_eot) {
    std::stringstream ss;
    StreamReader sr(ss);
    BOOST_CHECK_EQUAL(sr.nextChar(), EOT);
}

BOOST_AUTO_TEST_CASE(next_char_on_string_returns_first_char) {
    std::stringstream ss;
    ss << "test";
    StreamReader sr(ss);
    BOOST_CHECK_EQUAL(sr.nextChar(), 't');
}

BOOST_AUTO_TEST_CASE(next_char_after_next_char_on_string_returns_second_char) {
    std::stringstream ss;
    ss << "test";
    StreamReader sr(ss);
    sr.nextChar();
    BOOST_CHECK_EQUAL(sr.nextChar(), 'e');
}

BOOST_AUTO_TEST_CASE(next_char_after_skip_line_returns_first_char_in_next_line) {
    std::stringstream ss;
    ss << "test\nnewline";
    StreamReader sr(ss);
    sr.skipLine();
    BOOST_CHECK_EQUAL(sr.nextChar(), 'n');
}

BOOST_AUTO_TEST_CASE(next_char_after_skip_whitespace_returns_first_char_in_next_word) {
    std::stringstream ss;
    std::function<bool(char)> whiteSpace = [](char c) -> bool { return c == ' ' || c == '\n'; };
    ss << "      \n\n\nskip test";
    StreamReader sr(ss);
    sr.skip(whiteSpace);
    BOOST_CHECK_EQUAL(sr.nextChar(), 's');
}

BOOST_AUTO_TEST_SUITE_END()