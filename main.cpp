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
    auto file = std::make_shared<std::ifstream>(argv[1]);
    if(file) {
        auto sr = std::make_unique<StreamReader>(file);
        auto s = std::make_unique<Scanner>(std::move(sr));
        Parser p(std::move(s));
        auto program = p.parse();
        std::cout << program->evaluate() << std::endl;
        return 0;
    }
    std::cout << "Could not read file" << std::endl;
    return 1;
}