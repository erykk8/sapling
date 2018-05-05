#include "Parser.h"

Parser::Parser(Scanner &s) : scanner(s) {}

void Parser::parse() {
    parseProgram();
}