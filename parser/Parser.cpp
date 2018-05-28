#include "Parser.h"
#include <iostream>

Parser::Parser(std::unique_ptr<Scanner> s) {
    scanner = std::move(s);
    program = nullptr;
}

std::unique_ptr<Program> Parser::parse() {
    try {
        program = std::make_unique<Program>();
        parseProgram();
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << ": " << nextToken.getName() << " at line " << nextToken.getLine();
        std::cout << " at position " << nextToken.getPosition() << std::endl;
        throw std::runtime_error("Parsing error");
    }
    return std::move(program);
}