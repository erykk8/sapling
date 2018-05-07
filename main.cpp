#include <iostream>
#include "parser/Parser.h"
#include "scanner/Scanner.h"
#include "scanner/IO.h"
#include <fstream>
#include <iostream>
#include <memory>

int main(int argc, char** argv) {
    auto file = std::make_shared<std::ifstream>(argv[1]);
    file->open(argv[1]);
    auto sr = std::make_shared<StreamReader>(file);
    auto s = std::make_shared<Scanner>(sr);
    Parser p(s);
    std::cout << p.parse() << std::endl;
    return 0;
}