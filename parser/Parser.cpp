#include "Parser.h"
#include <iostream>

Parser::Parser(std::shared_ptr<Scanner> s) : scanner(s) {
    program = std::make_shared<Program>();
}

int Parser::parse() {
    try {
        parseProgram();
        return program->evaluate();
    }
    catch (std::runtime_error e) {
        std::cout << e.what() << ": " << nextToken.getName() << " at line " << nextToken.getLine();
        std::cout << " at position " << nextToken.getPosition() << std::endl;
        throw std::runtime_error("Parsing error");
    }
}