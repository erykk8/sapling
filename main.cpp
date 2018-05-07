#include <iostream>
#include "parser/Parser.h"
#include "scanner/Scanner.h"
#include "scanner/IO.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

int main(int argc, char** argv) {
    if(argc != 2) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        return 1;
    }
    auto file = std::make_shared<std::ifstream>();
    file->open(argv[1]);
    if(*file) {
        auto sr = std::make_shared<StreamReader>(file);
        auto s = std::make_shared<Scanner>(sr);
        Parser p(s);
        std::cout << p.evaluate() << std::endl;
        file->close();
        return 0;
    }
    std::cout << "Could not read file" << std::endl;
    return 1;
}