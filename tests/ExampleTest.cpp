#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "ExampleTest"
#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <string>

BOOST_AUTO_TEST_SUITE(ExampleTest)

int runExample(std::string filename) {
    int value;
    std::string program = "./Sapling";
    #ifdef SAPLING_PATH
        program = SAPLING_PATH;
    #endif
    std::string examples = "./examples/";
    #ifdef EXAMPLES_PATH
        examples = EXAMPLES_PATH;
    #endif
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    auto stream = popen((program + " " + examples + filename).c_str(), "re");
    char output[1024];
    char* readStatus = fgets(output, sizeof(output), stream);
    if(readStatus == NULL) {
        throw std::runtime_error(strerror(errno));
    }
    int status = pclose(stream);
    if(status != 0) {
        throw std::runtime_error(output);
    }
    value = std::atoi(output);
    return value;
}

BOOST_AUTO_TEST_CASE(simple) {
    int value = runExample("simple.sap");
    BOOST_CHECK_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(sumOfRange) {
    int value = runExample("sumOfRange.sap");
    BOOST_CHECK_EQUAL(value, 55);
}

BOOST_AUTO_TEST_CASE(priorities) {
    int value = runExample("priorities.sap");
    BOOST_CHECK_EQUAL(value, 10);
}

BOOST_AUTO_TEST_CASE(math) {
    int value = runExample("math.sap");
    BOOST_CHECK_EQUAL(value, 22);
}

BOOST_AUTO_TEST_CASE(lazy) {
    int value = runExample("lazy.sap");
    BOOST_CHECK_EQUAL(value, 0);
}

BOOST_AUTO_TEST_CASE(isPrime) {
    int value = runExample("isPrime.sap");
    BOOST_CHECK_EQUAL(value, 0);
}

BOOST_AUTO_TEST_SUITE_END()