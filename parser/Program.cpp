#include "Parser.h"

using namespace TokenType;

void Parser::parseProgram() {
    nextToken = scanner->getNextToken();
    while(true) {
        switch(nextToken) {
            case EOT:
                return;
            case LET:
                parseFunctionDeclaration();
                break;
            default:
                throw std::runtime_error("Unexpected token");
        }
    }
}